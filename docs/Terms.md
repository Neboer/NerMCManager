# NerMCManager

NerMCManager（NMM）是一个MC管理器，可以方便的管理多个MC实例。

MC实例以文件夹隔离。

# 概念

NMM里提出了一些概念，

### 1. 环境包 EnvPack EP

一个EP是一个Ready To Start的整合包的所有文件（不包含世界文件夹），运行其中的run.sh就可以直接启动游戏。

打包好的EP应该是tar.gz，不包含文件夹名字，不包含世界数据文件夹。

EP中必须存在的文件（夹）：

* start.sh
* server.properties
* NMM_info.json

EP中必须不存在的文件（夹）

* logs
* eula.txt
* ops.json
* banned-players.json
* user_jvm_args.txt 

每个EP都必须有一个名字+版本，通常都代表一个整合包。

EP的名字通常是整合包名字的简写。比如锻造大师整合包简称MB。

默认来说，无论如何，运行start.sh都应该启动游戏。可以选择的，start.sh在启动时会接受以下环境变量作为参数：

| 变量名 | 是否必填 | 变量值 | 变量说明 |
|----|----|----|----|
| NMM_AUTHLIB_INJECTOR |    | 空，或一个路径 | authlibinjector.jar的路径，空则不用 |
| NMM_AUTHLIB_URL |    | 空，或一个URL | authlibinjector.jar参数的URL，空则不用 |
| NMM_MEMORY_MB | 是 | 数字，如4096 | 游戏运行时需要使用的内存大小 |

EP_info.json 这个文件描述了这个整合包的特征。

| 变量名 | 是否必填 | 是否应自动识别 | 变量类型 | 变量说明 |
|----|----|----|----|----|
| name | 是 |    | string | EP的名字，全英文小写，无-字符 |
| version | 是 |    | string | EP的版本号，数字+点 |
| game_version |    | 是 | string | 游戏版本，1.20.1 |
| mod_platform |    | 是 | string | mod平台，如forge/fabric/neoforge/bukkit |
| mod_platform_version |    | 是 | string | mod平台的版本， |
| java_version |    | 是 | string | Java版本，比如java-17-jre |
| startup_output | 是 |    | string | 启动时的输出，用于判断是否启动。 |
| x_wd_dir | 是 |    | list | 额外的世界数据路径，这些路径是必包含在WD中的。 |

整合包中不要有可以自动备份世界的功能，这个功能由我们来代替。

文件与命名规范：

EP的名字必须为无符号的大小写字母+数字组合（URL规范，不区分大小写），不能包含任何符号。版本名必须只包含数字、点、英文小写字母，不能包含其他符号。在文件名中，用"名字-版本.tar.gz"来表示一个EP包。

每一个EP包都有一个独特的ID，这个ID是根据EP包中所有的文件+哈希计算得来的，唯一标识了一个文件夹的所有内容的组合，完全相同的文件夹就应该有完全相同的ID。

### 2. 世界数据 WorldData WD

玩家的世界数据，可以打包发送给玩家，也可以用来在不同版本间迁移。

世界数据正常情况下是与level-name同名的文件夹，和一个EP的名字绑定。世界数据中还可以包含一些其他的内容，比如ops.json，这些是可选的。

注意，世界数据可以随着EP的版本的更新而更新，但不同的EP不能使用同一个世界数据。

世界数据的命名规则：小队名+EP名+世界数据ID。

比如 MBA-MB-1 表示这个是MBA小队锻造大师的第一个存档。

这个1是用来标识MBA小队玩的第几个MB世界的，相同的世界，后面的数字总是相同，与EP版本无关。

我们推荐使用不需要在本地存储状态的插件。如果插件一定要在本地存储状态，那么需要把插件的数据位置单独添加。

对于有特殊含义的世界，比如灵动MC的 基佬村 GeroVillage，可以直接叫 LDMC-GeroVillage，不需要复杂的命名。

就算EP没有要求任何额外世界数据的路径，至少有以下路径是必须添加到世界数据之中的。

* ops.json
* <世界文件夹>
* <世界文件夹>_nether
* <世界文件夹>_the_end

一个世界数据可能处于正在被使用（using）的状态，这个时候除非占用世界数据的GI释放这个数据，否则

### 3. 游戏平台 GamePlatform GP

游戏平台，指的就是游戏版本+mod环境+mod环境版本。游戏平台仅与游戏Java版本有关。

需要自动识别游戏平台，自动找到对应的Java版本。

### 4. 用户认证

onlinemod=true/false，authlibinjector.

如何处理authlibinjector？靠环境变量。 

### 5. 小队 PlayerTeam PT

每个PT都是一个小队。相同的小队只能同时存在一个游戏实例。小队用来表示玩家。

小队的名字必须只能是数字和英文字母，唯一对应一个数字和英文字母的Unix用户名。

### 6. 游戏实例 GameInstance GI

由配置文件决定的、由EP和WD组成的，具有特定版本Java的，被systemd管理的一个进程?

或许可以不用systemd托管。

每个游戏实例完全是由配置文件生成的，一一对应。

游戏实例没有名字，PT-EPN-EPV-WD就是某个GI最好的表示。

#### 基本配置

| 配置项名 | 配置项值 | 解释 |
|----|----|----|
| team | string | 小队名字 MB2 |
| ep_name | string | EP名字 MB |
| ep_ver | string | EP版本 2.0 |
| wd | string | 世界数据名字 MBA-MB-1/LDMC-GeroVillage |

#### 认证配置

| 配置项名 | 配置项值 | 解释 |
|----|----|----|
| Auth | LittleSkin/Offline/Online | 用户认证方式 |
| RCONEnable | bool | 是否启用RCON |
| RCONPassword | string | RCON密码 |

#### 网络配置

| 配置项名 | 配置项值 | 解释 |
|----|----|----|
| ServerPort | int | 游戏端口，25565 |
| RCONPort | int | RCON端口，25575 |

GI的配置文件是全局唯一的，其内容是完全不可以修改的。**每次所谓的修改，本质上都是在创造一个新的GI**。同一小队同时最多只能有一个GI在运行，所以会受到规则的强烈限制。

GI在系统中由json模块解析后，将每一项的值经过hash后相加，对结果进行新的hash，最终得到这个配置的hash。这个hash唯一标识了一个游戏实例。

### 7. 备份 Backups

世界数据定期备份，这个没什么好说的

### 8. 默认管理员用户名 Admins

metadata. 类似ops.json这种文件，更换EP版本不会保留。所以需要用其他的方法报默认管理员保存起来。

如果服务器没有固定的默认管理员，则ops.json应该成为世界数据的一部分，随世界数据管理。

### 9. 游戏日志 Logs

游戏在运行中会留下很多日志，比如logs，比如authlib-injector.log。每次启动MC实例时，都不会带日志。MC在运行过程中生成的所有日志，会定期收集转储到游戏日志记录中。

游戏日志与游戏实例一一对应，每个独特的游戏实例都有独特的游戏日志——这就意味着，如果游戏实例中的任何一个部分更换了，则日志都会重新存储。日志不会自动清理，只会自动rotate转存到位置。

### 10. 追踪 Metrics

游戏需要使用Prometheus之类的工具追踪性能。这个问题没有想好，暂时不表。

## 有关小队、世界数据、环境包和游戏实例的说明

小队、世界数据、环境包和游戏实例之间的关系是这样的：

每个小队只能同时运行一个游戏实例，每个游戏实例由EP和WD组成。游戏会从配置文件中获取需要额外保留的WD路径，其中server.properties中的世界路径是必须保存的。

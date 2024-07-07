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

每个环境包根目录都有一个ep_info.json，这个文件描述了环境包的基本属性。

ep_info.json 这个文件描述了这个整合包的特征。

| 变量名 | 是否必填 | 变量类型 | 变量说明 |
|----|----|----|----|
| name | 是 | string | EP的名字，全英文小写，无-字符 |
| version | 是 | string | EP的版本号，数字+点 |
| game_version |    | string | 游戏版本，1.20.1 |
| mod_platform |    | string | mod平台，如forge/fabric\nneoforge/bukkit |
| mod_platform_version |    | string | mod平台的版本， |
| jre_version |    | int | Java版本，比如17 |
| startup_output | 是 | string | 启动时的输出，用于判断是否启动。 |
| x_wd_dir | 是 | list | 额外的世界数据路径，这些路径是必包含在WD中的。 |

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

小队名必须是标准的Unix用户名，不包含-。首位必须是大写/小写字母，除首位外，可以是数字，不能包含任何其他符号。比如MB2Kids是合法的名字，而MB-kids是不行的。

### 6. 游戏实例 GameInstance GI

GI唯一的配置文件决定。每个游戏实例完全是由配置文件生成的，一一对应。

#### 基本配置

| 配置项名 | 配置项值 | 解释 |
|----|----|----|
| team | string | 小队名字 MB2 |
| ep_name | string | EP名字 MB |
| ep_ver | string | EP版本 2.0 |
| wd_identifier | string | 小队世界数据id 1/GeroVillage |

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

GI从配置文件创建。同一小队同时最多只能有一个GI在运行，不过可以在不同的GI中保存。

GI配置文件命名：team-ep_name-ep_ver-wd_id.json

GI文件夹命名：team-ep_name-ep_ver-wd_id/

WD文件夹命名：team-ep_name-ep_ver-wd_id/ 

WD文件夹中的ep_ver指运行世界的最低ep版本，当用高版本的ep启动低版本世界时，世界的ep_ver会自动更新。

具体的过程：用高版本ep启动低版本wd的瞬间，wd文件夹会重命名为高版本，然后正常启动。


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

## 工作流程


 1. 准备配置文件
 2. 根据配置文件启动世界：输入配置文件并解析，检查相同小队是否有世界正在运行。
 3. 如果相同小队有其他世界在运行，停止。
 4. 如果小队系统用户未创建，则创建系统用户。
 5. 以小队用户身份在全局工作目录下，创建游戏文件夹，
 6. 读取EP缓存，如果未命中，从仓库中拉取并解压到本地，
 7. 根据配置文件和EP中的server.properties文件生成新的server.properties，将authlib的参数以环境变量传递给start.sh。
 8. 实际的游戏启动过程，需要执行一次overlayfs的mount，以EP:准备好的server.properties为lowerdir，以WD为upperdir.
 9. 根据计算或配置的合适Java版本以小队用户身份启动游戏，并等待游戏启动成功。
10. 游戏顺利启动，修改GI状态为运行中，守护游戏。
11. 游戏启动失败，导出日志，重置游戏状态。尝试重启。
12. 日志轮转：每次游戏结束后，将游戏日志文件收集起来，按目录存储到对应文件夹中。
13. WD备份：通过RCON连接游戏，暂停游戏自动保存，然后将WD备份，再启动自动保存。
14. 游戏停止：游戏停止时，先把进程停止，然后卸载EP，然后卸载WD。WD是完全可写的，所以相当于在游戏中实时自动保存。卸载WD后，会对WD进行一次trim，将
15. 自动启动：可以enable一个配置文件，这样这个配置会在下次开机时自动启动。
16. 备份世界数据、导出世界数据等功能。

## 软件配置

nmm提供如下配置项：

| 配置项 | 类型 | 说明 |
|----|----|----|
| data_dir | string | 用来存放EP和世界数据的文件夹 |
| java_versions | object | {"11": "/usr/lib/jvm/java-11-jvm"}一一对应 |
| ep_registry | string | nmm@ep.test.com:/home/nmm/ep-saves |
| dir_assemble_method | string | overlayfs/copy |
| user_isolation | bool | 是否开启用户隔离 |

跨版本运行java的原理非常简单，可以是

```javascript
 export JAVA_HOME=/usr/lib/jvm/java-8-openjdk
 export PATH="$JAVA_HOME/bin:$PATH"
 specificProgram
```

## 目录结构

```bash
data_dir/
  cached_ep/
    Utopia-1.27/
      ep_info.json
      ...
    LDMC-3.2/
      ep_info.json
      ...
  wd/
    LDMCer-LDMC-3.2-GeelaoVillage/
    MBAMC-Utopia-1.27-1/
  gi_configs/
    MBAMC-Utopia-1.27-1.conf
  running_gi/
    MBAMC-Utopia-1.27-1/
  logs/
    MBAMC-Utopia-1.27-1/
      latest.log
      crash_report/
          xxx
  download_temp/
    MBAMC-Utopia-1.27.tar.gz
```

## 运行时数据

后端在运行中时刻保存着一些数据在内存里。这些数据主要是GI信息。

GI信息（team-ep_name-ep_ver-wd_id）
游戏PID（是否运行）

## 使用方法

命令行用法

### nmm ep list

### nmm ep create <path> -t \<tag:version>

根据path中路径中的内容，创建一个环境包，名字叫tag，版本叫version。

### nmm ep delete -t \<tag:version>

如果有gi在使用此ep，不能删除ep。

### nmm ep rename -t \<tag:version> \<tag:version>

如果有gi在使用此ep，不能重命名。

### \~ nmm ep pull/push \<tag:version>

### nmm gi list

列出现在正在运行的游戏。team/ep/ep_ver/wd_id

同时还有对应的网络设置、认证设置，以及运行状态。

运行状态：运行中，启动中，已停止。

### nmm gi create  —config <path>

从gi config中生成一个gi，然后输出它的名字。

### nmm gi start <name>

根据path中的json配置，启动一个游戏实例。实例的名字会自动命名为team-ep_name-ep_ver-wd_id。

GI不能改名，可以停止，启动后需要把PID存数据库。

### nmm gi stop <name>

### nmm gi show <name>

展示某个GI具体的配置文件内容。

### nmm gi delete <name>

### nmm wd list

### nmm wd import \<path> -t \<ep_name:version> —name <name>

把一个非NMM创建的世界导入。这个世界属于哪个ep，由-t指定。

正常情况下，wd会自动创建，自动命名。如果你启动EP的时候，带了一个命名wd，系统会自动搜索这个名字是否存在，如果不存在会自动创建。启动ep的时候如果不带命名wd，那么实际程序会在转存ep配置文件的时候将wd+1，编好号。

### nmm wd rename  <full-name> <new-id-name>

注意。

这个命令的作用是，输入一个wd的"全名"（team-ep-ep_ver-wd_id），将其中的wd_id的名字更换。

注意不能和同小队同整合包的已有世界重名。这个重名检查与ep_ver无关，同小队同EP中的所有世界都不能重名。

### nmm wd delete <full-name>

删除某个世界。

### nmm wd export <full-name> <path>

导出某个世界到某个路径。

### nmm pt add xxx

新建一个小队。要求名字必须符合Unix名字标准。

### nmm pt delete xxx

同时删除对应的unix用户。

# 开发计划

加入世界数据备份功能，定期备份世界数据到本地或远程。使用rdiff-backup的功能。
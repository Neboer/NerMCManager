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
    ep1-name/
  wd/
    team1-ep1-1/
  gi_configs/
    36d9f48ef/
  running_gi/
    1f3d4c/
  logs/
    1f3d4c/
      latest.log
      crash_report/
          xxx
  download_temp/
    ep1-name.tar.gz
  runtime.db
```


## 使用方法

命令行用法

### nmm ep list

### nmm ep create <path>

根据path中路径中的内容，创建一个环境包。环境包的配置包含在目录下的EP_config.json中。

### nmm ep delete -t <tag:version>

### nmm ep rename -t <tag:version> <tag:version>

### nmm ep pull/push <tag:version>

### nmm gi list

### nmm gi start <name>/<guuid> —config <path>

根据path中的json配置，启动一个游戏实例。实例的名字会自动命名。

输出guuid，game的全局唯一标识。

### nmm gi stop <name>/<guuid>

### nmm gi show <name>/<guuid>

### nmm gi delete <name>/<guuid>

### nmm wd list

### nmm wd create <path>  —ep-config <path> —name <name>

把一个非NMM创建的世界导入。程序会参考config中指定的gi配置中的世界数据额外路径，配合默认的世界数据路径，将这个世界数据保存为name。

### nmm wd rename  <name> <name>

### nmm wd delete <name>

### nmm wd export <name> <path>

### nmm pt add xxx

### nmm pt delete xxx

# 开发计划

加入世界数据备份功能，定期备份世界数据到本地或远程。使用rdiff-backup的功能。
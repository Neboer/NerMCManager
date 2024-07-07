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
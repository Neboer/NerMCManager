
## runtime.db

一个SQLite数据库文件，里面内容如下：

### GAME_INSTANCE_CONFIG

注意，所有的xx_id都表示一个在本地自增的主键或对其的引用。

它需要知道"根据config生成的实例正在运行"，GI在不断改变，但config不变。

| 键名 | 类型 | 说明 |
|----|----|----|
| config_id | int | 游戏配置文件的ID |
| hash | string | 配置文件的json哈希 |
| running | bool | 是否正在运行 |
| pid | int | 游戏主线程PID |

配置的json哈希对应它在gi_configs路径中存储的文件名

### ENV_PACK

| 键名 | 类型 | 说明 |
|----|----|----|
| (env_id) | int | 无用 |
| name |    |    |
| version |    |    |
| hash |    |    |

### PLAYER_TEAM

| 键名 | 类型 | 说明 |
|----|----|----|
| team_id |    | 小队的本地ID |
| team_name |    | 小队的名字 |
| team_username |    | 小队使用的Unix用户的名字 |
| team_uid_gid |    | 小队使用的Unix用户的UID=GID |

### WORLD_DATA

| 键名 | 类型 | 说明 |
|----|----|----|
| wd_id | int | 世界数据id |
| name | string | 如果有意义，为世界数据的名字，可以为空 |
| player_team_id | int | 使用这个世界数据的小队ID |
| env_pack_name | string | 这个世界数据的EP名字 |
| wd_index | int | 这是这个小队玩这个EP的第几次个世界 |

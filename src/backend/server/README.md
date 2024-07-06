# JSON based TCP Server

TCP服务器使用流传输JSON——客户端发来JSON，服务器响应JSON。完全的C/S架构，完全同步，连接无任何状态。

每当客户端连接服务器，就从客户端听JSON。客户端JSON格式如下：

```json
{
    "type": "create_env_pack"
    "args": {
        "new_ep_dir": "/home/xxxx/ep-here"
    }
}
```

服务器处理请求的过程：假设a, b两流连接到服务器

-> 阻塞等待a, b之一可读。-> a可读，读a，等待读完，读完a，解析a的请求 -> 执行a请求，响应a -> 

完全同步。谁可读，就读谁，直到读完一整个包的内容。

这种模式不安全，低性能，但是对于我们的场景来说足够用了。它非常非常健壮。

客户端在发完请求后，就可以歇比了，等服务器回话，然后解析，然后结束。

服务器回话格式：

```json
{
    "error": "info",
    "payload": [
        "ep_name": xxx
    ]
}
```

如果没有error，说明请求成功。对于有结果的请求，结果会在payload中写出。
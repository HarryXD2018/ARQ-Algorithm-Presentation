# Stop-and-Wait ARQ Simulation

## 停止等待自动重复请求仿真程序

#### 说明

+ 本仿真程序有`C++`和`Python`两个版本。
+ Python版中`stop_and_wait_receiver.py`不属于工程文件。其中，发送方程序文件为`stop_and_wait_sender.Python`，由`stop_and_wait.py`启动。接收方程序文件`ReceiverService.java`由`Java`实现，属于`Spring boot`项目工程中的一个路由文件。
+ 你可能无法直接运行`Python`版本中的`Java`文件。但是我们已经将接收端部署到云端，你可以直接运行`stop_and_wait.Python`，并且可以在[这里](https://flxdu.cn/api/testLog)看到接收端输出。
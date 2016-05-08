# Unix Network Programming v2

#### 编译unpipc库的步骤：  
1. 下载   
在图灵社区的[下载页面](http://www.ituring.com.cn/book/156)有两个包：UNIX网络编程 卷2：进程间通.rar、UNIX网络编程 卷2：进程间通2.rar。  
两个的区别仅仅是里面的代码包的格式，第一个是tar.gz的，第二个是rar的。
2. 解压  
先解开下载的`UNIX网络编程 卷2：进程间通.rar`包，得到一个Readme.txt文件和一个代码包`unpv22e.tar.gz`。  
解压`unpv22e.tar.gz`：`tar xzvf unpv22e.tar.gz`
3. 编译  
按照Readme.txt中的步骤操作即可。如果遇到错误可以通过搜索引擎来解决，[这篇文章](http://www.cnblogs.com/lit10050528/p/5467122.html)记录我遇到的错误。
4. 拷贝头文件及库文件  
将`make`得到的`libunpipc.a`库以及`config.h`和`unpipc.h`拷贝出来放到自己的代码目录下，即可使用该本书中所用的unpipc库了。
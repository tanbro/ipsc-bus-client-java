# ipsc-bus-client-jni

Java Native Interface(C++ language) shared/dynamic-load library for IPSC's data-bus client.

## 补充说明

这是一个 JNI 项目，它是使用 `C++` 语言的！

JNI 的 Java 类声明和相关内容在 `com.hesong.ipsc.busnetcli.Client` 中.

## 开发环境

1. linux-x86_64
1. JDK-8，包括`JNI`头文件
1. gcc, g++, autotools
1. cmake
1. 下载依赖库 [`ipsc-bus-client`](https://bitbucket.org/hesong-opensource/ipsc-bus-client)，将其 include 头文件复制到 `/usr/local/include`, 库文件复制到 `/usr/local/lib`

## 编译

1. 设置 `JAVA_HOME` 环境变量

1. 进入项目所在目录，然后执行：

   ```sh
   # 建立一个构建目录：
   mkdir -p build
   # 进入构建目录：
   cd build
   # 生成 Unix Makefiles：
   cmake ../projects/cmake
   # 编译：
   make
   # 安装到系统目录，通常是 /usr/local， 某些操作系统也许需要 sudo
   make install
   ```

现在，你得到了 JNI 库文件 `libipsc-bus-client-jni.so`，别忘了它依赖于 `libbusnetcli.so`

现在，用 JAVA 程序调用它吧，别忘了 `-Djava.library.path=/your/jni.so/dir`

## 共享库路径问题

`libipsc-bus-client-jni.so` LINUX 的共享库搜索路径中连接 `libbusnetcli.so ` 。

为了统一部署，我们规定，将这两个库都放到 `usr/local/lib`，并且将这个路径加入到 `ld` 设置：

```sh
cat "/usr/local/lib" >> /etc/ld.so.conf
ldconfig
```

# hesong.cti.busnetcli

`hesong.cti.busnetcli` 是 `IPSC` 服务程序数据总线客户端的 Java 包装。

它用于向 Java 开发者提供 `IPSC` 数据总线的客户端功能。

## 特点

- JNI 直接封装 CTI Bus 的C语言实现客户端
- 完整的 `IPSC` data-bus 客户端功能包装。其功能基本上与C语言实现的原生客户端一一对应。

## 基础

见： <http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html>

## 作用

开发人员可以使用这个库，配合 IPSC 逻辑流程，构建 CTI 程序，如：基于 IPSC Common CTI Flow (CCF) 的 Java CTI服务程序。

## 编译

首先安装 maven，然后：

### 安装依赖包

```sh
mvn install
```

### 生成 jar 包

```sh
mvn package
```

## ttlib_micro
* **ttlib_mirco** 是一个 C 项目支持库，提高 C 开发效率。是 [ttlib](https://github.com/tangaoo/ttlib) 的轻量级版本，去掉部分超重模块（内存管理、流管理、数据库封装、平台相关等），仅保留必要功能。且构建工具增加支持 Make。

## 编译 
* ttlib_micro 构建工具用 [xmake](https://github.com/xmake-io/xmake)。

```console
git clone https://github.com/tangaoo/ttlib_micro.git

xmake
```

## 介绍
#### demo
- 库使用示例，详情见[代码](https://github.com/tangaoo/ttlib_micro/tree/main/src/demo)。

#### prefix (前置模块)
前置模块是任意 C 项目都必备的。
- abort 异常实现
- assert 检查宏
- check 宏
- 编译测试宏
- 静态配置信息
- 大小端测试宏
- 关键字
- 内存分配宏（mirco只支持系统内存分配接口）
- 错误状态码
- trace
- 类型定义
- utils 工具

#### container（容器模块）
容器模块主要实现常用数据结构，以及迭代器。
- 迭代器
- 外置单链表、外置双链表
- 动态数组
- 队列
- 堆栈

#### algorithm（算法模块）
算法模块主要实现基于数据结构的常规算法。
- 迭代器遍历、删除、统计算法
- 排序算法
	- 冒泡排序
	- 堆排序
	- 快速排序
	- 插入排序
- 查找算法
    - 线性遍历
    - 二分法搜索

#### buffer（缓冲模块）
- 环形缓冲（纯byte流）
- 制定类型环形缓冲（待实现）
  
#### 实用工具库
- 实现base64/32编解码
- 实现crc32、md5等常用hash算法
- 实现debug输出、断言
- 实现日志模块
- 实现位操作相关接口，支持各种数据格式的解析，可以对8bits、16bits、32bits、64bits字段进行解析操作，并且同时支持大端、小端和本地端模式。
- 实现单例模块，可以对静态对象、实例对象进行快速的单例封装，实现全局线程安

## TODO
* [ ] 增加 Make 构建工具支持；
* [ ] 增加模块必要文档；
* [ ] demo 覆盖完整；
* [ ] 引入第三方测试框架。
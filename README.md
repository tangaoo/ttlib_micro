## ttlib_micro
* **ttlib_mirco** 是一个 C 项目支持库，提高 C 开发效率。是 [ttlib](https://github.com/tangaoo/ttlib) 的轻量级版本，去掉超重模块（内存管理、流管理、数据库封装、平台相关等），保留必要功能，构建工具增加支持 Make。

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
- element (int ptr mem str等数据抽象), 详见文件[第2篇 ttlib element模块介绍](https://tangaoo.github.io/2021/07/12/ttlib-element/)。
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

#### hash (哈希模块)
- 包含各种哈希函数 bkdr crc fnv md5

#### buffer（缓冲模块）
- 环形缓冲（纯byte流）
- 制定类型环形缓冲（待实现）
  
#### utils（实用工具库）
- bit位操作
- crc8
- 内存dump
- 大小端
- 通用协议 
- trace实现

#### platform（平台相关模块）
平台模块主要是对操作系统资源的一层包裹，方便移植到其他系统。
- atomic 原子操作，需要 C11 支持。
- mutex
- memcpy
- semaphore
- spinlock 由互斥量/原子操作两种实现方式
- thread
- time


## TODO
* [ ] 增加 Make 构建工具支持；
* [ ] 增加模块必要文档；
* [ ] demo 覆盖完整；
* [ ] 引入第三方测试框架。

## 哪些库引用了 ttlib_micro
* [uSPF](https://github.com/tangaoo/uSPF)
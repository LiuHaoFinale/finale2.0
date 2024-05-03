<!--
 * @Author: LiuHao
 * @Date: 2024-05-02 12:21:47
 * @Description: 
-->
# finale2.0

### 构建和运行

```shell
./finale_build.sh
```

可执行文件存放在`build/bin/*`下

### 运行测试用例

```shell
cd llt/
./finale_llt.sh
```

`finale_llt.sh`运行路径

```shell
finale_llt.sh -> llt/CMakeLists.txt -> llt/*/CMakeLists.txt
```

5.3版本可能会出现重复编译问题，此时每次只能测试运行一个模块

```cmake
# build_project("vm")
# build_project("class")
# build_project("compiler")
# build_project("gc")
# build_project("parser")
build_project("common") # 运行模块
```

### 软件架构

```shell
./class  # 类与对象模块
├── include  
└── object 
./common  # 
├── lhlog  #log
├── merror # error
└── unicode  # unicode
./compiler  # 编译模块
├── assist  # 辅助目录
└── structure # 编程结构
./parser  # 解析器模块
./vm  # 虚拟机模块
├── alloc  # 内存分配
├── core  #  核心操作
├── exec  # 指令执行
├── prim  # 原生方法
│   ├── object  # 类相关
└── stable  # 数据结构操作
```

### 开源库

**`googletest`**

**`clang-libfuzz`**

**`clog`**
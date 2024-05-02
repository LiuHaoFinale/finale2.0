<!--
 * @Author: LiuHao
 * @Date: 2024-05-02 20:10:57
 * @Description: 
-->
# Unicode

编码格式：
- `ASCII`：用`1B`表示一个字符
- `Unicode`

`UTF-8`是`Unicode`的一种实现方式，即`UFS`，包括`UTF-8`、`UTF-16`

`UTF-8`指的是每次传输`8`位数据，是一种可编长的编码，使用`1-4`个字节表示一个符号，根据不同的符号而变化字节长度

字节序
- 大端：低高
- 小端：低低

网络传输是用大端来传输的

> 为什么分为大端和小端？计算机处理适合小端，以人类的处理方式来看，适合大端
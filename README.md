
# 编译原理 Project

Sky 语言编译器

组成员:

* 刘一辰 3180102886
* 黄海烽 3180102339
* 周思颖 3180104714

## 设计要点:
0. 使用换行 作为语句分割
1. `begin`, `end` 用 `{` , `}` 来代替
2. 注释使用 `//` 与 , `/**/` 来表示 （禁止嵌套注释）
3. 用 var 声明变量， let 声明常量 (整数默认为 int)
    - var a = 0, b = 0.1 (如果进行赋值（若类型可推断），则无需指定类型)
    - var a : int, b : char
    - let a = 233 (let 声明无需指定类型)
4. 类型采用: int, char, bool, int64, double, float
5. 有指针。声明方式与 C++ 相同 (int*,char*,bool* 等)
6. 面向对象，对象语法:
    - class : class2 {} 表示定义一个继承了 class2 的 class。 构造函数: __init__(), __del__(), 自身指针为 this
7. 函数定义:
    - func funcName(varName: type,varName: type) [-> returnType] {} (若无 return Type 则无返回值)
    - 编译器检查：若函数定义了返回值却没有返回则报错
8. 数组:
    - 定义: var a : int[size] (不允许 let 定义), 下标范围为[0..size-1]
    - 使用: a[i] 可以取出第 i 位的。
9. 动态空间分配：
    - 分配: var a = new int[233], var a = new int, var a = new Object()
    - 删除: delete a
10. if 语句 采用 C++ 形式
11. 由于我们知道再详细的描述都不如一个例子来的直观，所以剩下的看下面的例子吧

至于剩下的，看完了 [LLVM](https://github.com/Evian-Zhang/llvm-ir-tutorial/blob/master/LLVM%20IR%E5%85%A5%E9%97%A8%E6%8C%87%E5%8D%97(1)%E2%80%94%E2%80%94LLVM%E6%9E%B6%E6%9E%84%E7%AE%80%E4%BB%8B.md) 再说？

## Some Example

### 1. for 循环

```
for i in [1,10,1] {
   printf("%d", i)
}
// result: 123456789

for 循环变量名 in [起始值, 终止值, 每次循环增量] {
   被循环的语句
}
左闭右开？
```


## 进阶主题：
- 垃圾回收
- 面向对象
- 类型推断

## 使用方法

本项目中的编译器通过对代码进行语法分析和词法分析，通过LLVM框架生成LLVM-IR的字节码，得到字节码后需要通过如下操作来使其转化为可以在目标平台运行的代码

1. 使用本项目的编译器编译代码文件，假设保存为 a.out
2. 使用命令 `llc a.out -o a.out.asm`
3. 使用命令 `gcc a.out.asm -o a.out` ，该命令执行之后，即可生成可执行文件 `a.out`
4. \[可选\] 可以直接通过 `lli a.out` 来使用 LLVM-IR 解释器直接运行字节码

参考文献:
- [使用yacc和bison建立过滤器](https://www.itread01.com/content/1546621251.html)
- [使用LLVM的API](https://feng-qi.github.io/2018/08/19/llvm-how-to-get-started-with-the-llvm-c-api/)

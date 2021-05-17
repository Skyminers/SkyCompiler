
# 编译原理 Project

Sky 语言编译器

组成员:

* 刘一辰 3180102886
* 黄海峰 3180102339
* 周思颖 3180104714

设计要点:
0. 不用分号, 换行作为分割
1. `begin`, `end` 用 `{` , `}` 来代替
2. 注释使用 `//` 与 , `/**/` 来表示 （禁止嵌套注释）
3. 用 var 声明变量， let 声明常量 (整数默认为 int)
    - var a = 0, b = 0.1 (如果进行赋值（若类型可推断），则无需指定类型)
    - var a : int, b : char
    - let a = 233 (let 声明无需指定类型)
4. 类型采用: int, char, bool, int64, double, float
5. 有指针，但是不允许二重指针（即指向指针的指针）。声明方式与 C++ 相同 (int*,char*,bool* 等)
6. 面向对象，对象语法:
    - class : class2 {} 表示定义一个继承了 class2 的 class。 构造函数: __init__(), __del__(), 自身指针为 this
7. 函数定义:
    - func funcName(varName: type,varName: type) [-> returnType] {} (若无 return Type 则无返回值)
    - 编译器检查：若函数定义了返回值却没有返回则报错
8. 数组:
    - 定义: var a : int[size] (不允许 let 定义)
    - 使用: a[i] 可以取出第 i 位的。
9. 动态空间分配：
    - 分配: var a = new int[233], var a = new int, var a = new Object()
    - 删除: delete a
10. if 语句 与 for 语句 采用 C++ 形式

至于剩下的，看完了 [LIVM](https://github.com/Evian-Zhang/llvm-ir-tutorial/blob/master/LLVM%20IR%E5%85%A5%E9%97%A8%E6%8C%87%E5%8D%97(1)%E2%80%94%E2%80%94LLVM%E6%9E%B6%E6%9E%84%E7%AE%80%E4%BB%8B.md) 再说？


进阶主题：
- 垃圾回收
- 面向对象
- 类型推断



![image-title](image/title.png)



## <center>本科实验报告</center>



​							**课程名称**											**编译原理**

------

​																					    **刘一辰 3180102886**

​									**成员**										  	**黄海烽 3180102339**

​																					  	**周思颖 3180104714**

------

​									**学院**									  		**计算机科学与技术学院**

------

​									**专业**						  					**计算机科学与技术专业**

------

​							**指导教师**											**李莹**



## <center>2021年6月6日</center>



<div style="page-break-after: always;"></div>
[TOC]

<div style="page-break-after: always;"></div>

## 1.序言

### 1.1 概述

Sky语言是由本次实验小组创造的一个新语言。本组基于C++语言设计并实现了一个Sky语言的编译系统，该系统以符合Sky语言规范的代码文本文输入，输出为指定机器的目标代码。该Sky编译器的设计实现涵盖词法分析、语法分析、语义分析、代码生成等阶段和环节，所使用的具体技术包括但不限于：

- Flex实现词法分析
- Bison实现语法分析
- LLVM实现中间代码生成、目标代码生成

### 1.2 开发环境

- 操作系统：MacOS
- 编译环境：
  - Flex ？
  - Bison ？
  - LLVM  ？
- 编辑器：XCode, Vim

### 1.3 文件说明

本次实验提交的文件及其说明如下：

- src：源代码文件夹

  + sky.l：Flex源代码，主要实现词法分析，生成token
  + sky.y：Yacc源代码，主要实现语法分析，生成抽象语法树
  + CMakeLists.txt：定义编译链接规则
  + CompileException.h：
  + README.md：项目简介
  + convertEngine.cpp：
  + convertEngine.h：
  + defineList.h：
  + lex.yy.cpp：
  + main.cpp：主函数所在文件，主要负责调用词法分析器、语法分析器、代码生成器
  + nodeList.cpp：
  + nodeList.h：
  + sky.tab.cpp：
  + sky.tab.h：
  + test.sky：
- test：测试用例文件夹
  + auto-advisor.sky选课助手源程序
  + matrix-multiplication.sky矩阵乘法源程序
  + quicksort.sky 快速排序源程序
- doc：报告文档文件夹
  + report.pdf 报告

### 1.4 组员分工

| 组员   | 具体分工                |
| :----- | :---------------------- |
| 周思颖 | 词法分析，语法分析      |
| 黄海烽 | AST可视化，中间代码生成 |
| 刘一辰 | 语义分析，目标代码生成  |



## 2.词法分析



### 2.1 Lex







## 3.语法分析



### 3.1 Yacc



其EBNF形式的语法定义如下：

## 4.语义分析



### 4.1 LLVM



## 5.测试案例



## 6.总结

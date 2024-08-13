[toc]

## *sizeof*

> 以前以为 *sizeof* 是一个函数，没想到是一个操作符...

参考文章：

1. [sizeof operator in C](https://www.geeksforgeeks.org/sizeof-operator-c/?ref=lbp)
    
    这篇文章出自 *GeeksforGeeks* ，我真的超爱这个平台的教程，详略得当，内容丰富，排版清晰美观。

2. [The Sizeof() Operator In C | A Detailed Explanation (+Examples)](https://unstop.com/blog/sizeof-operator-in-c)
    
    这篇文章出自 *Unstop* ，该篇文章更为详细，内容涵盖了 *sizeof* 操作符的编译器实现，阅读起来稍有难度。

#### *语法*

``` c
sizeof(Expression);
```

#### *参数*

'*Expression*' 可以是一个数据类型( *data type* )，也可以是一个变量( *variable* )。

1.  *data type* ：例如 *int* 、 *double* 、 *char* ...
2.  *variable* ：例如`int c`， *c* 就是 *int* 型变量。

#### *解释*

 *sizeof* 会返回 *data type* / *variable* 所需内存空间大小，返回值的单位为字节。

例如 *int* 是 *4* 字节数据类型，它所需的内存空间大小为 *4 byte* 。则运行下列程序的结果是 *4* 。

``` c
#include <stdio.h>

int main(void)
{
    printf("%lu\n", sizeof(int));
}
```

#### *难以解释*

 *sizeof* 可以得到 *int* 、 *double* 等数据类型所需内存空间大小，结果也容易理解。但是 *struct* ，即结构体这种数据类型所需的内存空间大小却是反人类直观的。

例如：

``` c
typedef struct
{
    char a;
    int b;
}
struct_example;
```

上面例子中的结构体 *struct_example* 所需的内存空间大小，常理应该为 *char* 和 *int* 所需内存空间的总和，即为( *1* + *4* ) *byte* 。但是结果并不是 *5 byte* ，而是 *8 byte* 。

为什么会这样？这涉及到内存中数据的存放，专业名词为**数据对齐**。

##### *数据对齐*

当你定义了一个变量，或者连续定义了一系列的变量，这些变量在经过编译器编译后会被操作系统存放在内存中。但是这些变量不是在内存中随便找一个地址就存放了。

首先需要明白的是，内存存放数据的单位是 *1 byte* ，而不是 *1 bit* 。即使是只需要 *1 bit* 内存大小的 *bool* 型变量，存放在内存上时也会占据 *1 byte* 的空间，有 *7 bit* 的内存空间是空置的。这个涉及到微机原理的概念，不在这里展开叙述。

在现代机器上，内存数据的读取的单位却不是 *1 byte* 。 *32-bit* 机器每个读取周期都会读取 *4 byte* 的内存数据，而 *64-bit* 机器为 *8 byte* 。这也就意味着，即使是只读取一个 *char* 型数据( *1 byte* )，会有多余的 *3 byte* 数据被读取。

但是这大大提高了机器读取数据的效率。如果每次只读取一个字节，那一个 *int* 型数据需要花费 *4* 个读取周期读取！而这种读取方式也决定了内存实际上被分成了不同的区域，例如在 *32-bit* 的机器上，内存以 *4 byte* 为一组分成了不同的区，每个区的首地址可以被 *4* 整除，如下图所示。

![pic](https://github.com/WBlackhole/CS50_note/blob/master/pic/32-bit-data-bus-layout.png?raw=true)

这样的物理结构也形成了一个重要特性：**不能在一个读取周期内跨区访问内存**。即每次读取的数据都是 *bank0* ~ *bank3* ，而不能在一个周期内跨区读取 *4* 个 *bank* 。

扯了这么多，所以数据对齐是什么？根据不能跨区访问内存的特性，存放一个变量时让其所占的区尽量少会提高读取效率。例如存放一个 *4 byte* 的 *int* 型变量，如果以 *bank0* 为首地址存放，那将刚好存放在一个区内，读取也只需要一个周期，除此之外的任何存放方式都将需要两个周期。

本着提高效率的目的，诞生了数据对齐规则：

 *1* .  *1 byte* 对齐：大小为 *1 byte* 的变量( *char* 等)存放地址可以是任意地址。

 *2* .  *2 byte* 对齐：大小为 *2 byte* 的变量( *short int* 等)存放地址需要是偶数地址。

 *3* .  *4 byte* 对齐：大小为 *4 byte* 的变量( *int* 、 *float* 等)存放地址需要是 *4* 倍数地址。

 *4* .  *8 byte* 对齐：大小为 *8 byte* 的变量( *double* 等)存放地址需要是 *8* 倍数地址。

以上规则是人为规定的，由机器执行，和 *C* 语言本身无关。而这种数据对齐也称作数据类型的自然对齐。以下是一些例子：

``` c
int a; // 4 byte，假设地址为0x00(bank0)
char b; // 1 byte，地址为0x04

/* 根据自然对齐：
 * a存放在4倍数的内存地址上(bank 0)，并占据4 byte空间。
 * b可以紧接着a进行存放，并占据1 byte空间。
 */ 
```

``` c
int a; // 4 byte，假设地址为0x00(bank0) 
char b; // 1 byte，地址为0x04 
double c; // 8 byte，地址为0x08

/* 根据自然对齐：
 * c不可以紧接着b存放，下一个满足条件的地址在b地址3个byte后。
 */
```

第二种情况中， *c* 与 *b* 并不是连续着存放的，而是有 *3* 个 *byte* 的内存间隔。这种间隔像是一种填充：

```
int a; // 4 byte
char b; // 1 byte
char pad[3]; // 3 byte
double c; // 8 byte
```

这种因为数据对齐造成内存空间间隔的行为，叫 ***padding*** 。

但是以上分析都基于一个虚假的假设：变量按照代码的定义顺序进行顺序存放。虽然这种假设大部分时候正确，但是有时候并不是这样，这里重点是搞清楚数据对齐的概念，因此不做进一步分析。

##### 结构体数据对齐

*struct* 本身的自然对齐对标其**最大对齐字节成员**，例如如果成员中最大的对齐字节是 *8* 字节，那 *struct* 数据存放的地址需要是 *8* 倍数地址。

同时， *struct* 还有尾填充[^1]，即在数据的最后有一些字节填充。什么时候尾填充，填充多少字节呢？满足一个条件：**尾填充至下一个满足该 *struct* 存放条件的地址前**。例如如果该 *struct* 需要存放在 *8* 倍数地址，那在该 *struct* 所有数据存放完后，如果下一个地址不是 *8* 倍数地址，那将进行字节填充，填充至下一个 *8* 倍数地址前。这其实也会导致 *struct* 的内存空间大小是其对齐字节的倍数。

[^1]:尾填充的目的在参考文章2中有详细解释。很简单的原因。

总结struct的数据存放：

1. 各成员满足其本身的自然对齐

2.  *struct* 的自然对齐对标最大对齐字节成员

3. 尾填充

下面是一些实例：

``` c
typedef struct
{
    int a;
    char b;
    int c;
}
struct_example;

/* struct_example在4倍数地址上开始存放(struct的自然对齐)，假设是0x00
 * a存放在0x00，4 byte
 * b存放在0x04，1 byte
 * padding，3 byte
 * c存放在0x08，4 byte
 * 尾地址0x11，下一个地址0x12。无尾填充。
 * 共占12 byte。
 */
```

```c
typedef struct
{
    char a;
    double b;
    int c;
}
struct_example;

/* struct_example在8倍数地址上开始存放，假设是0x00
 * a存放在0x00，1 byte
 * padding，7 byte
 * b存放在0x08，8 byte
 * c存放在0x16，4 byte
 * 尾地址0x20，下一个地址0x21。尾填充至0x23，4 byte
 * 共占24 byte
 */
```

当然，sizeof可以贴心的帮你计算出来结构体所占的内存空间。

#### *其他*

' *Expression* '如果是一个表达式例如`x + y`， *sizeof* 返回的是该表达式结果所占的内存空间，这中间可能有数据转换，例如一个 *double* 型数据与 *int* 型数据相加，结果是 *double* ， *sizeof* 返回值也将会是 *8* 。

#### *参考文章*

1. [Structure Member Alignment, Padding and Data Packing](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)
    
    这篇文章出自GeeksforGeeks。内容非常精彩，有图片，通俗易懂。

2. [The Lost Art of Structure Packing](http://www.catb.org/esr/structure-packing/)

    这篇文章非常专业，非常干，像教材。但是内容很精彩，非常全面，介绍的非常彻底。

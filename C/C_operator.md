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

'*expression*' 可以是一个数据类型( *data type* )，也可以是一个变量( *variable* )。

1.  *data type* ：例如 *int* 、 *double* 、 *char* ...
2.  *variable* ：例如`int c`， *c* 就是 *int* 型变量。

#### *解释*

 *sizeof* 可以用来计算 *data type* 或者 *variable* 所需内存空间大小，返回值的单位为字节。

例如数据类型 *int* 为 *4* 字节数据类型，它所需的内存空间大小为 *4 byte* 。则运行下列程序的结果是 *4* 。

``` c
#include <stdio.h>

int main(void)
{
    printf("%lu\n", sizeof(int));
}
```

#### *难以解释*

 *sizeof* 的基本使用就是得到 *int* 、 *double* 等等数据类型的数据大小。但是难点在于， *struct* 这个数据类型的数据大小非常反人类直觉。

例如：

``` c
#include <stdio.h>

typedef struct
{
    char a;
    int b;
}
struct_a;

int main(void)
{
    struct_a my_struct;
    printf("%lu\n", sizeof(my_struct));
}
```

运行上面程序的结果是 *8* 。

正常来说， *struct_a* 结构体中包含一个 *char* 型数据( *1 byte* )、一个 *int* 型数据( *4 byte* )，则 *struct_a* 所占的内存空间大小应该为 *5 byte* 。

但为什么结果是 *8 byte* 呢？这涉及到内存的'数据对齐'( *data alignment* )。所谓的数据对齐，是一种能够提升数据读取速度的手段。理解数据对齐需要先明白内存数据的读取。

在现代机器上，读取内存数据并非是单字节读取的，而是同时读取多个字节的内存数据以提高效率(想想如果单字节读取，那读取一个 *int* 型数据需要 *4* 个读取周期...)。 *32-bit* 的机器字宽为 *4 byte* ，意味着同时读取 *4* 个字节的内存数据。 *64-bit* 的机器字宽为 *8 byte* ，可以同时读取 *8* 个字节的内存数据。

内存也以多个字节为单位进行了分区。例如在 *32-bit* 的机器中，内存以 *4* 个字节进行分区。其中一个重要的特性是：**不能跨区访问内存**。

所以为了尽可能快速的得到数据，在存放数据时，会进行数据对齐，这种对齐也称作该数据类型的自然对齐。以下是各数据类型的自然对齐：

-  *char* ： *1* 字节对齐。可以存放在任意地址。
-  *short int* ： *2* 字节对齐。内存首地址需要为 *2* 的倍数。
-  *int* ： *4* 字节对齐。内存首地址需要为 *4* 的倍数。
-  *double*  ： *8* 字节对齐。内存首地址需要为 *8* 的倍数。

而结构体数据类型的数据对齐称为**结构体数据对齐**。结构体数据对齐的方式为：

1. 所有成员满足自身的自然对齐。

2. 结构体尾填充满足结构体对齐。

假设结构体成员中最大字节对齐为 *n* 字节，则尾填充的结果会导致结构体内存大小为 *n* 的倍数。

参考文章：

1. [Structure Member Alignment, Padding and Data Packing](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)
    
    这篇文章出自GeeksforGeeks。内容非常精彩，有图片，通俗易懂。

2. [The Lost Art of Structure Packing](http://www.catb.org/esr/structure-packing/)

    这篇文章非常专业，非常干，像教材。但是内容很精彩，非常全面，介绍的非常彻底。

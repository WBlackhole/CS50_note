[toc]

内容参考：

[GeeksforGeeks:C Variables and Constans](https://www.geeksforgeeks.org/c-programming-language/?ref=shm)


在开始谈变量前，我想先说一个故事：

很久以前，地球上什么都没有只有你，你是这个地球的创世主。你觉得地球太空旷了，于是决定创造一些人。你学着女娲捏出了一个人，并赋予了这个人人名。当你准备把这个人放在地球上生存的时候，你发现地球拒绝了你。你思索后明白，这个人什么物资都没有，在地球上生存不下去，于是你给予了这个人物资，好让他生存下去。就这样，你创造了许多人。有时候，你觉得有的人你看着顺眼，作为创世主你决定重新设定她的物资，于是你利用你赋予的人名改变了她手里的物资...未完待续

上面的故事，就是作为程序员的你，创建一个变量并存储在内存的过程。

<br>

## **变量**

<br>

 *C* 语言中的变量，是一块存储了某种类型数据的内存，变量名则是这块内存的**名字**。我们可以使用变量名来改变这块内存存储的值。对应故事就是，变量是人，变量名是人名，内存是地球，变量值就是物资。创建变量的语法如下：

```C
[storage class] data_type variable_name = value;
```

 *storage class* 是变量的存储类型， *data_type* 是变量的数据类型。在创建变量时，变量的 *storage class* 可以省略，但是 *data_type* 不可以省略。按照故事中来说， *storage* 决定了这个人在哪个大洲生存， *data_type* 决定了这个人手里物资的类型，是食物还是工具等。

根据在程序中创建变量的位置不同，变量被分为了全局变量和局部变量。全局变量是在函数块和所有代码块外创建的变量，局部变量则是在函数块内以及代码块内创建的变量。它们之间一个比较明显的区别是，全局变量能在整个程序内使用，而局部变量只能在创建它的函数块和代码块内使用。

这就好像，你决定了你创建人的寿命，你创建全局变量就像创建了一个长生不老的人，只有地球毁灭她才会消失，局部变量则是有寿命的，随着寿命结束她就消失了，你也就不能再改变她手里的物资了，但是同时随着她的消失，你可以创建新的同名的人，嗯，有点像替身文学。

<br>

## **~~创建~~，声明和定义**

<br>

使用创建这个词终究是不专业的，更专业的说法是声明和定义。

声明，不会在内存中分配空间。而定义，才会在内存中分配空间。并没有特指声明和定义变量，是因为声明和定义同样用于函数，之间有些区别。就变量的声明定义而言，变量的声明和定义往往结合为了一步：

```C
data_type variable_name；

e.g.
int a;
```

即使没有赋予变量初值，这个变量也会在内存中被分配空间。因此声明定义同时实现。如果只想定义而不想分配空间，需要特定声明它的 *storage class* 为 *extern* ：

```
extern data_type variable_name;

e.g.
extern int a;
```

<br>

## **Storage class**

<br>

变量的存储类型总共有四类： *auto* 、 *extern* 、 *static* 、 *register* 。

<center>

![Storage Classes](https://github.com/WBlackhole/CS50_note/blob/master/pic/Storage-Classes-In-C.png?raw=true)

</center>

<br>

### **auto**

局部变量，默认 *storage class* 为 *auto* 。

 *auto* 类的变量在栈区分配空间，如果没有给变量赋予初值，则变量值为被分配内存空间的值，即为未知的垃圾值。作为局部变量的 *auto* 类变量，生命周期以及作用域都只在定义它的代码块内，一旦离开代码块，被分配的空间就会销毁，变量也就不存在了，后续也更不可能还能继续使用这个变量。

<br>

### **extern**

全局变量，默认 *storage class* 为 *extern* 。

 *extern* ， *external* 的缩写，即外部的。要谈及为什么是外部的，要明白域的范围到底为什么：

从大到小，一个变量能够被使用的范围依次为：整个程序 -> 整个文件 -> 函数内部/代码块内部。常说的全局变量，可以在整个文件中使用，该作用域也称“文件域”。

而要做到能在整个程序都能使用这个变量，就需要声明变量的 *storage class* 为 *extern* ，同时外部文件使用时，也用 *extern* 进行声明。同时，既然需要整个程序使用， *extern* 类的变量名整个程序只能出现一次，要不然编译出错。下面是外部文件使用的例子：

```C
#include <stdio.h>

extern int a;

int main(void)
{
    printf("%d\n", a);
    return 0;
}
```

在使用时，外部文件知道，哦，你是 *extern* 声明的变量啊，你没有在我这定义，那别的文件肯定能找到你。但是，如果你没有在任何一个文件中对 *a* 变量进行定义，也就是 *a* 压根没有分配内存空间，那程序会编译错误，在 *linker* 阶段错误。

在故事中就是，使用 *extern* 创造的人，全球身份唯一，当一个洲当想寻找一个人，同时发现这个人是 *extern* 类的，它就会知道，这个人我只需要在全球找而不需要在我这个洲创建她。

<BR>

### **static**

 *static* 类的变量，俗称静态变量。我们根据它声明的位置分类：

 *1* . 静态局部变量：即定义在函数块或代码块内的静态变量。它和局部变量只有一个区别：它仅会被定义一次，同时生命周期为整个程序，也就是说，它不会随着离开定义它的代码块或函数块而消失。然而作用域仍在定义它的函数块或代码块内。

 *2* . 静态全局变量：即定义在函数块或任意代码块外的静态变量。它和全局变量的区别是：它不能被外部文件通过 *extern* 引用，即作用域为文件域。

若未对静态变量初始化，静态变量的初始值默认为 *0* 。同时静态变量的初始化仅能使用一个常量，不能使用变量。例如下面程序会报错：

```C
#include <stdio.h>

int initializer(void)
{
	return 50;
}

int main(void)
{
	static int i = initializer();
	printf(" value of i = %d", i);
	getchar();
	return 0;
}
```

同时，结构体中不能拥有静态变量成员。

```C
#include <stdio.h>

void function()
{
    int x = 20; // local variable
    static int y = 30; // static variable
    x = x + 10;
    y = y + 10;
    printf("\tLocal: %d\n\tStatic: %d\n", x, y);
}

int main(void)
{
    printf("First Call\n");
    function();
    printf("Second Call\n");
    function();
    printf("Third Call\n");
    function();
    return 0;
}
```

OUTPUT

```
First Call
    Local: 30
    Static: 40
Second Call
    Local: 30
    Static: 50
Third Call
    Local: 30
    Static: 60
```


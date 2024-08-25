[toc]

<br>

内容参考：

1. [geeksforgeeks-C Programming Language](https://www.geeksforgeeks.org/c-programming-language)
: *C File Handling* 章节

2. [cplusplus-<stdio.h>](https://cplusplus.com/reference/cstdio/)

3. [cp5.pdf](https://www.jbiet.edu.in/coursefiles/cse/HO/cse1/CP5.pdf)

<br>

## *C的输入流和输出流*

如 *Shell* 一般， *C* 也有输入流和输出流。若将 *C* 程序对应为黑盒理论中的黑盒，则输入流流向黑盒的 *input* ，黑盒的 *output* 流出输出流。数据流如下：

> 数据来源 -> 输入端口 -> 程序 -> 输出端口 -> 数据去向

数据来源默认是键盘，数据去向默认是终端。这意味着默认情况下，当程序这个黑盒需要 *input* 时，你在键盘上敲下的按键数据将作为输入流成为黑盒的 *input* ；当程序这个黑盒输出 *output* 时， *output* 的数据将作为输出流流向终端进行显示。

文件，常常作为输入流和输出流的非默认来源、去向。而根据数据划分， *C* 处理的文件有两类：文本文件和二进制文件，分别以 .*txt* 和 .*bin* 作为文件名后缀。

<br>
<br>

## *C处理文件*

在 *C* 程序中处理文件的一般步骤：

1. 声明一个文件指针变量

2. 使用 *fopen()* 函数打开文件

3. 使用合适的函数处理文件

4. 使用 *fclose()* 和 *fflush()* 函数关闭文件

> 输入文件 -> 输入端口 -> 程序 -> 输出端口 -> 输出文件

<br>
<br>

## *声明指针变量*

```c
FILE *file_pointer_name;

eg.
FILE *fp;
```

`FILE`是一个[结构体](https://www.geeksforgeeks.org/data-type-file-c/)，*file_pointer_name* 则指向这个结构体。

我们可以将这个 *FILE* 视作一个端口，作为文件和程序交流的端口，每个 *FILE* 端口都会指向特定的一个文件。而我们定义指针指向这个端口，这个端口指向文件，于是我们就能通过这个指针再通过端口间接找到找到并操作文件。

但是 *FILE* 这个结构体到底是什么呢？不必理会。但是其中的一些成员需要了解：

1. *end-of-file indicator* ( *eof* )：文件结束指示器。当某些函数读取文件时，若文件位置指示器到达文件结尾，则会置位该变量。

2. *internal file position indicator*：文件位置指示器。用来指向文件读取位置。当某些函数处理文件时，会改变该变量以指向读取后的位置。

<br>
<br>

## *打开文件*

用 *fopen()* 函数来构建一个 *FILE* 端口，并让它指向文件。语法如下：

```c
FILE *fopen(const char *filename, const char *mode);

/* filename: 文件名
 * mode：打开文件的模式
 * 返回值：成功返回文件指针；失败返回NULL指针
 */
```

|mode| 描述|
|:---:|:---:|
|"r"|以只读模式打开一个文件|
|"w"|以只写模式打开或创建一个文件|
|"a"|以追加模式打开或创建一个文件|
|"r+"|以只读模式和只写模式打开一个文件|
|"w+"|以只读模式和只写模式打开或创建一个文件|
|"a+"|以只读模式和追加模式打开或创建一个文件|

<br>

*mode* 有以下点需注意：

1. 默认打开的为 *text* 文件，若要打开二进制文件，则在模式后加上 *b* 。例如："*rb*"、"*w+b*" / "*wb+*"。

2. 只写模式和追加模式的区别：
    - 文件存在时：只写模式会清空文件内容后再写；追加模式不清空文件内容，在文件末尾写。
    - 文件不存在时：无区别，都会创建文件。        

例：

```C
#include <stdio.h>

int main(void)
{
    FILE *fp;
    fp = fopen("file_nmae", "r");
    if(fp == NULL)
        printf("fail to open file.\n");
        return 1;
 
    printf("success to open file.\n");
    return 0;
}
```


<br>
<br>

## *关闭文件*

用 *fclose()* 函数关闭 *FILE* 端口。语法如下：

```C
int fclose(FILE *stream);

/* stream：文件指针，指向被打开的端口
 * 返回值：成功返回0；失败返回-1(EOF)
 */
```

例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file_name", "r+");
    if (fp == NULL)
        return 1;
 
    if (flcose(fp) == EOF)
        printf("fail to close file.");
        return 1;

    return 0;
}
```

<br>
<br>

## *处理文件*

#### *字符*

*getc()* 和 *putc()* 函数可以以字符为单位处理文件。语法如下：

```C
// 从文件位置指示器处读取一个字符，并将文件位置指示器后移一个字符
int getc(FILE *stream);

/* stream：指针，指向端口
 * 返回值：成功，返回读到的字符；失败，返回EOF
 */

/* 若使用默认端口，stream为stdin：getc(stdin)。等同于getchar()。
 * getc()和fgetc()等同。
 */
```

例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "r");
    if (fp == NULL)
        return 1;
    
    char c = getc(fp);
    printf("%c\n", c);
    
    fclose(fp);
    return 0;
}
```

---

```C
// 写一个字符至文件指示器处，并更新文件位置指示器
int putc(int character, FILE *stream);

/* stream：指针，指向输出端口
 * character：要写的（int -> unsigned char）型字符
 * 返回值：成功返回写入的字符；失败，返回EOF
 */

/* 若使用默认端口，stream为stdout：putc("c", stdout)。等同于putchar("c")。
 * putc()和fputc()等同。
 */
```

例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "w");
    if (fp == NULL)
        return 1;
    
    putc("c", fp);

    fclose(fp);
    return 0;
}
```


#### *字符串*

三个函数用于读取字符串，三个函数用于写入字符串。

- *fscanf()* & *fprintf()*

- *fgets()* & *fputs()*

- *fread()* & *fwrite()*

*fgets()* 和 *fputs()*用于读取和写入字符串。语法如下：

```C
// 从文件位置指示器处读取 num-1 个字符，并将其存储在str指向的字符数组中。当遇到换行符或文件结尾时，读取结束。
char *fgets(char *str, int num, FILE *stream);

/* str：指针，指向字符数组
 * num：要读取的字符数量最大值
 * stream：指针，指向输入端口
 * 返回值：返回str；遇到文件结尾时，置位eof。
 */

/* 1. 遇到换行符读取结束，但是它会把换行符'\n'读取进来！一定需要注意。
      倘若不想读取换行符，使用 fscanf() 函数。
 * 2. 为什么读取的是 num-1 个字符，是因为 fgets() 执行完后会自动补一个'\n'。
 * 3. 为什么 fgets() 需要给一个 str 来存储字符串，而不能像 getc() 那样返回呢？因为不能返回字符串。
 */
```
例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "r");
    if (fp == NULL)
        return 1;

    char str[100];
    fgets(str, 100, fp);
    printf("%s", str);
    
    fclose(fp);
    return 0;
}
```

---

```C
// 将str字符串写入文件位置指示器处
int fputs(const char *str, FILE *stream);

/* str：要写入的字符串
 * stream：指针，指向输出端口
 * 返回值：成功，返回非负值；失败，返回EOF
 */
```
例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "w");
    if (fp == NULL)
        return 1;

    if (fputs("Love you", fp) == EOF)
        return 1;
    
    fclose(fp);
    return 0;
}
```

---

*fread()* 和 *fwrite()* 函数用于读取数据，不局限于字符串。语法如下：

```c
// 从文件位置指示器处读取 count 个大小为 size bytes 的元素，并存储在 ptr 指向的内存块
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

/* ptr：指针，指向一块内存，内存用来存储读取的数据
 * size：要读取的元素大小(bytes)
 * count：要读取的元素个数
 * stream：指针，指向输入端口
 * 返回值：成功读取的元素个数。
 */
```
例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "r");
    if (fp == NULL)
        return 1;
    
    // 读取99个字符（最后一个需要补NULL）
    char buffer[100];
    if (fread(buffer, sizeof(char), 99, fp) == 99)
        buffer[99] = NULL;

    fclose(fp);
    return 0;
}
```

---

```C
// 从ptr指向的内存块读取 count 个大小为 size bytes 的元素，并写入到文件位置指示器处
size_t fwirte(const void *ptr, size_t size, size_t count, FILE *stream);

/* ptr：指针，指向要读取的内存块
 * size：要读取的元素大小(bytes)
 * count：要读取的元素个数
 * stream：指针，指向输出端口
 * 返回值：成功写入的元素个数
 */
```
例：
```C
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("file name", "w");
    if (fp == NULL)
        return 1;
        
    char buffer[] = {'L', 'O', 'V', 'E'};
    if (fwirte(buffer, sizeof(char), sizeof(buffer), fp) != sizeof(buffer))
        return 1;
    
    fclose(fp);
    return 0;
}
```

<br>
<br>

这些函数的原型都不好记忆，可以这么记忆，参数都按照下面这个顺序排布：

> [内存] -> 数据元素 -> 文件

```C
fgets(char *str, n, FILE *stream);
/* str -> n -> stream
 * 读取的数据存放在str指向的内存 -> 读取n个字符数据元素 -> stream的数据来源于文件
 */

fputs(char *str, FILE *stream);
/* str -> stream
 * 输出str字符串数据元素 -> stream的数据流向文件
 */

fread(void *ptr, size_t size, size_t count, FILE *stream);
/* ptr -> size * count -> stream
 * 读取的数据存放在ptr指向的内存 —> 读取size bytes大小 * count个数据元素 —> stream的数据来源于文件
 */
```

<br>

## **C语言实现get_string()**

<br>

众所周知啊，*C* 语言没有函数可以实现像 *python* 的 *input()* 函数那样，可以接收用户不定长的字符串输入。*gets()* 也不可以，因为它需要指定输入的最大长度，倘若不指定长度，可能会发生内存溢出的可能，因为最终 *get()* 从输入端接收的字符都会一股脑给存储字符串的内存，而这块内存是编程者事先分配好大小的。

所以要实现 *python* 的 *input()* 函数，怎么办？*Overflow* 社区有解答：[get_line()](https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c/314422#314422)。采用了实时检查输入字符串长度和动态分配内存的思路，很不错，函数原型如下：

```c
char * getline(void) 
{
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    
    if(line == NULL)
        return NULL;

    for(;;) 
    {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) 
        {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL)
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
```

值得注意的是，这个函数会将输入的回车符号'\n'作为输入字符串的一部分。若不需要最后的回车符，可以将函数中最后的`*line = '\0';`改为`*--line = '\0';`。关于这个函数原型，我的学习记录如下：

1. `realloc(linep, lenmax *= 2)`，这种在函数形参在括号内进行运算的写法，我第一次遇见，给了我比较大的震撼。这个写法巧妙在，`*=`运算符的运算优先级高于`,`，因此会先执行`lenmax *= 2`，然后结果作为形参传递进函数。这种写法可以使得程序表达更为简洁，好巧不巧，我这个人最爱简洁的程序。

2. 整个程序共有三个指针来指向动态分配的空间： *line* 、 *linen* 、 *linep* 。其中， *line* 实时指向字符串的最后一位字符地址， *linen* 和 *linep* 都指向内存首地址。为什么需要两个指针来指向内存首地址呢？
 - 当 *realloc* 出错返回 *NULL* ，需要释放 *linen* 指向的旧内存空间。
 - 需要 *linen* 指向旧内存空间首地址，方便计算利用 `line - linen` 计算当前字符串长度。 

3. `if((*line++ = c) == '\n')`这个式子也很精彩。一个式子同时实现了line指针增一、赋值、字符是否相等判断...

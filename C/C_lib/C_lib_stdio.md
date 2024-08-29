[toc]

参考库教程
1.  [C Standard Library Reference Tutorial](https://www.tutorialspoint.com/c_standard_library/index.htm)

2. [C++ sdtio.h](https://cplusplus.com/reference/cstdio/)


## *getchar*

#### *语法*

```c
int getchar(void);
```

#### *参数*

- 返回值：未遇到错误，将从 *stdin* 输入的字符转换为 *int* 后返回；遇到错误，返回 *EOF* 。

#### *解释*

 *getchar* 这个函数可以从标准输入 *stdin* 接收一个字符。

#### *用法*

```c
#include <stdio.h>

int main(void)
{
    char ch;
    if ((ch = getchar()) != EOF)
    {
        printf("%c\n", ch);
    }
    
    return 0;
}
```


<br>


## *putchar*

#### *语法*

```c
putchar(int char);
```

#### *参数*

-  *char* ：被打印的 *int* 型字符。 *int* 值会被当作 *ASCII* 码。

#### *解释*

 *putchar* 可以打印一个字符。然而它的形参是 *int* 型的变量，不是 *char* 型的变量。该函数执行的时候，会将 *int* 型的形参作为 *ASCII* 码，并打印对应的字符。

#### *用法*

```c
#include <stdio.h>

int main(void)
{
    char *str = "Hello,World!";
    while(*str)
    {
        putchar(*str++);
    }
    
    printf("\n");
    return 0;
}
```

**OUTPUT**

```
Hello,World!
```

```c
#include <stdio.h>

int main(void)
{
    for (int i = 65; i <= 70; i++)
    {
        putchar(i);
    }

    printf("\n");
    return 0;
}
```

**OUTPUT**

```
ABCDEF
```


<br>


## *fgets*

#### *语法*

```c
char *fgets(char *str, int n, FILE *stream);
```

#### *参数*

-  *str* ：指针，指向存放字符串的数组。

-  *n* ：读取字符串的最大长度，将包括末尾的 *null* 字符。实际字符串的长度最大为 *n-1* 。

-  *stream* ：指针，指向作为输入流读取的文件。

- 返回值：未遇到错误，返回 *str* ；遇到错误，如到达文件末尾导致无字符可读取，返回 *NULL* 。

#### *解释*

 *fgets* 用来接收字符串，并将接收的字符串存放在 *str* 指向的数组中。和 *scanf* 的功能类似，但是它专门用来接收字符串，而且可以接收空格等字符。

同时，它可以接受文件内容作为输入流。

#### *用法*

```c
#include <stdio.h>

int main(void)
{
    char example[50];
    if (fgets(example, sizeof(example), stdin) != NULL)
    {
        printf("%s", example);
    }
}
```


<br>


## *fputs*

#### *语法*

```c
int fputs(const char *str, FILE *stream);
```

#### *参数*

-  *str* ：指针，指向要打印的字符串(结尾是 *NULL* )

-  *stream* ：指针，指向要打印字符串的输出。输出可以是一个文件，也可以是标准输入 / 输入。

- 返回值：打印成功，返回一个非负值；打印失败，返回 *EOF* ( *-1* )。

#### *解释*

 *fputs* 可以用来打印字符串，可以打印在文件里面，也可以打印在标准输出。

#### *用法*

```c
#include <stdio.h>

int main(void)
{
    char *str = "Hello,World!";
    
    fputs(str, stdout);
    
    printf("\n");
    return 0;
}
```

**OUTPUT**

```
Hello,World!
```

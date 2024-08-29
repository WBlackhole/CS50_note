[toc]

内容参考：

[GeeksforGeeks:C Control Statements Decision-Making](https://www.geeksforgeeks.org/c-programming-language/?ref=shm)

<br>

## **for循环**

<br>

 *for* 循环的语法如下：

```c
for (initialization; check/test expression; updation)
{
    // body consisting of multiple statements
}
```

 *for* 循环开始于 *initialization* ，即初始化。然后检查 *expression* 条件，如果条件为真，则开始执行 *body consisting*   *of multiple*   *statements* 。在执行完后，执行 *updation* ，即更新参数。

参数说明：

 *1* .  *initialization* ：变量初始化。

 *2* .  *expression* ：每次循环前检查，若条件为真，执行循环，条件为假，则退出循环。

 *3* .  *updation* ：每次循环完后执行，用于更新变量。

<center>

![for loop](https://github.com/WBlackhole/CS50_note/blob/master/pic/C-for-Loop.png?raw=true)

</center>

*for* 循环的用法：

1. 常规：
    
    ```C
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", i);
    } 

    /* output:
     * 0
     * 1
     * 2
     * 3
     * 4 
     */ 
    ```

2. 无初始循环：
    
    ```C
    for (;;)
    {
        printf("god!I can't stop!\n");
    }
    ```

<br>

#### **关于i++和++i**

i++和++i的区别在于：

1. i++在**语句结束**后增1。

    ```C
    int i = 1, j = 1;
    j = i++;

    // 执行完两个语句后：j为1，i为2。等效于执行：
    int i = 1, j = 1;
    j = i;
    i = i + 1;
    ```

2. ++i立即增1。

    ```C
    int i = 1, j = 1;
    j = ++i;

    // 执行完两个语句后：j为2，i为2。等效于执行：
    int i = 1, j = 1;
    j = (i = i + 1);
    ```

作为 *for* 循环的 *updation* ，两者实际没区别，因为 *for* 循环的 *updation* 在执行完循环体后才执行。


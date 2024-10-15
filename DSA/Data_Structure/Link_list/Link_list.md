[toc]

<br>

创建时间：2024.8.29
<br>
编辑时间：

<br>

内容参考：

1. [cs50:Lecture 5](https://cs50.harvard.edu/x/2023/notes/5)

2. [GeeksforGeeks:DSA tutorial](https://www.geeksforgeeks.org/learn-data-structures-and-algorithms-dsa-tutorial/)

3. 数据结构教程第五版 主编：李春葆

<br>

## **链表**

<br>

链表是一种由一系列节点相连组成的线性数据结构，其中节点由实际数据和指向下一个节点的指针组成。

<center>

![Singlelinkedlist](https://github.com/WBlackhole/CS50_note/blob/master/pic/Singlelinkedlist.png?raw=true)

</center>

不同于顺序表（数组），链表在内存中是非连续的，而链表的数据结构也非常有利于元素的插入和删除。例如在数组中插入元素，需要将插入位置后的所有元素都后移一位，而链表只需改变相关节点的指针即可。

链表有多种形式，除了常见的单链表外，还有双链表和循环链表。而链表的相关操作，引用数据库sql的CRUD一词：

1. C：create，创建链表。

2. R：read，遍历链表。

3. U：update，更新链表。

4. D：delete，删除链表。

<br>

## **单链表**

<br>

单链表是链表的一种，每个节点都只与下节点相连。

![Singly Linked List](https://raw.githubusercontent.com/WBlackhole/CS50_note/master/pic/Singly-Linked-List.webp)

<br>

### **Create**

<br>

创建链表有两种选择：创建一个含头指针但是无头节点的链表，或创建一个含头节点的链表。头节点，是链表的第一个节点，但是不存储数据（头节点中的数据为垃圾位），第一个数据在头节点后的第一个节点中存储，而该节点也称作首节点。头节点和头指针都可以作为链表的开始索引，区别在于，有头节点的链表在节点的插入和删除上，不用对第一个节点作区分，而只有头指针的链表需要。

创建链表步骤：

1. 定义节点数据类型

2. 创建头指针/头节点


```c
// create head pointer
typedef struct node
{
    int data; // data
    struct node *next; // pointer
}
node;

node *head; // head pointer 
```

```c
// create head node
typedef struct node
{
    int data;
    struct node *next;
}
node;

node *head = malloc(sizeof(node)); // head node
if (head == NULL)
    return 1;

head->next = NULL;
```

<br>

### **Read**

<br>

遍历链表，是链表操作中的重要一环。在遍历过程中可以完成一系列操作，例如打印数据、寻找指定值等等。

遍历步骤：

1. 初始化遍历指针指向首节点

2. 访问节点

3. 指向下一个节点：若节点为NULL，结束遍历；否则回到2.


```c
// head pointer

// version1
node *p = head;
while (p != NULL)
{
    printf("%d\n", p->data);
    p = p->next;
}

// version2
for (node *p = head; p != NULL; p = p->next)
    printf("%d\n", p->data);
```

```c
// head node

// version1
node *p = head->next;
while (p != NULL)
{
    printf("%d\n", p->data);
    p = p->next;
}

// version2
for (node *p = head->next; p != NULL; p = p->next)
    printf("%d\n", p->data);
```

<br>

### **Update**

<br>

更新链表，即为加入新元素。加入新元素有两种情况：

1. 在创建链表时，就有一些需要加入链表的元素。

2. 在创建完链表后，需要在指定位置加入新元素。

第一种情况下，有两种将这些元素加入新链表的方法：头插法和尾插法。头插法即为在链表头部不断插入元素，尾插法则为在链表尾部不断插入元素。无论哪种插入，插入方式都相同：

1. 新节点指向插入位置的节点

2. 插入位置的节点上一个节点指向新节点

> 头插法

```c
#define num 10

int List_data[num];
typedef struct node
{
    int data;
    struct node *next;
}
node;

// input data
for (int i = 0; i < num; i++)
{
    printf("Please input List data of the %d position: ", i + 1);
    scanf("%d", &List_data[i]);
}

node *head = malloc(sizeof(node));
if (head == NULL)
    return 1;

for (int i = 0; i < num; i++)
{
    node *p = malloc(sizeof(node));
    if (p == NULL)
        return 1;
    
    // 头插
    p->next = head->next;
    p->data = List_data[i];
    head->next = p;
}
```

> 尾插法

```c
#define num 10

int List_data[num];
typedef struct node
{
    int data;
    struct node *next;
}
node;

// input data
for (int i = 0; i < num; i++)
{
    printf("Please input List data of the %d position: ", i + 1);
    scanf("%d", &List_data[i]);
}

node *head = malloc(sizeof(node));
if (head == NULL)
    return 1;

node *end = head;
for (int i = 0; i < num; i++)
{
    node *p = malloc(sizeof(node));
    if (p == NULL)
        return 1;
    
    // 尾插
    p->data = List_data[i];
    end->next = p;
    end = p;
}
```

在创建完链表后，需要在指定位置插入元素的步骤：

1. 创建指针p遍历链表：指向指定位置前一个节点或指针为空结束遍历

2. 若p非空：待插元素指向p指向节点的后一个节点，p指向节点指向待插元素；否则退出程序

> 指定位置插入

```c
#define new_position 2
#define new_data 2

int List_data[num];
typedef struct node
{
    int data;
    struct node *next;
}
node;

// head node
node *head = malloc(sizeof(node));
if (head == NULL)
    return 1;

// new node
node *new = malloc(sizeof(node));
if (new == NULL)
    return 1;

node *p = head;
for (int i = 0; i < position - 1 && p != NULL; i++)
    p = p->next;

if (p == NULL)
    return 1;

// insert
new->data = new_data;
new->next = p->next;
p->next = new;
```

<br>

### **Delete**

<br>

删除链表指定元素的步骤：

1. 创建指针p遍历链表：指向指定位置前一个节点或指针为空结束遍历

2. 若p非空：删除p指向节点的后一位节点；否则退出程序

```c
// delete
node *temp = p->next;
p->next = p->next->next;
free(temp);
```

<br>

### **Other-reverse**

<br>

[翻转链表:](https://www.geeksforgeeks.org/reverse-a-linked-list/)

```c
Node *reverse(Node *head)
{
    Node *pre = NULL, *curr = head, *next;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    
    return pre;
}
```

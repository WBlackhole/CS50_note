[toc]


|Creat Time|Last Update|
|:--:|:--:|
|2024.8.30|2024.8.30|


<br>

Reference:

1. [GeeksforGeeks:tree data structure](https://www.geeksforgeeks.org/tree-data-structure/)

2. [cs50:Lecture](https://cs50.harvard.edu/x/2023/notes/5/)

## **树**

树是一种分层数据结构，由一些节点组成，两个节点之间通过边相连。树的数据模型：最顶层的节点为根节点，根节点通过边连接0到n个子树。子树为树，同样具有根节点，根节点下连接0到n个子树，如此嵌套即为树的数据模型。

![Tree Data Structure](/pic/Representation-of-Tree-Data-Structure.webp)

## **树的术语**

![Tree](/pic/Introduction-to-tree-.webp)

1. 父节点：某节点的前驱节点称为该节点的父节点。节点D为节点I、J的父节点。

2. 孩子节点：某节点的后继节点称为该节点的孩子节点。节点I、J为节点D的孩子节点。

3. 根节点：没有父节点的节点为根节点。节点A为根节点。

4. 叶子节点：没有孩子节点的节点为叶子节点。节点I、J、K、F、G、H为叶结点。

5. 兄弟节点：拥有同一个父节点的节点为兄弟节点。节点F、G是节点H的兄弟节点。

6. 祖先节点：某节点到根节点路径上的所有节点及根节点为该节点的祖先节点。节点A、D、B为节点I的祖先节点。

7. 邻居节点：某节点的父节点及孩子节点均为该节点的邻居节点。节点B、I为节点D的邻居节点。

8. 节点的度：某节点到根节点路径上的边数量为节点的度。根节点的度为0。

## **树的作用**

树是一个折中的数据结构，就数据访问速度而言，它比链表快比数组慢，就数据插入和删除而言，它比数组快比链表慢。例如，就二分查找算法而言，链表无法实行二分查找算法，而数据排布合适的二叉树可以。

## **树的操作**

### **Create**





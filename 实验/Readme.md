本文所有代码打包链接：https://download.csdn.net/download/qq_39932172/11211533
<br>

## 实验一：求两个一元多项式P(x)和Q(x)的乘积： P(x)*Q(x)
<br>

**一、实验要求：**
1.通过键盘随机输入两个多项式P（x）和Q（x）的内容。
2.输出结果要有P（x）和Q（x）以及它们的乘积P(x)*Q(x)。

**二、实验程序：**
```cpp
#include<stdio.h>
#include<stdlib.h> 

//多项式中的一项的结构

typedef  struct term{
	double coef; // 定义系数 
 	int expn; // 定义指数 
    struct term* next;  // struct关键字可要可不要 
}PolyNode ,*pPolyNode;

//创建一个保存多项式的链表，返回指向头结点的指针。多项式按指数降序排列
pPolyNode CreatePoly()
{
 PolyNode *p,*q,*s,*head=NULL;
 double coef;
 int expn;

 head=(pPolyNode)malloc( sizeof(PolyNode) );
 if(head==NULL)
 {
  printf("内存分配失败!\n");
  return NULL;
 }
 head->coef =0.0;
 head->expn =0;
 head->next =NULL;

 printf("\n请输入多项式的系数和指数（输入0 0结束）:\n");
 //scanf("%lf%d",&coef,&expn);
 printf("请输入系数:");
 scanf("%lf",&coef);
 printf("请输入指数:");
 scanf("%d",&expn);


 while( (long)coef !=0 && expn !=0 )
 {
  s = (pPolyNode)malloc(sizeof(PolyNode));
  s->coef = coef;
  s->expn = expn;
  
  q=head->next ;
  p=head;
  while(q && expn <q->expn  )
  {
   p=q;
   q=q->next;
  }

  if(q== NULL || expn > q->expn )
  {
   p->next =s;
   s->next =q;
  }
  else
  {
   q->coef+=coef;
  }
  printf("请输入系数:");
  scanf("%lf",&coef);
  printf("请输入指数:");
  scanf("%d",&expn);
 }
 return head;

}

//将多项式逆置,按升幂排列

pPolyNode  Reverse(pPolyNode head)
{
 PolyNode *p,*q,*t;
 p=NULL;
 q=head->next;
 while( q!=NULL )
 {
  t=q->next;
  q->next =p;
  p=q;
  q=t;
 }
 head->next =p;
 return head;
}
//两个多项式相乘
pPolyNode multiply(pPolyNode A,pPolyNode B)
{
 PolyNode *pa,*pb,*pc,*u,*head;
 int k ,maxExp;
 double coef;


 head=(pPolyNode)malloc( sizeof (PolyNode) );
 if(head==NULL)
 {
  printf("内存分配失败!\n");
  return NULL;
 }

 head->coef=0.0;
 head->expn =0;
 head->next =NULL;
 
 if(A->next !=NULL && B->next != NULL)
 {
  maxExp=(A->next) ->expn +(B->next )->expn ;
 }
 else
 {
  return head;
 }
 pc=head;
 B=Reverse (B);

 for(k=maxExp; k>=0; k--)
 {
  pa = A->next ;
  while(pa != NULL && pa->expn >k)
   pa=pa->next ;
  
  pb = B->next ;
  while( pb != NULL && pa != NULL && (pa->expn + pb->expn) < k )
   pb=pb->next;

  coef=0.0;
  while(pa != NULL && pb != NULL )
  {
   if( (pa->expn +pb->expn )==k )
   {
    coef+=pa->coef * pb->coef;
    pa=pa->next;
    pb=pb->next;
   }
   else
   {
    if(( pa->expn  +  pb->expn ) > k )
    {
     pa=pa->next;
    }
    else
    {
     pb=pb->next;
    }
   }
  }
  if( coef != 0.0 )
  {
   u=(pPolyNode)malloc(sizeof(PolyNode));
   u->coef =coef;
   u->expn =k;
   u->next =pc->next;
   pc->next=u;
   pc=u;
  }
 }
 B=Reverse(B);
 return head;
 
}


void Printpoly(pPolyNode head)
{
 PolyNode *p=head->next;

 while(p)
 {
  printf("%1.1f",p->coef);
  if(p->expn )
   printf("*x^%d",p->expn );
  if(p->next && p->next->coef >0)
   printf("+");
  p=p->next;
 }
}

int main()
{
 pPolyNode A,B,C;
 A=CreatePoly();
 printf("A(x)=");
 Printpoly (A);
 printf("\n");

 B=CreatePoly();
 printf("B(x)=");
 Printpoly (B);
 printf("\n");

 C=multiply(A,B);

 printf("C(x)=");
 Printpoly (C);
 printf("\n");

 return 0;
}
```





**三、实验结果：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528134800686.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5OTMyMTcy,size_16,color_FFFFFF,t_70)
<br> 
<br>

## 实验二： 迷宫问题


**一、问题描述：**
以一个m*n的长方形表示迷宫，1和0分别表示迷宫中的通路和障碍。设计一个程序，对任意设定的迷宫，求出一条从入口到出口的通路，或得出没有通路的结论。

**二、实验要求：**
实现一个以链表作存储结构的栈类型，然后编写一个求解迷宫的非递归程序。求得的通路以三元组
（i，j，k）的形式输出，其中：（i，j）指示迷宫中的一个坐标，d表示走到下一坐标的方向
（东、南、西、北）

**三、实验程序：**
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int n,m;

const int maxn=20;

int maxtri[maxn][maxn];
int flag[maxn][maxn];

vector<pair<int,int> > ans;

pair<int ,int> begin_point,end_point;

int X[4]={0,-1,0,1};
int Y[4]={-1,0,1,0};

int p_flag=0;

void DFS(int x,int y)
{
    flag[x][y]=1;
    ans.push_back(make_pair(x,y));
    if(x==end_point.first&&y==end_point.second)
    {
        if(p_flag==0)    p_flag=1;
        //ans.push_back(make_pair(x,y));
        for(int i=0;i<ans.size();i++)
        {
            if(i>0)
            {
                printf("->");
            }
            printf("(%d,%d)",ans[i].first,ans[i].second);
        }
        printf("\n");
        return ;
    }
    for(int i=0;i<4;i++)
    {
        int newx=x+X[i];
        int newy=y+Y[i];
        if(newx>=1&&newx<=n&&newy>=1&&newy<=m&&maxtri[newx][newy]==1&&flag[newx][newy]==0)
        {
            DFS(newx,newy);
            ans.pop_back();
            flag[newx][newy]=0;
        }
    }
    return ;
}

int main()
{
    cout<<"输入m,n "<<endl;
    memset(flag,0,sizeof(flag));
    scanf("%d %d",&n,&m);
    cout<<"输入一个m行n列的矩阵，及其起点与终点(1表示通路，0表示无路)" <<endl; 
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&maxtri[i][j]);
        }
    }
    //画边界
    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
        {
            if(i==0||j==0||i==n+1||j==m+1)
            {
                maxtri[i][j]=0;
            }
        }
    }
    scanf("%d %d",&begin_point.first,&begin_point.second);
    scanf("%d %d",&end_point.first,&end_point.second);
    DFS(begin_point.first,begin_point.second);
    if(p_flag==0)
    {
        printf("-1\n");
    }
    return 0;
}
```


**四、实验结果**：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528135047377.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5OTMyMTcy,size_16,color_FFFFFF,t_70)
<br>
<br>

## 实验三：哈夫曼树/译码器

 <br>
 
**一、实验目的：**
  通过对简单哈夫曼编/译码系统的设计与实现来熟练掌握树型结构在实际问题中的应用
  
**二、实验内容:**  

（一）、问题描述
利用哈夫曼编码进行通信可以大大提高信道利用率，缩短信息传输时间，降低传输成本。但是，这要求在发送端通过一个编码系统对待传数据预先编码，在接收端将传来的数据进行译码，此实验即设计这样的一个简单编/码系统。系统应该具有如下的几个功能：
1. 构造哈夫曼树
从终端读入字符集大小n，以及n个字符和n个权值，建立哈夫曼树，并将它存于文件nodedata.dat中
2. 编码
利用已建好的哈夫曼树（如不在内存，则从文件nodedata.dat中读入），对文件中的正文进行编码，然后将结果存入文件code.dat中
3. 译码
利用已建好的哈夫曼树将文件code.dat中的代码进行译码，结果存入文件textfile.dat中
4. 打印代码文件
将文件code.dat以紧凑的格式显示在终端上，每行50个代码，同时将此字符形式的编码文件写入文件codeprint.dat中
5. 打印哈夫曼树
将已在内存中的哈夫曼树以只管的形式（树或凹入表）显示在终端上

（二）、结构设计
1. 构造哈夫曼树时使用静态链表作为哈夫曼树的存储
在构造哈夫曼树时，设计一个结构体数组HuffNode保存哈夫曼树中各结点的信息，根据二叉树的性质可知，具有n个叶子结点的哈夫曼树共有2n-1个结点，所以数组HuffNode的大小设置为2n-1，描述结点的数据类型为：
typedef struct
{
int weight;//结点权值
int parent;
int lchild;
int rchild;
char inf;
}HNodeType;

2. 求哈夫曼编码时使用一维结构数组HuffCode来存储编码信息
求哈夫曼编码，就是在已建立的哈夫曼树中，从叶子结点开始，沿结点的双亲链域回退到根结点，每回退一步，就走过了哈夫曼树的一个分支，从而得到一位哈夫曼码值，由于一个字符的哈夫曼编码是从根结点到相应叶子结点所经过的路径上各分支所组成的0、1序列，因此先得到的分支代码为所求编码的低位码，后得到的分支代码位所求编码的高位码，所以设计如下数据类型：
typedef struct
{
int bit[MAXBIT]；
int start；
}HcodeType

（三）、函数设计
1. 构建哈夫曼树函数
从键盘接收字符集大小n，以及n个字符和n个权值；使用得到的数据按照教材中的构造哈夫曼树的算法构造哈夫曼树，并将这个结构体数组存于文件hfmtree.dat中
2. 哈夫曼编码函数
将字符与0、1代码串的一一对应关系打印到屏幕上，然后从键盘读入要编码的字符串，根据构建的哈夫曼树进行编码，将编码结果显示到屏幕上，并存入code.dat中
3. 译码函数
将code.dat文件中的内容进行译码，显示在屏幕上，同时将译码结果存入textfile.dat中
4. 哈夫曼树打印函数
将哈夫曼树以凹入表的形式打印出来

**三、程序代码**
```cpp
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#define MaxBit 10
#define Maxvalue 100//应该大于权重之和
#define Maxleaf 100
#define Maxnode Maxleaf*2-1

using namespace std;

typedef struct
{
    int weight;
    int parent;
    int lchild;
    int rchild;
    char inf;
} HNodeType,*HuffmanTree;//储存哈夫曼树中各结点信息
struct HcodeType
{
    int bit[MaxBit];
    int start;
};//储存哈夫曼编码信息

void Creat_Haffmantree(int &n)//建树
{
    HNodeType *HaffNode=new HNodeType[2*n-1];
    int i,j;
    int m1,m2,x1,x2;
    for(i=0; i<2*n-1; i++)//初始化
    {
        HaffNode[i].weight=0;
        HaffNode[i].parent=-1;
        HaffNode[i].lchild=-1;
        HaffNode[i].rchild=-1;
        HaffNode[i].inf='0';
    }
    for(i=0; i<n; i++)
    {
        cout<<"请输入字符"<<endl;
        cin>>HaffNode[i].inf;
        cout<<"请输入该字符的权值"<<endl;
        cin>>HaffNode[i].weight;
    }

    /*
       x1记录权值最小结点的下标，x2记录次小下标，m1记录最小权值，m2记录次小权值
       让每个结点的左孩子权值小于右孩子

       屏幕显示的双亲和左右孩子均为其在结构体数组中的下标值
       */
    for(i=0; i<n-1; i++)
    {
        m1=m2=Maxvalue;
        x1=x2=0;
        for(j=0; j<n+i; j++) //选取最小和次小
        {
            if(HaffNode[j].parent==-1 && HaffNode[j].weight<m1)
            {
                m2=m1;
                x2=x1;
                m1=HaffNode[j].weight;
                x1=j;
            }
            else
            {
                if(HaffNode[j].parent==-1 && HaffNode[j].weight<m2)
                {
                    m2=HaffNode[j].weight;
                    x2=j;
                }
            }
        }

        //将找到的最小和次小合并，创造其父母结点
        HaffNode[x1].parent=n+i;
        HaffNode[x2].parent=n+i;
        HaffNode[n+i].weight=HaffNode[x1].weight+HaffNode[x2].weight;
        HaffNode[n+i].lchild=x1;
        HaffNode[n+i].rchild=x2;
        HaffNode[n+i].inf=NULL;
    }

    cout<<"显示存储的哈弗曼树信息:"<<endl;
    cout<<"权值 左孩子 右孩子 双亲"<<endl;
    for(i=0; i<2*n-1; i++)
    {
        cout<<HaffNode[i].weight<<" ";
        cout<<HaffNode[i].lchild<<" ";
        cout<<HaffNode[i].rchild<<" ";
        cout<<HaffNode[i].parent<<" ";
        cout<<HaffNode[i].inf<<endl;
    }

//写入文件
    fstream outfile1;
    outfile1.open("D:\\nodedata.dat",ios::out|ios::trunc|ios::binary);//建立进行写入的文件
    if(!outfile1) //没有创建成功则显示相应信息
    {
        cout<<"nodedata.dat文件不能打开"<<endl;
        abort();
    }
    for(i=0; i<2*n-1; i++) //将内存中从HaffNode[i]地址开始的sizeof(HaffNode[i])的内容写入文件中
        outfile1.write((char*)&HaffNode[i],sizeof(HaffNode[i]));
    outfile1.close ();//关闭文件
    delete []HaffNode;
}

void HaffCode(int &n)//哈夫曼编码
{
    HNodeType *HaffNode=new HNodeType[Maxnode];
    HcodeType *HaffCode=new HcodeType[Maxleaf];
    HcodeType cd;
    int i,j,c,p;
    fstream in("D:\\nodedata.dat",ios::in|ios::binary);
    in.read((char*)HaffNode,(2*n-1)*sizeof(HNodeType));
    in.close();
    fstream outfile;
    outfile.open("D:\\codedata.dat",ios::out|ios::binary);//建立进行写入的文件
    for(i=0; i<n; i++)
    {
        cd.start=n-1;//编码结束符的位置
        c=i;
        p=HaffNode[c].parent;
        while(p!=-1)
        {
            if(HaffNode[p].lchild==c)
                cd.bit[cd.start]=0;
            else
                cd.bit[cd.start]=1;
            cd.start--;
            c=p;
            p=HaffNode[c].parent;
        }
        for(j=cd.start+1; j<n; j++)
            HaffCode[i].bit[j]=cd.bit[j];
        HaffCode[i].start=cd.start;
    }
    for(i=0; i<n; i++)
    {
        outfile<<HaffNode[i].inf;
        for(j=HaffCode[i].start+1; j<n; j++)
            outfile<<HaffCode[i].bit[j];
    }

    cout<<"字符信息--编码信息"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<HaffNode[i].inf<<"---";
        for(j=HaffCode[i].start+1; j<n; j++)
            cout<<HaffCode[i].bit[j];
        cout<<endl;
    }
    outfile.close ();

    cout<<"请输入要编码的字符串,基本元素为（";
    for(i=0; i<n; i++)
        cout<<HaffNode[i].inf<<",";
    cout<<")"<<endl;
    char inf[100];
    cin>>inf;
    int f=strlen(inf);//记录要编码字符串的长度

    fstream outfile1;
    outfile1.open("D:\\code.dat",ios::out|ios::binary);//建立进行写入的文件
    if(!outfile1)
    {
        cout<<"code.dat文件不能打开!"<<endl;
        abort();
    }
    else
    {
        cout<<endl;
        cout<<"字符串编码后为:";
        for(int x=0; x<f; x++)
        {
            for(i=0; i<n; i++)
            {
                if(inf[x]==HaffNode[i].inf)
                {
                    for(j=HaffCode[i].start+1; j<n; j++)
                    {
                        outfile1.write((char*)&HaffCode[i].bit[j],sizeof(HaffCode[i].bit[j]));
                        cout<<HaffCode[i].bit[j];
                    }

                }

            }

        }

    }
    cout<<endl;
    cout<<"编译后的代码串已经存入code.dat文件中!"<<endl;
    cout<<endl;
    outfile1.close();
    delete []HaffNode;
    delete []HaffCode;
}

void decode( int &n)//解码
{
    int i;
    HNodeType *HaffNode=new HNodeType[2*n-1];
    fstream infile1;
    infile1.open("D:\\nodedata.dat",ios::in|ios::binary);//读出哈夫曼树
    if(!infile1)
    {
        cout<<"nodedata.dat文件不能打开"<<endl;
        abort();
    }
    for(i=0; i<2*n-1; i++)
        infile1.read((char*)&HaffNode[i],sizeof(HNodeType));
    infile1.close();
    int tempcode[100];
    int num=0;
    for(i=0; i<100; i++)
        tempcode[i]=-1;
    HcodeType *Code=new HcodeType[n];
    fstream infile2;//读编码
    infile2.open("D:\\code.dat",ios::in|ios::binary);
    while(!infile2.eof())
    {
        infile2.read((char*)&tempcode[num],sizeof(tempcode[num]));
        num++;
    }
    infile2.close();
    num--;

    cout<<"从文件中读出的编码为"<<endl;

    for(i=0; i<num; i++)
        cout<<tempcode[i];
    cout<<endl;
    int m=2*n-2;
    i=0;
    cout<<endl;

    cout<<"译码后为:"<<endl;

    fstream outfile;
    outfile.open("D:\\textfile.txt",ios::out);
    if(!outfile)
    {
        cout<<"textfile.txt文件不能打开!"<<endl;
        abort();
    }
    while(i<num)// 小于字符串的长度
    {
        while(HaffNode[m].lchild!=-1&&HaffNode[m].rchild!=-1)
        {
            if(tempcode[i]==0)
            {
                m=HaffNode[m].lchild;
                i++;
            }
            else if(tempcode[i]==1)
            {
                m=HaffNode[m].rchild;
                i++;
            }
        }
        cout<<HaffNode[m].inf;
        outfile<<HaffNode[m].inf;
        m=2*n-2;
    }
    cout<<endl;
    outfile.close();

    cout<<"译码后的结果已经存入textfile.txt中!"<<endl;
    delete []HaffNode;
}


//以凹入法显示哈夫曼树
void print(HNodeType *T,int n,int nlayer)
{//n为根结点的编号，nlayer为根结点所在的层次
    int i;
    if(T[n].lchild==-1 && T[n].rchild==-1)
    {
        for(i=0; i<2*nlayer; i++)
            cout << " ";
        cout << T[n].inf <<endl;
        return;
    }
    else
    {
        print(T,T[n].lchild,nlayer+1);//递归打印左子树
        for(i=0; i<2*nlayer; i++)
            cout << " ";
        cout <<T[n].weight<<endl;//打印根结点
        print(T,T[n].rchild,nlayer+1);//递归打印右子树
    }
}

int main()
{
    int n;
    cout<<"************* 欢迎进入编/译码系统！*********************"<<endl;
    int ch1;
    do
    {
        cout<<" 1.建树"<<endl;
        cout<<" 2:编码，并显示字符和对应的编码"<<endl;
        cout<<" 3:译码"<<endl;
        cout<<" 4:打印哈夫曼树"<<endl;
        cout<<" 0:退出"<<endl;
        cout<<"********************************************************"<<endl;
        cout<<"请选择(0~4):";
        cin>>ch1;
        while(!(ch1<=4&&ch1>=0)) //输入不在0到4之间无效
        {
            cout<<"数据输入错误，请重新选择(0~4):";
            cin>>ch1;
        }
        switch(ch1)
        {
        case 1:
        {
            cout<<"请输入编码个数:";//叶子结点个数
            cin>>n;
            Creat_Haffmantree(n);
            break;
        }
        case 2:
            HaffCode(n);
            break;
        case 3:
            decode(n);
            break;
        case 4:
            //从文件中读取树
            HNodeType *HaffNode=new HNodeType[Maxnode];
            fstream in("D:\\nodedata.dat",ios::in|ios::binary);
            in.read((char*)HaffNode,(2*n-1)*sizeof(HNodeType));
            in.close();
            HNodeType *T = HaffNode;
            print(T,2*n-2,0);
            break;

        }
    }
    while(ch1!=0);
    return 0;
}
```

**四、程序运行结果:**

在建树时输入6个字符及其权值，A--1，B--3，C--5，D--9，E--18，T--27测试结果如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528135759407.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019052813581026.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5OTMyMTcy,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528135847712.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5OTMyMTcy,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528135908435.png)![在这里插入图片描述](https://img-blog.csdnimg.cn/2019052813591967.png)
<br>
<br> 
 

 

## 实验四：用迪杰斯特拉算法编写一个校园导游图
<br>

**一、实验目的：**
 用迪杰斯特拉算法思想实现校园导游图，为游客提供一条从当前位置到目的地的最短路径
 
**二、实验思路:**

- **Step1:** 用邻接矩阵作为校园平面图的存储结构，每两个景点之间的距离作为边的权值，首先定义一个初始化函数，初始化邻接矩阵
- **Step2:** 定义三个一维数组，一个bool类型数组final[]用来记录从v0到vi是否已经确定了最短路径，是则记final[i]=true,否记final[i]= flase；一个int 类型数组P[]用来记录从v0到vi的当前最短路径上的vi的直接前驱顶点编号，若v 到vi之间有边则记P[i] = v的编号，否则记P[i] = -1；最后一个数组D[]用来记录从v0到vi之间的最短路径长度，存在则记v0到vi之间边的权值或者权值和，否则记为INFINITY
- **Step3**:定义一个求最短路径的函数，传入的参数为图、起点、数组P、数组D
然后进行n-1次for循环，找出vo到其余n-1个顶点之间的最短路径，比较当前D[]数组中最小值，找到最小值的编号v，该编号就是从v0出发到所有顶点中距离最短的顶点编号，然后把final[v]的值置为true。说明从v0出发到顶点v已经找到最短路径；
- **Step4**:更新D[]数组
- **Step5**:循环2、5步得到数组D

**三、实验代码:**
```cpp
#include<iostream>
#include<stdlib.h>
#include<string>
#define INFINITY 100000
#define MAX_VERTEX_NUM 20

using namespace std;

typedef struct ArcCell
{
    int adj;
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    int vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum,arcnum;
} MGraph;

MGraph G;//把图定义为全局变量

void CreateUDN(MGraph &G)
{
    //采用邻接矩阵法构造无向网G
    G.vexnum=15;
    int i,j;
    for(i=0; i<G.vexnum; ++i)
        G.vexs[i]=i;//将1-15个顶点向量存入数组

    for(i=0; i<G.vexnum; ++i)
        for(j=0; j<G.vexnum; ++j)
            G.arcs[i][j].adj=INFINITY;//初始化邻接矩阵，INFINITY表示两点之间无法到达

    //将校园路线的邻接矩阵输入
    for(i=0; i<G.vexnum; ++i)
        G.arcs[i][i].adj=0;
    G.arcs[1][0].adj=10;
    G.arcs[2][0].adj=310;
    G.arcs[2][1].adj=310;
    G.arcs[3][2].adj=10;
    G.arcs[4][2].adj=50;
    G.arcs[5][2].adj=500;
    G.arcs[5][4].adj=600;
    G.arcs[6][5].adj=200;
    G.arcs[7][3].adj=100;
    G.arcs[8][2].adj=70;
    G.arcs[8][4].adj=100;
    G.arcs[9][2].adj=500;
    G.arcs[9][8].adj=400;
    G.arcs[10][3].adj=250;
    G.arcs[10][7].adj=200;
    G.arcs[11][2].adj=800;
    G.arcs[11][8].adj=600;
    G.arcs[12][10].adj=400;
    G.arcs[13][2].adj=1000;
    G.arcs[13][12].adj=350;
    G.arcs[14][2].adj=1500;
    G.arcs[14][11].adj=500;
    G.arcs[14][12].adj=300;
    G.arcs[14][13].adj=150;
    for(i=0; i<G.vexnum; ++i)
        for(j=0; j<i; ++j)
            G.arcs[j][i].adj= G.arcs[i][j].adj;
}

void ShortestPath_DIJ(MGraph G,int v0,int p[][MAX_VERTEX_NUM],int D[])
{
 //S集为已求得的最短路径的终点集合，设置一个数组final,当final[v]=true时，即已经求得从v0到v的最短路径
//D数组记录弧的权值
    int i,j,k,w,v,min;
    bool final[15];
    for(v=0; v<G.vexnum; v++) //初始化
    {
        final[v]=false;
        D[v]=G.arcs[v0][v].adj;
        for(w=0; w<G.vexnum; w++)
            p[v][w]=-1;
        if(D[v]<INFINITY)
        {
            p[v][0]=v0;
            p[v][1]=v;
        }
    }
    D[v0]=0;
    final[v0]=true;
    //开始主循环
    for(i=0; i<G.vexnum; ++i)
    {
        min=INFINITY;
        for(w=0; w<G.vexnum; w++)
        {
            if(!final[w])
                if(D[w]<min)
                {
                    v=w;
                    min=D[w];
                }
        }
        final[v]=true;//离v0最近的v加入S集
        for(w=0; w<G.vexnum; w++) //更新当前路径
        {
            if(!final[w] && (min+G.arcs[v][w].adj < D[w]))
            {
                D[w]=min+G.arcs[v][w].adj;
                for(j=0; j<G.vexnum; j++)
                {
                    p[w][j]=p[v][j];
                    if(p[w][j]==-1)//在p[w][]第一个等于-1的地方加上顶点w
                    {
                        p[w][j]=w;
                        break;
                    }
                }
            }
        }

    }//for
}

int main()
{
    int ch1,ch2,j,n;
    int D[15];
    int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    CreateUDN(G);
    while(1)
    {
        cout <<endl;
        cout <<"********** 欢迎来到中国海洋大学校园导游系统！**********"<<endl;
        cout <<"*******************************************************"<<endl;
        cout <<"********** 1.景点信息查询******************************"<<endl;//1、2系统还没有完善
        cout <<"********** 2.显示景点视图******************************"<<endl;
        cout <<"********** 3.最短路径查询******************************"<<endl;
        cout <<"********** 0.退出系统**********************************"<<endl;
        cout <<"********** ********************************************"<<endl;
        cout <<"请选择："<<endl;
        cin >> n;
        if(n==3)
        {
            cout <<"********** 以下是我们的校园景点编号 *******************" <<endl;
            cout <<"0.北门    1.校医院   2.北区宿舍楼     3.北区操场  4.北区食堂  5.东区操场"<<endl;
            cout <<"6.东门    7.大学生活动中心       8.第三教学区     9.屋子顶      10.西门"<<endl;
            cout <<"11.信息学院     12.图书馆      13.行远楼      14.南门 "<<endl;
            cout <<"********** 请输入你的当前位置 ************************"<<endl;
            cin >> ch1;
            cout <<"********** 请输入你的目的地 **************************"<<endl;
            cin >> ch2;

            ShortestPath_DIJ(G,ch1,p,D);
            if(D[ch2]==-1)
            {
                cout<<ch1<<"到"<<ch2<<"之间无最短路径！"<<endl;
                 exit(0);
            }
            cout<< ch1 <<"到"<< ch2 <<"的最短距离为："<< D[ch2]<<endl;
            cout <<"最短路径为："<<endl;
            for(j=0; j<G.vexnum; j++)
            {
                if(p[ch2][j]>-1)
                    cout<<G.vexs[p[ch2][j]]<<"-->";
            }
            cout <<endl;
            }
        else if(n==0)
        {
            cout << ">>>退出成功！" << endl;
            exit(0);
        }
    }
}
```
<br>

**四、程序运行结果:**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528140348723.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5OTMyMTcy,size_16,color_FFFFFF,t_70)

 

/*
����һ�����ַ������У���ASCII���ӡ��������״���㷨��
��Linux����̨��д�����⣬��DOS�����е��ҡ�
���ò�α鷨��
�㷨׾�ӣ�������ѧ������ϰ��������Ҳ�ǳ�ѧ�ߣ���ѧ���ݽṹ���պ�ѧ�����������һ�£�
��·���ң��������е����ͷ�󣬸㼸����������⣬ȴ��֪���乹����״��
�����ͼ�Σ��У��������۵�ģ�ȴ�е�ƫ�뱾�µ�ѧϰĿ�ģ�ֻ�����ַ���ӡ��
linux�����д�ӡ�Ļ����ԣ��ģϣ����е㲻�ȶ���������и��õ��㷨һ�����ߴͽ̡�
�ҵģѣѣ�137241638 mail��hnflcp@139.com
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

#include<iostream>
#include<string>
#include<fstream>
#include<ostream>

using namespace std;

//Pstart�Ƕ������������һ���е�λ�ã�һ�����ܴ�ӡ124���ַ���ȡ��1/2��
//��������������Ļ�����������ı��ļ�� aa.exe>>aa.txt
#define Pstart 62

typedef struct node //�������洢�ṹ
{
	int    key;
	int    data;
	struct node *lchild,
		*rchild;
}BTNode;
typedef struct pnode        //Ϊ��ӡ����������һ���ṹ��
{
	int key;                   //�ؼ������ݣ�
	int data;                  //�ؼ������ݣ�
	struct pnode *lchild,      //����
		*rchlid,      //�Һ���
		*parent;      //���ڵ�
	int lrflag,                //��Ǳ��ڵ������ӣ����ڣ�ʱ���������Һ��ӣ����ڣ�ʱ��
		space,                 //�洢���ڵ��ӡλ��
		level;                 //�洢���ڵ����ڲ�Ρ�
}PBTNode;

/*������������
�����ű�ʾ����ʾ�������ַ�����������������
*/
BTNode* CreateBTNode(char *s)
{
	char ch;
	BTNode *p = NULL,
		*b = NULL,
		*ps[MaxSize];
	int top = -1,
		tag = -1;
	ch = *s;
	while (ch)
	{
		switch (ch)
		{
		case '(':ps[++top] = p; tag = 1; break;
		case ',':tag = 2; break;
		case ')':top--; break;
		default:
			p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)
				b = p;
			else
			{
				switch (tag)
				{
				case 1:ps[top]->lchild = p; break;
				case 2:ps[top]->rchild = p; break;
				}
			}
		}
		ch = *(++s);
	}
	return b;
}

//���ʺű�ʾ����ӡ��������
void DispBTNode(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);
			if (b->rchild != NULL)printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}
int BTNodeHeight(BTNode *b)
{
	int lchildh, rchildh;
	if (b == NULL)return 0;
	else
	{
		lchildh = BTNodeHeight(b->lchild);
		rchildh = BTNodeHeight(b->rchild);
		return (lchildh>rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}

/*����һ����������ӡ������Ϣ��
ֻ��int CreatePBTNode(BTNode *b,PBTNode *pqu[])����*/
void SetPBTNodeInfo(BTNode *b, PBTNode *parent, PBTNode *pb, int level, int lrflag)
{
	int f = 3;
	pb->data = b->data;
	pb->key = b->key;
	pb->parent = parent;
	pb->level = level;
	pb->lrflag = lrflag;
	pb->space = -1;
}

/*�ò�α�������BTNode�ṹ�洢�Ķ�����ת��Ϊ��PBTNode�ṹ�Ķ�����*/
int CreatePBTNode(BTNode *b, PBTNode *pqu[])
{
	BTNode *p;
	BTNode *qu[MaxSize];
	int front = -1,
		rear = -1;
	rear++;
	qu[rear] = b;
	pqu[rear] = (PBTNode*)malloc(sizeof(PBTNode));
	SetPBTNodeInfo(b, NULL, pqu[rear], 1, -1);
	while (rear != front)
	{
		front++;
		p = qu[front];
		if (p->lchild != NULL)
		{
			rear++;
			qu[rear] = p->lchild;
			pqu[rear] = (PBTNode*)malloc(sizeof(PBTNode));
			SetPBTNodeInfo(p->lchild, pqu[front], pqu[rear], pqu[front]->level + 1, 0);
		}
		if (p->rchild != NULL)
		{
			rear++;
			qu[rear] = p->rchild;
			pqu[rear] = (PBTNode*)malloc(sizeof(PBTNode));
			SetPBTNodeInfo(p->rchild, pqu[front], pqu[rear], pqu[front]->level + 1, 1);
		}
	}
	return rear;
}

//��ӡһ���㣬���ò����븸��������·����
void PBTNodePrint(PBTNode *pb[], int n, int h)
{
	ofstream fp("aaa.txt");
	int l = -1,
		r = 0,
		i, j, k,
		end;
	char c;
	PBTNode *p;
	if (n <= 0 || h <= 0)
	{
		return;
	}
	else if (n == 1)
	{
		for (i = 0; i<pb[0]->space; i++)
			fp<<" ";
		fp<< pb[0]->data;
		fp<<"\n";
		return;
	}
	h = h - pb[0]->level + 2;
	for (k = 0; k<h; k++)
	{
		j = 0;
		l--;
		r++;

		for (i = 0; i<n; i++)//��ӡ����
		{
			p = pb[i];
			end = (p->lrflag == 0) ? l : r;
			end += p->parent->space;
			for (; j<end; j++)
				fp<<" ";
			c = (p->lrflag == 0) ? '/' : '\\';
			fp<< c;
		}
		fp<<"\n";
	}
	for (i = 0; i<n; i++)//���㱾�����ӡλ��
	{
		p = pb[i];
		if (p->lrflag == 0)
			p->space = p->parent->space + l;
		else
			p->space = p->parent->space + r;
	}
	for (i = 0, j = 0; i<n; i++)//��ӡ�ؼ�������
	{
		p = pb[i];
		for (; j<p->space; j++)
			fp<<" ";
		fp<< p->data;
	}
	fp<<"\n";

	fp.close();
}
//ѭ����ӡ���в������
void DispBTree(BTNode *b)
{
	int n, i, j, high,
		level;
	PBTNode *p;
	PBTNode *pqu[MaxSize];
	PBTNode *levelpqu[MaxSize];
	n = CreatePBTNode(b, pqu);
	high = BTNodeHeight(b);
	j = 0;
	level = 1;
	pqu[0]->space = Pstart;
	for (i = 0; i <= n; i++)
	{
		p = pqu[i];
		if (p->level == level)
		{
			levelpqu[j] = p;
			j++;
		}
		else
		{
			PBTNodePrint(levelpqu, j, high);
			level = p->level;
			j = 0;
			levelpqu[j] = p;
			j++;
		}
	}
	PBTNodePrint(levelpqu, j, high);

}
void main()
{
	int iDepth = 0,
		iWidth = 0,
		iCount = 0;
	char *str1 = "A(B(D,E(H,X(J,K(L,M(T,Y))))),C(F,G(X,I)))";
	char *str2 = "A(B(D(,G)),C(E,F))";
	BTNode *b = CreateBTNode(str2);
	DispBTNode(b); printf("\n");
	iDepth = BTNodeHeight(b);
	printf("Depth:%d\n", iDepth);
	DispBTree(b);
	system("pause");
}



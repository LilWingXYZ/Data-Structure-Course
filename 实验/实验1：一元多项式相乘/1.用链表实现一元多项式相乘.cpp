#include<stdio.h>
#include<stdlib.h> 

//����ʽ�е�һ��Ľṹ

typedef  struct term{
 double coef; // ����ϵ�� 
 int expn; // ����ָ�� 
        struct term* next;  // struct�ؼ��ֿ�Ҫ�ɲ�Ҫ 
}PolyNode ,*pPolyNode;

//����һ���������ʽ����������ָ��ͷ����ָ�롣����ʽ��ָ����������
pPolyNode CreatePoly()
{
 PolyNode *p,*q,*s,*head=NULL;
 double coef;
 int expn;

 head=(pPolyNode)malloc( sizeof(PolyNode) );
 if(head==NULL)
 {
  printf("�ڴ����ʧ��!\n");
  return NULL;
 }
 head->coef =0.0;
 head->expn =0;
 head->next =NULL;

 printf("\n���������ʽ��ϵ����ָ��������0 0������:\n");
 //scanf("%lf%d",&coef,&expn);
 printf("������ϵ��:");
 scanf("%lf",&coef);
 printf("������ָ��:");
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
  printf("������ϵ��:");
  scanf("%lf",&coef);
  printf("������ָ��:");
  scanf("%d",&expn);
 }
 return head;

}

//������ʽ����,����������

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
//��������ʽ���
pPolyNode multiply(pPolyNode A,pPolyNode B)
{
 PolyNode *pa,*pb,*pc,*u,*head;
 int k ,maxExp;
 double coef;


 head=(pPolyNode)malloc( sizeof (PolyNode) );
 if(head==NULL)
 {
  printf("�ڴ����ʧ��!\n");
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

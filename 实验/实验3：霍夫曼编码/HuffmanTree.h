#pragma once
/* c6-7.h �շ������ͺշ�������Ĵ洢��ʾ */
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
	TElemType data;
}HTNode, *HuffmanTree; /* ��̬��������洢�շ����� */
typedef char **HuffmanCode; /* ��̬��������洢�շ�������� */


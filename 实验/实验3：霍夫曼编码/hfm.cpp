#include"Declaraction .h"
typedef char TElemType;
#include"HuffmanTree.h"
#include<iostream>
#include<string>
#include<fstream>
#include<ostream>

using namespace std;

//struct HfmCharacter{
//	char character;
//	int weight;
//	char Hcode[100000];
//};

int min1(HuffmanTree t, int i)
{ /* ����void select()���� */
	int j, flag;
	unsigned int k = UINT_MAX; /* ȡkΪ��С�ڿ��ܵ�ֵ */
	for (j = 1; j <= i; j++)
		if (t[j].weight<k&&t[j].parent == 0)
			k = t[j].weight, flag = j;
	t[flag].parent = 1;
	return flag;
}

void select(HuffmanTree t, int i, int *s1, int *s2)
{ /* s1Ϊ��С������ֵ�����С���Ǹ� */
	int j;
	*s1 = min1(t, i);
	*s2 = min1(t, i);
	if (*s1>*s2)
	{
		j = *s1;
		*s1 = *s2;
		*s2 = j;
	}
}

void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, char *character, int n) /* �㷨6.12 */
{ /* w���n���ַ���Ȩֵ(��>0),����շ�����HT,�����n���ַ��ĺշ�������HC */
	int m, i, s1, s2, start;
	unsigned c, f;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); /* 0�ŵ�Ԫδ�� */
	for (p = *HT + 1, i = 1; i <= n; ++i, ++p, ++w, ++character)
	{
		(*p).weight = *w;
		(*p).data = *character;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; ++i, ++p)
		(*p).parent = 0;
	for (i = n + 1; i <= m; ++i) /* ���շ����� */
	{ /* ��HT[1~i-1]��ѡ��parentΪ0��weight��С���������,����ŷֱ�Ϊs1��s2 */
		select(*HT, i - 1, &s1, &s2);
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	/* ��Ҷ�ӵ���������ÿ���ַ��ĺշ������� */
	*HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	/* ����n���ַ������ͷָ������([0]����) */
	cd = (char*)malloc(n * sizeof(char)); /* ���������Ĺ����ռ� */
	cd[n - 1] = '\0'; /* ��������� */
	for (i = 1; i <= n; i++)
	{ /* ����ַ���շ������� */
		start = n - 1; /* ���������λ�� */
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)
			/* ��Ҷ�ӵ�3����������� */
			if ((*HT)[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));
		/* Ϊ��i���ַ��������ռ� */
		strcpy((*HC)[i], &cd[start]); /* ��cd���Ʊ���(��)��HC */
	}
	free(cd); /* �ͷŹ����ռ� */
}


void HuffmanDeCoding(HuffmanTree HT,string code,int n) {

	ofstream fp("TextFile.txt");
	int m = 2 * n - 1;
	for (int i = 0; i < code.length(); i++) {

		m = (code[i] == '0') ? HT[m].lchild : HT[m].rchild;

		if (HT[m].lchild==0||HT[m].rchild==0) {
			fp << HT[m].data;
			m = 2 * n - 1;
		}
	}
	fp.close();
}

void PrintTreeInFile(HuffmanTree ht, int n, int nLayer)       //�����������
{
	ofstream fp("TreePrint.txt", ios::app);
	int i;
	if (ht[n].lchild == 0 || ht[n].rchild == 0) {
		for (i = 0; i<2*nLayer; i++)
			fp<<"   ";
		fp<<ht[n].data<<"\n";
		fp.close();
		return;
	}
	PrintTreeInFile(ht, ht[n].lchild, nLayer + 1);
	for (i = 0; i<2*nLayer; i++)
		fp << "   ";
	fp << ht[n].weight << "\n";
	fp.close();
	PrintTreeInFile(ht, ht[n].rchild, nLayer + 1);
	
	
}

void PrintTree(HuffmanTree ht, int n, int nLayer)       //�����������
{
	int i;
	if (ht[n].lchild == 0 || ht[n].rchild == 0) {
		for (i = 0; i<2 * nLayer; i++)
			cout << "   ";
		cout << ht[n].data << "\n";
		return;
	}
	PrintTree(ht, ht[n].lchild, nLayer + 1);
	for (i = 0; i<2 * nLayer; i++)
		cout << "   ";
	cout << ht[n].weight << "\n";
	PrintTree(ht, ht[n].rchild, nLayer + 1);


}

void Initialization(HuffmanTree *HT, HuffmanCode *HC, int n) {
	cout << "�������¹��������������������б��룺" << endl;

	int w[] = { 80,15,30,40,130,20,15,60,65,5,5,35,30,70,80,20,2,65,60,90,30,10,15,5,20,2,140};
	char c[27];

	for (int i = 0; i < 26; i++) {
		c[i] = i + 'a';
	}
	c[26] = ' ';
	cout << "�ַ���\t\t" << " Ȩֵ��" << endl;
	for (int i = 0; i < 27; i++) {
		cout << c[i] << "\t\t" << w[i] << endl;
	}

	HuffmanCoding(HT, HC, w, c, n);

	ofstream fpHfm("hfmTree.txt");
	for (int i = 1; i <= n; i++) {
		fpHfm << (*HC)[i] << endl;
	}
	fpHfm.close();
}

string ReadLine(char *filename, int line)
{
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(filename, ios::in);

	while (getline(file, temp) && i<line - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

void Encoding(HuffmanTree HT,int n) {
	ifstream in("ToBeTran.txt");
	string s1, s2;
	while (getline(in, s1))
	{
		s2 += s1;
		s2 += '\n';
	}


	ofstream fp("CodeFile.txt");

	for (int i = 0; i < s2.length() - 1; i++) {
		if (s2[i] == ' ') {
			fp << ReadLine("hfmTree.txt", 27);
		}
		else {
			fp << ReadLine("hfmTree.txt", s2[i] - 'a' + 1);
		}
	}
	fp.close();

}

void Decoding(HuffmanTree HT, int n) {

	fstream in("CodeFile.txt");
	string s1, s2;
	while (getline(in, s1))
	{
		s2 += s1;
		s2 += '\n';
	}
	HuffmanDeCoding(HT, s2, n);

}

void print() {
	fstream in("CodeFile.txt");
	string s1, s2;
	while (getline(in, s1))
	{
		s2 += s1;
		s2 += '\n';
	}

	for (int i = 0; i < s2.length() - 1; i++) {
		cout << s2[i];
		if ((i + 1) % 50 == 0)
			cout << endl;
	}
	cout << endl;

	fstream in2("ToBeTran.txt");
	s1 = s2 = "";
	while (getline(in2, s1))
	{
		s2 += s1;
		s2 += '\n';
	}
	ofstream fp("CodePrin.txt");
	fp << s2;
	fp.close();
}


void main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int n = 27;
	while (1) {

		cout << "��ѡ���ܣ�" << endl;
		cout << "1.Initialization" << endl;
		cout << "2.Encoding" << endl;
		cout << "3.Decoding" << endl;
		cout << "4.print" << endl;
		cout << "5.PrintTree" << endl;

		int choice;
		cin >> choice;

		if (choice == 1) {
			Initialization(&HT, &HC, n);
		}
		if (choice == 2) {
			Encoding(HT, n);
		}
		if (choice == 3) {
			Decoding(HT, n);
		}

		if (choice == 4) {
			print();
		}

		if (choice == 5) {
			PrintTree(HT, n * 2 - 1, 1);
			PrintTreeInFile(HT, n * 2 - 1, 1);
		}

	}
	system("pause");
}



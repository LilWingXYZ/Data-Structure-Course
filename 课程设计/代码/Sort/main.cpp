#include<iostream>
#include<ctime>
#include<math.h>
#define N 100001
using namespace std;

long long sum[5][10][3];
int randNum[N];
int randNum1[N - 1];

//��ʾ����
void show(int randNum[N]) {
	for (int i = 1; i < N; i++)
		printf("%6d", randNum[i]);
	cout << endl;
}

//���������
void proRandNum(int *randNum) {

	randNum[0] = 0;
	srand((unsigned)clock());
	for (int i = 1; i < N; i++)
		randNum[i] = rand();
}
//��������
void proPosiNum(int *posiNum) {

	posiNum[0] = 0;
	for (int i = 1; i < N; i++)
		posiNum[i] = i;
}
//��������
void proNegaNum(int *negaNum) {

	negaNum[0] = 0;
	for (int i = 1; i < N; i++)
		negaNum[i] = N- i;
}
//ǰһ�����򣬺�һ�����
void proPosiRandNum(int *posiRand) {

	posiRand[0] = 0;
	for (int i = 1; i < N / 2 + 1; i++)
		posiRand[i] = i;
	srand((unsigned)time(NULL));
	for (int i = N / 2 + 1; i < N; i++)
		posiRand[i] = rand();
}
//ǰһ���������һ������
void proRandPosiNum(int *randPosi) {
	randPosi[0] = 0;

	srand((unsigned)time(NULL));
	for (int i = 1; i < N / 2 + 1; i++)
		randPosi[i] = rand();
	for (int i = N / 2 + 1; i < N; i++)
		randPosi[i] = i;
}

//������
void resultPrint(int num, int num2) {
	cout << "             �Ƚϴ���    �ƶ�����     ����ʱ�䣨ms��\n";
	switch (num2) {
	case 0:
		if (num + 1 == 11) {
			for (int i = 0; i < 10; i++) {
				switch (i + 1) {
				case 1:cout << "ֱ�Ӳ�������"; break;
				case 2:cout << "  ϣ������  ��"; break;
				case 3:cout << "  ð������  ��"; break;
				case 4:cout << "  ��������  ��"; break;
				case 5:cout << "��ѡ������"; break;
				case 6:cout << "   ������   ��"; break;
				case 7:cout << "  �鲢����  ��"; break;
				case 8:cout << "  ��������  ��"; break;
				case 9:cout << "�۰��������"; break;
				case 10:cout << "2·��������"; break;
				default:
					break;
				}
				printf("%12lld", (sum[0][i][0] + sum[1][i][0] + sum[2][i][0] + sum[3][i][0] + sum[4][i][0]) / 5);
				printf("%12lld", (sum[0][i][1] + sum[1][i][1] + sum[2][i][1] + sum[3][i][1] + sum[4][i][1]) / 5);
				printf("%12lld", (sum[0][i][2] + sum[1][i][2] + sum[2][i][2] + sum[3][i][2] + sum[4][i][2]) / 5);
				cout << endl;
			}
			break;
		}
		for (int i = 0; i < 5; i++) {
			cout << "����" << i + 1 << "��  ";
			printf("%12lld", sum[i][num][0]);
			printf("%12lld", sum[i][num][1]);
			printf("%12lld", sum[i][num][2]);
			cout << endl;
		}
		cout << "��ֵ:    ";
		printf("%12lld", (sum[0][num][0] + sum[1][num][0] + sum[2][num][0] + sum[3][num][0] + sum[4][num][0]) / 5);
		printf("%12lld", (sum[0][num][1] + sum[1][num][1] + sum[2][num][1] + sum[3][num][1] + sum[4][num][1]) / 5);
		printf("%12lld", (sum[0][num][2] + sum[1][num][2] + sum[2][num][2] + sum[3][num][2] + sum[4][num][2]) / 5);
		cout << endl;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		if (num + 1 == 11) {
			for (int i = 0; i < 10; i++) {
				switch (i + 1) {
				case 1:cout << "ֱ�Ӳ�������"; break;
				case 2:cout << "  ϣ������  ��"; break;
				case 3:cout << "  ð������  ��"; break;
				case 4:cout << "  ��������  ��"; break;
				case 5:cout << "��ѡ������"; break;
				case 6:cout << "   ������   ��"; break;
				case 7:cout << "  �鲢����  ��"; break;
				case 8:cout << "  ��������  ��"; break;
				case 9:cout << "�۰��������"; break;
				case 10:cout << "2·��������"; break;
				default:
					break;
				}
				printf("%12lld", sum[4][i][0]);
				printf("%12lld", sum[4][i][1]);
				printf("%12lld", sum[4][i][2]);
				cout << endl;
			}
			break;
		}
		cout << "����"<< "��   ";
		printf("%12lld", sum[4][num][0]);
		printf("%12lld", sum[4][num][1]);
		printf("%12lld", sum[4][num][2]);
		cout << endl;
		break;
	}
	//����
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 3; k++)
				sum[i][j][k] = 0;
}
//1.ֱ�Ӳ�������
void straightInsertSort(int *randNum, int n) {
	int i, j;
	for (i = 2; i < N;++i)
		if (sum[n][0][0]++,randNum[i] < randNum[i - 1]) {
			randNum[0] = randNum[i];
			randNum[i] = randNum[i - 1]; sum[n][0][1] += 2;
			for (j = i - 2; sum[n][0][0]++, randNum[0] < randNum[j]; --j)
			{
				randNum[j + 1] = randNum[j]; sum[n][0][1]++;
			}
			randNum[j + 1] = randNum[0]; sum[n][0][1]++;
		}
}
//2.ϣ������
void shellSort(int randNum[N], int n) {
	int dlta[17];
	int j;
	for (int k = 0; k <= 16; k++) {
		dlta[k] = pow(2, 16 - k) + 1;
	}
	for (int k = 0; k <= 16; k++) {
		for (int i = dlta[k] + 1; i < N; i++) {
			if (sum[n][1][0]++, randNum[i] < randNum[i - dlta[k]]) {
				sum[n][1][1]++; randNum[0] = randNum[i];
				for (j = i - dlta[k]; sum[n][1][0]++, j > 0 && randNum[0] < randNum[j]; j -= dlta[k])
				{
					sum[n][1][1]++; randNum[j + dlta[k]] = randNum[j];
				}
				sum[n][1][1]++; randNum[j + dlta[k]] = randNum[0];
			}
		}
	}
	//show(randNum);
}
//3.ð������
void bubbleSort(int randNum[N], int n) {
	int i, j;
	long long t;
	for (i = 1; i<N-1; i++)
		for (j = 1; j<N - i; j++)
		{
			if (sum[n][2][0]++, randNum[j]>randNum[j + 1])
			{
				t = randNum[j];
				randNum[j] = randNum[j + 1];
				randNum[j + 1] = t;
				sum[n][2][1] += 3;
			}
		}
	//show(randNum);
}
//4.��������
//ȡ������������low��mid��high����λ�������ݣ�ѡȡ�����м���Ǹ�������Ϊ����
int SelectPivotMedianOfThree(int arr[], int low, int high)
{
	int mid = low + (high - low) / 2;

	if (arr[mid] > arr[high])
		swap(arr[mid], arr[high]);
	if (arr[low] > arr[high])
		swap(arr[low], arr[high]);
	if (arr[mid] > arr[low])
		swap(arr[mid], arr[low]);

	return arr[low];
}

int partition(int *randNum, int low, int high, int n) {
	randNum[0] = randNum[low];
	int pivotkey = SelectPivotMedianOfThree(randNum, low, high);
	while (low < high) {
		while (low < high&&randNum[high] >= pivotkey) {
			--high; sum[n][3][0]++;
		}
		randNum[low] = randNum[high]; sum[n][3][1]++;
		while (low < high&&randNum[low] <= pivotkey) {
			++low; sum[n][3][0]++;
		}
		randNum[high] = randNum[low]; sum[n][3][1]++;
	}
	randNum[low] = randNum[0];

	return low;
}
void QSort(int *randNum, int low, int high, int n) {
	if (low < high) {
		int pivotloc = partition(randNum, low, high, n);
		if (pivotloc - 1 - low <= high - pivotloc - 1) {
			if(pivotloc!=low)
				QSort(randNum, low, pivotloc - 1, n);
			if(pivotloc != high)
				QSort(randNum, pivotloc + 1, high, n);
		}
		else {
			if (pivotloc != high)
				QSort(randNum, pivotloc + 1, high, n);
			if (pivotloc != low)
				QSort(randNum, low, pivotloc - 1, n);
		}
	}
}
void quickSort(int *randNum, int n) {
	QSort(randNum, 1, N - 1, n);
	//show(randNum);
}

//5.��ѡ������
void simpleSelectionSort(int randNum[N], int n) {
	int i, j, min, ex;
	for (i = 1; i < N-1; i++) {
		min = i;
		for (j = i+1; j < N; j++) {
			if (sum[n][4][0]++, randNum[min] > randNum[j])
				min = j;
		}
		if (min != i) {
			ex = randNum[i];
			randNum[i] = randNum[min];
			randNum[min] = ex;
			sum[n][4][1] += 3;
		}
	}
	//show(randNum);
}

//6.������
void heapAdjust(int *randNum, int s, int m, int n) {
	int rc = randNum[s];
	for (int j = 2 * s; j <= m; j *= 2) {
		if (sum[n][5][0]++, j < m&&randNum[j] < randNum[j + 1]) ++j;
		if (rc >= randNum[j]) break;
		randNum[s] = randNum[j]; s = j; sum[n][5][1]++;
	}
	randNum[s] = rc; sum[n][5][1]++;
}
void heapSort(int *randNum, int n) {
	int i,ex;
	for (i = (N - 1) / 2; i > 0; --i)
		heapAdjust(randNum, i, N - 1, n);
	for (i = N - 1; i > 1; --i) {
		swap(randNum[i], randNum[1]);

		heapAdjust(randNum, 1, i - 1, n);
	}
	//show(randNum);
}

//7.�鲢����
void mergingSort(int *randNum, int n) {
	//MSort(randNum, randNum, 1, N - 1, n);
	int i, left_min, left_max, right_min, right_max, next;
	int *tmp = (int*)malloc(sizeof(int) * (N-1));

	if (tmp == NULL)
	{
		fputs("Error: out of memory\n", stderr);
		abort();
	}


	for (i = 1; i < N-1; i *= 2) // iΪ������1,2,4,8����
	{
		for (left_min = 1; left_min < N - i; left_min = right_max)
		{
			right_min = left_max = left_min + i;
			right_max = left_max + i;

			if (right_max > N)
				right_max = N;

			next = 0;
			while (left_min < left_max && right_min < right_max) {
				tmp[next++] = randNum[left_min] > randNum[right_min] ? randNum[right_min++] : randNum[left_min++];
				sum[n][6][0]++;  sum[n][6][1]++;
			}

			while (left_min < left_max) {
				randNum[--right_min] = randNum[--left_max];
				sum[n][6][1]++;
			}

			while (next > 0) {
				randNum[--right_min] = tmp[--next];
				sum[n][6][1]++;
			}
		}
	}
	free(tmp);
	//show(randNum);
}

//8.��������
//�ҵ�num�Ĵӵ͵��ߵĵ�posλ������
int GetNumInPosition(int num, int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}

void radixSort(int randNum[N], int n)
{
	int *radixArrays[10];    //�ֱ�Ϊ0~9�����пռ�
	for (int i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * N);
		radixArrays[i][0] = 0;    //indexΪ0����¼�������ݵĸ���
	}
	for (int pos = 1; pos <= 10; pos++)    //�Ӹ�λ��ʼ��10λ��10Ϊ�ؼ��ָ���������Ϊ����λ��
	{
		for (int i = 1; i < N; i++)    //�������
		{
			int num = GetNumInPosition(randNum[i], pos); sum[n][7][0]++;
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = randNum[i]; sum[n][7][1]++;
		}

		for (int i = 0, j = 1; i < 10; i++)    //�ռ�
		{
			for (int k = 1; k <= radixArrays[i][0]; k++) {
				randNum[j++] = radixArrays[i][k]; sum[n][7][1]++;
			}
			radixArrays[i][0] = 0;    //��λ
		}
	}
	//show(randNum);
}

//9.�۰��������
void binaryInsertionSort(int randNum[N], int n) {
	int low, high, mid;
	for (int i = 2; i < N; i++) {
		low = 1; high = i - 1;
		randNum[0] = randNum[i]; sum[n][8][1]++;
		while (sum[n][8][0]++, low <= high) {
			mid = (high + low) / 2;
			if (sum[n][8][0]++, randNum[i] >= randNum[mid])
				low = mid + 1;
			else
				high = mid - 1;
		}
		for (int j = i; j > low; j--) {
			randNum[j] = randNum[j - 1]; sum[n][8][1]++;
		}
		randNum[low] = randNum[0]; sum[n][8][1]++;
	}
}
//10.��·��������
void TwoWayInsertionSort(int *randNum, int n) {

	int first = 0, last = 0;
	randNum1[0] = randNum[1]; sum[n][9][1]++;
	for (int i = 2; i < N; i++) {
		if (sum[n][9][0]++, randNum[i] > randNum1[last]) {
			last = (last + 1) % (N - 1);
			randNum1[last] = randNum[i]; sum[n][9][1]++;
		}
		else if (sum[n][9][0]++, randNum[i] < randNum1[first]) {
			first = (first - 1 + N - 1) % (N - 1);
			randNum1[first] = randNum[i]; sum[n][9][1]++;
		}
		else {
			int j = last++;
			while (sum[n][9][0]++, randNum[i] < randNum1[j]) {
				randNum1[j + 1] = randNum1[j]; sum[n][9][1]++;
				j = (j - 1 + N - 1) % (N - 1);
			}
			randNum1[j + 1] = randNum[i]; sum[n][9][1]++;
		}
	}
}

int main() {
	int num, num2, x = -1;
	int compareNum, moveNum;
	clock_t timeBegin, timeEnd;


	int result;

	while (true) {
		while (true) {
			cout << "��ѡ���������ͣ�\n";
			cout <<"1.�������  "
                 <<"2.���� "
                 <<"3.���� "<<endl;
                 //<<"4.ǰһ�������һ������"<<endl
                 //<<"5.ǰһ�������һ�����" << endl;
			cin >> num2;
			if (num2 >= 1 && num2 <= 5) break;
			else
				cout << "ѡ�����������ѡ��";
		}

		while (true) {
			cout << "��ѡ�����򷽷���\n";
			cout << " 1.ֱ�Ӳ�������  "
			       <<" 2.ϣ������   "
			       <<" 3.ð������  "
			       <<" 4.��������  "
			       <<" 5.��ѡ������  "<<endl
				   << " 6.������   "
				   <<" 7.�鲢����  "
				   <<" 8.��������  "<<endl;
				   //<<" 9.�۰��������  "
				   //<<"10.2·��������  "<<endl
				   //<<"11.ȫ��  " << endl;
			cin >> num;
			if (num >= 1 && num <= 11) {
							switch (num) {
				case 1:cout << "ֱ�Ӳ�������"<<endl;break;
				case 2:cout << "  ϣ������  ��"<<endl;break;
				case 3:cout << "  ð������  ��"<<endl;break;
				case 4:cout << "  ��������  ��"<<endl;break;
				case 5:cout << "��ѡ������"<<endl;break;
				case 6:cout << "   ������   ��"<<endl;break;
				case 7:cout << "  �鲢����  ��"<<endl;break;
				case 8:cout << "  ��������  ��"<<endl;break;
				case 9:cout << "�۰��������"<<endl;break;
				case 10:cout << "2·��������"<<endl;break;
				case 11:cout << "ȫ������Ƚϣ�"<<endl;break;
				default:
					break;
				}
				break;
			}
			else
				cout << "ѡ�����������ѡ��";

		}

		while (++x < 5) {
			switch (num2) {
			case 1:
				proRandNum(randNum);
				break;
			case 2:
				proPosiNum(randNum);x = 4;
				break;
			case 3:
				proNegaNum(randNum); x = 4;
				break;
			case 4:
				proRandPosiNum(randNum); x = 4;
				break;
			case 5:
				proPosiRandNum(randNum); x = 4;
				break;
			default:
				break;
			}

			switch (num) {
			case 1:
				timeBegin = clock();

				straightInsertSort(randNum, x);
				timeEnd = clock();
				sum[x][0][2] = timeEnd - timeBegin;
				break;
			case 2:

				timeBegin = clock();

				shellSort(randNum, x);
				timeEnd = clock();
				sum[x][1][2] = timeEnd - timeBegin;
				break;
			case 3:

				timeBegin = clock();

				bubbleSort(randNum, x);
				timeEnd = clock();
				sum[x][2][2] = timeEnd - timeBegin;
				break;
			case 4:

				timeBegin = clock();

				quickSort(randNum, x);
				timeEnd = clock();
				sum[x][3][2] = timeEnd - timeBegin;
				break;
			case 5:

				timeBegin = clock();

				simpleSelectionSort(randNum, x);
				timeEnd = clock();
				sum[x][4][2] = timeEnd - timeBegin;
				break;
			case 6:

				timeBegin = clock();

				heapSort(randNum, x);
				timeEnd = clock();
				sum[x][5][2] = timeEnd - timeBegin;
				break;
			case 7:

				timeBegin = clock();

				mergingSort(randNum, x);
				timeEnd = clock();
				sum[x][6][2] = timeEnd - timeBegin;
				break;
			case 8:

				timeBegin = clock();

				radixSort(randNum, x);
				timeEnd = clock();
				sum[x][7][2] = timeEnd - timeBegin;
				break;
			case 9:
				timeBegin = clock();

				binaryInsertionSort(randNum, x);
				timeEnd = clock();
				sum[x][8][2] = timeEnd - timeBegin;
				break;
			case 10:
				timeBegin = clock();

				TwoWayInsertionSort(randNum, x);
				timeEnd = clock();
				sum[x][9][2] = timeEnd - timeBegin;
				break;
			case 11:

				timeBegin = clock();straightInsertSort(randNum, x);timeEnd = clock();sum[x][0][2] = timeEnd - timeBegin;
				timeBegin = clock();shellSort(randNum, x);timeEnd = clock();sum[x][1][2] = timeEnd - timeBegin;
				timeBegin = clock();bubbleSort(randNum, x);timeEnd = clock();sum[x][2][2] = timeEnd - timeBegin;
				timeBegin = clock();quickSort(randNum, x);timeEnd = clock();sum[x][3][2] = timeEnd - timeBegin;
				timeBegin = clock();simpleSelectionSort(randNum, x);timeEnd = clock();sum[x][4][2] = timeEnd - timeBegin;
				timeBegin = clock();heapSort(randNum, x);timeEnd = clock();sum[x][5][2] = timeEnd - timeBegin;
				timeBegin = clock();mergingSort(randNum, x);timeEnd = clock();sum[x][6][2] = timeEnd - timeBegin;
				timeBegin = clock();radixSort(randNum, x);timeEnd = clock();sum[x][7][2] = timeEnd - timeBegin;
				break;
			default:
				break;
			}

		}
		x = -1;
		resultPrint(num - 1, num2 - 1);

		while (true) {
			cout << "��ѡ�� 1.���� 0.�˳�" << endl;
			int num;
			cin >> num;
			if (num == 0) return 0;
			else if (num == 1) break;
			else
				cout << "ѡ�����������ѡ��";
		}
	}

	system("pause");
	return 0;

}

#include<iostream>
using namespace std;

int board[20][20];//����
const int N = 1e5 + 7;

void inboard();//������������
void printfboard();//��ӡ���
void play1(int x,int y);//�������ӣ���1Ϊ���ӣ�2Ϊ����
void play2(int x, int y);//���е�����
void inspect(int x,int y);//����Ƿ��´�λ��
void record(int x, int y);//��¼֮ǰ������
void loop();//ѭ��


void inboard()
{
	int i, j, k = 0;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			k = i + 1;

			board[i][0] = k - 1;
			k = j + 1;
			board[0][j] = k - 1;
			board[i + 1][j + 1] = 0;
		}

	}
}

void printfboard()
{
	int i, j;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			printf("%3d", board[i][j]);
			//cout << board[i][j];
			//cout << " ";

		}
		cout << endl;
	}
}

void play1(int x,int y)//����
{
	
	board[x][y] = 1;
	printfboard();

}

void play2(int x,int y)
{
	board[x][y]=2;
	printfboard();

}

void loop()
{
	
	int a, b, x, y;
	while (1)
	{   
		cout << "��������Ҫ�µ�λ�ã��к��У�����ע���ÿո������";
		cin >> x >> y;
		
		play1(x, y);		
		cout << "��ϣ��������һ������" << endl;
		cout << "��������Ҫ�µ�λ�ã��к��У�����ע���ÿո������";
		cin >> a >> b;
		
		play2(a, b);
	}
}

void inspect(int x, int y)
{
	if (board[x][y] == 1 || board[x][y] == 2)
	{
		cout << "�Բ��𣬴�λ���Ѿ������ӣ�������ѡ����Ҫ�µ�λ��" << endl;//�����Ϻ�Ҫ�ع���һ��
	
	}
	if (x < 0 || x>15 || y < 0 || y>15)
	{
		cout << "�Բ������̲����ڴ�λ�ã����Ѿ�Խ��" << endl << "������ѡ����Ҫ�µ�λ��" << endl;

	}

}

void record(int x, int y)//��ԭ����λ������ͬ��������
{
	
}
int main()
{

	inboard();
	printfboard();
	
	cout << endl;
	loop();

	
	/*cout << "��������" << endl;
	int m, n, a, b;
	cout << "���������У��м��ÿո������" << endl;
	cin >> m >> n;*/

	/*board[m][n] = 1;
	printfboard();*/

	/*play1(m, n);
	cout << "�������ǰ���" << endl;
	cout << "���������У��м��ÿո������" << endl;
	cin >> a >> b;
	play2(a, b);*/
	//while (1)//11.25 14:15
	//{
	//	cout << "��������Ҫ�µ�λ�ã��к��У�����ע���ÿո������";
	//	cin >> m >> n;
	//	play1(m, n);
	//	cout << "������ϣ�����׼����" << endl;
	//	cout << "��������Ҫ�µ�λ�ã��к��У�����ע���ÿո������";
	//	cin >> a >> b;
	//	play2(a, b);
 //   }



	
	return 0;
}


//pass1 
// 11.25 10��30
//char board[20][20];
//
//void inboard();//�����̴����ά����֮��
//void printfboard();//��ӡ����
//
//
//void inboard()
//{
// int i, j, n;
// 
// 
// for (i = 0; i < 16; i++)
// {
// 
//  
//     for (j = 0; j < 16; j++)
//  {
//   board[i][j] = '+';
//
//  }
// }
//
//}
//
//void printfboard()
//{
// int i, j;
// for (i = 0; i < 16; i++)
// {
//  for (j = 0; j < 16; j++)
//  {
//   cout << board[i][j];
//   cout << " ";//������
//  }
//  cout << endl;
// }
//}
//int main()
//{
// inboard();
// printfboard();
// //cout << "��"<<"   "<<"��"; ���ڸ���ճ���ڰ���,ռ�����ַ���λ����Ҫ������
// return 0;
//}

#include<iostream>
using namespace std;

int board[20][20];//棋盘
const int N = 1e5 + 7;

void inboard();//创建基础棋盘
void printfboard();//打印输出
void play1(int x,int y);//更换棋子，设1为黑子，2为白子
void play2(int x, int y);//后行的棋子
void inspect(int x,int y);//检查是否下错位置
void record(int x, int y);//记录之前的数组
void loop();//循环


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

void play1(int x,int y)//黑子
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
		cout << "请输入你要下的位置（行和列），并注意用空格隔开：";
		cin >> x >> y;
		
		play1(x, y);		
		cout << "完毕，请进行下一步操作" << endl;
		cout << "请输入你要下的位置（行和列），并注意用空格隔开：";
		cin >> a >> b;
		
		play2(a, b);
	}
}

void inspect(int x, int y)
{
	if (board[x][y] == 1 || board[x][y] == 2)
	{
		cout << "对不起，此位置已经有棋子，请重新选择你要下的位置" << endl;//检查完毕后要回归上一步
	
	}
	if (x < 0 || x>15 || y < 0 || y>15)
	{
		cout << "对不起，棋盘不存在此位置，你已经越界" << endl << "请重新选择你要下的位置" << endl;

	}

}

void record(int x, int y)//在原来的位置上下同样的棋子
{
	
}
int main()
{

	inboard();
	printfboard();
	
	cout << endl;
	loop();

	
	/*cout << "黑子先行" << endl;
	int m, n, a, b;
	cout << "请输入行列，中间用空格隔开：" << endl;
	cin >> m >> n;*/

	/*board[m][n] = 1;
	printfboard();*/

	/*play1(m, n);
	cout << "接下来是白子" << endl;
	cout << "请输入行列，中间用空格隔开：" << endl;
	cin >> a >> b;
	play2(a, b);*/
	//while (1)//11.25 14:15
	//{
	//	cout << "请输入你要下的位置（行和列），并注意用空格隔开：";
	//	cin >> m >> n;
	//	play1(m, n);
	//	cout << "黑手完毕，白子准备下" << endl;
	//	cout << "请输入你要下的位置（行和列），并注意用空格隔开：";
	//	cin >> a >> b;
	//	play2(a, b);
 //   }



	
	return 0;
}


//pass1 
// 11.25 10：30
//char board[20][20];
//
//void inboard();//将棋盘存入二维数组之中
//void printfboard();//打印棋盘
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
//   cout << " ";//正方体
//  }
//  cout << endl;
// }
//}
//int main()
//{
// inboard();
// printfboard();
// //cout << "●"<<"   "<<"○"; 用于复制粘贴黑白棋,占两个字符的位置需要开二倍
// return 0;
//}

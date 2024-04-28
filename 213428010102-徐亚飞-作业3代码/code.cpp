#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <string.h>

using namespace std;

const int N = 20;  //定义棋盘边长最大值>=17即可
const int MAXN = 1e5 + 7;  //栈的最大值

struct node//每一步棋的坐标信息
{
	int x;
	int y;
};

int board[N][N];  //棋盘
node stack[MAXN];  //栈

int top;  //栈顶元素的上一个
int pass_time;  //记录跳过的次数

//函数声明部分
void Initial();  //初始化
void Menu();  //菜单
void Reset();  //重置
void Exit();  //退出程序
void Start();  //开始游戏
void View();  //展示棋盘
int Check(int x, int y, int aim);  //判断输赢
void Middle(int y);  //居中输出
int Toint(string s);  //转换为数字

//函数定义部分
void Initial()  //文字改为亮白色
{
	system("color 0F");
	return;
}

void Menu()//彩色
{
	system("cls");
	Reset();
	cout << "        ********* Menu *********" << endl;
	cout << "        *     A.开始对战       *" << endl;
	cout << "        *     B.退出           *" << endl;
	cout << "        ************************" << endl;
	cout << "请输入A到B" << endl;
	string cmd;
	cin >> cmd;
	if (cmd == "a" || cmd == "A")
		Start();
	else if (cmd == "b" || cmd == "B")
		Exit();
	else
	{
		cout << "没有该指令！请重新输入！" << endl;
		Menu();
	}
	return;
}

void Reset()  //重置
{
	memset(board, 0, sizeof(board));
	memset(stack, 0, sizeof(stack));
	top = 0;
	pass_time = 0;
	return;
}

void Exit()
{
	system("cls");
	cout << "感谢您的使用！" << endl;
	return;
}

void Start()
{
	system("cls");//清空屏幕
	while (top + 1)
	{
		system("cls");
		int x, y;
		View();  //显示

		cout << "请执";
		if (!(top % 2))  //奇数是白子 偶数是黑子
			cout << "黑";
		else
			cout << "白";
		cout << "者输入坐标(若要跳过请输入“PASS” 若要悔棋请输入“悔棋”) :";

		string tmp;
		cin >> tmp;
		if (tmp == "PASS")
		{
			pass_time++;
			top++;
			cout << "成功跳过!" << endl;
			system("pause");
			continue;
		}
		else if (tmp == "悔棋")
		{
			cout << endl;
			if (!top)  //第一步不可以悔棋
			{
				cout << "无法悔棋！" << endl;
			}
			else
			{
				cout << "对方正在请求悔棋（若要同意请输入“同意”，拒绝请输入“拒绝”）:" << endl;
				cin >> tmp;
				if (tmp == "同意")
				{
					top--;
					if (stack[top].x == 0 && stack[top].y == 0)
						pass_time--;
					board[stack[top].x][stack[top].y] = 0;
					cout << "成功悔棋！" << endl;
				}
				else
				{
					cout << "对方拒绝了你的请求！" << endl;
				}
			}
			system("pause");
			continue;

		}
		else
			x = Toint(tmp);  //转化为int类型的数字
		cin >> tmp;
		y = Toint(tmp);
		cout << endl;
		if (x == -2 || y == -2)
		{
			cout << "参数错误！请重新输入！" << endl;
			system("pause");
		}
		else if (x < 1 || x > 15 || y < 1 || y > 15)
		{
			cout << "参数错误！请重新输入！" << endl;
			system("pause");
		}
		else if (board[x][y] != 0)
		{
			cout << "该坐标已存在棋子！请重新输入！" << endl;
			system("pause");
		}
		else
		{
			stack[top].x = x;
			stack[top].y = y;
			board[x][y] = top % 2 + 1;  //判断谁的子
			top++;
			if (Check(x, y, board[x][y]))
			{
				system("cls");
				View();
				if (!(top % 2))
					cout << "白子";
				else
				{
					if (Check(x, y, board[x][y]) == -1)
					{
						cout << "长连禁手！" << endl;
						cout << "白子";
					}
					else
						cout << "黑子";
				}
				cout << "玩家获胜！" << endl;
				system("pause");
				Menu();
				break;
			}
			else if (top - pass_time == 15 * 15)  //下满 pass_time是跳过的次数
			{
				system("cls");
				View();
				cout << "平局！" << endl;
				system("pause");
				Menu();
				break;
			}
		}
	}
	return;
}

void View()
{
	Middle(0);
	for (int i = 0; i <= 15; i++)
		cout << setw(3) << std::right << i;  //缩进对齐
	cout << endl;


	for (int i = 1; i <= 15; i++)
	{
		Middle(i);
		cout << setw(3) << std::right << i;
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] == 0)
				cout << setw(3) << std::right << "十";
			else if (board[i][j] == 1)
				cout << setw(3) << std::right << "○";
			else if (board[i][j] == 2)
				cout << setw(3) << std::right << "●";
		}
		cout << endl;
	}
	return;
}

int Check(int x, int y, int aim)
{
	int cnt;
	//0
	cnt = 1;
	for (int i = y - 1; board[x][i] == aim; i--)
		cnt++;
	for (int i = y + 1; board[x][i] == aim; i++)
		cnt++;
	if (cnt == 5)
		return 1;
	else if (cnt > 5)
		return -1;

	//90
	cnt = 1;
	for (int i = x - 1; board[i][y] == aim; i--)
		cnt++;
	for (int i = x + 1; board[i][y] == aim; i++)
		cnt++;
	if (cnt == 5)
		return 1;
	else if (cnt > 5)
		return -1;

	//45
	cnt = 1;
	for (int i = x + 1, j = y - 1; board[i][j] == aim; i++, j--)
		cnt++;
	for (int i = x - 1, j = y + 1; board[i][j] == aim; i--, j++)
		cnt++;
	if (cnt == 5)
		return 1;
	else if (cnt > 5)
		return -1;

	//135
	cnt = 1;
	for (int i = x - 1, j = y - 1; board[i][j] == aim; i--, j--)
		cnt++;
	for (int i = x + 1, j = y + 1; board[i][j] == aim; i++, j++)
		cnt++;
	if (cnt == 5)
		return 1;
	else if (cnt > 5)
		return -1;

	return 0;
}

void Middle(int y)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);  //获取控制台的屏幕大小
	int dwSizeX = bInfo.dwSize.X, dwSizey = bInfo.dwSize.Y;
	int len = 52;
	int x = dwSizeX / 2 - len / 2;  //输入字符长度除于二
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);  //输入（内置好的）
	return;
}

int Toint(string s)  //把string转为int
{
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] <= '9' && s[i] >= '0')
			ans = ans * 10 + s[i] - '0';
		else
			return -2;  //输入有问题 错误
	}
	return ans;
}

int main()
{
	Initial();  //初始化
	Menu();  //菜单
	return 0;
}
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <string.h>

using namespace std;

const int N = 20;  //�������̱߳����ֵ>=17����
const int MAXN = 1e5 + 7;  //ջ�����ֵ

struct node//ÿһ�����������Ϣ
{
	int x;
	int y;
};

int board[N][N];  //����
node stack[MAXN];  //ջ

int top;  //ջ��Ԫ�ص���һ��
int pass_time;  //��¼�����Ĵ���

//������������
void Initial();  //��ʼ��
void Menu();  //�˵�
void Reset();  //����
void Exit();  //�˳�����
void Start();  //��ʼ��Ϸ
void View();  //չʾ����
int Check(int x, int y, int aim);  //�ж���Ӯ
void Middle(int y);  //�������
int Toint(string s);  //ת��Ϊ����

//�������岿��
void Initial()  //���ָ�Ϊ����ɫ
{
	system("color 0F");
	return;
}

void Menu()//��ɫ
{
	system("cls");
	Reset();
	cout << "        ********* Menu *********" << endl;
	cout << "        *     A.��ʼ��ս       *" << endl;
	cout << "        *     B.�˳�           *" << endl;
	cout << "        ************************" << endl;
	cout << "������A��B" << endl;
	string cmd;
	cin >> cmd;
	if (cmd == "a" || cmd == "A")
		Start();
	else if (cmd == "b" || cmd == "B")
		Exit();
	else
	{
		cout << "û�и�ָ����������룡" << endl;
		Menu();
	}
	return;
}

void Reset()  //����
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
	cout << "��л����ʹ�ã�" << endl;
	return;
}

void Start()
{
	system("cls");//�����Ļ
	while (top + 1)
	{
		system("cls");
		int x, y;
		View();  //��ʾ

		cout << "��ִ";
		if (!(top % 2))  //�����ǰ��� ż���Ǻ���
			cout << "��";
		else
			cout << "��";
		cout << "����������(��Ҫ���������롰PASS�� ��Ҫ���������롰���塱) :";

		string tmp;
		cin >> tmp;
		if (tmp == "PASS")
		{
			pass_time++;
			top++;
			cout << "�ɹ�����!" << endl;
			system("pause");
			continue;
		}
		else if (tmp == "����")
		{
			cout << endl;
			if (!top)  //��һ�������Ի���
			{
				cout << "�޷����壡" << endl;
			}
			else
			{
				cout << "�Է�����������壨��Ҫͬ�������롰ͬ�⡱���ܾ������롰�ܾ�����:" << endl;
				cin >> tmp;
				if (tmp == "ͬ��")
				{
					top--;
					if (stack[top].x == 0 && stack[top].y == 0)
						pass_time--;
					board[stack[top].x][stack[top].y] = 0;
					cout << "�ɹ����壡" << endl;
				}
				else
				{
					cout << "�Է��ܾ����������" << endl;
				}
			}
			system("pause");
			continue;

		}
		else
			x = Toint(tmp);  //ת��Ϊint���͵�����
		cin >> tmp;
		y = Toint(tmp);
		cout << endl;
		if (x == -2 || y == -2)
		{
			cout << "�����������������룡" << endl;
			system("pause");
		}
		else if (x < 1 || x > 15 || y < 1 || y > 15)
		{
			cout << "�����������������룡" << endl;
			system("pause");
		}
		else if (board[x][y] != 0)
		{
			cout << "�������Ѵ������ӣ����������룡" << endl;
			system("pause");
		}
		else
		{
			stack[top].x = x;
			stack[top].y = y;
			board[x][y] = top % 2 + 1;  //�ж�˭����
			top++;
			if (Check(x, y, board[x][y]))
			{
				system("cls");
				View();
				if (!(top % 2))
					cout << "����";
				else
				{
					if (Check(x, y, board[x][y]) == -1)
					{
						cout << "�������֣�" << endl;
						cout << "����";
					}
					else
						cout << "����";
				}
				cout << "��һ�ʤ��" << endl;
				system("pause");
				Menu();
				break;
			}
			else if (top - pass_time == 15 * 15)  //���� pass_time�������Ĵ���
			{
				system("cls");
				View();
				cout << "ƽ�֣�" << endl;
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
		cout << setw(3) << std::right << i;  //��������
	cout << endl;


	for (int i = 1; i <= 15; i++)
	{
		Middle(i);
		cout << setw(3) << std::right << i;
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] == 0)
				cout << setw(3) << std::right << "ʮ";
			else if (board[i][j] == 1)
				cout << setw(3) << std::right << "��";
			else if (board[i][j] == 2)
				cout << setw(3) << std::right << "��";
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
	GetConsoleScreenBufferInfo(hOutput, &bInfo);  //��ȡ����̨����Ļ��С
	int dwSizeX = bInfo.dwSize.X, dwSizey = bInfo.dwSize.Y;
	int len = 52;
	int x = dwSizeX / 2 - len / 2;  //�����ַ����ȳ��ڶ�
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);  //���루���úõģ�
	return;
}

int Toint(string s)  //��stringתΪint
{
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] <= '9' && s[i] >= '0')
			ans = ans * 10 + s[i] - '0';
		else
			return -2;  //���������� ����
	}
	return ans;
}

int main()
{
	Initial();  //��ʼ��
	Menu();  //�˵�
	return 0;
}
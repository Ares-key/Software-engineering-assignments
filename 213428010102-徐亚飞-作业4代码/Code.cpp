#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>

using namespace std;

#define ADDITION 1  //�ӷ�
#define SUBTRACTION 2  //����
#define MULTIPLICATION 4  //�˷�
#define DIVISION 8  //����
#define QUESTIONNUMBER 100000  //��Ŀ�������ֵ
#define MAXIMUMNUMBER 1e8  //�����������ֵ
#define MAXIMUMNUMBERITEMS 10  //�����������
#define MAXIMUMBRACKETS 3  //�����������
#define DECIMALPROBABILITY 20  //ÿ������С����Ŀ�ĸ���
#define DECIMALGENERATEPROBABILITY 30  //��������С������

//������
//������
class Setting;
//��ʽ��
class Equation;
//��Ŀ��
class Question;

//Question* q = new Question[s.GetQuestionNumber() + 7];  //������Ŀ�����Ŀռ�


//��������
//������Ŀ
void Generate(Setting& s);
//����
void Export(Setting& s);
//����
void SetUp(Setting& s);
//�˵�
void Menu();

//�ඨ��
//������
class Setting
{
public:
	//���ù��캯��
	Setting();

	//���ò���
	//������Ŀ����
	bool SetQuestionNumber(int QuestionNumber);
	//���ÿ��÷���
	bool SetOP(int OP);
	//��������
	bool SetBrackets();
	//����С��
	bool SetDecimal();
	//�����������
	bool SetMaximumNumber(int MaximumNumber);
	//�����������
	bool SetMaximumNumberItems(int MaximumNumberItems);
	//��������
	bool SetSeed(int Seed);

	//��ȡ��Ϣ
	//��ȡ��Ŀ����
	int GetQuestionNumber();
	//��ȡ���÷���
	int GetOP();
	//��ȡ�Ƿ��������
	bool GetBrackets();
	//��ȡ�Ƿ����С��
	bool GetDecimal();
	//��ȡ�������
	int GetMaximumNumber();
	//��ȡ�������
	int GetMaximumNumberItems();
	//��ȡ����
	int GetSeed();

private:
	int QuestionNumber;  //��Ŀ����
	int OP;  //���÷���
	bool Brackets;  //����
	bool Decimal;  //С��
	int MaximumNumber;  //�������
	int MaximumNumberItems;  //�������
	int Seed;  //����
};

//��ʽ��
class Equation
{
public:
	//���캯��
	Equation();

	//���ò���
	//���ò�����
	bool SetOperand(double Operand);
	//���ò�����
	bool SetOperator(char Operator);

	//��ȡ��Ϣ
	//��ȡ������
	double GetOperand();
	//��ȡ������
	char GetOperator();
	//��ȡ��ǰ����
	int GetType();

private:
	double Operand;  //������
	char Operator;  //������
	int Type;  //-1Ϊ��������0δ���壬1Ϊ������
};

//��Ŀ��
class Question
{
public:
	//��Ŀ���캯��
	Question();

	//���ò���
	//������Ŀ���
	bool SetID(int ID);
	//���ò���������
	bool SetOperandsNumber(int OperandsNumber);

	//��ȡ��Ϣ
	//��ȡ��ϸ��Ϣ
	void GetInformation();
	//��ȡ��Ŀ���
	int GetID();
	//��ȡ����������
	int GetOperandsNumber();
	//��ȡ��������
	int GetBracketsNumber();
	//��ȡ��׺���ʽ
	void GetInfixExpression();
	//�ļ���ȡ��׺���ʽ
	void GetInfixExpression(ofstream& ofs);
	//��ȡ��׺���ʽ
	void GetPostfixExpression();
	//��ȡ��ǰ��
	double GetAnswer();

	//ִ�в���
	//����
	void Reset();
	//�����������
	void GenerateIntegers(Setting s);
	//�������С��
	void GenerateDecimals(Setting s);
	//������ɲ�����
	void GenerateOperators(Setting s);
	//���㵱ǰ���
	double Calculate();
	//��װ��ǰ��ʽ
	void Assemble();
	//ת������׺���ʽ
	bool Convert();
	//���´�
	bool UpdateAnswer();
	//�����������
	bool GenerateBrackets(Setting s);

private:
	int ID;  //��Ŀ���
	int OperandsNumber;  //����������
	double Operands[MAXIMUMNUMBERITEMS + 1];  //������
	char Operators[MAXIMUMNUMBERITEMS + 1];  //������
	int BracketsNumber;  //��������
	int BracketsPosition[MAXIMUMBRACKETS + 1][2];  //����λ��
	int InfixExpressionLength;  //��׺���ʽ����
	Equation InfixExpression[(MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS) * 2];  //��׺���ʽ
	int PostfixExpressionLength;  //��׺���ʽ����
	Equation PostfixExpression[(MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS) * 2];  //��׺���ʽ
	double Answer;  //�洢��ǰ��Ŀ��
};

Question q[QUESTIONNUMBER];

//���ù��캯��
Setting::Setting()
{
	this->QuestionNumber = 10;
	this->OP = ADDITION ^ SUBTRACTION ^ MULTIPLICATION ^ DIVISION;
	this->Brackets = false;
	this->Decimal = false;
	this->MaximumNumber = 100;
	this->MaximumNumberItems = 3;
	this->Seed = 0;
	return;
}

//������Ŀ����
bool Setting::SetQuestionNumber(int QuestionNumber)
{
	//ȷ����Ŀ�����Ϸ�
	if (QuestionNumber < 1 || QuestionNumber > QUESTIONNUMBER)
	{
		return false;
	}
	else
	{
		this->QuestionNumber = QuestionNumber;
	}
	return true;
}

//���ÿ��÷���
bool Setting::SetOP(int OP)
{
	//ȷ�������ڿ�������
	if (OP != ADDITION && OP != SUBTRACTION && OP != MULTIPLICATION && OP != DIVISION)
	{
		return false;
	}
	//��ֹ�޷��ſ���
	if ((this->OP ^ OP) == 0)
	{
		return false;
	}
	else
	{
		this->OP ^= OP;
	}
	return true;
}

//��������
bool Setting::SetBrackets()
{
	//ȷ����������ʹ������
	if (this->Brackets == false && this->MaximumNumberItems == 2)
	{
		return false;
	}
	if (this->Brackets == true)
	{
		this->Brackets = false;
	}
	else
	{
		this->Brackets = true;
	}
	return true;
}

//����С��
bool Setting::SetDecimal()
{
	if (this->Decimal == true)
	{
		this->Decimal = false;
	}
	else
	{
		this->Decimal = true;
	}
	return true;
}

//�����������
bool Setting::SetMaximumNumber(int MaximumNumber)
{
	//ȷ��������ֺϷ�
	if (MaximumNumber < 0 || MaximumNumber > MAXIMUMNUMBER)
	{
		return false;
	}
	else
	{
		this->MaximumNumber = MaximumNumber;
	}
	return true;
}

//�����������
bool Setting::SetMaximumNumberItems(int MaximumNumberItems)
{
	//ȷ�����������������ͻ
	if (this->Brackets == true && MaximumNumberItems == 2)
	{
		return false;
	}
	//ȷ����������Ϸ�
	if (MaximumNumberItems < 2 || MaximumNumberItems > MAXIMUMNUMBERITEMS)
	{
		return false;
	}
	else
	{
		this->MaximumNumberItems = MaximumNumberItems;
	}
	return true;
}

//��������
bool Setting::SetSeed(int Seed)
{
	if (Seed < 0)
	{
		return false;
	}
	else
	{
		this->Seed = Seed;
	}
	return true;
}

//��ȡ��Ŀ����
int Setting::GetQuestionNumber()
{
	return this->QuestionNumber;
}

//��ȡ���÷���
int Setting::GetOP()
{
	return this->OP;
}

//��ȡ�Ƿ��������
bool Setting::GetBrackets()
{
	return this->Brackets;
}

//��ȡ�Ƿ����С��
bool Setting::GetDecimal()
{
	return this->Decimal;
}

//��ȡ�������
int Setting::GetMaximumNumber()
{
	return this->MaximumNumber;
}

//��ȡ�������
int Setting::GetMaximumNumberItems()
{
	return this->MaximumNumberItems;
}

//��ȡ����
int Setting::GetSeed()
{
	return this->Seed;
}

//��ʽ���캯��
Equation::Equation()
{
	this->Operand = 0;
	this->Operator = 0;
	this->Type = 0;
	return;
}

//���ò�����
bool Equation::SetOperand(double Operand)
{
	this->Type = -1;
	this->Operand = Operand;
	this->Operator = 0;
	return true;
}

//���ò�����
bool Equation::SetOperator(char Operator)
{
	this->Type = 1;
	this->Operator = Operator;
	this->Operand = 0;
	return true;
}

//��ȡ������
double Equation::GetOperand()
{
	return this->Operand;
}

//��ȡ������
char Equation::GetOperator()
{
	return this->Operator;
}

//��ȡ��ǰ����
int Equation::GetType()
{
	return this->Type;
}

//��Ŀ���캯��
Question::Question()
{
	this->ID = 0;
	this->OperandsNumber = 0;
	memset(this->Operands, 0, sizeof(this->Operands));
	memset(this->Operators, 0, sizeof(this->Operators));
	this->BracketsNumber = 0;
	memset(this->BracketsPosition, 0, sizeof(this->BracketsPosition));
	this->InfixExpressionLength = 0;
	this->PostfixExpressionLength = 0;
	this->Answer = 0;
	return;
}

//������Ŀ���
bool Question::SetID(int ID)
{
	if (ID < 0)
	{
		return false;
	}
	else
	{
		this->ID = ID;
	}
	return true;
}

//���ò���������
bool Question::SetOperandsNumber(int OperandsNumber)
{
	if (OperandsNumber < 2 || OperandsNumber > MAXIMUMNUMBERITEMS)
	{
		return false;
	}
	else
	{
		this->OperandsNumber = OperandsNumber;
	}
	return true;
}

//��ȡ��ϸ��Ϣ
void Question::GetInformation()
{
	//���Ų���
	/*this->BracketsNumber = 1;
	this->BracketsPosition[0][0] = 0;
	this->BracketsPosition[0][1] = 1;*/
	this->UpdateAnswer();
	cout << "��Ŀ��ţ�" << this->ID << endl;
	cout << "������������" << this->OperandsNumber << endl;
	cout << "���в�������";
	if (this->OperandsNumber == 0)
	{
		cout << "��" << endl;
	}
	else
	{
		for (int i = 0; i < this->OperandsNumber; i++)
		{
			cout << this->Operands[i] << " ";
		}
		cout << endl;
	}
	cout << "���в�������";
	if (this->OperandsNumber == 0)
	{
		cout << "��" << endl;
	}
	else
	{
		for (int i = 0; i < this->OperandsNumber - 1; i++)
		{
			cout << this->Operators[i] << " ";
		}
		cout << endl;
	}
	cout << "����������" << this->BracketsNumber << endl;
	cout << "����λ�ã�";
	if (this->BracketsNumber == 0)
	{
		cout << "��" << endl;
	}
	else
	{
		cout << endl;
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			cout << this->BracketsPosition[i][0] << "����" << this->BracketsPosition[i][1] << endl;
		}
	}
	cout << "��׺���ʽ���ȣ�" << this->InfixExpressionLength << endl;
	cout << "��׺���ʽ��";
	this->GetInfixExpression();
	cout << endl;
	cout << "��׺���ʽ���ȣ�" << this->PostfixExpressionLength << endl;
	cout << "��׺���ʽ��";
	this->GetPostfixExpression();
	cout << endl;
	cout << "���ʽ�����" << this->Answer << endl;
	return;
}

//��ȡ��Ŀ���
int Question::GetID()
{
	return this->ID;
}

//��ȡ����������
int Question::GetOperandsNumber()
{
	return this->OperandsNumber;
}

//��ȡ��������
int Question::GetBracketsNumber()
{
	return this->BracketsNumber;
}

//��ȡ��׺���ʽ
void Question::GetInfixExpression()
{
	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		if (this->InfixExpression[i].GetType() == -1)  //������
		{
			cout << InfixExpression[i].GetOperand();
		}
		else if (this->InfixExpression[i].GetType() == 1)  //������
		{
			cout << InfixExpression[i].GetOperator();
		}
	}
	return;
}

//�ļ���ȡ��׺���ʽ
void Question::GetInfixExpression(ofstream& ofs)
{
	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		if (this->InfixExpression[i].GetType() == -1)  //������
		{
			ofs << InfixExpression[i].GetOperand();
		}
		else if (this->InfixExpression[i].GetType() == 1)  //������
		{
			if (this->InfixExpression[i].GetOperator() == '*')
			{
				ofs << "��";
			}
			else if (this->InfixExpression[i].GetOperator() == '/')
			{
				ofs << "��";
			}
			else
			{
				ofs << InfixExpression[i].GetOperator();
			}
		}
	}
	return;
}

//��ȡ��׺���ʽ
void Question::GetPostfixExpression()
{
	for (int i = 0; i < this->PostfixExpressionLength; i++)
	{
		if (this->PostfixExpression[i].GetType() == -1)  //������
		{
			cout << PostfixExpression[i].GetOperand() << " ";
		}
		else if (this->PostfixExpression[i].GetType() == 1)  //������
		{
			cout << PostfixExpression[i].GetOperator() << " ";
		}
	}
	return;
}

//��ȡ��ǰ��
double Question::GetAnswer()
{
	return this->Answer;
}

//����
void Question::Reset()
{
	this->ID = 0;
	this->OperandsNumber = 0;
	memset(this->Operands, 0, sizeof(this->Operands));
	memset(this->Operators, 0, sizeof(this->Operators));
	this->BracketsNumber = 0;
	memset(this->BracketsPosition, 0, sizeof(this->BracketsPosition));
	this->InfixExpressionLength = 0;
	this->PostfixExpressionLength = 0;
	this->Answer = 0;
	return;
}

//�����������
void Question::GenerateIntegers(Setting s)
{
	for (int i = 0; i < this->OperandsNumber; i++)
	{
		this->Operands[i] = rand() % s.GetMaximumNumber();
		if (this->Operands[i] == 0)
		{
			i--;
		}
	}
	return;
}

//�������С��
void Question::GenerateDecimals(Setting s)
{
	for (int i = 0; i < this->OperandsNumber; i++)
	{
		int flag = rand() % 100;
		if (flag < DECIMALGENERATEPROBABILITY)
		{
			this->Operands[i] = rand() % (s.GetMaximumNumber() * 10) / 10.0;
			if (this->Operands[i] == 0)
			{
				i--;
			}
		}
		else
		{
			this->Operands[i] = rand() % s.GetMaximumNumber();
			if (this->Operands[i] == 0)
			{
				i--;
			}
		}
	}
	return;
}

//������ɲ�����
void Question::GenerateOperators(Setting s)
{
	//ͳ�ƿ��ò�����
	char OP[4];
	int Count = 0;
	if (s.GetOP() & ADDITION)
	{
		OP[Count++] = '+';
	}
	if (s.GetOP() & SUBTRACTION)
	{
		OP[Count++] = '-';
	}
	if (s.GetOP() & MULTIPLICATION)
	{
		OP[Count++] = '*';
	}
	if (s.GetOP() & DIVISION)
	{
		OP[Count++] = '/';
	}

	//������ɲ�����
	for (int i = 0; i < this->OperandsNumber - 1; i++)
	{
		this->Operators[i] = OP[rand() % Count];
	}
	return;
}

//���㵱ǰ���
double Question::Calculate()
{
	//��ʼ��
	double Stack[MAXIMUMNUMBERITEMS + 1];
	memset(Stack, 0, sizeof(Stack));
	int top = 0;

	//���к�׺���ʽ����
	for (int i = 0; i < this->PostfixExpressionLength; i++)
	{
		//����ѹ��ջ
		if (this->PostfixExpression[i].GetType() == -1)
		{
			Stack[top++] = this->PostfixExpression[i].GetOperand();
		}

		//���Ž�������
		if (this->PostfixExpression[i].GetType() == 1)
		{
			if (this->PostfixExpression[i].GetOperator() == '+')
			{
				top--;
				Stack[top - 1] = Stack[top - 1] + Stack[top];
			}
			if (this->PostfixExpression[i].GetOperator() == '-')
			{
				top--;
				Stack[top - 1] = Stack[top - 1] - Stack[top];
			}
			if (this->PostfixExpression[i].GetOperator() == '*')
			{
				top--;
				Stack[top - 1] = Stack[top - 1] * Stack[top];
			}
			if (this->PostfixExpression[i].GetOperator() == '/')
			{
				top--;
				Stack[top - 1] = Stack[top - 1] / Stack[top];
			}
		}
	}
	return Stack[0];
}

//��װ��ǰ��ʽ
void Question::Assemble()
{
	this->InfixExpressionLength = this->OperandsNumber * 2 - 1 + this->BracketsNumber * 2;
	int cnt = 0;
	int OperandsCnt = 0;
	int OperatorsCnt = 0;
	while (cnt < this->InfixExpressionLength)
	{
		//����������
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][0] == OperandsCnt)
			{
				this->InfixExpression[cnt++].SetOperator('(');
			}
		}

		//���ò�����
		this->InfixExpression[cnt++].SetOperand(this->Operands[OperandsCnt++]);

		//����������
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][1] == OperandsCnt - 1)
			{
				this->InfixExpression[cnt++].SetOperator(')');
			}
		}

		//�ж��Ƿ����
		if (cnt >= this->InfixExpressionLength)
		{
			break;
		}

		//���ò�����
		this->InfixExpression[cnt++].SetOperator(this->Operators[OperatorsCnt++]);
	}
	return;
}

bool Question::Convert()
{
	//�ж��Ƿ������׺���ʽ
	if (this->InfixExpressionLength == 0)
	{
		return false;
	}

	//���㳤��
	this->PostfixExpressionLength = this->OperandsNumber * 2 - 1;  //��������

	char Stack[MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS * 2];  //����׺���ʽ�ĸ���ջ
	memset(Stack, 0, sizeof(Stack));
	int top = 0;
	int PostfixCnt = 0;

	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		//����ֱ�ӵ���
		if (this->InfixExpression[i].GetType() == -1)
		{
			this->PostfixExpression[PostfixCnt++].SetOperand(this->InfixExpression[i].GetOperand());
		}

		//������ֱ����ջ
		if (this->InfixExpression[i].GetType() == 1 && this->InfixExpression[i].GetOperator() == '(')
		{
			Stack[top++] = this->InfixExpression[i].GetOperator();
		}

		//�Ӽ�������
		if (this->InfixExpression[i].GetType() == 1 &&
			(this->InfixExpression[i].GetOperator() == '+' ||
				this->InfixExpression[i].GetOperator() == '-'))
		{
			while (top != 0)
			{
				if (Stack[top - 1] == '+' || Stack[top - 1] == '-' ||
					Stack[top - 1] == '*' || Stack[top - 1] == '/')
				{
					this->PostfixExpression[PostfixCnt++].SetOperator(Stack[--top]);
				}
				else
				{
					break;
				}
			}
			Stack[top++] = this->InfixExpression[i].GetOperator();
		}

		//�˳�������
		if (this->InfixExpression[i].GetType() == 1 &&
			((this->InfixExpression[i].GetOperator() == '*') ||
				this->InfixExpression[i].GetOperator() == '/'))
		{
			while (top != 0)
			{
				if (Stack[top - 1] == '*' || Stack[top - 1] == '/')
				{
					this->PostfixExpression[PostfixCnt++].SetOperator(Stack[--top]);
				}
				else
				{
					break;
				}
			}
			Stack[top++] = this->InfixExpression[i].GetOperator();
		}

		//�����ſ�ʼ����
		if (this->InfixExpression[i].GetType() == 1 && this->InfixExpression[i].GetOperator() == ')')
		{
			while (Stack[top - 1] != '(')
			{
				this->PostfixExpression[PostfixCnt++].SetOperator(Stack[--top]);
			}
			top--;
		}
		/*cout << "��ǰջ��";
		for (int index = 0; index < top; index++)
		{
			cout << Stack[index] << " ";
		}
		cout << endl;*/
	}

	//���ε���ʣ�����
	while (top != 0)
	{
		this->PostfixExpression[PostfixCnt++].SetOperator(Stack[--top]);
	}

	if (this->PostfixExpressionLength == PostfixCnt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//���´�
bool Question::UpdateAnswer()
{
	this->Assemble();
	if (!this->Convert())
	{
		return false;
	}
	this->Answer = this->Calculate();
	return true;
}

//�����������
bool Question::GenerateBrackets(Setting s)
{
	//����������
	this->BracketsPosition[this->BracketsNumber][0] = rand() % (this->OperandsNumber - 1);

	//����������
	this->BracketsPosition[this->BracketsNumber][1] =
		this->BracketsPosition[this->BracketsNumber][0] + 1 + rand() %
		(this->OperandsNumber - this->BracketsPosition[this->BracketsNumber][0] - 1);

	/*cout << "OperandsNumber:" << this->OperandsNumber << endl;
	cout << this->OperandsNumber - 1 << " " << this->OperandsNumber - this->BracketsPosition[this->BracketsNumber][0] - 1 << endl;
	cout << "���ɵ����ţ�" << this->BracketsPosition[this->BracketsNumber][0]
		<< " " << this->BracketsPosition[this->BracketsNumber][1] << endl;*/

		//�������ֻ������һ������
	for (int i = 0; i < this->BracketsNumber; i++)
	{
		if (this->BracketsPosition[i][0] == this->BracketsPosition[this->BracketsNumber][1])
		{
			this->BracketsPosition[this->BracketsNumber][0] = 0;
			this->BracketsPosition[this->BracketsNumber][1] = 0;
			return false;
		}
		if (this->BracketsPosition[i][1] == this->BracketsPosition[this->BracketsNumber][0])
		{
			this->BracketsPosition[this->BracketsNumber][0] = 0;
			this->BracketsPosition[this->BracketsNumber][1] = 0;
			return false;
		}
	}

	//�������ʽ�ӱ�����������
	if (this->BracketsPosition[this->BracketsNumber][0] == 0)
	{
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][1] == this->OperandsNumber - 1)
			{
				this->BracketsPosition[this->BracketsNumber][0] = 0;
				this->BracketsPosition[this->BracketsNumber][1] = 0;
				return false;
			}
		}
	}
	if (this->BracketsPosition[this->BracketsNumber][1] == this->OperandsNumber - 1)
	{
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][0] == 0)
			{
				this->BracketsPosition[this->BracketsNumber][0] = 0;
				this->BracketsPosition[this->BracketsNumber][1] = 0;
				return false;
			}
		}
	}

	this->BracketsNumber++;

	//�ж������Ƿ�������
	this->Assemble();
	this->Convert();
	if (this->Answer == this->Calculate())  //������
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else if (this->Calculate() < -s.GetMaximumNumber() || this->Calculate() > s.GetMaximumNumber())  //������Χ
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else if (!s.GetDecimal() && this->Calculate() - int(this->Calculate()) != 0)  //������С��
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else  //������
	{
		/*cout << "<-" << this->Answer << endl;*/
		this->UpdateAnswer();
		/*cout << "->" << this->Answer << endl;*/
		return true;
	}

	return true;
}

//������Ŀ
void Generate(Setting& s)
{
	system("cls");

	//�������ʼ��
	if (s.GetSeed() == 0)
	{
		s.SetSeed(time(0));
	}
	srand(s.GetSeed());

	for (int i = 0; i < s.GetQuestionNumber(); i++)  //������Ŀ����
	{
		q[i].Reset();

		q[i].SetID(i + 1);  //���ñ��

		//�����������
		q[i].SetOperandsNumber(rand() % (s.GetMaximumNumberItems() - 1) + 2);

		int flag = rand() % 100;
		//������ɲ�����
		if (s.GetDecimal() && flag < DECIMALPROBABILITY)  //����С��
		{
			q[i].GenerateDecimals(s);
		}
		else  //��������
		{
			q[i].GenerateIntegers(s);
		}

		//������ɲ�����
		q[i].GenerateOperators(s);

		//���´�
		q[i].UpdateAnswer();

		//�жϽ���Ƿ���Ҫ��Χ
		if (q[i].GetAnswer() < -s.GetMaximumNumber() || q[i].GetAnswer() > s.GetMaximumNumber())
		{
			i--;
			continue;
		}

		//�жϽ���Ƿ�ΪС��
		if (!s.GetDecimal() || flag >= DECIMALPROBABILITY)
		{
			if (q[i].GetAnswer() - int(q[i].GetAnswer()) != 0)
			{
				i--;
				continue;
			}
		}

		//����������
		if (s.GetBrackets())
		{
			for (int j = 0; j < MAXIMUMBRACKETS; j++)
			{
				q[i].GenerateBrackets(s);
			}
		}

		//��ȡ��Ϣ
		/*q[i].GetInformation();
		cout << endl;*/
	}

	Export(s);  //����
	/*delete[] q;*/
	return;
}

//����
void Export(Setting& s)
{
	while (1)
	{
		system("cls");

		//�����Ŀ
		for (int i = 0; i < s.GetQuestionNumber(); i++)
		{
			cout << "[" << q[i].GetID() << "] ";
			q[i].GetInfixExpression();
			cout << "=";
			cout << endl;
		}

		cout << endl;
		cout << s.GetQuestionNumber() << "����Ŀ��ȫ��������ϣ�" << endl;
		cout << "�Ƿ񱣴浽���أ���Y/N��";

		string cmd;
		cin >> cmd;
		for (int i = 0; i < cmd.length(); i++)
		{
			if (cmd[i] >= 'a' && cmd[i] <= 'z')
			{
				cmd[i] = cmd[i] - 'a' + 'A';
			}
		}

		if (cmd == "Y" || cmd == "YES")  //ʹ���ļ����
		{
			cout << endl;
			cout << "�������ļ�����";
			string Name;
			getchar();
			getline(cin, Name);
			cout << "�����뱣��·����";
			string Path;
			cin >> Path;
			string FullPath;
			FullPath = Path + "\\" + Name + ".csv";
			ofstream ofs;
			ofs.open(FullPath, ios::out | ios::trunc);
			if (ofs.is_open() == false)
			{
				cout << endl;
				cout << "δ�ҵ�·����" << endl;
				system("pause");
				continue;
			}
			ofs << "���" << ',' << "��Ŀ" << ',' << "����д��" << endl;
			for (int i = 0; i < s.GetQuestionNumber(); i++)
			{
				ofs << q[i].GetID() << ',';
				q[i].GetInfixExpression(ofs);
				ofs << "=";
				ofs << ',' << endl;
			}
			ofs.close();
			FullPath = Path + "\\" + Name + "_��.csv";
			ofs.open(FullPath, ios::out | ios::trunc);
			if (ofs.is_open() == false)
			{
				cout << endl;
				cout << "δ�ҵ�·����" << endl;
				system("pause");
				continue;
			}
			ofs << "���" << ',' << "��Ŀ" << ',' << "��" << endl;
			for (int i = 0; i < s.GetQuestionNumber(); i++)
			{
				ofs << q[i].GetID() << ',';
				q[i].GetInfixExpression(ofs);
				ofs << "=";
				ofs << ',' << q[i].GetAnswer() << endl;
			}
			ofs.close();
			cout << "�ѳɹ�������" << endl;
			system("pause");
			break;
		}
		else if (cmd == "N" || cmd == "NO")  //��ʹ���ļ����
		{
			cout << endl;
			cout << "��л����ʹ�ã�" << endl;
			system("pause");
			break;
		}
		else
		{
			cout << "���������������룡" << endl;
			system("pause");
		}
	}
	return;
}

//����
void SetUp(Setting& s)
{
	while (1)
	{
		system("cls");
		cout << "��ǰ����������ʾ������R���أ���" << endl;
		cout << "A.��Ŀ������" << s.GetQuestionNumber() << endl;
		cout << "B.ʹ�÷��ţ�";
		if (s.GetOP() & ADDITION)
		{
			cout << "�ӷ���+�� ";
		}
		if (s.GetOP() & SUBTRACTION)
		{
			cout << "������-�� ";
		}
		if (s.GetOP() & MULTIPLICATION)
		{
			cout << "�˷���*�� ";
		}
		if (s.GetOP() & DIVISION)
		{
			cout << "������/�� ";
		}
		cout << endl;
		cout << "C.�Ƿ�ʹ�����ţ�";
		if (s.GetBrackets())
		{
			cout << "��" << endl;
		}
		else
		{
			cout << "��" << endl;
		}
		cout << "D.�Ƿ�ʹ��С����";
		if (s.GetDecimal())
		{
			cout << "��" << endl;
		}
		else
		{
			cout << "��" << endl;
		}
		cout << "E.������ֲ�������" << s.GetMaximumNumber() << endl;
		cout << "F.���������������" << s.GetMaximumNumberItems() << endl;
		cout << "G.��ǰ���ӣ�����Ϊ0��������ɣ���" << s.GetSeed() << endl;
		string cmd;
		cin >> cmd;
		if (cmd == "A" || cmd == "a")  //�޸���Ŀ����
		{
			int QuestionNumber;
			cin >> QuestionNumber;
			if (!s.SetQuestionNumber(QuestionNumber))
			{
				cout << "��Ŀ�������Ϸ���" << endl;
				system("pause");
			}
		}
		else if (cmd == "B" || cmd == "b")  //�޸Ŀ��÷���
		{
			char OP;
			cin >> OP;
			int OPNumber = 0;
			if (OP == '+')
			{
				OPNumber = ADDITION;
			}
			else if (OP == '-')
			{
				OPNumber = SUBTRACTION;
			}
			else if (OP == '*')
			{
				OPNumber = MULTIPLICATION;
			}
			else if (OP == '/')
			{
				OPNumber = DIVISION;
			}
			if (!s.SetOP(OPNumber))
			{
				cout << "ʹ�÷��Ų��Ϸ���" << endl;
				system("pause");
			}
		}
		else if (cmd == "C" || cmd == "c")  //�޸��Ƿ�ʹ������
		{
			bool Flag = s.SetBrackets();
			if (!Flag && s.GetBrackets() == false)
			{
				cout << "��ǰ����ʹ�����ţ�" << endl;
				system("pause");
			}
			else if (!Flag && s.GetBrackets() == true)
			{
				cout << "��ǰ����ʹ�����ţ�" << endl;
			}

		}
		else if (cmd == "D" || cmd == "d")  //�޸��Ƿ�ʹ��С��
		{
			bool Flag = s.SetDecimal();
			if (!Flag && s.GetDecimal() == false)
			{
				cout << "��ǰ����ʹ��С����" << endl;
				system("pause");
			}
			else if (!Flag && s.GetDecimal() == true)
			{
				cout << "��ǰ����ʹ��С��" << endl;
				system("pause");
			}
		}
		else if (cmd == "E" || cmd == "e")  //�޸��������
		{
			int MaximumNumber;
			cin >> MaximumNumber;
			if (!s.SetMaximumNumber(MaximumNumber))
			{
				cout << "������ֲ��Ϸ���" << endl;
				system("pause");
			}
		}
		else if (cmd == "F" || cmd == "f")  //�޸��������
		{
			int MaximumNumberItems;
			cin >> MaximumNumberItems;
			if (!s.SetMaximumNumberItems(MaximumNumberItems))
			{
				cout << "����������Ϸ���" << endl;
				system("pause");
			}
		}
		else if (cmd == "G" || cmd == "g")  //�޸�����
		{
			int Seed;
			cin >> Seed;
			if (!s.SetSeed(Seed))
			{
				cout << "���Ӳ��Ϸ���" << endl;
				system("pause");
			}
		}
		else if (cmd == "R" || cmd == "r")  //����
		{
			return;
		}
		else
		{
			cout << "���������������룡" << endl;
			system("pause");
		}
	}
	return;
}

//�˵�
void Menu()
{
	Setting s;
	while (1)
	{
		system("cls");
		cout << "**********����������ϰ������ϵͳ**********" << endl;
		cout << "**********      A.������Ŀ      **********" << endl;
		/*cout << "**********      B.��������      **********" << endl;*/
		cout << "**********      B.����          **********" << endl;
		cout << "**********      C.�˳�          **********" << endl;
		cout << "******************************************" << endl;
		string cmd;
		cin >> cmd;
		if (cmd == "A" || cmd == "a")
		{
			Generate(s);
		}
		/*else if (cmd == "B" || cmd == "b")
		{
			system("pause");
		}*/
		else if (cmd == "B" || cmd == "b")
		{
			SetUp(s);
		}
		else if (cmd == "C" || cmd == "c")
		{
			cout << "�������˳���" << endl;
			system("pause");
			return;
		}
		else
		{
			cout << "���������������룡" << endl;
			system("pause");
			continue;
		}
	}
	return;
}

int main()
{
	Menu();
	return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>

using namespace std;

#define ADDITION 1  //加法
#define SUBTRACTION 2  //减法
#define MULTIPLICATION 4  //乘法
#define DIVISION 8  //除法
#define QUESTIONNUMBER 100000  //题目数量最大值
#define MAXIMUMNUMBER 1e8  //出现数字最大值
#define MAXIMUMNUMBERITEMS 10  //数字最大项数
#define MAXIMUMBRACKETS 3  //括号最大数量
#define DECIMALPROBABILITY 20  //每次生成小数题目的概率
#define DECIMALGENERATEPROBABILITY 30  //单项生成小数概率

//声明类
//设置类
class Setting;
//算式类
class Equation;
//题目类
class Question;

//Question* q = new Question[s.GetQuestionNumber() + 7];  //开辟题目数量的空间


//声明函数
//生成题目
void Generate(Setting& s);
//导出
void Export(Setting& s);
//设置
void SetUp(Setting& s);
//菜单
void Menu();

//类定义
//设置类
class Setting
{
public:
	//设置构造函数
	Setting();

	//设置参数
	//设置题目数量
	bool SetQuestionNumber(int QuestionNumber);
	//设置可用符号
	bool SetOP(int OP);
	//设置括号
	bool SetBrackets();
	//设置小数
	bool SetDecimal();
	//设置最大数字
	bool SetMaximumNumber(int MaximumNumber);
	//设置最大项数
	bool SetMaximumNumberItems(int MaximumNumberItems);
	//设置种子
	bool SetSeed(int Seed);

	//获取信息
	//获取题目数量
	int GetQuestionNumber();
	//获取可用符号
	int GetOP();
	//获取是否可用括号
	bool GetBrackets();
	//获取是否可用小数
	bool GetDecimal();
	//获取最大数字
	int GetMaximumNumber();
	//获取最大项数
	int GetMaximumNumberItems();
	//获取种子
	int GetSeed();

private:
	int QuestionNumber;  //题目数量
	int OP;  //可用符号
	bool Brackets;  //括号
	bool Decimal;  //小数
	int MaximumNumber;  //最大数字
	int MaximumNumberItems;  //最大项数
	int Seed;  //种子
};

//算式类
class Equation
{
public:
	//构造函数
	Equation();

	//设置参数
	//设置操作数
	bool SetOperand(double Operand);
	//设置操作符
	bool SetOperator(char Operator);

	//获取信息
	//获取操作数
	double GetOperand();
	//获取操作符
	char GetOperator();
	//获取当前类型
	int GetType();

private:
	double Operand;  //操作数
	char Operator;  //操作符
	int Type;  //-1为操作数，0未定义，1为操作符
};

//题目类
class Question
{
public:
	//题目构造函数
	Question();

	//设置参数
	//设置题目编号
	bool SetID(int ID);
	//设置操作数数量
	bool SetOperandsNumber(int OperandsNumber);

	//获取信息
	//获取详细信息
	void GetInformation();
	//获取题目编号
	int GetID();
	//获取操作数数量
	int GetOperandsNumber();
	//获取括号数量
	int GetBracketsNumber();
	//获取中缀表达式
	void GetInfixExpression();
	//文件获取中缀表达式
	void GetInfixExpression(ofstream& ofs);
	//获取后缀表达式
	void GetPostfixExpression();
	//获取当前答案
	double GetAnswer();

	//执行操作
	//重置
	void Reset();
	//随机生成整数
	void GenerateIntegers(Setting s);
	//随机生成小数
	void GenerateDecimals(Setting s);
	//随机生成操作符
	void GenerateOperators(Setting s);
	//计算当前结果
	double Calculate();
	//组装当前算式
	void Assemble();
	//转换成中缀表达式
	bool Convert();
	//更新答案
	bool UpdateAnswer();
	//随机生成括号
	bool GenerateBrackets(Setting s);

private:
	int ID;  //题目编号
	int OperandsNumber;  //操作数数量
	double Operands[MAXIMUMNUMBERITEMS + 1];  //操作数
	char Operators[MAXIMUMNUMBERITEMS + 1];  //操作符
	int BracketsNumber;  //括号数量
	int BracketsPosition[MAXIMUMBRACKETS + 1][2];  //括号位置
	int InfixExpressionLength;  //中缀表达式长度
	Equation InfixExpression[(MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS) * 2];  //中缀表达式
	int PostfixExpressionLength;  //后缀表达式长度
	Equation PostfixExpression[(MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS) * 2];  //后缀表达式
	double Answer;  //存储当前题目答案
};

Question q[QUESTIONNUMBER];

//设置构造函数
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

//设置题目数量
bool Setting::SetQuestionNumber(int QuestionNumber)
{
	//确保题目数量合法
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

//设置可用符号
bool Setting::SetOP(int OP)
{
	//确保符号在可用区间
	if (OP != ADDITION && OP != SUBTRACTION && OP != MULTIPLICATION && OP != DIVISION)
	{
		return false;
	}
	//防止无符号可用
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

//设置括号
bool Setting::SetBrackets()
{
	//确保两项以上使用括号
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

//设置小数
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

//设置最大数字
bool Setting::SetMaximumNumber(int MaximumNumber)
{
	//确保最大数字合法
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

//设置最大项数
bool Setting::SetMaximumNumberItems(int MaximumNumberItems)
{
	//确保项数不与括号起冲突
	if (this->Brackets == true && MaximumNumberItems == 2)
	{
		return false;
	}
	//确保最大项数合法
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

//设置种子
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

//获取题目数量
int Setting::GetQuestionNumber()
{
	return this->QuestionNumber;
}

//获取可用符号
int Setting::GetOP()
{
	return this->OP;
}

//获取是否可用括号
bool Setting::GetBrackets()
{
	return this->Brackets;
}

//获取是否可用小数
bool Setting::GetDecimal()
{
	return this->Decimal;
}

//获取最大数字
int Setting::GetMaximumNumber()
{
	return this->MaximumNumber;
}

//获取最大项数
int Setting::GetMaximumNumberItems()
{
	return this->MaximumNumberItems;
}

//获取种子
int Setting::GetSeed()
{
	return this->Seed;
}

//算式构造函数
Equation::Equation()
{
	this->Operand = 0;
	this->Operator = 0;
	this->Type = 0;
	return;
}

//设置操作数
bool Equation::SetOperand(double Operand)
{
	this->Type = -1;
	this->Operand = Operand;
	this->Operator = 0;
	return true;
}

//设置操作符
bool Equation::SetOperator(char Operator)
{
	this->Type = 1;
	this->Operator = Operator;
	this->Operand = 0;
	return true;
}

//获取操作数
double Equation::GetOperand()
{
	return this->Operand;
}

//获取操作符
char Equation::GetOperator()
{
	return this->Operator;
}

//获取当前类型
int Equation::GetType()
{
	return this->Type;
}

//题目构造函数
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

//设置题目编号
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

//设置操作数数量
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

//获取详细信息
void Question::GetInformation()
{
	//括号测试
	/*this->BracketsNumber = 1;
	this->BracketsPosition[0][0] = 0;
	this->BracketsPosition[0][1] = 1;*/
	this->UpdateAnswer();
	cout << "题目编号：" << this->ID << endl;
	cout << "操作数数量：" << this->OperandsNumber << endl;
	cout << "所有操作数：";
	if (this->OperandsNumber == 0)
	{
		cout << "无" << endl;
	}
	else
	{
		for (int i = 0; i < this->OperandsNumber; i++)
		{
			cout << this->Operands[i] << " ";
		}
		cout << endl;
	}
	cout << "所有操作符：";
	if (this->OperandsNumber == 0)
	{
		cout << "无" << endl;
	}
	else
	{
		for (int i = 0; i < this->OperandsNumber - 1; i++)
		{
			cout << this->Operators[i] << " ";
		}
		cout << endl;
	}
	cout << "括号数量：" << this->BracketsNumber << endl;
	cout << "括号位置：";
	if (this->BracketsNumber == 0)
	{
		cout << "无" << endl;
	}
	else
	{
		cout << endl;
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			cout << this->BracketsPosition[i][0] << "——" << this->BracketsPosition[i][1] << endl;
		}
	}
	cout << "中缀表达式长度：" << this->InfixExpressionLength << endl;
	cout << "中缀表达式：";
	this->GetInfixExpression();
	cout << endl;
	cout << "后缀表达式长度：" << this->PostfixExpressionLength << endl;
	cout << "后缀表达式：";
	this->GetPostfixExpression();
	cout << endl;
	cout << "表达式结果：" << this->Answer << endl;
	return;
}

//获取题目编号
int Question::GetID()
{
	return this->ID;
}

//获取操作数数量
int Question::GetOperandsNumber()
{
	return this->OperandsNumber;
}

//获取括号数量
int Question::GetBracketsNumber()
{
	return this->BracketsNumber;
}

//获取中缀表达式
void Question::GetInfixExpression()
{
	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		if (this->InfixExpression[i].GetType() == -1)  //操作数
		{
			cout << InfixExpression[i].GetOperand();
		}
		else if (this->InfixExpression[i].GetType() == 1)  //操作符
		{
			cout << InfixExpression[i].GetOperator();
		}
	}
	return;
}

//文件获取中缀表达式
void Question::GetInfixExpression(ofstream& ofs)
{
	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		if (this->InfixExpression[i].GetType() == -1)  //操作数
		{
			ofs << InfixExpression[i].GetOperand();
		}
		else if (this->InfixExpression[i].GetType() == 1)  //操作符
		{
			if (this->InfixExpression[i].GetOperator() == '*')
			{
				ofs << "×";
			}
			else if (this->InfixExpression[i].GetOperator() == '/')
			{
				ofs << "÷";
			}
			else
			{
				ofs << InfixExpression[i].GetOperator();
			}
		}
	}
	return;
}

//获取后缀表达式
void Question::GetPostfixExpression()
{
	for (int i = 0; i < this->PostfixExpressionLength; i++)
	{
		if (this->PostfixExpression[i].GetType() == -1)  //操作数
		{
			cout << PostfixExpression[i].GetOperand() << " ";
		}
		else if (this->PostfixExpression[i].GetType() == 1)  //操作符
		{
			cout << PostfixExpression[i].GetOperator() << " ";
		}
	}
	return;
}

//获取当前答案
double Question::GetAnswer()
{
	return this->Answer;
}

//重置
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

//随机生成整数
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

//随机生成小数
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

//随机生成操作符
void Question::GenerateOperators(Setting s)
{
	//统计可用操作符
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

	//随机生成操作符
	for (int i = 0; i < this->OperandsNumber - 1; i++)
	{
		this->Operators[i] = OP[rand() % Count];
	}
	return;
}

//计算当前结果
double Question::Calculate()
{
	//初始化
	double Stack[MAXIMUMNUMBERITEMS + 1];
	memset(Stack, 0, sizeof(Stack));
	int top = 0;

	//进行后缀表达式计算
	for (int i = 0; i < this->PostfixExpressionLength; i++)
	{
		//数字压入栈
		if (this->PostfixExpression[i].GetType() == -1)
		{
			Stack[top++] = this->PostfixExpression[i].GetOperand();
		}

		//符号进行运算
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

//组装当前算式
void Question::Assemble()
{
	this->InfixExpressionLength = this->OperandsNumber * 2 - 1 + this->BracketsNumber * 2;
	int cnt = 0;
	int OperandsCnt = 0;
	int OperatorsCnt = 0;
	while (cnt < this->InfixExpressionLength)
	{
		//检索左括号
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][0] == OperandsCnt)
			{
				this->InfixExpression[cnt++].SetOperator('(');
			}
		}

		//放置操作数
		this->InfixExpression[cnt++].SetOperand(this->Operands[OperandsCnt++]);

		//检索右括号
		for (int i = 0; i < this->BracketsNumber; i++)
		{
			if (this->BracketsPosition[i][1] == OperandsCnt - 1)
			{
				this->InfixExpression[cnt++].SetOperator(')');
			}
		}

		//判断是否结束
		if (cnt >= this->InfixExpressionLength)
		{
			break;
		}

		//放置操作符
		this->InfixExpression[cnt++].SetOperator(this->Operators[OperatorsCnt++]);
	}
	return;
}

bool Question::Convert()
{
	//判断是否存在中缀表达式
	if (this->InfixExpressionLength == 0)
	{
		return false;
	}

	//计算长度
	this->PostfixExpressionLength = this->OperandsNumber * 2 - 1;  //不带括号

	char Stack[MAXIMUMNUMBERITEMS + MAXIMUMBRACKETS * 2];  //求中缀表达式的辅助栈
	memset(Stack, 0, sizeof(Stack));
	int top = 0;
	int PostfixCnt = 0;

	for (int i = 0; i < this->InfixExpressionLength; i++)
	{
		//数字直接弹出
		if (this->InfixExpression[i].GetType() == -1)
		{
			this->PostfixExpression[PostfixCnt++].SetOperand(this->InfixExpression[i].GetOperand());
		}

		//左括号直接入栈
		if (this->InfixExpression[i].GetType() == 1 && this->InfixExpression[i].GetOperator() == '(')
		{
			Stack[top++] = this->InfixExpression[i].GetOperator();
		}

		//加减法弹出
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

		//乘除法弹出
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

		//右括号开始弹出
		if (this->InfixExpression[i].GetType() == 1 && this->InfixExpression[i].GetOperator() == ')')
		{
			while (Stack[top - 1] != '(')
			{
				this->PostfixExpression[PostfixCnt++].SetOperator(Stack[--top]);
			}
			top--;
		}
		/*cout << "当前栈：";
		for (int index = 0; index < top; index++)
		{
			cout << Stack[index] << " ";
		}
		cout << endl;*/
	}

	//依次弹出剩余符号
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

//更新答案
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

//随机生成括号
bool Question::GenerateBrackets(Setting s)
{
	//生成左括号
	this->BracketsPosition[this->BracketsNumber][0] = rand() % (this->OperandsNumber - 1);

	//生成右括号
	this->BracketsPosition[this->BracketsNumber][1] =
		this->BracketsPosition[this->BracketsNumber][0] + 1 + rand() %
		(this->OperandsNumber - this->BracketsPosition[this->BracketsNumber][0] - 1);

	/*cout << "OperandsNumber:" << this->OperandsNumber << endl;
	cout << this->OperandsNumber - 1 << " " << this->OperandsNumber - this->BracketsPosition[this->BracketsNumber][0] - 1 << endl;
	cout << "生成的括号：" << this->BracketsPosition[this->BracketsNumber][0]
		<< " " << this->BracketsPosition[this->BracketsNumber][1] << endl;*/

		//如果括号只包含了一个数字
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

	//如果整个式子被括号括起来
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

	//判断括号是否有意义
	this->Assemble();
	this->Convert();
	if (this->Answer == this->Calculate())  //无意义
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else if (this->Calculate() < -s.GetMaximumNumber() || this->Calculate() > s.GetMaximumNumber())  //超出范围
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else if (!s.GetDecimal() && this->Calculate() - int(this->Calculate()) != 0)  //不允许小数
	{
		this->BracketsNumber--;
		this->BracketsPosition[this->BracketsNumber][0] = 0;
		this->BracketsPosition[this->BracketsNumber][1] = 0;
		this->Assemble();
		this->Convert();
		return false;
	}
	else  //有意义
	{
		/*cout << "<-" << this->Answer << endl;*/
		this->UpdateAnswer();
		/*cout << "->" << this->Answer << endl;*/
		return true;
	}

	return true;
}

//生成题目
void Generate(Setting& s)
{
	system("cls");

	//随机数初始化
	if (s.GetSeed() == 0)
	{
		s.SetSeed(time(0));
	}
	srand(s.GetSeed());

	for (int i = 0; i < s.GetQuestionNumber(); i++)  //生成题目数量
	{
		q[i].Reset();

		q[i].SetID(i + 1);  //设置编号

		//随机生成项数
		q[i].SetOperandsNumber(rand() % (s.GetMaximumNumberItems() - 1) + 2);

		int flag = rand() % 100;
		//随机生成操作数
		if (s.GetDecimal() && flag < DECIMALPROBABILITY)  //生成小数
		{
			q[i].GenerateDecimals(s);
		}
		else  //生成整数
		{
			q[i].GenerateIntegers(s);
		}

		//随机生成操作符
		q[i].GenerateOperators(s);

		//更新答案
		q[i].UpdateAnswer();

		//判断结果是否处于要求范围
		if (q[i].GetAnswer() < -s.GetMaximumNumber() || q[i].GetAnswer() > s.GetMaximumNumber())
		{
			i--;
			continue;
		}

		//判断结果是否为小数
		if (!s.GetDecimal() || flag >= DECIMALPROBABILITY)
		{
			if (q[i].GetAnswer() - int(q[i].GetAnswer()) != 0)
			{
				i--;
				continue;
			}
		}

		//随机添加括号
		if (s.GetBrackets())
		{
			for (int j = 0; j < MAXIMUMBRACKETS; j++)
			{
				q[i].GenerateBrackets(s);
			}
		}

		//获取信息
		/*q[i].GetInformation();
		cout << endl;*/
	}

	Export(s);  //导出
	/*delete[] q;*/
	return;
}

//导出
void Export(Setting& s)
{
	while (1)
	{
		system("cls");

		//输出题目
		for (int i = 0; i < s.GetQuestionNumber(); i++)
		{
			cout << "[" << q[i].GetID() << "] ";
			q[i].GetInfixExpression();
			cout << "=";
			cout << endl;
		}

		cout << endl;
		cout << s.GetQuestionNumber() << "道题目已全部生成完毕！" << endl;
		cout << "是否保存到本地？（Y/N）";

		string cmd;
		cin >> cmd;
		for (int i = 0; i < cmd.length(); i++)
		{
			if (cmd[i] >= 'a' && cmd[i] <= 'z')
			{
				cmd[i] = cmd[i] - 'a' + 'A';
			}
		}

		if (cmd == "Y" || cmd == "YES")  //使用文件输出
		{
			cout << endl;
			cout << "请输入文件名：";
			string Name;
			getchar();
			getline(cin, Name);
			cout << "请输入保存路径：";
			string Path;
			cin >> Path;
			string FullPath;
			FullPath = Path + "\\" + Name + ".csv";
			ofstream ofs;
			ofs.open(FullPath, ios::out | ios::trunc);
			if (ofs.is_open() == false)
			{
				cout << endl;
				cout << "未找到路径！" << endl;
				system("pause");
				continue;
			}
			ofs << "题号" << ',' << "题目" << ',' << "答案填写处" << endl;
			for (int i = 0; i < s.GetQuestionNumber(); i++)
			{
				ofs << q[i].GetID() << ',';
				q[i].GetInfixExpression(ofs);
				ofs << "=";
				ofs << ',' << endl;
			}
			ofs.close();
			FullPath = Path + "\\" + Name + "_答案.csv";
			ofs.open(FullPath, ios::out | ios::trunc);
			if (ofs.is_open() == false)
			{
				cout << endl;
				cout << "未找到路径！" << endl;
				system("pause");
				continue;
			}
			ofs << "题号" << ',' << "题目" << ',' << "答案" << endl;
			for (int i = 0; i < s.GetQuestionNumber(); i++)
			{
				ofs << q[i].GetID() << ',';
				q[i].GetInfixExpression(ofs);
				ofs << "=";
				ofs << ',' << q[i].GetAnswer() << endl;
			}
			ofs.close();
			cout << "已成功导出！" << endl;
			system("pause");
			break;
		}
		else if (cmd == "N" || cmd == "NO")  //不使用文件输出
		{
			cout << endl;
			cout << "感谢您的使用！" << endl;
			system("pause");
			break;
		}
		else
		{
			cout << "输入有误！请检查输入！" << endl;
			system("pause");
		}
	}
	return;
}

//设置
void SetUp(Setting& s)
{
	while (1)
	{
		system("cls");
		cout << "当前设置如下所示（输入R返回）：" << endl;
		cout << "A.题目数量：" << s.GetQuestionNumber() << endl;
		cout << "B.使用符号：";
		if (s.GetOP() & ADDITION)
		{
			cout << "加法（+） ";
		}
		if (s.GetOP() & SUBTRACTION)
		{
			cout << "减法（-） ";
		}
		if (s.GetOP() & MULTIPLICATION)
		{
			cout << "乘法（*） ";
		}
		if (s.GetOP() & DIVISION)
		{
			cout << "除法（/） ";
		}
		cout << endl;
		cout << "C.是否使用括号：";
		if (s.GetBrackets())
		{
			cout << "是" << endl;
		}
		else
		{
			cout << "否" << endl;
		}
		cout << "D.是否使用小数：";
		if (s.GetDecimal())
		{
			cout << "是" << endl;
		}
		else
		{
			cout << "否" << endl;
		}
		cout << "E.最大数字不超过：" << s.GetMaximumNumber() << endl;
		cout << "F.最大项数不超过：" << s.GetMaximumNumberItems() << endl;
		cout << "G.当前种子（种子为0将随机生成）：" << s.GetSeed() << endl;
		string cmd;
		cin >> cmd;
		if (cmd == "A" || cmd == "a")  //修改题目数量
		{
			int QuestionNumber;
			cin >> QuestionNumber;
			if (!s.SetQuestionNumber(QuestionNumber))
			{
				cout << "题目数量不合法！" << endl;
				system("pause");
			}
		}
		else if (cmd == "B" || cmd == "b")  //修改可用符号
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
				cout << "使用符号不合法！" << endl;
				system("pause");
			}
		}
		else if (cmd == "C" || cmd == "c")  //修改是否使用括号
		{
			bool Flag = s.SetBrackets();
			if (!Flag && s.GetBrackets() == false)
			{
				cout << "当前不可使用括号！" << endl;
				system("pause");
			}
			else if (!Flag && s.GetBrackets() == true)
			{
				cout << "当前必须使用括号！" << endl;
			}

		}
		else if (cmd == "D" || cmd == "d")  //修改是否使用小数
		{
			bool Flag = s.SetDecimal();
			if (!Flag && s.GetDecimal() == false)
			{
				cout << "当前不可使用小数！" << endl;
				system("pause");
			}
			else if (!Flag && s.GetDecimal() == true)
			{
				cout << "当前必须使用小数" << endl;
				system("pause");
			}
		}
		else if (cmd == "E" || cmd == "e")  //修改最大数字
		{
			int MaximumNumber;
			cin >> MaximumNumber;
			if (!s.SetMaximumNumber(MaximumNumber))
			{
				cout << "最大数字不合法！" << endl;
				system("pause");
			}
		}
		else if (cmd == "F" || cmd == "f")  //修改最大项数
		{
			int MaximumNumberItems;
			cin >> MaximumNumberItems;
			if (!s.SetMaximumNumberItems(MaximumNumberItems))
			{
				cout << "最大项数不合法！" << endl;
				system("pause");
			}
		}
		else if (cmd == "G" || cmd == "g")  //修改种子
		{
			int Seed;
			cin >> Seed;
			if (!s.SetSeed(Seed))
			{
				cout << "种子不合法！" << endl;
				system("pause");
			}
		}
		else if (cmd == "R" || cmd == "r")  //返回
		{
			return;
		}
		else
		{
			cout << "输入有误！请检查输入！" << endl;
			system("pause");
		}
	}
	return;
}

//菜单
void Menu()
{
	Setting s;
	while (1)
	{
		system("cls");
		cout << "**********四则运算练习题生成系统**********" << endl;
		cout << "**********      A.生成题目      **********" << endl;
		/*cout << "**********      B.自助批改      **********" << endl;*/
		cout << "**********      B.设置          **********" << endl;
		cout << "**********      C.退出          **********" << endl;
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
			cout << "程序已退出！" << endl;
			system("pause");
			return;
		}
		else
		{
			cout << "输入有误！请检查输入！" << endl;
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
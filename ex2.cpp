/*十以内带括号的表达式运算*/
#include <iostream>
#include <string>
#include <cctype>
#include "lk_stack.h"		// 顺序表类
using namespace std;

class Calculator {
public:
	void Run(); //执行表达式
	void setExp(string str) {infExp = str;}
private:
	LinkStack<double> OPND; //操作数栈
	LinkStack<char> OPTR; //操作符栈         
//	int isp(char op); //栈内优先数
	int icp(char op); //栈外优先数
	void Equvar(); //中缀表达式等价变换为后缀表达式 
	void Solve(); //后缀表达式求值 
	bool isoperator(char op); 
private:
	string infExp; //中缀表达式 
	string sufExp; //后缀表达式
	bool status = 1;
};

void Calculator::Run() {
	double result;
	Equvar(); //中缀表达式等价变换为后缀表达式
	if(status) {
		Solve(); //后缀表达式求值
		OPND.Pop(result);
		cout << result; 
	}
}

void Calculator::Solve() {
	char in;
	double out, dig1, dig2, dig3;
	for (int i = 0; i < sufExp.length(); i++) {
		in = char(sufExp[i]);
		if (isdigit(in)) OPND.Push(double(in - '0'));
		else {
			OPND.Pop(out);
			dig1 = out;
			OPND.Pop(out);
			dig2 = out;
			switch(in) {
				case'+':
					dig3 = dig2 + dig1;
					break;
				case'-':
					dig3 = dig2 - dig1;
					break;
				case'*':
					dig3 = dig2 * dig1;
					break;
				case'/':
					dig3 = dig2 / dig1;
					break;
				default:break;
			}
			OPND.Push(dig3);
		}
	}
}

bool Calculator::isoperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')') return 1;
	else return 0;
}

int Calculator::icp(char op) {
	switch(op) {
		case'*':case'/':
			return 2;break;
		case'+':case'-':
			return 1;break;
		default:return 0;break;
	}
}

void Calculator::Equvar() {
	char in, out, temp;
	for (int i = 0; i < infExp.length(); i++) {
		in = char(infExp[i]);
		if (isdigit(in)) sufExp.append(1, in); 
		else if (!isoperator(in)) {
			cout << "Input Error" << endl;
			status = 0;
			break;
		}
		else if (OPTR.IsEmpty()) OPTR.Push(in);
		else {
			switch(in) {
				case'(':
					OPTR.Push(in);
					break;
				case')':
					while(OPTR.GetTop(temp) && (temp != '(')) {
						OPTR.Pop(out);
						sufExp.append(1, out);
					}
					OPTR.Pop(out);
					break;
				case'+':case'-':case'*':case'/':
					while(OPTR.GetTop(temp) && (temp != '(') && (icp(in) < icp(temp))) {
						OPTR.Pop(out);
						sufExp.append(1, out);
					}
					OPTR.Push(in);
					break;
				default:break;
				}
			}
		}
		
	while(!OPTR.IsEmpty()) {
			OPTR.Pop(out);
			if (out == '(') {
				cout << "Input Error" << endl;
				status = 0;
				break;
			}
			sufExp.append(1, out);
		}
}

int main(void) {
	Calculator cal;
	char ch; 
	string temp;
	cout << "please input the expression:";
	while (cin >> ch) {
		temp.append(1, ch);
	}
	cal.setExp(temp);
	cal.Run();
	return 0;
}


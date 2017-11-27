/*ʮ���ڴ����ŵı��ʽ����*/
#include <iostream>
#include <string>
#include <cctype>
#include "lk_stack.h"		// ˳�����
using namespace std;

class Calculator {
public:
	void Run(); //ִ�б��ʽ
	void setExp(string str) {infExp = str;}
private:
	LinkStack<double> OPND; //������ջ
	LinkStack<char> OPTR; //������ջ         
//	int isp(char op); //ջ��������
	int icp(char op); //ջ��������
	void Equvar(); //��׺���ʽ�ȼ۱任Ϊ��׺���ʽ 
	void Solve(); //��׺���ʽ��ֵ 
	bool isoperator(char op); 
private:
	string infExp; //��׺���ʽ 
	string sufExp; //��׺���ʽ
	bool status = 1;
};

void Calculator::Run() {
	double result;
	Equvar(); //��׺���ʽ�ȼ۱任Ϊ��׺���ʽ
	if(status) {
		Solve(); //��׺���ʽ��ֵ
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


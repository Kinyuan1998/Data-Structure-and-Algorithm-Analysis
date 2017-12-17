#include <iostream>
#include <fstream>
#include <queue>
#include <string> 
using namespace std;

typedef struct HuffmanTree {
	//���������ṹ�� 
    char ch;
    int frq;
    string code;
    HuffmanTree *left, *right;
    Tree() {
    	ch = '\0';
    	code = "";
    	frq = 0;
    	left = right = NULL;
	}
}Tree, *PTree;

struct cmp {
	bool operator()(Tree const *a, Tree const *b) {
        return a->frq > b->frq;
    }
};

//���� 
void Encode(PTree current, ofstream &out) {
	if (current->ch != '\0')
		out << current->ch << "��" << current->code << endl;
	else {
		current->left->code = current->code + "0";
        current->right->code = current->code + "1";
		Encode(current->left, out);
	    Encode(current->right, out);
	}
}

//����
void Decode(PTree root, string s, ofstream &out) {
	PTree current = root;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '0') current = current->left;
		if (s[i] == '1') current = current->right;
		if (current->ch) {
			out << current->ch << " ";
			current = root;
		}
	}
}

int main (void) {
	int length;
	ifstream in;
	ofstream out;
	string inFile, outFile, str1, str2;
	
	//�����ļ������� 
	cout << "Please input the inputfile name(Encode):";
	cin >> inFile;
	in.open (inFile.c_str());
	
	while (!in) {
		cout << "Error in openning! Please input the correct inputfile name:";
		cin >> inFile;
		in.open (inFile.c_str());
	}
		
	getline(in, str1);
	in.clear(); 
	in.close();
	cout << "Please input the outputfile name(Encode):";
	cin >> outFile;
	out.open (outFile.c_str());

	//���� Tree�����ȶ���
    priority_queue<PTree, vector<PTree>, cmp> q;
    
	//ͳ����Ƶ 	
	for (int i = 65; i <= 90; i++) {
		int count = 0;
		for (int j = 0; j < str1.length(); j++)
			if(str1[j] == i) count++;
			
		if (count != 0) {
			Tree *node = new Tree;
			node->ch = i;
			node->frq += count;
			q.push(node);
		}
	}
	
	//��ɶ��й���
	while (q.size() != 1) {
		PTree node = new Tree;
		PTree nodel, noder;
		nodel = q.top();
	    q.pop();
	    noder = q.top();
	    q.pop();
	    
	    node->frq = nodel->frq + noder->frq;
	    node->left = nodel;
	    node->right = noder;
	    q.push(node);
	}
	
	//��������������� 
	PTree root = q.top();
	
	//ǰ���������������Ҷ�ӽڵ� 
	Encode(root, out);
	out.clear();
	out.close();
	
	//�����ļ������� 
	cout << "Please input the inputfile name(Decode):";
	cin >> inFile;
	in.open (inFile.c_str());
	
	while (!in) {
		cout << "Error in openning! Please input the correct inputfile name:";
		cin >> inFile;
		in.open (inFile.c_str());
	}
	
	getline(in, str2);
	in.close();
	cout << "Please input the outputfile name(Decode):";
	cin >> outFile;
	out.open (outFile.c_str());
	
	root = q.top();
	Decode(root, str2, out);
	out.close();
	
    return 0;
} 

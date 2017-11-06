#include <iostream>
#include <fstream> 
#include <string>
#include <stdlib.h> 
using namespace std;

class DblNode {		//结点类 
	string str;
	DblNode *back;
	DblNode *next;
	
public:
	friend class DblLinkList;
	DblNode() {back = next = NULL;}
	DblNode(string s, DblNode *linkback = NULL, DblNode *linknext = NULL):str(s), back(linkback), next(linknext) {}
};

class DblLinkList {		//链表类 
	DblNode *head, *current;
	
public:
	DblLinkList();
	DblLinkList(string s);
	~DblLinkList();
	int length();
	int location();
	bool empty();
	bool next();
	bool prior();
	bool begin();
	bool find(int n);
	bool insert(int n, string s);
	void change(string s);
	void clear();
	void Traverse();
	void remove();
	string getstr();
};

DblLinkList::DblLinkList() {
	head = new DblNode();
	current = NULL;
}

DblLinkList::DblLinkList(string s) {
	head = new DblNode(s);
	current = NULL;
}

DblLinkList::~DblLinkList() {
	clear();
	delete head;
}

int DblLinkList::length() {
	int count = 0;
	for (DblNode *p = head; p -> next != NULL; p = p -> next) {
		count++;
	}
    return count;
}

int DblLinkList::location() {
    int count = 1;
    for (DblNode *p = current; p != head -> next; p = p -> back) {
		count++;
	}
    return count;
}

bool DblLinkList::empty() {
	return length() == 0;
}

bool DblLinkList::begin() {
	find(1);
	return 1;
    if (current = NULL)
		return 0;
}

bool DblLinkList::next() {
	if (current -> next == NULL ) {
		return 0;
	}
    current = current -> next;
	return 1;

}

bool DblLinkList::prior() {
	if (current -> back == head ) {
		return 0; 
	}
    current = current -> back;
	return 1;
}

bool DblLinkList::find(int n) {
	current = head;
    if ( n < 0 || n > length())
    	return 0;
    for( int i = 0; i < n; i++)
    	current = current -> next;
    return 1;
}

bool DblLinkList::insert(int n, string s) {
	if (current == NULL)
         current = head -> next = new DblNode (s, head, NULL);
	else {
		if (!find(n - 1))
			return 0;
		current -> next = new DblNode (s, current, current -> next);
		current = current -> next;
		}
		if (current -> next != NULL)
			current -> next -> back = current;
		return 1; 
	}

void DblLinkList::change(string t) {
	current -> str = t;
}

void DblLinkList::clear() {
	find(1);
	while (length() > 0) {
		remove();
	}
}

void DblLinkList::Traverse() {
	if (begin()) {
		for (int i = 1; i < length(); i++) {
			cout << current -> str << endl;
			current = current -> next;
		}
		cout << current -> str << endl;
			
	}
	else {
		cout << "Empty!" << endl;
	}
}

void DblLinkList::remove() {
	if (current != NULL) {
		current -> back -> next = current -> next;
		if (current -> next != NULL)
    		current -> next -> back = current -> back;
    	current = current -> back;
	}
   if (current == head)
       if (empty()) current = NULL;
       else {
       	cout << "Warning: At head node!" << endl;
       	current = current -> next;
	   }
}

string DblLinkList::getstr() {
	return current -> str;
}

int main(void) {
	char command;
	string inputfile, temp;
	cout << "Please input the inputfile name:";
	cin >> inputfile;
	ifstream icin;
	ofstream icout;
	icin.open (inputfile.c_str());
	while (!icin) {
		cout << "Error in openning! Please input the correct inputfile name:";
		cin >> inputfile;
		icin.open (inputfile.c_str());
	}
    DblLinkList editor;
    
    int read = 1;
	while (getline(icin, temp)) {
		if (!editor.insert(read, temp)) {
			cout << "insert error!" << endl;
			break;
		}
		read++;
	}
	icin.close();
	cout << "Please enter commands('h' for help):\n**";
	cin >> command;
    do {
    	int line;
    	string s, t;
    	switch (command) {
	    	case'h':cout << "Valid commands are:" << endl;
					cout << "f(irstline) e(ndline) c(hange) s(earch) d(elete)" << endl;	
					cout << "g(oto) h(elp) l(ength) n(ext) p(rior) a(sum up)" << endl;
					cout << "q(uit) i(nsert) r(eplace) t(raverse) v(save)" << endl;
					break;
			case'f':editor.find(1); break;
			case'e':editor.find(editor.length()); break;
			case'c':cout << "Which substring?:";
					fflush(stdin);
					getline(cin, s);
					line = 0;
					cout << "Please input the replacement:";
					fflush(stdin);
					getline(cin, t);
					for (int i = 1; i <= editor.length(); i++) {
						editor.find(i);
						if (editor.getstr().find(s) != string::npos) {
							editor.change(editor.getstr().replace(editor.getstr().find(s), s.length(), t));
							line++;
						}
					}
					if (line == 0) cout << "Error in changling! Not found!" << endl;
					else cout << "Succeed!" << endl;
					break;
			case'd':editor.remove(); cout << "Current line has been deleted successfully!" << endl; break;
			case's':cout << "Which substring?:";
					fflush(stdin);
					getline(cin, s);
					line = 0;
					for (int i = 1; i <= editor.length(); i++) {
						editor.find(i);
						if (editor.getstr().find(s) != string::npos) {
							cout << "It is at the line " << i << " at " << editor.getstr().find(s) << endl;
							line++;
						}
					}
					if (line == 0) cout << "Not found!" << endl;
					break;
			case'g':cout << "Which line?:";
					cin >> line;
					editor.find(line);
					break;
			case'i':cout << "After which line?:";
					cin >> line;
					fflush(stdin);
					cout << "Please input the string:";
					getline(cin, s);
					editor.insert(line, s);
					break;
			case'n':if (!editor.next()) cout << "Warning: at end of buffer!"; break;
			case'p':if (!editor.prior()) cout << "Warning: at start of buffer!"; break;
			case'q':cout << "Bye!"; exit(0);
			case'l':cout << editor.length() << endl; break;
			case'r':cout << "Which line?:";
					cin >> line;
					editor.find(line);
					editor.remove();
					fflush(stdin);
					cout << "Please input the replacement:";
					getline(cin, s);
					editor.insert(line, s);
					break;
			case't':editor.Traverse(); break;
			case'v':editor.begin();
					icout.open(inputfile.c_str());
					for(int i = 1; i < editor.length(); i++) {
						icout << editor.getstr() << "\n";
					  	editor.find(i + 1);
					}
					icout << editor.getstr();
					icout.close();
					cout << "Saved!" << endl;
					break;
			case'a':line = 0;
					for (int i = 1; i <= editor.length(); i++) {
						editor.find(i);
						line += editor.getstr().length();
						}
					cout << "Characters add up to:" << line << endl;
					break;
					
			default:cout << "Command error!" << endl; break;
		}
		cout << "\n" << editor.location() << ":" << editor.getstr() << endl;
		cout << "\nPlease enter commands:\n**";
	} while (cin >> command);
    return 0;
}

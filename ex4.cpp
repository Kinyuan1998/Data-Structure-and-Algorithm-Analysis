#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Course {
	string number, name, prior1, prior2;
	int period, semester;
	Course() {
		period = semester = 0;
		name = number = prior1 = prior2 = "";
	}
};

//边表节点结构，adjvex存储邻接点的位置，next指针指向下一个节点
typedef struct EdgeNode {
	int adjvex;
	struct EdgeNode *next;
}EdgeNode;
 
//顶点表节点结构，data存储数据，firstedge指向边表的第一个节点
typedef struct {
	Course data;
	EdgeNode *firstedge;
}AdjList;

//numVertex, numEdge是图的顶点数和边数
typedef struct {
	AdjList adjList[38];
	int numVertex, numEdge;
}GraphAdjList;

void CreateGraph(GraphAdjList &G, Course cr[]) {
	int temp = 0;
	EdgeNode *e;
	G.numVertex = 38;
	for (int i = 0; i < 38; i++) {
		if (cr[i].prior1 != "") temp++;
		if (cr[i].prior2 != "") temp++;
		G.adjList[i].data = cr[i];
	}
	G.numEdge = temp;
	for (int i = 0; i < G.numVertex; i++) {
        G.adjList[i].firstedge = NULL;
        for (int j = 0; j < G.numVertex; j++) {
        	if ((cr[j].prior1 == cr[i].number) || (cr[j].prior2 == cr[i].number)) {
				if (G.adjList[i].firstedge == NULL) {
					e = new EdgeNode;
					e->adjvex = j;
		            e->next = NULL;
		            G.adjList[i].firstedge = e;
				}
				else {
					EdgeNode *p = G.adjList[i].firstedge;
					while (p->next != NULL) p = p->next;
		            e = new EdgeNode;
		            e->adjvex = j;
		            e->next = NULL;
		            p->next = e;
				}
			}
   		}
    }
    
}

void Toposort(GraphAdjList gl) {
	//定义存储图中每个顶点入度的一维整型数组d
	int *d = new int[38];
	//初始化数组d中的每个元素值为0
	for(int i = 0; i < gl.numVertex; i++) d[i] = 0;
	//利用数组d中的对应元素统计出每个顶点的入度
	for (int i = 0; i < gl.numVertex; i++) {
    		for (int j = 0; j < gl.numVertex; j++) {
	    		EdgeNode *e = gl.adjList[j].firstedge;
	        	while(e) {
	           	 if (i == e->adjvex) d[i]++;
	            	e = e->next;
	       		}
		}
    }
    
    //设置学期 
	for (int i = 1; i <= 8; i++) {
    		vector<int> count;
    		int limit; 
    		for(int j = 0; j < gl.numVertex; j++) {
			if ((d[j] == 0) && (gl.adjList[j].data.semester == 0)) count.push_back(j);
		}
		
		switch(i) {
			case 1:
				limit = 4;
				cout << "第一学期： ";
				break;
			case 2:
				limit = 6;
				cout << "第二学期： ";
				break;
			case 3:
				limit = 2;
				cout << "第三学期： ";
				break;
			case 4:
				limit = 6;
				cout << "第四学期： ";
				break;
			case 5:
				limit = 4;
				cout << "第五学期： ";
				break;
			case 6:
				limit = 4;
				cout << "第六学期： ";
				break;
			case 7:
				limit = 4;
				cout << "第七学期： ";
				break;
			case 8:
				limit = 0;
				cout << "第八学期： ";
				break;
		}
		
		for (int j = 0; j < limit; j++) {
			gl.adjList[count[j]].data.semester += i;
			EdgeNode *e = gl.adjList[count[j]].firstedge;
			while(e) {
	            d[e->adjvex]--;
	            e = e->next;
	        }
		}
		
		for(int j = 0; j < gl.numVertex; j++) {
			if (gl.adjList[j].data.semester == i) cout << gl.adjList[j].data.name << " ";
		}
		cout << endl; 
	}
}

int main(void) {
	ifstream in;
	string str, temp;
	vector<string> res;
	Course cr[38];
	GraphAdjList gr;
	in.open ("course_inf.txt");
	
	//信息分块 
	for (int j = 0; j < 38; j++) {
		getline(in, str);
		string s;
		stringstream input(str);
		while(input >> temp)
        	res.push_back(temp);
        for(int i = 0; i < res.size(); i++) {
        	stringstream ss(res[i]);
        	switch(i) {
        		case 0:
				ss >> cr[j].number;
				break;
        		case 1:
				ss >> cr[j].name;
				break;
        		case 2:
				ss >> cr[j].period;
				break;
        		case 3:
        			ss >> cr[j].semester;
        			break;
        		case 4:
        			ss >> cr[j].prior1;
        			break;
        		case 5:
        			ss >> cr[j].prior2;
        			break;
			}
		}
		res.clear();
	}
	CreateGraph(gr, cr);
	Toposort(gr);
	
	return 0;
}

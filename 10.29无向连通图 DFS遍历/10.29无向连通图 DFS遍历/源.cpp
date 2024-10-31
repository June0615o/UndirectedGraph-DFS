#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int data;                     //Node中的data为顶点的标记. 例如0表示第一个顶点. 
	Node* next;
	Node(int givenData) {
		this->data = givenData;
		this->next = nullptr;
	}
};

/*
     Insert函数 在传入头指针的链表末尾插入元素
	                                             */
void Insert(Node*& head, int givenData) {             
	Node* newNode = new Node(givenData);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void showList(Node* head) {
	Node* current = head;
	while (current->next != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	if (current->next == nullptr) {
		cout << current->data;
	}
	cout << endl;
}

void DFS(Node* vertex, vector<bool>& visited, vector<int>& result, const vector<Node*>& vertexVector) {
	if (vertex == nullptr) {
		return;
	}
	//标记当前节点为已访问
	visited[vertex -> data] = true;
	result.push_back(vertex->data);
	//获取邻接点的链表序列
	vector<int> neighbors;
	Node* current = vertex->next;
	while (current != nullptr) {
		neighbors.push_back(current->data);
		current = current->next;
	}
	sort(neighbors.begin(), neighbors.end());
	//递归访问邻接点
	for (int neighbor : neighbors) {
		if (!visited[neighbor]) {
			DFS(vertexVector[neighbor], visited, result,vertexVector);
		}
	}
}


/*
          如果需要访问特定结点的连接关系,可以使用showList
                                                                 */
int main() {
	int operation;
	cin >> operation;
	for (int i = 0; i < operation; i++) {
		cin.ignore();
		int n, e, s; //n个顶点 e条边 从s开始访问其连接关系
		cin >> n >> e >> s;
		vector<Node*> vertexVector; //存储顶点以及其连接关系的容器 vertexVector
		for (int a = 0; a < n; a++) {
			vertexVector.push_back(new Node(a));
		}
		for (int E = 0; E < e; E++) { //载入边连接关系
			int startVertex, endVertex = 0;
			cin >> startVertex >> endVertex;
			Insert(vertexVector[startVertex], endVertex);
			Insert(vertexVector[endVertex], startVertex);
		}
		vector<bool>visited(n, false);
		vector<int>result;
		DFS(vertexVector[s],visited,result,vertexVector);
		for (int j = 0; j < result.size(); j++) {
			if (j != result.size() - 1) {
				cout << result[j] << " ";
			}
			else {
				cout << result[j];
			}
		}
		cout << endl;
	}
	return 0;
}
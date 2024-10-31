#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int data;                     //Node�е�dataΪ����ı��. ����0��ʾ��һ������. 
	Node* next;
	Node(int givenData) {
		this->data = givenData;
		this->next = nullptr;
	}
};

/*
     Insert���� �ڴ���ͷָ�������ĩβ����Ԫ��
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
	//��ǵ�ǰ�ڵ�Ϊ�ѷ���
	visited[vertex -> data] = true;
	result.push_back(vertex->data);
	//��ȡ�ڽӵ����������
	vector<int> neighbors;
	Node* current = vertex->next;
	while (current != nullptr) {
		neighbors.push_back(current->data);
		current = current->next;
	}
	sort(neighbors.begin(), neighbors.end());
	//�ݹ�����ڽӵ�
	for (int neighbor : neighbors) {
		if (!visited[neighbor]) {
			DFS(vertexVector[neighbor], visited, result,vertexVector);
		}
	}
}


/*
          �����Ҫ�����ض��������ӹ�ϵ,����ʹ��showList
                                                                 */
int main() {
	int operation;
	cin >> operation;
	for (int i = 0; i < operation; i++) {
		cin.ignore();
		int n, e, s; //n������ e���� ��s��ʼ���������ӹ�ϵ
		cin >> n >> e >> s;
		vector<Node*> vertexVector; //�洢�����Լ������ӹ�ϵ������ vertexVector
		for (int a = 0; a < n; a++) {
			vertexVector.push_back(new Node(a));
		}
		for (int E = 0; E < e; E++) { //��������ӹ�ϵ
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
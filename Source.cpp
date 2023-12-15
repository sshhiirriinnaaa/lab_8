#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <fstream>  

using namespace std; 

struct Node {
	int data;
	Node* next;
};


void printAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Vertex " << i << " is adjacent to: ";
			Node* current = adjacencyList[i];
			while (current != nullptr) {
				cout << current->data << " ";
				current = current->next;
			} if (current == nullptr) cout << i <<" ";
		cout << endl;
	}
}

Node** adjacencyMatrixToAdjacencyList(int** matrix, int size) {
	Node** adjacencyList = new Node * [size];

	for (int i = 0; i < size; i++) {
		adjacencyList[i] = nullptr; 

		for (int j = size - 1; j >= 0; j--) { 
			if (matrix[i][j] == 1) {
				Node* newNode = new Node;
				newNode->data = j;
				newNode->next = adjacencyList[i];
				adjacencyList[i] = newNode;
			}
		}
	}

	return adjacencyList;
}



void freeAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] adjacencyList;
}

int** createMatrix(int size) {
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	return matrix;
}


void deleteMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}


void fillMatrixRandom(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else {
				int randomValue = rand() % 2;
				matrix[i][j] = randomValue;
				matrix[j][i] = randomValue; 
			}
		}
	}
}


void printMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j];
			cout << ", ";

		}
		cout << endl;
	}
}
int summMatrix(int** matrix, int size) {
	int summ = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			summ += matrix[i][j];
		}
	}
	return summ;
}

int* breadthFirstSearch(int** graph, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; 
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (graph[currentVertex][i] == 1 && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	return traversalOrder;
}


int* bfsTraversal(Node** adjacencyList, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		
		Node* current = adjacencyList[currentVertex];
		while (current != nullptr) {
			int neighbor = current->data;
			if (!visited[neighbor]) {
				q.push(neighbor);
				visited[neighbor] = true;
			}
			current = current->next;
		}
	}

	delete[] visited;
	return traversalOrder;
}


void addEdge(Node** adjacencyList, int vertex, int data) {
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = adjacencyList[vertex];
	adjacencyList[vertex] = newNode;
}



struct QueueNode {
	int data;
	QueueNode* next;
};


struct Queue {
	QueueNode* front;
	QueueNode* rear;
};


Queue* createQueue() {
	Queue* queue = new Queue;
	queue->front = queue->rear = nullptr;
	return queue;
}


bool isEmpty(Queue* queue) {
	return queue->front == nullptr;
}


void enqueue(Queue* queue, int data) {
	QueueNode* newNode = new QueueNode;
	newNode->data = data;
	newNode->next = nullptr;

	if (isEmpty(queue)) {
		queue->front = queue->rear = newNode;
		return;
	}

	queue->rear->next = newNode;
	queue->rear = newNode;
}


int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		cerr << "Очередь пуста!" << endl;
		return -1; 
	}

	int data = queue->front->data;
	QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	delete temp;

	if (queue->front == nullptr) {
		queue->rear = nullptr;
	}

	return data;
}

int* BFScustomList(int** matrix, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; 
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	Queue* queue = createQueue();
	enqueue(queue, startVertex);
	visited[startVertex] = true;

	while (!isEmpty(queue)) {
		int currentVertex = dequeue(queue);
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (matrix[currentVertex][i] == 1 && !visited[i]) {
				enqueue(queue, i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	delete(queue);

	return traversalOrder;
}



int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int choice;

	do {

		cout << "Меню:" << endl;
		cout << "1. генерация матрицы и поиск в ширину" << endl;
		cout << "2. тест алгоритмов обхода в ширину" << endl;
		cout << "3. Выход" << endl;


		cout << "Пожалуйста, введите номер выбранного пункта: ";
		cin >> choice;


		switch (choice) {
		case 1: {
			cout << "Вы выбрали пункт 1." << endl;

			int size;
			cout << "\nВведите размер матрицы смежности: ";
			cin >> size;
			int** adjacencyMatrix = createMatrix(size);
			fillMatrixRandom(adjacencyMatrix, size);
			printMatrix(adjacencyMatrix, size);

			cout << "\nAdjacency List:\n";
			Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
			printAdjacencyList(adjacencyList, size);

			int startVertex;
			cout << "Введите начальную вершину для обхода: ";
			cin >> startVertex; cout << "\n";
			if (startVertex > size - 1) {
				cout << "its too much" << endl;
				break;
			}
			else {
				int sum = summMatrix(adjacencyMatrix, size);
				if (sum == 0) {
					cout << "нету" << endl;
					break;
				}
				else {
					int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);


					for (int i = 0; i < size; i++) {
						cout << traversalOrder[i] << " ";
					}

					cout << " ВbreadthFirstSearch\n" << endl;
					delete[] traversalOrder;

					int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);


					for (int i = 0; i < size; i++) {
						cout << traversalOrder1[i] << " ";
					}
					cout << " bfsTraversal\n" << endl;

					delete[] traversalOrder1;

					int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);

					for (int i = 0; i < size; i++) {
						cout << traversalOrder2[i] << " ";
					}

					delete[] traversalOrder2;

					cout << " BFScustomList\n" << endl;

					deleteMatrix(adjacencyMatrix, size);
				}
			}
				break;
			} 
		case 2: {
			cout << "Вы выбрали пункт 2." << endl;


			int sizes[] = { 1000, 2000, 5000 };

			ofstream outputFile("graph_traversal_times.txt");
			if (!outputFile.is_open()) {
				cerr << "Failed to open the output file." << endl;
				return 1;
			}

			outputFile << "Matrix Size\tBFS Matrix (s)\tBFS List (s)\tBFS Custom (s)\n";

			for (int i = 0; i < 3; i++) {
				int size = sizes[i];
				int** adjacencyMatrix = createMatrix(size);
				fillMatrixRandom(adjacencyMatrix, size);

				Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
				int startVertex = 0;

				clock_t startTime, endTime;

				startTime = clock();
				int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsMatrixTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder;

				startTime = clock();
				int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);
				endTime = clock();
				double bfsListTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder1;


				startTime = clock();
				int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsCustomTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder2;

				outputFile << size << "\t\t" << bfsMatrixTime << "\t\t" << bfsListTime << "\t\t" << bfsCustomTime << "\n";

				deleteMatrix(adjacencyMatrix, size);
				freeAdjacencyList(adjacencyList, size);
			}


			outputFile.close();

			break; }
		case 3:
			cout << "Выход." << endl;
			break;
		default:
			cout << "Неправильный выбор. Пожалуйста, введите верный номер пункта." << endl;
			break;
		}

	} while (choice != 3);

	return 0;
}
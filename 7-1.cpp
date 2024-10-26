#include<iostream>
#include<vector>
using namespace std;

class MaxHeap {
public:
	int maxElement;
	int minElement;
	int* heap;
	int size;//当前大小
	int capacity;
	MaxHeap(int max, int min, int n = 10) {
		capacity = n;
		size = 0;
		heap = new int[capacity * 2 + 1];
		maxElement = max;
		minElement = min;
		heap[size++] = maxElement;
		for (int i = capacity + 1; i < capacity * 2 + 1; i++) {
			heap[i] = minElement;
		}
	}

	void Push(int data) {
		heap[size++] = data;
		int curIndex = size - 1;
		while (curIndex > 1 && heap[curIndex] > heap[curIndex / 2]) {
			swap(heap[curIndex], heap[curIndex / 2]);
			curIndex /= 2;
		}
	}

	//删最大元素
	void Pop() {
		if (size <= 1) {
			cout << "Heap Is Empty" << endl;
			return;
		}
		else if (size == 2) {
			if (heap[1] < heap[2]) {
				swap(heap[1], heap[2]);
			}
			return;
		}
		heap[1] = heap[size - 1];
		size--;
		int maxIndex = 1;
		int curIndex = 1;
		do {
			curIndex *= 2;
			if (heap[curIndex] < heap[curIndex + 1]) {
				curIndex++;
			}
			if (heap[maxIndex] < heap[curIndex]) {
				swap(heap[maxIndex], heap[curIndex]);
			}
			else
				break;
		} while (curIndex < size);
	}

	void Print() {
		for (int i = 1; i < size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};
int main() {
	MaxHeap myHeap(1000, -1000); 

	myHeap.Push(10);
	myHeap.Push(20);
	myHeap.Push(5);
	myHeap.Push(30);
	myHeap.Push(25);

	myHeap.Print();

	myHeap.Pop();
	myHeap.Print();

	myHeap.Pop();
	myHeap.Print();
	return 0;
}
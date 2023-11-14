#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename Item_Type>
struct queueNode {
    Item_Type qData;
    queueNode* next;

    queueNode(const Item_Type& item) : qData(item), next(nullptr) {}	//default Node constructor
};

template <typename Item_Type>
class Queue {
private:
	queueNode<Item_Type>* front;
	queueNode<Item_Type>* rear;
	int num_items;

public:
	Queue();
	void enQueue(const Item_Type& item); //add qData item to the end of the queue
	Item_Type deQueue();     //remove a qData item from the front of the queue
	Item_Type queueFront();        //return the element at the front of the queue
	bool isEmpty();           //return true if the queue is empty (front = nullptr?), false otherwise
	int queueTotal() const;		//return the number of items in the queue
	void printQueue() const;	//print all items in Queue
};

#include "Queue.h"

template <typename Item_Type>
Queue<Item_Type>::Queue() {		//default Queue constructor
	front = nullptr;
	rear = nullptr;
	num_items = 0;
}

template <typename Item_Type>
void Queue<Item_Type>::enQueue(const Item_Type& item) {
	queueNode<Item_Type>* tempQNode = new queueNode<Item_Type>(item);
	if (rear == nullptr) {	//If rear is null, queue is empty so assign new tempQNode to front and rear
		front = rear = tempQNode;
	}
	else { //else, place new tempQNode after the last Node in queue
		rear->next = tempQNode;
		rear = tempQNode;
	}
	++num_items; //increase number of items in queue by 1
}

template <typename Item_Type>
Item_Type Queue<Item_Type>::deQueue() {

	if (front == nullptr) {		//Can't remove if queue is empty, throw error
		throw runtime_error("Queue is EMPTY!");
	}
	
	Item_Type item = front->qData;		//assign item to the data of front Node
	queueNode<Item_Type>* delQNode = front;		//assign delQNode to front Node
	front = front->next;	//front Node becomes the next Node after front one

	if (front == nullptr)	//reset the queue if front becomes null
		rear = nullptr;

	delete delQNode;		//delete the previous front Node
	delQNode = nullptr;
	
	//decrease the count of items in Queue and return deleted item
	--num_items;
	return item; 
}


template <typename Item_Type>
Item_Type Queue<Item_Type>::queueFront() {	//Returns the data of the node at the front of the queue
	if (front != nullptr)
		return front->qData;
	else
		cout << "Queue is EMPTY!\n";		//or prints message that Queue is empty if front is null
}

template <typename Item_Type>
bool Queue<Item_Type>::isEmpty() {	//Returns true if front is null meaning Queue is empty, else returns false
	if (front == nullptr)
		return true;
	return false;
}

template <typename Item_Type>
int Queue<Item_Type>::queueTotal() const {	//Returns the int num_items initially set to 0 when Queue is created
	return num_items;
}

template <typename Item_Type>
void Queue<Item_Type>::printQueue() const {
	//start at front of Queue and print the data of every Node until it reaches end
	queueNode<Item_Type>* currentQNode = front;		
	while (currentQNode != nullptr) { 
		cout << currentQNode->qData << ", ";
		currentQNode = currentQNode->next;
	}
}

template class Queue<int>;
template class Queue<double>;
template class Queue<string>;
template class Queue<char>;
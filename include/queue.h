#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>


struct QNode {
	int pid;
	std::string name;
	struct QNode* next;
};

class ProcessQueue
{
public:
	ProcessQueue();
	int getCount(){return this->count;};
	void push_back(int k, std::string name);
	void pop_front();
	bool isEmpty();
	bool printQueue();
	
	ProcessQueue* findNameInQueue(std::string name);
	ProcessQueue* findPidInQueue(int k);
	bool printNameFromQueue();
	bool printPidFromQueue();
	bool deleteQueue();

private:
	struct QNode* newNode(int k, std::string name);

	int count;
	struct QNode *front;
	struct QNode *rear;
};

#endif // QUEUE_H

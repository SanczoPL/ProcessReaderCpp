#include "../include/queue.h"

//#define DEBUG

static const std::string logEnd = "\x1b[0m";
static const std::string logDebug = "\x1b[32m";

ProcessQueue::ProcessQueue()
{
	this->front = this->rear = NULL;
	this->count = 0;
}

void ProcessQueue::push_back(int k, std::string name)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: pushQueue(" << k << "," << name << ")" << logEnd << std::endl;
	#endif
	struct QNode* temp = newNode(k, name);

	if (this->rear == NULL) 
	{
		this->front = this->rear = temp;
		this->count++;
		return;
	}

	this->rear->next = temp;
	this->rear = temp;
	this->count++;
}

bool ProcessQueue::isEmpty()
{
	return (this->rear == NULL);
}

struct QNode* ProcessQueue::newNode(int k, std::string name)
{
	struct QNode* temp = new struct QNode();
	temp->pid = k;
	temp->name = name;
	temp->next = NULL;
	return temp;
}

void ProcessQueue::pop_front()
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: pop_front()" << logEnd << std::endl;
	#endif

	if (this->front == NULL) 
	{
		return;
	}

	struct QNode* temp = this->front;

	if (this->front->next == NULL) 
	{
		this->front = NULL;
		this->count--;
		this->rear = NULL;
		delete(temp);
		return;
	}

	this->front = this->front->next;
	if (this->front == NULL) 
	{
		this->rear = NULL;
	}
	this->count--;

	delete(temp);
}

bool ProcessQueue::printQueue()
{
	bool returnFlag = false;
	if (!this->isEmpty()) 
	{
		returnFlag = true;
		struct QNode* temp = this->front;

		while (temp != NULL) 
		{
			std::cout << temp->name << " " << temp->pid << logEnd << std::endl;
			if (temp->next == NULL)
			{
				break;
			}
			temp = temp->next;
		}
	}
	return returnFlag;
}

ProcessQueue* ProcessQueue::findNameInQueue(std::string name)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: pop_front(" << name << ")" << logEnd << std::endl;
	#endif
	ProcessQueue* outQueue = new ProcessQueue();

	if (this->front == NULL) 
	{
		#ifdef DEBUG
		std::cout<< logDebug << "DEBUG: queue is empty" << logEnd << std::endl;
		#endif
		return outQueue;
	}
	struct QNode* temp = this->front;
	while (temp != NULL) 
	{
		if (name == temp->name) 
		{
			outQueue->push_back(temp->pid, temp->name);
		}
		if (temp->next == NULL) 
		{
			break;
		}
		temp = temp->next;
	}

	return outQueue;
}


ProcessQueue* ProcessQueue::findPidInQueue(int k)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: findPidInQueue()" << logEnd << std::endl;
	#endif
	ProcessQueue* outQueue = new ProcessQueue();

	if (this->front == NULL) 
	{
		return outQueue;
	}
	struct QNode* temp = this->front;

	while (temp != NULL) 
	{
		if (k == temp->pid) 
		{
			outQueue->push_back(temp->pid, temp->name);
		}
		if (temp->next == NULL) 
		{
			break;
		}
		temp = temp->next;
	}
	return outQueue;
}

bool ProcessQueue::printNameFromQueue()
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: printNameFromQueue()" << logEnd << std::endl;
	#endif

	bool returnFlag{false};
	if (!this->isEmpty())
	{
		returnFlag = true;
		struct QNode* temp = this->front;

		while (temp != NULL)
		{
			std::cout << temp->name << std::endl;
			if (temp->next == NULL)
			{
				break;
			}
			temp = temp->next;
		}
	}
	return returnFlag;
}

bool ProcessQueue::printPidFromQueue()
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: printPidFromQueue()" << logEnd << std::endl;
	#endif
	bool returnFlag = false;
	if (!this->isEmpty()) {
		returnFlag = true;
		struct QNode* temp = this->front;

		while (temp != NULL) {
			std::cout << temp->pid << std::endl;
			if (temp->next == NULL) {
				break;
			}
			temp = temp->next;
		}
	}
	return returnFlag;
}

bool ProcessQueue::deleteQueue()
{
#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: deleteQueue()" << logEnd << std::endl;
#endif

	while (this->front != NULL) 
	{
		pop_front();
	}
	if (this->rear == NULL && this->front == NULL) 
	{
		return true;
	}
	return false;
}
#ifndef PROCESS_READER_H
#define PROCESS_READER_H

#include "queue.h"


#include <iostream>
#include <fstream>

class ProcessReader
{
public:
	ProcessReader(std::string & procDirInput);

	bool printProcess();
	bool showName(std::string& pid);
	bool showPid(std::string & name);
	static bool checkIsDigit(const std::string& input);
	
private:
	void readProcessIntoQueue();
	void getPid(std::string & name, std::string & path);
private:
	ProcessQueue m_queue;
	std::string m_procDirInput;
};

#endif // PROCESS_READER_H
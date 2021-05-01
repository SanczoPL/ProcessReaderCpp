#ifndef PROCESS_READER_H
#define PROCESS_READER_H

#include "queue.h"

#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>

class ProcessReader
{
public:
	ProcessReader();
	bool printProcess(std::string procDirInput);
	bool showName(std::string& pid, std::string & procDirInput);
	bool showPid(std::string & name, std::string & procDirInput);

private:
	bool checkIsDigit(const std::string& input);
	void readProcessIntoQueue(std::string & procDirInput);
	void getPid(std::string & name, std::string & path);
private:
	ProcessQueue m_queue;
};

#endif // PROCESS_READER_H
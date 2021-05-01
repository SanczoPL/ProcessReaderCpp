#include "../include/processreader.h"
#include <QDir>

#define DEBUG

const std::string logError = "\x1b[31m";
const std::string logEnd = "\x1b[0m";
const std::string logWarn = "\x1b[33m";
const std::string logDebug = "\x1b[32m";

ProcessReader::ProcessReader(std::string & procDirInput)
:m_procDirInput(procDirInput)
{};

bool ProcessReader::printProcess()
{
	readProcessIntoQueue();
	return m_queue.printQueue();
}

bool ProcessReader::checkIsDigit(const std::string & input)
{
	std::string::const_iterator it = input.begin();
	while (it != input.end() && std::isdigit(*it)) ++it;
	return !input.empty() && it == input.end();
}

void ProcessReader::readProcessIntoQueue()
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: readProcessIntoQueue(" << m_procDirInput << ")" << logEnd<< std::endl;
	#endif
	QDir qDir(QString::fromStdString(m_procDirInput));
	QStringList dirs = qDir.entryList(QStringList(), QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	foreach (QString name, dirs)
	{
		std::string nameStd = name.toStdString();
		std::cout<< logDebug << "DEBUG: dir:" << nameStd << "" << logEnd<< std::endl;
		if (!checkIsDigit(nameStd)) 
		{
			continue;
		}
		std::string currentPath = m_procDirInput + "/" + nameStd + "/status";
		getPid(nameStd, currentPath);
		int pid = name.toInt();
		m_queue.push_back(pid, nameStd);
	}
	return;
}

void ProcessReader::getPid(std::string & name, std::string & path)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: getPid(" << path << ")" << logEnd<< std::endl;
	#endif
	std::string line;
	std::ifstream fs(path.c_str());
	if (fs.is_open())
	{
		fs >> line >> name;
		fs.close();
	}
	return;
}

bool ProcessReader::showName(std::string & pid)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: showName(" << pid << ")" << logEnd<< std::endl;
	#endif
	if (checkIsDigit(pid) == 0) {
		std::cout<< logDebug << "DEBUG: shcheckIsDigit == 0 :( " << logEnd<< std::endl;
		return false;
	}
	int pidInt = (QString::fromStdString(pid)).toInt();
	ProcessReader::readProcessIntoQueue();
	ProcessQueue* findQ = m_queue.findPidInQueue(pidInt);
	return findQ->printNameFromQueue();
}

bool ProcessReader::showPid(std::string & name)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: showPid(" << name << ")" << logEnd<< std::endl;
	#endif
	ProcessReader::readProcessIntoQueue();
	ProcessQueue* findQ = m_queue.findNameInQueue(name);
	return findQ->printPidFromQueue();
}

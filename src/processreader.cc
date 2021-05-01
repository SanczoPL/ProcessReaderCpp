#include "../include/processreader.h"
#include <QDir>

#define DEBUG

const std::string logError = "\x1b[31m";
const std::string logEnd = "\x1b[0m";
const std::string logWarn = "\x1b[33m";
const std::string logDebug = "\x1b[32m";

ProcessReader::ProcessReader(){};

bool ProcessReader::printProcess(std::string procDirInput)
{
	readProcessIntoQueue(procDirInput);
	m_queue.printQueue();
}

bool ProcessReader::checkIsDigit(const std::string& input)
{
	std::string::const_iterator it = input.begin();
	while (it != input.end() && std::isdigit(*it)) ++it;
	return !input.empty() && it == input.end();
}

void ProcessReader::readProcessIntoQueue(std::string & procDirInput)
{
	std::string currentPath;

	QDir qDir(QString::fromStdString(procDirInput));

	qDir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
	qDir.setSorting(QDir::Name);

	QStringList dirs = qDir.entryList(QStringList(), QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	foreach (QString name, dirs)
	{
		std::string nameStd = name.toStdString();
		std::cout<< logDebug << "DEBUG: dir:" << nameStd << "" << logEnd<< std::endl;
		if (!checkIsDigit(nameStd)) 
		{
			continue;
		}
		currentPath = procDirInput + "/" + nameStd + "/status";
		int pid = name.toInt();

		getPid(nameStd, currentPath);
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

bool ProcessReader::showName(std::string & pid, std::string & procDirInput)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: showName(" << pid << ")" << logEnd<< std::endl;
	#endif

	if (checkIsDigit(pid) == 0) {
		std::cout<< logDebug << "DEBUG: shcheckIsDigit == 0 :( " << logEnd<< std::endl;
		return false;
	}
	int pidInt = (QString::fromStdString(pid)).toInt();

	ProcessReader::readProcessIntoQueue(procDirInput);
	ProcessQueue* findQ = m_queue.findPidInQueue(pidInt);
	findQ->printNameFromQueue();


}

bool ProcessReader::showPid(std::string & name, std::string & procDirInput)
{
	#ifdef DEBUG
	printf("%sDEBUG: showPid(%s, %s)\n%s", logDebug, name, procDirInput, logEnd);
	#endif
	ProcessReader::readProcessIntoQueue(procDirInput);
	ProcessQueue* findQ = m_queue.findNameInQueue(name);
	findQ->printPidFromQueue();

}

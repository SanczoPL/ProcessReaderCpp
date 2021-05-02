#include "../include/processreader.h"

#include <stdio.h>
#include <fcntl.h>

//#define DEBUG

const std::string logError = "\x1b[31m";
const std::string logEnd = "\x1b[0m";
const std::string logWarn = "\x1b[33m";
const std::string logDebug = "\x1b[32m";
std::string procDir = "/proc";

int outputFile;
int save_outputFile;

void usage(char* progName);

void getOpt(int* argc,
	char* argv[],
	char* state,
	std::string & input_param,
	std::string & file_name);

void redirectStdout(char* name);

void stopRedirectStdout();

void showUsageAndExit(char* name);

int main(int argc, char* argv[])
{
	std::string input_param;
	std::string file_name;
	char state = 0;
	if (argc < 2) 
	{
		showUsageAndExit(argv[0]);
	}
	getOpt(&argc, argv, &state, input_param, file_name);

	#ifdef DEBUG
	std::cout << logDebug << "DEBUG: state:" << state << "" << logEnd<< std::endl;
	std::cout << logDebug << "DEBUG: input_param:" << input_param << "" << logEnd<< std::endl;
	#endif

	if (!state) 
	{
		showUsageAndExit(argv[0]);
	}

	ProcessReader pr(procDir);
	switch (state) 
	{
	case 1:
		pr.printProcess();
		break;
	case 2:
		pr.showName(input_param);
		break;
	case 3:
		pr.showPid(input_param);
		break;
	}
	if (file_name.size()) 
	{
		stopRedirectStdout();
	}
	return 0;
}

void usage(char* progName)
{
	std::cout << progName << "[Options] [Optional]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t-a        | show all process" << std::endl;
	std::cout << "\t-u <pid>  | show <pid> process name" << std::endl;
	std::cout << "\t-n <name> | show pid of process <name>" << std::endl;
	std::cout << "Optional:" << std::endl;
	std::cout << "\t-f <file> | save output to <file>" << std::endl;
}

void getOpt(int* argc,
	char* argv[],
	char* state,
	std::string & input_param,
	std::string & file_name)
{
	int opt = 0;
	while ((opt = getopt(*argc, argv, "au:n:f:")) != -1) 
	{
	#ifdef DEBUG
	std::cout << logDebug << "DEBUG: state:" << *state << "" << logEnd<< std::endl;
	#endif
		switch (opt) 
		{
		case 'a':
			if (*state > 0) 
			{
				showUsageAndExit(argv[0]);
			}
			*state = 1;
			break;
		case 'u':
			if (*state > 0) 
			{
				showUsageAndExit(argv[0]);
			}
			input_param = optarg;
			*state = 2;
			break;
		case 'n':
			if (*state > 0) 
			{
				showUsageAndExit(argv[0]);
			}
			input_param = optarg;
			*state = 3;
			break;
		case 'f':
			file_name = optarg;
			redirectStdout(optarg);
			break;
		default:
			showUsageAndExit(argv[0]);
			break;
		}
	}
}

void redirectStdout(char* name)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: redirectStdout("<< logEnd<< std::endl;
	#endif
	outputFile = open(name, O_RDWR | O_CREAT | O_APPEND, 0600);
	save_outputFile = dup(fileno(stdout));
	if (-1 == dup2(outputFile, fileno(stdout))) 
	{
		perror("cannot redirect stdout");
		exit(-55);
	}
}

void stopRedirectStdout()
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: stopRedirectStdout("<< logEnd<< std::endl;
	#endif
	fflush(stdout);
	close(outputFile);
	dup2(save_outputFile, fileno(stdout));
	close(save_outputFile);
}

void showUsageAndExit(char* name)
{
	#ifdef DEBUG
	std::cout<< logDebug << "DEBUG: showUsageAndExit("<< logEnd<< std::endl;
	#endif
	usage(name);
	exit(-1);
}

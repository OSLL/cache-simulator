#ifndef COMMAND_LINE_ARGUMENTS_H_
#define COMMAND_LINE_ARGUMENTS_H_
#include <QStringList>

class CommandLineArguments{

private:
	static QStringList s_arguments;
	
public: 

	static void init(int argc, char** argv);
	static bool isKeySet(const QString& key);

};
#endif

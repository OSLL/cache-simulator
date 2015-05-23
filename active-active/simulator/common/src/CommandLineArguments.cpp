#include "CommandLineArguments.h"

QStringList CommandLineArguments::s_arguments = QStringList();

void CommandLineArguments::init(int argc, char** argv)
{
	for (int i=0; i<argc; i++)
		s_arguments.append(argv[i]);
}

bool CommandLineArguments::isKeySet(const QString& key)
{
	return s_arguments.contains(key);
}

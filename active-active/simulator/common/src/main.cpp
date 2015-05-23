#include <QDebug>
#include <QCoreApplication>
#include <QtGlobal>
#include "SettingsReader.h"
#include "Modeler.h"
#include "ResultsFileWriter.h"
#include "CommandLineArguments.h"
#include "AAMessageHandler.h"



int main(int argc, char** argv )
{
    qInstallMsgHandler(AAMessageHandler);
	QCoreApplication app(argc, argv);
	if (argc < 2){
        qFatal( "Not enough arguments. Usage:\n./simulator settings_file [--verbose|--quiet]");
		return 1;
	}

	CommandLineArguments::init(argc, argv);
	// Initialize SettingsReader
	SettingsReader::init(argv[1]);
	ResultsFileWriter::getInstance();

	Modeler modeler;

	modeler.doModeling();

	delete ResultsFileWriter::getInstance();

	return 0;
}

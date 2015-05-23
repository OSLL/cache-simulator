#include "TestSettingsReader.h"
#include <QDebug>

#define TEST_FILE_NAME "test_settings.ini" 
#define TEST_KEY "TEST_KEY"
#define TEST_VALUE QString("TEST_VALUE")
#define TEST_VALUE1 QString("TEST_VALUE1")

TestSettingsReader::TestSettingsReader():QObject(){
	qDebug() << "Initializing TestSettingsReader::TestSettingsReader";
	SettingsReader::init(TEST_FILE_NAME);
}

void TestSettingsReader::testGetValue(){
	qDebug() << SettingsReader::getValue(TEST_KEY).toString();
	QCOMPARE(SettingsReader::getValue(TEST_KEY).toString(), TEST_VALUE);
}

void TestSettingsReader::testSetValue(){
	SettingsReader::setValue(TEST_KEY, TEST_VALUE1);
	QCOMPARE(SettingsReader::getValue(TEST_KEY).toString(), TEST_VALUE1);
	qDebug() << SettingsReader::getValue(TEST_KEY).toString();
	SettingsReader::setValue(TEST_KEY, TEST_VALUE);
	QCOMPARE(SettingsReader::getValue(TEST_KEY).toString(), TEST_VALUE);
	qDebug() << SettingsReader::getValue(TEST_KEY).toString();
}

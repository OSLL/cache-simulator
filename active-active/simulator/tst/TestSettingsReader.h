#ifndef TEST_SETTINGS_READER_H
#define TEST_SETTINGS_READER_H

#include <QObject>
#include <QtTest>
#include "SettingsReader.h"

class TestSettingsReader: public QObject{
		Q_OBJECT
	private slots:
		void testGetValue();
		void testSetValue();
	public:
		TestSettingsReader();
};

#endif

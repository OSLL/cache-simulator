#include <QtTest/QtTest>
#include <QtCore/QtCore>
#include <QCoreApplication>
#include "TestSettingsReader.h"
#include "TestLoadBalancers.h"
#include "TestEvent.h"
#include "TestReadAheadDecisionMakers.h"
#include "TestRedirectDecisionMaker.h"

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);

	QObject *tests[] =
	{
		new TestSettingsReader(),
		new TestLoadBalancers(),
        new TestEvent(),
        new TestReadAheadDecisionMakers(),
		new TestRedirectDecisionMaker()
	};

	for (unsigned int i = 0; i < sizeof(tests)/sizeof(QObject*); i++)
	{
		QTest::qExec(tests[i], argc, argv);
	}
	return 0;
}

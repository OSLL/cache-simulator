#ifndef TEST_REDIRECT_DECISION_MAKER_H
#define TEST_REDIRECT_DECISION_MAKER_H

#include <QDebug>
#include <QVariant>
#include <QtTest>
#include "RedirectDecisionMaker.h"


#define VALID_MAX_QUEUE_LENGTH 38

class TestRedirectDecisionMaker : public QObject
{
    Q_OBJECT
public:
    TestRedirectDecisionMaker(QObject *parent = 0): QObject(parent){}
private slots:
    void testMaxQueueSize(){
        RedirectDecisionMaker decisionMaker;
        qDebug() << "decisionMaker.getMaxICQueueLength()" << decisionMaker.getMaxICQueueLength();
	QVERIFY( decisionMaker.getMaxICQueueLength() == VALID_MAX_QUEUE_LENGTH );
    }

    void testDecisionMaking(){
        RedirectDecisionMaker decisionMaker;
        qulonglong testArray[] = { 23, 39, 40, 23, 23, 23, 23 };
	bool validResults[]    = { true, false, false, false, true, true, true };

	unsigned int length = sizeof(testArray) / sizeof(qulonglong*);

	for (unsigned int i = 0 ; i < length; i++){
		decisionMaker.stat(testArray[i]);
		qDebug() << "Step # " << i 
			<< ", made decision == "  
			<< decisionMaker.makeDecision() 
			<< ", valid decision == " << validResults[i];
		QVERIFY( decisionMaker.makeDecision() == testArray[i]);
	}
    }
};

#endif

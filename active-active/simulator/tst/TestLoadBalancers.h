#ifndef TEST_LOAD_BALANCERS_H
#define TEST_LOAD_BALANCERS_H

#include <QObject>
#include <QtTest>
#include "RoundRobin.h"
#include "MinQueueDepthAlgorithm.h"

class TestLoadBalancers: public QObject{
		Q_OBJECT
	private:
		RoundRobin m_roundRobin;
		MinQueueDepthAlgorithm m_minQueueDepth;

	private slots:
		void testRoundRobin();
		void testMinQueueDepth();
	public:
		TestLoadBalancers();
};

#endif

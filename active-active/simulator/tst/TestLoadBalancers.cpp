#include "TestLoadBalancers.h"
#include "SettingsReader.h"
#include "defines.h"
#include "StorageProcessorsStatistic.h"

#include <QDebug>

#define TEST_FILE_NAME "test_settings.ini" 
#define TEST_RR_WORKLOAD 3
#define TEST_REPEAT_COUNT 9
#define TEST_STEPS {0, 0, 0, 1, 1, 1, 0, 0, 0}

#define TEST_STAT0 10
#define TEST_STAT1 9
#define TEST_MIN_QUEUE_DEPTH_VALID_NUM 1

TestLoadBalancers::TestLoadBalancers(){
	SettingsReader::init(TEST_FILE_NAME);
	SettingsReader::setValue(RR_NODE_WORKLOAD, TEST_RR_WORKLOAD);
	m_roundRobin.init(SP_COUNT);
	m_minQueueDepth.init(SP_COUNT);
}

void TestLoadBalancers::testRoundRobin(){
	int validTestResults[] = TEST_STEPS;
	for (int i=0; i< TEST_REPEAT_COUNT; i++){
		QCOMPARE(validTestResults[i], m_roundRobin.getNodeNumber());
	}
}

void TestLoadBalancers::testMinQueueDepth(){
	StorageProcessorsStatistic* instance = StorageProcessorsStatistic::getInstance();
	instance->updateStatistic(0, TEST_STAT0);
	instance->updateStatistic(1, TEST_STAT1);

	QCOMPARE(TEST_MIN_QUEUE_DEPTH_VALID_NUM, m_minQueueDepth.getNodeNumber());
}



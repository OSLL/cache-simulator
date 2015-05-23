#include "RoundRobin.h"
#include "defines.h"
#include "SettingsReader.h"

#include <QDebug>


RoundRobin::RoundRobin()
{

}

void RoundRobin::init(int nodeCount){
    m_nodeCount = nodeCount;
    m_currentWorkLoad = 0;
    // Reading node workload from settings
    m_nodeWorkLoad = SettingsReader::getValue(RR_NODE_WORKLOAD).toInt();
    m_totalWorkLoad = m_nodeWorkLoad * m_nodeCount;
}


int RoundRobin::getNodeNumber(){

	int result = m_currentWorkLoad  / m_nodeWorkLoad;	
	m_currentWorkLoad = (m_currentWorkLoad + 1) % m_totalWorkLoad;

//	qDebug() << "RR: " << "m_currentWorkLoad =" <<m_currentWorkLoad<<
//		", result ="<< result;

	return result;

}

#ifndef ROUND_ROBIN_H_
#define ROUND_ROBIN_H_

#include "ILoadBalancingAlgorithm.h"

class RoundRobin: public ILoadBalancingAlgorithm{

private:
    int m_nodeCount;
	int m_nodeWorkLoad;
	int m_currentWorkLoad;
	int m_totalWorkLoad;

public:

    RoundRobin();

    int getNodeNumber();

    void init(int nodeCount);
};

#endif

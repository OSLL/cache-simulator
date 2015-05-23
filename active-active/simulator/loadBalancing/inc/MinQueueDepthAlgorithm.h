#ifndef MINQUEUEDEPTHALGORITHM_H
#define MINQUEUEDEPTHALGORITHM_H

#include "ILoadBalancingAlgorithm.h"

class MinQueueDepthAlgorithm : public ILoadBalancingAlgorithm
{
public:
    int getNodeNumber();
    void init(int );
};

#endif // MINQUEUEDEPTHALGORITHM_H

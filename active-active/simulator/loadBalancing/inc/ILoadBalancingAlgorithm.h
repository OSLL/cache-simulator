#ifndef ILOADBALANCINGALGORITHM_H
#define ILOADBALANCINGALGORITHM_H

class ILoadBalancingAlgorithm
{
public:
     virtual int getNodeNumber() =0;
     virtual void init(int nodeCount) =0;
};

#endif // ILOADBALANCINGALGORITHM_H

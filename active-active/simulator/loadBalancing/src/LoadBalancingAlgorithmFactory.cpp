#include "LoadBalancingAlgorithmFactory.h"
#include "RoundRobin.h"
#include "MinQueueDepthAlgorithm.h"
#include "SettingsReader.h"
#include "defines.h"

ILoadBalancingAlgorithm* LoadBalancingAlgorithmFactory::getLoadBalancingAlgorithm(){
    ILoadBalancingAlgorithm* algorithm = NULL;
    QString algorithmType = SettingsReader::getValue(LOAD_BALANCING_ALGORITHM).toString();

    if (algorithmType == ROUND_ROBIN_ALGORITHM){
        algorithm = new RoundRobin();
    }else if (algorithmType == MIN_QUEUE_DEPTH_ALGORITHM){
        algorithm = new MinQueueDepthAlgorithm();
    }


    algorithm->init(SP_COUNT);

    return algorithm;
}

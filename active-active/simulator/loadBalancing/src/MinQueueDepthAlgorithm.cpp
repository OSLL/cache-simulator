#include "MinQueueDepthAlgorithm.h"
#include "StorageProcessorsStatistic.h"
#include <QDebug>

int MinQueueDepthAlgorithm::getNodeNumber(){

    qDebug() << "MinQueueDepthAlgorithm" << StorageProcessorsStatistic::getInstance()->getMinimalQueueSP();

    return StorageProcessorsStatistic::getInstance()->getMinimalQueueSP();
}

void MinQueueDepthAlgorithm::init(int ){

}

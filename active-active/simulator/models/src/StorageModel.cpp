#include "StorageModel.h"
#include "ApplicationModel.h"
#include "LoadBalancerModel.h"
#include "RaidModel.h"
#include "StorageProcessorModel.h"
#include "SettingsReader.h"
#include "defines.h"

#include <QDebug>

StorageModel* StorageModel::m_instance=NULL;

StorageModel* StorageModel::getInstance(){

    if(m_instance == NULL)
        m_instance = new StorageModel();

    return m_instance;
}

void StorageModel::deleteStorageModel()
{
    delete m_instance;
    m_instance = NULL;
}


StorageModel::StorageModel()
{

}

StorageModel::~StorageModel()
{
    delete m_applicationModel;
    m_applicationModel = NULL;

    delete m_loadBalancerModel;
    m_loadBalancerModel = NULL;

    delete m_raidModel;
    m_raidModel = NULL;

    foreach(StorageProcessorModel* s, m_storageProcessorModels){
        delete s;
        s = NULL;
    }
}

void StorageModel::init(){
    m_applicationModel = new ApplicationModel();
    m_loadBalancerModel = new LoadBalancerModel();


    m_storageProcessorModels.push_back(new StorageProcessorModel());
    m_storageProcessorModels.push_back(new StorageProcessorModel());

    m_raidModel = new RaidModel();

}


ApplicationModel *StorageModel::getApplicationModel() const
{
    return m_applicationModel;
}

IStorageElement* StorageModel::getLoadBalancerModel() const
{
    return m_loadBalancerModel;
}
RaidModel* StorageModel::getRaidModel() const
{
    return m_raidModel;
}

StorageProcessorModel* StorageModel::getOtherStorageProcessor(StorageProcessorModel* sp) const
{
    //qDebug() << "\tgetOtherStorageProcessor";
    foreach (StorageProcessorModel* s, m_storageProcessorModels) {
        if (s!=sp) {
            return s;
        }
    }
    //qDebug() << "\tNothing found";
    return NULL;
}

QList<StorageProcessorModel *> StorageModel::getStorageProcessors() const
{
    return m_storageProcessorModels;
}

int StorageModel::getStorageProcessorNumber( const StorageProcessorModel* sp) const
{
    if (m_storageProcessorModels.size() != SP_COUNT) return 0;
    for (int i = 0; i < m_storageProcessorModels.size(); i++) {
        if ( m_storageProcessorModels[i] == sp)
            return i;
    }

    return -1;
}

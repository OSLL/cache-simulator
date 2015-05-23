#include "Modeler.h"
#include "SettingsReader.h"
#include "GlobalState.h"
#include "defines.h"
#include "ApplicationModel.h"
#include "ReadRequest.h"
#include "EventExecutor.h"
#include "LimitedThroughput.h"
#include "StorageProcessorModel.h"

#include <QSet>
#include <QDebug>

qulonglong Modeler::m_step=0;

Modeler::Modeler()
{
    StorageModel::getInstance()->init();
}



qulonglong Modeler::getStep()
{
    return m_step;
}

void Modeler::increaseStep()
{
    m_step++;
}


void Modeler::doModeling()
{
    ApplicationModel * app = StorageModel::getInstance()->getApplicationModel();
    EventExecutor eventExecutor;
    eventExecutor.setEvents(SettingsReader::getEvents());

    QMultiMap<ReadRequest*, GlobalState> states;
    for (; ! app->isModelingFinished(getStep()) ; increaseStep()){
        qulonglong i = getStep();

        LimitedThroughput::clearForNextStep();

        qDebug() << "step = " << i << ", states.size = "<< states.size() ;

        eventExecutor.executeEvents(i);

        // Process existing states
        QMultiMap<ReadRequest*, GlobalState>::iterator j;
        for (j = states.begin(); j != states.end(); ++j)
        {
            qDebug() << "Checking " << &(*j) << i;
            if((*j).isFinished())
            {
                j->printRequest();

                ReadRequest * baseRequest = states.key(*j);
                baseRequest->memorizeResults(i, *j);


                if (baseRequest->isFinished()){
                    delete baseRequest;
                }
                states.remove(baseRequest, *j);

            }else{
                // Calculate next state
                (*j).calculateNextStep();
            }
        }

        // Create new request
        app->createNewReadRequest(getStep(), states);
        StorageProcessorModel::printIcQueueStatistics();
    }

}

Modeler::~Modeler()
{
    StorageModel::deleteStorageModel();
}






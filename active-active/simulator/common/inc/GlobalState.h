#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#include "DataType.h"
#include <QByteArray>
#include <QStringList>

class StorageProcessorModel;
class IStorageElement;
class ApplicationModel;

class GlobalState
{
    static qulonglong s_id;
    qulonglong m_id;

    DataType m_dataType;

    qulonglong m_dataAddress;
    QByteArray m_data;

    qulonglong m_totalTime;

    qulonglong m_stepNumber;

    IStorageElement* m_currentElement;

    StorageProcessorModel* m_storageProcessor;

    QStringList m_elements;

    QString getElementsString() const;

    bool isStorageProcessor( const IStorageElement *element) const;


public:
    explicit GlobalState(qulonglong stepNumber = 0, qulonglong dataAddress = 0,
                IStorageElement* currentElement = NULL);

    void calculateNextStep();

    DataType getDataType() const;
    qulonglong getDataAddress() const;
    IStorageElement* getCurrentElement() const;


    void setDataType(DataType dataType);
    void setCurrentElement(IStorageElement* currentElement);

    QString toString() const;
    bool isFinished() const;

    qulonglong getTotalTime() const;
    void increaseTotalTime(qulonglong time);

    qulonglong getId() const;

    void setData(const QByteArray& data);
    QByteArray getData() const;

    qulonglong getStartStepNumber() const ;

    void printRequest() const;

    StorageProcessorModel* getStorageProcessor() const;
    void setStorageProcessor(StorageProcessorModel* sp);

    void setFinished();
    void touchStorageProcessorStatistics(IStorageElement *currentElement);
    ~GlobalState();
};
uint qHash ( const GlobalState & obj );
bool operator ==(GlobalState a, GlobalState b);

#endif // GLOBALSTATE_H

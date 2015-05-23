#ifndef READREQUEST_H
#define READREQUEST_H

#include <QSet>
#include "GlobalState.h"
#include <QMultiMap>
#include <QVector>

class ReadRequest
{
    static qulonglong s_id;
    qulonglong m_id;

    QVector<GlobalState> m_globalStates;

    QMultiMap<qulonglong, GlobalState> m_results;
public:

    QVector<GlobalState> getGlobalStates() const;

    bool isFinished();

    void memorizeResults(qulonglong step, GlobalState state);

    void printResults();

    qulonglong getId() const;
    ReadRequest(qulonglong stepNumber, qulonglong startAddress, qulonglong offset);
    void setGlobalStates(const QVector<GlobalState> &states);
    ReadRequest();
};
bool operator <(ReadRequest a,ReadRequest  b);
bool operator ==(ReadRequest a, ReadRequest b);

#endif // READREQUEST_H

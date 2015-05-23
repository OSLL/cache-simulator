#ifndef REDIRECTDECISIONMAKER_H
#define REDIRECTDECISIONMAKER_H

// Determine does we need to send cache miss requests directly to RAID or not


#include <QtGlobal>

class RedirectDecisionMaker
{
    qulonglong m_stepsToApply;

public:
    bool isForcedDirectSendingEnabled() const;

    qulonglong getMaxICQueueLength(qulonglong raidQueueSize) const;

    RedirectDecisionMaker();

    void stat(qulonglong icQueueSize, qulonglong raidQueueSize);

    // return true if request should go to other sp
    bool makeDecision();
};

#endif // REDIRECTDECISIONMAKER_H

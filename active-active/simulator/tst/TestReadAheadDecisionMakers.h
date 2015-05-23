#ifndef TESTREADAHEADDECISIONMAKERS_H
#define TESTREADAHEADDECISIONMAKERS_H

#include <QObject>


#include <QtGlobal>

class AbstractReadAheadDecisionMaker;

class TestReadAheadDecisionMakers : public QObject
{
    Q_OBJECT

    void checkDecisionMaker(AbstractReadAheadDecisionMaker* maker,
                            qulonglong testArray[], unsigned int size, unsigned int validTurnOnIndex);
public:
    explicit TestReadAheadDecisionMakers();
private slots:
    void testReadAheadDecisionMaker();
    void testSmartReadAheadDecisionMaker();
};

#endif // TESTREADAHEADDECISIONMAKERS_H

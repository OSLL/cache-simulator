#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QVariant>

enum EventType{
    // Config value is changed only once
    INSTANT_EVENT,


    // Config value is increased on each step from
    // [m_applyStep, m_applyStep+m_stepsNumberToApply]
    // for the m_valueDelta
    GRADUAL_EVENT
};

// This class stores data of the one modeling event -
// instant or gradual config parameter changing

class Event
{
private:
    EventType m_type;

    // Parameter which will be changed
    QString m_parameter;
    // New value in case of INSTANT_EVENT
    QVariant m_newValue;

    // Modeling step number when Event should be applyed (or started to apply)
    qulonglong m_applyStep;

    //// GRADUAL_EVENT params
    //// value is treated like qulonlong, int is used for delta sign
    int m_valueDelta;
    // Number of modeling steps during which value will be changed
    qulonglong m_stepsNumberToApply;

    void init(const QString& parameter, const qulonglong applyStep);


public:

    Event();

    // INSTANT_EVENT
    Event(const QString& parameter, const qulonglong applyStep, const QVariant& newValue);

    Event(const QString& parameter, const qulonglong applyStep,
          const int valueDelta, const qulonglong stepsNumberToApply);

    bool shouldBeApplied(const qulonglong step) const;

    QVariant getValueForStep(const qulonglong step) const;

    QString getParameterName() const;

    bool isFinished(const qulonglong step) const;

    bool operator<(const Event& other) const ;


    bool operator==(const Event& other) const ;


    QString toString() const;

};

#endif // EVENT_H

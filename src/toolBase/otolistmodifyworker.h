#ifndef OTOPROCESSOR_H
#define OTOPROCESSOR_H

#include <QObject>
#include <otoentry.h>
#include "tooloptions.h"

class OtoListModifyWorker : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OtoListModifyWorker(QObject *parent = nullptr);
    virtual bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const ToolOptions& options);
};

#endif // OTOPROCESSOR_H

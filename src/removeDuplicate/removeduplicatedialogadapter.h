#ifndef REMOVEDUPLICATEDIALOGADAPTER_H
#define REMOVEDUPLICATEDIALOGADAPTER_H

#include <QWidget>
#include "toolBase/tooldialogadapter.h"

class RemoveDuplicateDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveDuplicateDialogAdapter(QObject *parent = nullptr);
    void replaceUIWidgets(QLayout *rootLayout) override;
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const OptionContainer& options, QWidget *dialogParent) override;
    DEFINE_TOOL_NAME("Remove and organize duplicated entries")
};

#endif // REMOVEDUPLICATEDIALOGADAPTER_H

#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "toolBase/tooldialogadapter.h"

namespace Ui {
    class ToolDialog;
}

class ToolDialog : public QDialog
{
    Q_OBJECT

#ifdef SHINE5402OTOBOX_TEST
    friend class RemoveDuplicateTest;
#endif

public:
    explicit ToolDialog(ToolDialogAdapter* adapter, QWidget *parent = nullptr);
    ~ToolDialog();

private slots:
    void otoFileLoaded();
    void accept() override;
private:
    Ui::ToolDialog *ui;
    void reAssignUIWidgets();
    ToolDialogAdapter* adapter;
    bool doWork(const OtoEntryList& srcList, const QString& srcFileName, const OtoFileSaveWidgetAbstract* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent);
    bool doWork(const QList<OtoEntryList>& srcLists, const QStringList srcFileNames, const OtoFileSaveWidgetAbstract* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent);
};

#endif // TOOLDIALOG_H

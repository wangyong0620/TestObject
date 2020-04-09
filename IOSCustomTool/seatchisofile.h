#ifndef SEATCHISOFILE_H
#define SEATCHISOFILE_H

#include <DWidget>
#include <DPushButton>
#include <DLabel>
#include <DPushButton>
#include <dfilechooseredit.h>

DWIDGET_USE_NAMESPACE

class SeatchISOFile : public QWidget
{
    Q_OBJECT
public:
    explicit SeatchISOFile(QWidget *parent = nullptr);
    void initSearchISOFile();

signals:
    void sendSignalSwitchWindow();
    void sendSignalStopPrintButton(QString &);

public slots:
    void setNextButtonStats(QString fileName);

private:
    DLabel *m_label;
    DFileChooserEdit *m_searchFile;
    DPushButton *m_nextButton;
};

#endif // SEATCHISOFILE_H

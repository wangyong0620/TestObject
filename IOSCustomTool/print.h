#ifndef PRINT_H
#define PRINT_H

#include <DWidget>
#include <DPushButton>
#include <DLabel>
#include <DWaterProgress>

DWIDGET_USE_NAMESPACE

class Print : public DWidget
{
    Q_OBJECT
public:
    explicit Print(DWidget *parent = nullptr);
    void initPrint();
    void processResult();

signals:
    void signalSendCloce();
public slots:
    void setCompressed();
    void setNextButton(QString &);
    void sendCloseSignal();
    void lookFileMessage();
private:
    DPushButton *m_nextButton;
    DPushButton *m_successButton;
    DPushButton *m_failButton;
    DPushButton *m_lookFileButton;
    DWidget *m_buttonWidget;
    DLabel *m_titelLabel;
    DLabel *m_messageLabel;
    DLabel *m_detailsLabel;
    DLabel *m_pixmapLabel;
    DWaterProgress *m_compressedSchedule;
    int m_value;
    QTimer *m_time;
};

#endif // PRINT_H

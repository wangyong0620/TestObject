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

signals:

public slots:
    void setCompressed();
    void setNextButton(QString &);
private:
    DPushButton *m_nextButton;
    DLabel *m_titelLabel;
    DLabel *m_messageLabel;
    DLabel *m_successLabel;
    DWaterProgress *m_compressedSchedule;
    int m_value;
    QTimer *m_time;
};

#endif // PRINT_H

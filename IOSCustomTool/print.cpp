#include "print.h"

#include <DFontSizeManager>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

Print::Print(DWidget *parent) : DWidget(parent)
{
    m_value = 0;
    initPrint();
}

void Print::initPrint()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_titelLabel = new DLabel(this);
    m_titelLabel->setText("准备输出");
    m_titelLabel->setAlignment(Qt::AlignCenter);
    m_titelLabel->setFont(font);
    DFontSizeManager::instance()->bind(m_titelLabel, DFontSizeManager::T2);

    m_compressedSchedule = new  DWaterProgress(this);
    m_compressedSchedule->setFixedSize(100,100);

    m_successLabel = new DLabel(this);
    m_successLabel->setAlignment(Qt::AlignCenter);

    m_messageLabel = new DLabel(this);
    m_messageLabel->setFont(font);
    m_messageLabel->setAlignment(Qt::AlignCenter);

    m_time = new QTimer();
    m_time->setInterval(100);

    m_nextButton = new DPushButton(this);
    m_nextButton->setText("下一步");
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layOut = new QVBoxLayout(this);
    layOut->addSpacing(20);
    layOut->addWidget(m_titelLabel,0,Qt::AlignCenter);
    layOut->addStretch();
    layOut->addWidget(m_compressedSchedule,0,Qt::AlignCenter);
    layOut->addWidget(m_successLabel,0,Qt::AlignCenter);
    layOut->addWidget(m_messageLabel,0,Qt::AlignCenter);
    layOut->addStretch();
    layOut->addWidget(m_nextButton,0,Qt::AlignCenter);
    layOut->addSpacing(50);

    connect(m_nextButton,&DPushButton::clicked,[=]() {
        m_time->start();
    });
    connect(m_time, &QTimer::timeout, this,&Print::setCompressed);

    m_compressedSchedule->setValue(0);
    m_compressedSchedule->start();
}

void Print::setCompressed()
{
    m_value++;
    qDebug() << m_value;

    if (m_value == 100) {
  //      m_value = 0;
        m_successLabel->setText("制作成功");
        m_titelLabel->setText("输出成功");
        DFontSizeManager::instance()->bind(m_successLabel, DFontSizeManager::T6);
        m_time->stop();

    }
    m_compressedSchedule->setValue(m_value);
}

void Print::setNextButton(QString &fileName)
{
    if (fileName.isEmpty()) {
        m_nextButton->setEnabled(false);
        return;
    }

    m_nextButton->setEnabled(true);
}

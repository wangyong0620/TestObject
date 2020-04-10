#include "print.h"

#include <DFontSizeManager>
#include <DFileDialog>

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

    m_pixmapLabel = new DLabel(this);
    m_pixmapLabel->setAlignment(Qt::AlignCenter);

    m_messageLabel = new DLabel(this);
    m_messageLabel->setFont(font);
    m_messageLabel->setAlignment(Qt::AlignCenter);

    m_detailsLabel = new DLabel(this);
    m_detailsLabel->setFont(font);
    m_detailsLabel->setAlignment(Qt::AlignCenter);
    DFontSizeManager::instance()->bind(m_detailsLabel, DFontSizeManager::T10);

    m_time = new QTimer();
    m_time->setInterval(100);
    QTimer *testTime = new QTimer();
    testTime->setInterval(9900);

    m_nextButton = new DPushButton(this);
    m_nextButton->setText("下一步");
    m_nextButton->setFixedSize(250,35);

    m_successButton = new DPushButton(this);
    m_successButton->setText("完成");
    m_successButton->setFixedSize(250,35);

    m_failButton = new DPushButton(this);
    m_failButton->setText("关闭");
    m_failButton->setFixedSize(250,35);

    m_lookFileButton = new DPushButton(this);
    m_lookFileButton->setText("查看文件");
    m_lookFileButton->setFixedSize(250,35);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_successButton);
    buttonLayout->addWidget(m_lookFileButton);

    m_buttonWidget = new DWidget(this);
    m_buttonWidget->setLayout(buttonLayout);

    QVBoxLayout *layOut = new QVBoxLayout(this);
    layOut->addSpacing(20);
    layOut->addWidget(m_titelLabel,0,Qt::AlignCenter);
    layOut->addStretch();
    layOut->addWidget(m_compressedSchedule,0,Qt::AlignCenter);
    layOut->addWidget(m_pixmapLabel,0,Qt::AlignCenter);
    layOut->addWidget(m_messageLabel,0,Qt::AlignCenter);
    layOut->addWidget(m_detailsLabel,0,Qt::AlignCenter);
    layOut->addStretch();
    layOut->addWidget(m_nextButton,0,Qt::AlignCenter);
    layOut->addWidget(m_failButton,0,Qt::AlignCenter);
    layOut->addWidget(m_buttonWidget,0,Qt::AlignCenter);
    layOut->addSpacing(50);

    connect(m_nextButton,&DPushButton::clicked,[=]() {
        testTime->start();
        m_time->start();
        m_compressedSchedule->start();
    });
    connect(m_time, &QTimer::timeout, this,&Print::setCompressed);
    connect(testTime,&QTimer::timeout,[=]() {
        m_time->stop();
        processResult();
    });


    connect(m_successButton,&DPushButton::clicked,this,&Print::sendCloseSignal);
    connect(m_failButton,&DPushButton::clicked,this,&Print::sendCloseSignal);
    connect(m_lookFileButton,&DPushButton::clicked,this,&Print::lookFileMessage);

    m_compressedSchedule->setValue(0);
    m_buttonWidget->hide();
    m_failButton->hide();

}

void Print::processResult()
{
    qDebug() << m_value;
    if (m_value == 100) {
//        QIcon img= QIcon::fromTheme("dcc_fail");
        QPixmap pixmap(":/icons/deepin/builtin/dark/icons/dcc_progress_111px.svg");
        m_pixmapLabel->setPixmap(pixmap);
        m_titelLabel->setText("输出成功");
//        m_compressedSchedule->setValue(m_value);
        m_compressedSchedule->hide();
        m_nextButton->hide();
//        m_time->stop();
        m_buttonWidget->show();
        m_compressedSchedule->stop();
        m_value = 0;
    } else {
        QPixmap pixmap(":/icons/deepin/builtin/dark/icons/dcc_fail_110px.svg");
        m_pixmapLabel->setPixmap(pixmap);
        m_titelLabel->setText("输出失败");
        m_messageLabel->setText("制作失败");
        m_detailsLabel->setText("失败原因：未知的错误");
//        m_compressedSchedule->setValue(m_value);
        m_compressedSchedule->hide();
        m_nextButton->hide();
//        m_time->stop();
        m_buttonWidget->hide();
        m_failButton->show();
        m_compressedSchedule->stop();
        m_value = 0;
    }
}

void Print::setCompressed()
{
    m_value++;
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

void Print::sendCloseSignal()
{
    emit signalSendCloce();
}

void Print::lookFileMessage()
{
    DFileDialog::getOpenFileName(this, tr("Open File"),
                                                          "/home/Desktop/",
                                                          QString("*"));
}

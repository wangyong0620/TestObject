#include "lastcleaning.h"

#include <DFontSizeManager>
#include <DFileIconProvider>
#include <DFileDialog>

LastCleaning::LastCleaning(DWidget *parent) : DWidget(parent)
{
    initMidtermInstallation();
}

void LastCleaning::initMidtermInstallation()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_label = new DLabel(this);
    m_label->setText("后期清理");
    m_label->setAlignment(Qt::AlignLeft);
    m_label->setFont(font);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T3);

    DWidget *widget = new DWidget(this);
//    widget->setFixedSize(600,350);

    m_fontLabel = new DLabel(widget);
    m_fontLabel->setText("请选择后期清理");
    m_fontLabel->setAlignment(Qt::AlignCenter);
    m_fontLabel->setEnabled(false);
    DFontSizeManager::instance()->bind(m_fontLabel, DFontSizeManager::T2);

    m_showFileLayout = new QVBoxLayout();
    m_showFileWidget = new DWidget(widget);
    m_showFileWidget->setLayout(m_showFileLayout);

    QVBoxLayout *widgetLayout = new QVBoxLayout(this);
    widgetLayout->addWidget(m_showFileWidget,0,Qt::AlignTop);
    widgetLayout->addWidget(m_fontLabel,0,Qt::AlignCenter);
    widget->setLayout(widgetLayout);

    m_searchButton = new DCommandLinkButton("选择脚本",this);
    m_nextButton = new DPushButton("下一步",this);
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addWidget(m_label);
    //    layout->addLayout(hLayout);
    layout->addWidget(widget,0,Qt::AlignCenter);
    layout->setStretchFactor(widget,3);
    layout->addWidget(m_searchButton,0,Qt::AlignCenter);
    layout->addWidget(m_nextButton,0,Qt::AlignCenter);
    layout->addSpacing(50);
    this->setLayout(layout);

    connect(m_searchButton,&DCommandLinkButton::clicked,this,&LastCleaning::openFilePath);
    m_showFileWidget->hide();
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
}

void LastCleaning::openFilePath()
{
    const QString fileName = DFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/home/Desktop/",
                                                      QString("*.deb"));
    if (fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);
    DFileIconProvider icon_provider;
    QIcon icon = icon_provider.icon(fileInfo);

    QFont font;
    font.setFamily("SimHei");

    DFloatingMessage *pDFloatMessage = new DFloatingMessage(DFloatingMessage::ResidentType, m_showFileWidget);
    DFontSizeManager::instance()->bind(pDFloatMessage, DFontSizeManager::T10);
    pDFloatMessage->setMinimumHeight(50);
    pDFloatMessage->setFont(font);
    pDFloatMessage->setIcon(icon);
    pDFloatMessage->setMessage(fileName);
    pDFloatMessage->show();

    m_list.append(pDFloatMessage);
    m_showFileLayout->addWidget(pDFloatMessage,0,Qt::AlignTop);
    m_fontLabel->hide();

    m_showFileWidget->show();
    connect(pDFloatMessage,&DFloatingMessage::closeButtonClicked,this,&LastCleaning::deleteList);
}

void LastCleaning::deleteList()
{
    for (auto iter = m_list.begin(); iter < m_list.end(); ++iter) {
   //     if ((*iter)-)
           m_list.erase(iter++);
        }

    if (m_list.isEmpty()) {
        m_showFileWidget->hide();
        m_fontLabel->show();
    }
}

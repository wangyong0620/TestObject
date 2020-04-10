#include "midterminstallation.h"

#include <DFontSizeManager>
#include <DFileIconProvider>
#include <DFileDialog>

MidtermInstallation::MidtermInstallation(DWidget *parent) : DWidget(parent)
{
    initMidtermInstallation();
}

void MidtermInstallation::initMidtermInstallation()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_label = new DLabel(this);
    m_label->setText("中期安装");
    m_label->setAlignment(Qt::AlignLeft);
    m_label->setFont(font);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T3);

    m_fontLabel = new DLabel(this);
    m_fontLabel->setText("请选择中期安装");
    m_fontLabel->setAlignment(Qt::AlignCenter);
    m_fontLabel->setEnabled(false);
    DFontSizeManager::instance()->bind(m_fontLabel, DFontSizeManager::T2);

    m_floatMessageLayout = new QVBoxLayout(this);
    m_showFileWidget = new DWidget(this);
    m_showFileWidget->setLayout(m_floatMessageLayout);

    m_showFileLayout = new QVBoxLayout();
    m_showFileLayout->addWidget(m_fontLabel,Qt::AlignCenter);
    m_showFileLayout->addWidget(m_showFileWidget,0,Qt::AlignHCenter);
    m_showFileLayout->addStretch();

    m_showWidget = new DWidget(this);
    m_showWidget->setLayout(m_showFileLayout);


    m_searchButton = new DCommandLinkButton("选择脚本",this);
    m_nextButton = new DPushButton("下一步",this);
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addWidget(m_label);
    layout->addWidget(m_showWidget);
    layout->setStretchFactor(m_showWidget,3);
    layout->addWidget(m_searchButton,0,Qt::AlignHCenter);
    layout->addWidget(m_nextButton,0,Qt::AlignHCenter);
    layout->addSpacing(50);
    this->setLayout(layout);

    connect(m_searchButton,&DCommandLinkButton::clicked,this,&MidtermInstallation::openFilePath);
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
    m_showFileWidget->hide();
}

void MidtermInstallation::openFilePath()
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

    DFloatingMessage *pDFloatMessage = new DFloatingMessage(DFloatingMessage::ResidentType, this);
    DFontSizeManager::instance()->bind(pDFloatMessage, DFontSizeManager::T10);
    pDFloatMessage->setMinimumHeight(50);
    pDFloatMessage->setFont(font);
    pDFloatMessage->setIcon(icon);
    pDFloatMessage->setMessage(fileName);
    pDFloatMessage->show();
    pDFloatMessage->setBlurBackgroundEnabled(true);
    m_list.append(pDFloatMessage);
    m_floatMessageLayout->addWidget(pDFloatMessage,0,Qt::AlignTop);

    m_fontLabel->hide();
    m_showFileWidget->show();

    connect(pDFloatMessage,&DFloatingMessage::closeButtonClicked,this,&MidtermInstallation::deleteList);
}

void MidtermInstallation::deleteList()
{
    for (auto iter = m_list.begin(); iter < m_list.end(); ++iter) {
           m_list.erase(iter++);
        }

    if (m_list.isEmpty()) {
        m_showFileWidget->hide();
        m_fontLabel->show();
    }
}

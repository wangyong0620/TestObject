#include "programconfig.h"
#include <DFontSizeManager>
#include <DColumnView>
#include <DFileIconProvider>

#include <QHBoxLayout>
#include <QDebug>


ProgramConfig::ProgramConfig(QWidget *parent) : QWidget(parent)
{
    initProgramConfig();
}

void ProgramConfig::initProgramConfig()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_label = new DLabel(this);
    m_label->setText("程序配置");
    m_label->setAlignment(Qt::AlignLeft);
    m_label->setFont(font);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T3);

    m_clearButton = new DCommandLinkButton("全部清除",this);
    DFontSizeManager::instance()->bind(m_clearButton, DFontSizeManager::T6);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_label);
    hLayout->addWidget(m_clearButton,0,Qt::AlignRight);

    DWidget *widget = new DWidget(this);

    m_showFont = new DLabel(widget);
    m_showFont->setText("请选择程序");
    m_showFont->setAlignment(Qt::AlignCenter);
    m_showFont->setEnabled(false);
    DFontSizeManager::instance()->bind(m_showFont, DFontSizeManager::T2);

    pHBoxLayout2 = new QVBoxLayout();
    m_showFileWidget = new DWidget(widget);
    m_showFileWidget->setLayout(pHBoxLayout2);

    QVBoxLayout *widgetLayout = new QVBoxLayout(this);
    widgetLayout->addWidget(m_showFileWidget,0,Qt::AlignTop);
    widgetLayout->addWidget(m_showFont,0,Qt::AlignCenter);
    widget->setLayout(widgetLayout);

    m_searchButton = new DCommandLinkButton("选择程序deb包",this);
    m_nextButton = new DPushButton("下一步",this);
    m_nextButton->setFixedSize(250,35);

    layout->addSpacing(20);
    layout->addLayout(hLayout);
    layout->addWidget(widget,0,Qt::AlignCenter);
    layout->setStretchFactor(widget,3);
    layout->addWidget(m_searchButton,0,Qt::AlignCenter);
    layout->addWidget(m_nextButton,0,Qt::AlignCenter);
    layout->addSpacing(50);
    this->setLayout(layout);

    m_fileDialog = new DFileDialog(this);

    connect(m_clearButton,&DCommandLinkButton::clicked,this,&ProgramConfig::clearAllFile);
    connect(m_searchButton,&DCommandLinkButton::clicked,this,&ProgramConfig::openFilePath);
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
    m_showFileWidget->hide();
}

void ProgramConfig::clearAllFile()
{
    for (int i = 0; i < m_list.size(); ++i) {
        m_list.at(i)->close();
    }
    m_list.clear();

    m_showFileWidget->hide();
    m_showFont->show();
}

void ProgramConfig::openFilePath()
{
    const QString fileName = m_fileDialog->getOpenFileName(this, tr("Open File"),
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
    pHBoxLayout2->addWidget(pDFloatMessage,0,Qt::AlignTop);
    m_showFont->hide();
    m_showFileWidget->show();

    connect(pDFloatMessage,&DFloatingMessage::closeButtonClicked,this,&ProgramConfig::deleteList);
}

void ProgramConfig::deleteList()
{
    for (auto iter = m_list.begin(); iter < m_list.end(); ++iter) {
   //     if ((*iter)-)
           m_list.erase(iter++);
        }

    if (m_list.isEmpty()) {
        m_showFileWidget->hide();
        m_showFont->show();
    }
}

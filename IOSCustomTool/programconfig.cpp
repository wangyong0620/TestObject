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

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_label);
    hLayout->addWidget(m_clearButton,0,Qt::AlignRight);
    DWidget *topWidget = new DWidget(this);
    topWidget->setLayout(hLayout);

    m_showFont = new DLabel(this);
    m_showFont->setText("请选择程序");
    m_showFont->setAlignment(Qt::AlignCenter);
    m_showFont->setEnabled(false);
    DFontSizeManager::instance()->bind(m_showFont, DFontSizeManager::T2);

    m_floatMessageLayout = new QVBoxLayout();
    m_showFileWidget = new DWidget(this);
    m_showFileWidget->setLayout(m_floatMessageLayout);

    m_widgetLayout = new QVBoxLayout(this);
    m_widgetLayout->addWidget(m_showFont,Qt::AlignHCenter);
    m_widgetLayout->addWidget(m_showFileWidget,0,Qt::AlignHCenter);
    m_widgetLayout->addStretch();

    DWidget *widget = new DWidget(this);
    widget->setLayout(m_widgetLayout);

    m_searchButton = new DCommandLinkButton("选择程序deb包",this);
    m_nextButton = new DPushButton("下一步",this);
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(20);
    layout->addWidget(topWidget);
    layout->addWidget(widget);
    layout->setStretchFactor(widget,3);
    layout->addWidget(m_searchButton,0,Qt::AlignCenter);
    layout->addWidget(m_nextButton,0,Qt::AlignCenter);
    layout->addSpacing(50);
    this->setLayout(layout);

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
    pDFloatMessage->setFixedSize(500,60);
    pDFloatMessage->setFramRadius(10);
    pDFloatMessage->setBlurBackgroundEnabled(true);
    pDFloatMessage->show();
    DFontSizeManager::instance()->bind(pDFloatMessage, DFontSizeManager::T6);

    m_list.append(pDFloatMessage);
    m_floatMessageLayout->addWidget(pDFloatMessage,0,Qt::AlignTop);

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

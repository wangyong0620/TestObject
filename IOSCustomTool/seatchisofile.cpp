#include "seatchisofile.h"
#include <DFontSizeManager>

#include <QFont>
#include <QVBoxLayout>
#include <QDebug>


SeatchISOFile::SeatchISOFile(QWidget *parent) : QWidget(parent)
{
    initSearchISOFile();
    connect(m_searchFile,&DFileChooserEdit::fileChoosed,this,&SeatchISOFile::setNextButtonStats);
    connect(m_searchFile,&DFileChooserEdit::textChanged,this,&SeatchISOFile::setNextButtonStats);
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
}

void SeatchISOFile::initSearchISOFile()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_label = new DLabel("选择ISO",this);
    m_label->setFont(font);
    m_label->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T3);

    m_searchFile = new DFileChooserEdit(this);
    m_searchFile->setNameFilters(QStringList("*.iso"));

    m_nextButton = new DPushButton(this);
    m_nextButton->setEnabled(false);
    m_nextButton->setText("下一步");
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layOut = new QVBoxLayout(this);
    layOut->addSpacing(20);
    layOut->addWidget(m_label,0,Qt::AlignLeft);
    layOut->addWidget(m_searchFile);
    layOut->addSpacing(300);
    layOut->addWidget(m_nextButton,0,Qt::AlignCenter);
    layOut->addSpacing(45);
}

void SeatchISOFile::setNextButtonStats(QString fileName)
{
    if (m_searchFile->text().isEmpty() ) {
        m_nextButton->setEnabled(false);
        emit sendSignalStopPrintButton(fileName);
        return;
    }

    emit sendSignalStopPrintButton(fileName);
    m_nextButton->setEnabled(true);
}



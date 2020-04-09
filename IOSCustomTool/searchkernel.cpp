#include "searchkernel.h"

#include <DFontSizeManager>

#include <QDebug>

SearchKernel::SearchKernel(DWidget *parent) : DWidget(parent)
{
    initSearchKernel();
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
}

void SearchKernel::initSearchKernel()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    m_titelLabel = new DLabel(this);
    m_titelLabel->setText("选择Kernel");
    m_titelLabel->setAlignment(Qt::AlignLeft);
    m_titelLabel->setFont(font);
    DFontSizeManager::instance()->bind(m_titelLabel, DFontSizeManager::T3);

    m_kernelLabel = new DLabel("kernel",this);
    m_kernelLabel->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(m_kernelLabel, DFontSizeManager::T6);

    m_initrdLabel = new DLabel("kernel",this);
    m_initrdLabel->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(m_initrdLabel, DFontSizeManager::T6);

    m_searchKernelFile = new DFileChooserEdit(this);

    m_searchinitrdFile = new DFileChooserEdit(this);
    m_searchinitrdFile->setNameFilters(QStringList("*.lz"));

    m_nextButton = new DPushButton(this);
    m_nextButton->setEnabled(false);
    m_nextButton->setText("下一步");
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layOut = new QVBoxLayout(this);
    layOut->addSpacing(20);
    layOut->addWidget(m_titelLabel,Qt::AlignCenter);
    layOut->addWidget(m_kernelLabel,Qt::AlignCenter);
    layOut->addWidget(m_searchKernelFile,Qt::AlignCenter);
    layOut->addWidget(m_initrdLabel,Qt::AlignCenter);
    layOut->addWidget(m_searchinitrdFile,Qt::AlignCenter);
    layOut->addSpacing(300);
    layOut->addWidget(m_nextButton,0,Qt::AlignCenter);
    layOut->addSpacing(50);
    connect(m_searchinitrdFile,&DFileChooserEdit::fileChoosed,this,&SearchKernel::setNextButtonAbledSlot);
    connect(m_searchinitrdFile,&DFileChooserEdit::textChanged,this,&SearchKernel::setNextButtonAbledSlot);
    connect(m_searchKernelFile,&DFileChooserEdit::textChanged,this,&SearchKernel::setNextButtonAbledSlot);
}

void SearchKernel::setNextButtonAbledSlot()
{
    if (m_searchKernelFile->text().isEmpty() || m_searchinitrdFile->text().isEmpty()) {
        m_nextButton->setEnabled(false);
        return;
    }
    m_nextButton->setEnabled(true);
}

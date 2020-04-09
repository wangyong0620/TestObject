#include "searcharchitecture.h"

#include <DLabel>
#include <DPushButton>
#include <DFontSizeManager>

#include <QIcon>
#include <QVBoxLayout>

SearchArchitecture::SearchArchitecture(QWidget *parent) : QWidget(parent)
{
    initSearchArchitecture();
    connect(m_nextButton,&DPushButton::clicked,[=]() {
        emit sendSignalSwitchWindow();
    });
}

void SearchArchitecture::initSearchArchitecture()
{
    QFont font;
    font.setFamily("SimHei");
    font.setBold(true);

    DLabel *label = new DLabel(this);
    label->setText("选择架构");
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setAlignment(Qt::AlignLeft);

    m_architectureList = new DListView(this);
    m_model = new QStandardItemModel();
    DStandardItem *itemARM = new DStandardItem("ARM");
 //   itemARM->
    m_model->appendRow(itemARM);
    DStandardItem *itemX86 = new DStandardItem("X86");
 //   itemOne->
    m_model->appendRow(itemX86);
    DStandardItem *itemMips = new DStandardItem("MIPS");
 //   itemOne->
    m_model->appendRow(itemMips);
    m_architectureList->setModel(m_model);

    m_nextButton = new DPushButton(this);
    m_nextButton->setEnabled(false);
    m_nextButton->setText("下一步");
    m_nextButton->setFixedSize(250,35);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addSpacing(20);
    layout->addWidget(label);
    layout->addWidget(m_architectureList);
    layout->addWidget(m_nextButton,0,Qt::AlignCenter);
    layout->addSpacing(50);
    this->setLayout(layout);

    connect(m_architectureList,&QListView::clicked,this,&SearchArchitecture::setCheckStats);
}

void SearchArchitecture::setCheckStats(QModelIndex index)
{
    for (int i = 0; i < m_model->rowCount(); ++i) {
        QStandardItem *item = m_model->item(i,0);
        item->setCheckState(Qt::Unchecked);
    }

    QStandardItem *item = m_model->itemFromIndex(index);
    item->setCheckState(Qt::Checked);
    m_nextButton->setEnabled(true);
}

#include "mainwindow.h"
#include "seatchisofile.h"
#include "searcharchitecture.h"
#include "programconfig.h"
#include "searchkernel.h"
#include "print.h"
#include "sharedclass.h"

#include <DLabel>
#include <DStandardItem>

#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : DMainWindow(parent)
{    
    m_titlebar = this->titlebar();
    m_titlebar->setDisableFlags(Qt::WindowMinimizeButtonHint
                              | Qt::WindowMaximizeButtonHint
                              | Qt::WindowSystemMenuHint);
    m_titlebar->setAutoHideOnFullscreen(true);
    m_titlebar->setIcon(QIcon::fromTheme("dcc_icon"));

    DLabel *label = new DLabel("ISO定制工具",m_titlebar);
    m_titlebar->addWidget(label,Qt::AlignCenter);

    initLiftView();
    initRightView();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(m_liftFrame);
    mainLayout->addWidget(m_rightFrame);
    mainLayout->setStretchFactor(m_liftFrame,1);
    mainLayout->setStretchFactor(m_rightFrame,3);

    QWidget *centerWidget = new QWidget(this);
    setCentralWidget(centerWidget);
    centerWidget->setLayout(mainLayout);

    connect(m_liftView,&DListView::clicked,this,&MainWindow::setShowInterfaceSlot);
    connect(m_liftView,SIGNAL(currentChanged(QModelIndex)),this,SLOT(setCursorMovementShowInterfaceSlot(QModelIndex)));
}

void MainWindow::initLiftView()
{
    m_liftFrame = new DFrame(this);
    m_liftView = new DListView(this);
    m_liftView->setMinimumWidth(200);
    m_liftView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    standarModel = new QStandardItemModel(this);
    DStandardItem *itemOne = new DStandardItem(QIcon::fromTheme("dcc_inactive1"),"选择ISO");
    itemOne->setCheckState(Qt::Checked);
    standarModel->appendRow(itemOne);
    DStandardItem *itemTwo = new DStandardItem(QIcon::fromTheme("dcc_inactive2"),"选择架构");
    itemTwo->setEnabled(false);

    standarModel->appendRow(itemTwo);
    DStandardItem *itemThree = new DStandardItem(QIcon::fromTheme("dcc_inactive3"),"程序配置");
    itemThree->setEnabled(false);
    standarModel->appendRow(itemThree);
    DStandardItem *itemFour = new DStandardItem(QIcon::fromTheme("dcc_inactive4"),"前期准备");
    itemFour->setEnabled(false);
    standarModel->appendRow(itemFour);
    DStandardItem *itemFive = new DStandardItem(QIcon::fromTheme("dcc_inactive5"),"中期安装");
    itemFive->setEnabled(false);
    standarModel->appendRow(itemFive);
    DStandardItem *itemSix = new DStandardItem(QIcon::fromTheme("dcc_inactive6"),"后期清理");
    itemSix->setEnabled(false);
    standarModel->appendRow(itemSix);
    DStandardItem *itemSeven = new DStandardItem(QIcon::fromTheme("dcc_inactive7"),"选择Kernel");
    itemSeven->setEnabled(false);
    standarModel->appendRow(itemSeven);
    DStandardItem *itemEight = new DStandardItem(QIcon::fromTheme("dcc_inactive8"),"输出");
    itemEight->setEnabled(false);
    standarModel->appendRow(itemEight);

    m_liftView->setModel(standarModel);
    QHBoxLayout *liftLayout = new QHBoxLayout(this);
    liftLayout->addWidget(m_liftView);
    m_liftFrame->setLayout(liftLayout);
    m_liftView->setCurrentIndex(standarModel->item(0,0)->index());
}

void MainWindow::initRightView()
{
    m_rightFrame = new DFrame(this);
    SeatchISOFile *searchIssoFile = new SeatchISOFile(this);
    SearchArchitecture *searchArchitecture = new SearchArchitecture(this);
    ProgramConfig *programConfig = new ProgramConfig(this);
//    Preparation *preparation = new Preparation(this);
//    MidtermInstallation *midInstall = new  MidtermInstallation(this);
//    LastCleaning *lastClear = new LastCleaning(this);
    SearchKernel *searchKerenl = new SearchKernel(this);
    Print *print = new Print(this);

    SharedClass *preparation = new SharedClass("前期准备","请选择前期准备");
    SharedClass *midInstall = new SharedClass("中期安装","请选择中期安装");
    SharedClass *lastClear = new SharedClass("后期清理","请选择后期清理");

    m_rightView = new DStackedWidget(this);
    m_rightView->addWidget(searchIssoFile);
    m_rightView->addWidget(searchArchitecture);
    m_rightView->addWidget(programConfig);
    m_rightView->addWidget(preparation);
    m_rightView->addWidget(midInstall);
    m_rightView->addWidget(lastClear);
    m_rightView->addWidget(searchKerenl);
    m_rightView->addWidget(print);

    QHBoxLayout *rightLayout = new QHBoxLayout(this);
    rightLayout->addWidget(m_rightView);
    m_rightFrame->setLayout(rightLayout);

    connect(searchIssoFile,&SeatchISOFile::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(searchIssoFile,&SeatchISOFile::sendSignalStopPrintButton,print,&Print::setNextButton);
    connect(searchArchitecture,&SearchArchitecture::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(programConfig,&ProgramConfig::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(preparation,&SharedClass::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(midInstall,&SharedClass::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(lastClear,&SharedClass::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(searchKerenl,&SearchKernel::sendSignalSwitchWindow,this,&MainWindow::switchWindowSlot);
    connect(print,&Print::signalSendCloce,this,&MainWindow::close);
}

void MainWindow::setShowInterfaceSlot(QModelIndex index)
{
    QStandardItem *item = standarModel->itemFromIndex(index);

    if (item->checkState() == Qt::Checked) {
        m_rightView->setCurrentIndex(index.row());
    }
}

void MainWindow::setCursorMovementShowInterfaceSlot(QModelIndex index)
{
    Q_UNUSED(index)

    QModelIndex currIndex = m_liftView->currentIndex();
    QStandardItem *item = standarModel->itemFromIndex(currIndex);

    if (item->checkState() == Qt::Checked) {
        m_rightView->setCurrentIndex(currIndex.row());
    }
}

void MainWindow::switchWindowSlot()
{
    /*
    QModelIndex currIndex = m_liftView->currentIndex();  // 当前行
    QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(m_liftView->model());
    QModelIndex nextIndex = model->index(currIndex.row() + 1,  0); // 当前行的下一行
    qDebug() << "41212" << currIndex << nextIndex;
    */
    QModelIndex currIndex = m_liftView->currentIndex();
    QModelIndex nextIndex = currIndex.sibling(currIndex.row() + 1, currIndex.column());

    QStandardItem *item = standarModel->itemFromIndex(nextIndex);
    item->setEnabled(true);
    item->setCheckState(Qt::Checked);
    m_liftView->setCurrentIndex(nextIndex);
    m_rightView->setCurrentIndex(nextIndex.row());
}

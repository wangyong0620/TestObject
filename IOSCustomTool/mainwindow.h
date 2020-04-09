#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DListView>
#include <DStackedWidget>
#include <DTitlebar>
#include <DFrame>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initLiftView();
    void initRightView();
signals:

public slots:
    void setShowInterfaceSlot(QModelIndex index);
    void setCursorMovementShowInterfaceSlot(QModelIndex index);
    void switchWindowSlot();
private:
    DListView *m_liftView;
    DStackedWidget *m_rightView;
    DTitlebar *m_titlebar;
    DFrame *m_liftFrame;
    DFrame *m_rightFrame;
    QStandardItemModel *standarModel;

};

#endif // MAINWINDOW_H

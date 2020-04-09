#ifndef SEARCHARCHITECTURE_H
#define SEARCHARCHITECTURE_H

#include <DWidget>
#include <DListView>
#include <DStandardItem>

DWIDGET_USE_NAMESPACE

class SearchArchitecture : public DWidget
{
    Q_OBJECT
public:
    explicit SearchArchitecture(QWidget *parent = nullptr);
    void initSearchArchitecture();

signals:
    void sendSignalSwitchWindow();
public slots:
    void setCheckStats(QModelIndex index);
private:
    DPushButton *m_nextButton;
    DListView *m_architectureList;
    QStandardItemModel *m_model;
};

#endif // SEARCHARCHITECTURE_H

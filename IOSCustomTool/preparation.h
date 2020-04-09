#ifndef PREPARATION_H
#define PREPARATION_H

#include <DWidget>
#include <DLabel>
#include <DPushButton>
#include <DCommandLinkButton>
#include <DFloatingMessage>

#include <QVBoxLayout>


DWIDGET_USE_NAMESPACE

class Preparation : public DWidget
{
    Q_OBJECT
public:
    explicit Preparation(DWidget *parent = nullptr);
    void initPreparation();


signals:
    void sendSignalSwitchWindow();
public slots:
    void openFilePath();
    void deleteList();
private:
    DPushButton *m_nextButton;
    DLabel *m_label;
    DLabel *m_fontLabel;
    QVBoxLayout *m_showFileLayout;
    DWidget *m_showFileWidget;
    DWidget *m_showWidget;
    DCommandLinkButton *m_searchButton;
    QList<DFloatingMessage *> m_list;
    QVBoxLayout *m_floatMessageLayout;
};

#endif // PREPARATION_H

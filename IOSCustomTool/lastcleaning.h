#ifndef LASTCLEANING_H
#define LASTCLEANING_H

#include <DWidget>
#include <DLabel>
#include <DPushButton>
#include <DCommandLinkButton>
#include <DFloatingMessage>

#include <QVBoxLayout>


DWIDGET_USE_NAMESPACE

class LastCleaning : public DWidget
{
    Q_OBJECT
public:
    explicit LastCleaning(DWidget *parent = nullptr);
    void initMidtermInstallation();

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
    DCommandLinkButton *m_searchButton;
    QList<DFloatingMessage *> m_list;
    QVBoxLayout *m_floatMessageLayout;
    DWidget *m_showWidget;
};

#endif // LASTCLEANING_H

#ifndef MIDTERMINSTALLATION_H
#define MIDTERMINSTALLATION_H

#include <DWidget>
#include <DLabel>
#include <DPushButton>
#include <DCommandLinkButton>
#include <DFloatingMessage>

#include <QVBoxLayout>


DWIDGET_USE_NAMESPACE

class MidtermInstallation : public DWidget
{
    Q_OBJECT
public:
    explicit MidtermInstallation(DWidget *parent = nullptr);
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
    DWidget *m_showWidget;
//    DFloatingMessage *pDFloatMessage;
    QVBoxLayout *m_floatMessageLayout;
};

#endif // MIDTERMINSTALLATION_H

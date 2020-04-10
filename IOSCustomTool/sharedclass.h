#ifndef SHAREDCLASS_H
#define SHAREDCLASS_H

#include <DWidget>
#include <DLabel>
#include <DPushButton>
#include <DCommandLinkButton>
#include <DFloatingMessage>

#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE


class SharedClass : public DWidget
{
    Q_OBJECT
public:
    explicit SharedClass(DWidget *parent = nullptr);
    SharedClass(QString showFont,QString titelFont,DWidget *parent = nullptr);
    void initSharedClass(QString &showFont,QString &titelFont);

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

#endif // SHAREDCLASS_H

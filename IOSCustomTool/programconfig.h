#ifndef PROGRAMCONFIG_H
#define PROGRAMCONFIG_H

#include <DWidget>
#include <DGroupBox>
#include <DPushButton>
#include <DLabel>
#include <DCommandLinkButton>
#include <DFileDialog>
#include <DFloatingMessage>

#include <QVBoxLayout>
DWIDGET_USE_NAMESPACE

class ProgramConfig : public DWidget
{
    Q_OBJECT
public:
    explicit ProgramConfig(QWidget *parent = nullptr);
    void initProgramConfig();
signals:
    void sendSignalSwitchWindow();
public slots:
    void clearAllFile();
    void openFilePath();
    void deleteList();

private:
    DCommandLinkButton *m_searchButton;
    DCommandLinkButton *m_clearButton;
    DPushButton *m_nextButton;
    DLabel *m_label;
    DLabel *m_showFont;
    DFileDialog *m_fileDialog;
    DWidget *m_showFileWidget;
    QVBoxLayout *pHBoxLayout2;
    QList<DFloatingMessage *> m_list;
};

#endif // PROGRAMCONFIG_H

#ifndef SEARCHKERNEL_H
#define SEARCHKERNEL_H

#include <DWidget>
#include <DLabel>
#include <DPushButton>
#include <dfilechooseredit.h>

DWIDGET_USE_NAMESPACE

class SearchKernel : public DWidget
{
    Q_OBJECT
public:
    explicit SearchKernel(DWidget *parent = nullptr);
    void initSearchKernel();
signals:
    void sendSignalSwitchWindow();
public slots:
    void setNextButtonAbledSlot();
private:
    DPushButton *m_nextButton;
    DLabel *m_titelLabel;
    DLabel *m_kernelLabel;
    DLabel *m_initrdLabel;
    DFileChooserEdit *m_searchKernelFile;
    DFileChooserEdit *m_searchinitrdFile;
};

#endif // SEARCHKERNEL_H

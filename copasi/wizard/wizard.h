/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:05 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'wizard.ui'
 **
 ** Created: Tue Sep 28 23:32:28 2004
 **      by: The User Interface Compiler ($Id: wizard.h,v 1.1.1.1 2004/10/26 15:18:05 anuragr Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QPushButton;
class QTextBrowser;

class WizardDialog : public QDialog
  {
    Q_OBJECT

  public:
    WizardDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~WizardDialog();

    QButtonGroup* buttonGroup;
    QPushButton* button1;
    QPushButton* button6;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    QPushButton* button5;
    QTextBrowser* textBrowser;
    QPushButton* backButton;
    QPushButton* forwardButton;
    QPushButton* cancelButton;

    static char* texts[6];

    virtual void init();
    virtual void setCopasiMainWindow(QWidget * copasiMainWindow);

  public slots:
    virtual void buttonGroup2_clicked(int);
    virtual void forwardButton_clicked();
    virtual void backButton_clicked();
    virtual void textBrowser_anchorClicked(const QString & name, const QString & link);

  protected:
    static char* Error;
    static QString helpPath;
    QWidget* copasiMainWindow;

    QVBoxLayout* WizardDialogLayout;
    QHBoxLayout* layout12;
    QHBoxLayout* layout9;

  protected slots:
    virtual void languageChange();
  };

#endif // WIZARDDIALOG_H

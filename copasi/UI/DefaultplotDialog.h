/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DefaultplotDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 14:08:20 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'DefaultplotDialog.ui'
 **
 ** Created: Wed Oct 5 15:59:05 2005
 **      by: The User Interface Compiler ($Id: DefaultplotDialog.h,v 1.2 2005/10/05 14:08:20 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef DEFAULTPLOTDIALOG_H
 #define DEFAULTPLOTDIALOG_H

#include <qvariant.h>
 #include <qdialog.h>
 #include <vector>
 #include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QListBox;
class QListBoxItem;
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;
class CCopasiProblem;
class CCopasiTask;

class DefaultPlotDialog : public QDialog
  {
    Q_OBJECT

  public:
    DefaultPlotDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~DefaultPlotDialog();

    QListBox* listBox;
    QLabel* titleLabel;
    QLineEdit* lineEditTitle;
    QTextEdit* textEdit;
    QPushButton* createButton;
    QPushButton* cancelButton;

  public slots:
    virtual void setTask(CCopasiTask * t);
    virtual void newSlot();

  protected:
    CCopasiTask* mpTask;
    std::vector<C_INT32> mList;
    int mIndex;

    QGridLayout* DefaultPlotDialogLayout;
    QHBoxLayout* layoutButtons;
    QSpacerItem* spacerButtons;

  protected slots:
    virtual void languageChange();

    virtual void slotCreate();
    virtual void slotSelect();
  };

#endif // DEFAULTPLOTDIALOG_H

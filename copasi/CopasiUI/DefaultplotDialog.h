/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DefaultplotDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/18 09:04:14 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'DefaultplotDialog.ui'
 **
 ** Created: Mo Apr 18 00:01:46 2005
 **      by: The User Interface Compiler ($Id: DefaultplotDialog.h,v 1.1 2005/04/18 09:04:14 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef DEFAULTPLOTDIALOG_H
#define DEFAULTPLOTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "utilities/CCopasiProblem.h"

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

    virtual void setProblem(const CCopasiProblem * p);

  protected:
    const CCopasiProblem* mpProblem;
    std::vector<CDefaultPlotDescription> mList;
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

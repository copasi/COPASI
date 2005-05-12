/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTextDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/12 11:39:23 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQTextDialog.ui'
 **
 ** Created: Thu May 12 07:13:05 2005
 **      by: The User Interface Compiler ($Id: CQTextDialog.h,v 1.1 2005/05/12 11:39:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQTEXTDIALOG_H
#define CQTEXTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QPushButton;

class CQTextDialog : public QDialog
  {
    Q_OBJECT

  public:
    CQTextDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQTextDialog();

    QTextEdit* mpTextEdit;
    QPushButton* mpBtnOK;
    QPushButton* mpBtnCancel;

    QString getText();

  protected:
    QVBoxLayout* CQTextDialogLayout;
    QHBoxLayout* mpBtnLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();
  };

#endif // CQTEXTDIALOG_H

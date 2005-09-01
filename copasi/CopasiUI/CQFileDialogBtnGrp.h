/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFileDialogBtnGrp.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/01 17:02:40 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFileDialogBtnGrp.ui'
 **
 ** Created: Thu Sep 1 12:31:22 2005
 **      by: The User Interface Compiler ($Id: CQFileDialogBtnGrp.h,v 1.1 2005/09/01 17:02:40 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFILEDIALOGBTNGRP_H
 #define CQFILEDIALOGBTNGRP_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QToolButton;

class CQFileDialogBtnGrp : public QWidget
  {
    Q_OBJECT

  public:
    CQFileDialogBtnGrp(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFileDialogBtnGrp();

    QToolButton* mpBtnHome;
    QToolButton* mpBtnExamples;

  protected:
    QVBoxLayout* CQFileDialogBtnGrpLayout;
    QSpacerItem* mpSpacer;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;
    QPixmap image1;
  };

#endif // CQFILEDIALOGBTNGRP_H

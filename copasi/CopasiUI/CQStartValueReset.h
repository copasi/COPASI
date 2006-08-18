/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQStartValueReset.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/18 16:33:59 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQStartValueReset.ui'
 **
 ** Created: Fri Aug 18 12:29:46 2006
 **      by: The User Interface Compiler ($Id: CQStartValueReset.h,v 1.1 2006/08/18 16:33:59 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQSTARTVALUERESET_H
#define CQSTARTVALUERESET_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;

class CQStartValueReset : public QDialog
  {
    Q_OBJECT

  public:
    CQStartValueReset(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQStartValueReset();

    QPushButton* mpBtnModel;
    QPushButton* mpBtnSolution;
    QPushButton* mpBtnRandom;
    QPushButton* mpBtnCancel;

    enum Result {MODEL = QDialog::Accepted + QDialog::Rejected + 1, RANDOM, SOLUTION};

  protected:
    QVBoxLayout* CQStartValueResetLayout;
    QSpacerItem* mpSpace;

  protected slots:
    virtual void languageChange();

  private slots:
    void slotModel();
    void slotRandom();
    void slotSolution();
  };

#endif // CQSTARTVALUERESET_H

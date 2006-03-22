/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingResultTab1.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 16:52:55 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingResultTab1.ui'
 **
 ** Created: Tue Mar 21 11:12:48 2006
 **      by: The User Interface Compiler ($Id: CQFittingResultTab1.h,v 1.1 2006/03/22 16:52:55 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGRESULTTAB1_H
 #define CQFITTINGRESULTTAB1_H

#include <qvariant.h>
 #include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class CFitProblem;

class CQFittingResultTab1 : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingResultTab1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingResultTab1();

    QLabel* mpLblObjectiveValue;
    QLineEdit* mpEditCPUTime;
    QLineEdit* mpEditEvaluations;
    QLabel* mpLblEvaluations;
    QLineEdit* mpEditRMS;
    QLabel* mpLblCPUTime;
    QLineEdit* mpEditSpeed;
    QLineEdit* mpEditObjectiveValue;
    QLineEdit* mpEditStdDeviation;
    QLabel* mpLblSpeed;
    QLabel* mpLblRMS;
    QLabel* mpLblStdDeviation;

    void load(const CFitProblem * pProblem);

  protected:
    QVBoxLayout* CQFittingResultTab1Layout;
    QSpacerItem* mpSpacer;
    QGridLayout* mpLayoutGrid;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CQFITTINGRESULTTAB1_H

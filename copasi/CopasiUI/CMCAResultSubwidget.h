/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CMCAResultSubwidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/26 15:30:36 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Tue Oct 26 17:21:40 2004
 **      by: The User Interface Compiler ($Id: CMCAResultSubwidget.h,v 1.2 2004/10/26 15:30:36 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "model/CState.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QTabWidget;
class QTable;
class CModel;
class CMCATask;
class CMCAMethod;

class CMCAResultSubwidget : public QWidget
  {
    Q_OBJECT

  public:
    CMCAResultSubwidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CMCAResultSubwidget();

    QLabel* mTopLabel;
    QTabWidget* mTabWidget;
    QWidget* tab;
    QTable* mTableElasticities;
    QWidget* tab_2;
    QTable* mTableFCC;
    QWidget* TabPage;
    QTable* mTableCCC;

    virtual void loadAll(const CMCAMethod * mcaMethod);
    virtual void loadElasticities(const CMCAMethod * mcaMethod);
    virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
    virtual void loadFluxCCs(const CMCAMethod * mcaMethod);

  protected:
    QVBoxLayout* CMCAResultSubwidgetLayout;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* TabPageLayout;

  protected slots:
    virtual void languageChange();

    virtual void init();
  };

#endif // CMCARESULTSUBWIDGET_H

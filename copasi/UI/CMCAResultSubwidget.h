/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/cvs_admin/c++style,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Wed Oct 27 16:02:33 2004
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
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

    virtual void loadAll(CMCAMethod * mcaMethod);
    virtual void loadElasticities(CMCAMethod * mcaMethod);
    virtual void loadConcentrationCCs(CMCAMethod * mcaMethod);
    virtual void loadFluxCCs(CMCAMethod * mcaMethod);

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

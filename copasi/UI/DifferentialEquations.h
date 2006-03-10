/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/10 09:57:42 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/DifferentialEquations.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Differential Equations
 *****************************************************************************/

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H
#include <qpushbutton.h> 
//#include <qtextbrowser.h>

#include "copasi.h"
#include "copasiWidget.h" 
//class CMathModel;
class CModel;
class CMetab;
class CReaction;
class QtMmlWidget;
class QScrollView;

class DifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  protected:
    //QTextBrowser *textBrowser;
    QScrollView* mScrollView;
    QtMmlWidget* mMmlWidget;

    //QPushButton *btnOK;
    //QPushButton *btnCancel;

  public:
    DifferentialEquations(QWidget *parent, const char * name = 0, WFlags f = 0);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool enter(const std::string & key = "");

  protected slots:
    //virtual void slotBtnOKClicked();
    //virtual void slotBtnCancelClicked();

  private:
    void loadDifferentialEquations(CModel * model);

    static void writeLHS(std::ostream & out, const std::string & metabName,
                         const std::string & compName, unsigned C_INT32 l);

    static void writeRHS(std::ostream & out, const CMetab* pMetab, const CReaction* pReac,
                         bool expand, bool expandFull,
                         unsigned C_INT32 l);

    //list keys of all reactions that have the metab in their balances
    static std::set<std::string> listReactionsForMetab(const CModel* model,
        const std::string & key);

    static void createParameterMapping(const CReaction* pReac,
                                       std::vector<std::vector<std::string> > & params);
  };

#endif

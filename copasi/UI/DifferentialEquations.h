/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H

#include <sstream>

#include <qpushbutton.h>

#include "copasi.h"
#include "CopasiUI/copasiWidget.h"
class CModel;
class CMetab;
class CModelEntity;
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

    QPushButton *btnSaveToFile;
    //QPushButton *btnOK;
    //QPushButton *btnCancel;

  public:
    DifferentialEquations(QWidget *parent, const char * name = 0, WFlags f = 0);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void saveToFileClicked();
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

    void writeLHS_ModelValue(std::ostream & out,
                             const std::string & valueName, unsigned C_INT32 l);

    void writeRHS_ModelEntity(std::ostream & out,
                              const CModelEntity* pEntity,
                              bool expandFull, unsigned C_INT32 l);

    std::ostringstream mml;
  };

#endif

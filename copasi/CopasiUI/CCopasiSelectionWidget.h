/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiSelectionWidget.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/08/31 15:45:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionWidget_H__
#define CCopasiSelectionWidget_H__

#include "qwidgetstack.h"
#include <vector>

class ObjectBrowserWidget;
class CCopasiSimpleSelectionTree;
class CModel;
class QWidget;
class CCopasiObject;

class CCopasiSelectionWidget: public QWidgetStack
  {
    Q_OBJECT

  public:
    CCopasiSelectionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CCopasiSelectionWidget();

    virtual void populateTree(const CModel * model);
    virtual void setOutputVector(std::vector<CCopasiObject *> * outputVector);
    virtual void setSingleSelection(bool singleSelection);
    virtual bool isSingleSelection() const;
    virtual void setExpertMode(bool expertMode);
    virtual bool expertMode() const;
    virtual void commit();

  protected:
    CCopasiSimpleSelectionTree* mpSimpleTree;
    ObjectBrowserWidget* mpObjectBrowser;
    std::vector<CCopasiObject*>* mpOutputVector;
    bool mSingleSelect;
    bool mExpertMode;
  };

class CCopasiRuleExpressionSelectionWidget: public CCopasiSelectionWidget
  {
    Q_OBJECT

  public:
    CCopasiRuleExpressionSelectionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    virtual ~CCopasiRuleExpressionSelectionWidget(){};
    virtual void setSingleSelection(bool){};
    virtual bool isSingleSelection() const{return true;};
    virtual void setExpertMode(bool){};
    virtual bool expertMode() const{return false;};
  };

#endif

/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiSelectionWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/10 12:45:09 $
   End CVS Header */

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

    virtual void populateTree(CModel * model);
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

#endif

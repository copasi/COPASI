/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ParametersWidget.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <qvariant.h>
#include <qdialog.h>

#include "CopasiUI/copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QListView;
class QListViewItem;
class QLabel;
class CParameterListItem;

class ParametersWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ParametersWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParametersWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    bool loadFromModel();
    bool saveToModel() const;

    std::string objKey;

    QPushButton* commitButton;
    QPushButton* revertButton;
    QListView* listView;
    QLabel* labelTitle;

    QGridLayout* ParametersWidgetLayout;
    QSpacerItem* spacer2;
    QVBoxLayout* layoutLeft;
    QSpacerItem* spacer1;

    CParameterListItem* mTimeItem;
    CParameterListItem* mCompItem;
    CParameterListItem* mReacItem;
    CParameterListItem* mMetabItem;
    CParameterListItem* mParamItem;

  protected slots:
    virtual void commitPressed();
    virtual void revertPressed();

    virtual void editItem(QListViewItem * item, const QPoint & pnt, int c);
    virtual void editItem(QListViewItem * item);
  };

#endif // PARAMETERSWIDGET_H

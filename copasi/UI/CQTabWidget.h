// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQTabWidget.h
 *
 *  Created on: May 8, 2012
 *      Author: shoops
 */

#ifndef COPASI_CQTabWidget
#define COPASI_CQTabWidget

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTabWidget.h"

#include <vector>

#ifdef COPASI_Provenance
#include "CEntityProvenanceDialog.h"
#endif

class CQTabWidget: public CopasiWidget, public Ui::CQTabWidget
{
  Q_OBJECT

public:
  CQTabWidget(const ListViews::ObjectType & objectType, CopasiWidget * pCopasiWidget,
              QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
  virtual ~CQTabWidget();

  void selectTab(int index) const;
  int getSelectedTab() const;

  /**
   * @return the number of tabs
   */
  const int getNumTabs() const;

  /**
   * @return the tab widget with given index
   */
  CopasiWidget *getTab(int index);

  /**
   * @return the header layout
   */
  QHBoxLayout* getHeaderLayout();

  /**
   * @return the button layout
   */
  QHBoxLayout* getButtonLayout();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void load();

  bool save();

private slots:
  void slotBtnCommit();
  void slotBtnRevert();
  void slotBtnDelete();
  void slotBtnNew();
  void slotBtnCopy();

signals:
  void deleteClicked();
  void newClicked();
  void copyClicked();

private:
  std::vector< CopasiWidget * > mPages;
  ListViews::ObjectType mObjectType;
  bool mIgnoreLeave;
#ifdef COPASI_Provenance
  CEntityProvenanceDialog* mpEntityProvenanceDialog;
  QString mPathFile;
  QList<QString> mVersionPathToCurrentModel;
#endif
};

#endif // COPASI_CQTabWidget

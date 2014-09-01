// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSpeciesWidget.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/14 16:17:45 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSpeciesWidget_h
#define CQSpeciesWidget_h

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQSpeciesWidget.h"

#include "copasi/UI/CQSortFilterProxyModel.h"
#include "copasi/UI/CQComboDelegate.h"
#include "copasi/UI/CQSpecieDM.h"

class CQSpeciesWidget : public CopasiWidget, public Ui::CQSpeciesWidget
{
  Q_OBJECT

public:
  CQSpeciesWidget(QWidget* parent = 0, const char* name = 0);
  ~CQSpeciesWidget();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();
  virtual void setFramework(int framework);

private:
  CQSpecieDM* mpSpecieDM;
  CQSortFilterProxyModel *mpProxyModel;
  QStringList mCompartments;
  CQComboDelegate* mpCompartmentDelegate;
  CQIndexComboDelegate* mpTypeDelegate;
  void deleteSelectedSpecies();
  void updateDeleteBtns();

protected:
  virtual bool enterProtected();
  virtual void keyPressEvent(QKeyEvent* ev);
  void refreshCompartments();

protected slots:
  virtual void slotBtnNewClicked();
  virtual void slotBtnDeleteClicked();
  virtual void slotBtnClearClicked();
  virtual void slotSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected);
  virtual void slotDoubleClicked(const QModelIndex proxyIndex);
  virtual void dataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight);
  virtual void slotFilterChanged();

#ifdef COPASI_UNDO
  virtual void slotChangeWidget(const size_t & id);
#endif
};

#endif // CQSpeciesWidget_h

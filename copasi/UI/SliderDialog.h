// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SLIDER_DIALOG_H__
#define SLIDER_DIALOG_H__

#include <QDialog>
//Added by qt3to4:
#include <QtCore/QEvent>
#include <QContextMenuEvent>
#include <QCloseEvent>
#include "copasi/copasi.h"
#include <vector>
#include <map>
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/UI/CWindowInterface.h"
#include "copasi/UI/ui_SliderDialog.h"
#include "copasi/UI/listviews.h"

class QScrollArea;
class QCheckBox;
class QPushButton;
class QSlider;
class CDataObject;
class QMenu;
class QAction;
class QFrame;
class DataModelGUI;
class CopasiSlider;
class CCopasiTask;
class CSlider;
class CopasiUI3Window;

class SliderDialog: public CWindowInterface, public Ui::SliderDialog
{
  Q_OBJECT

public:
  SliderDialog(QWidget* parent, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  virtual ~SliderDialog();
  void addSlider(CSlider* slider);
  void setCurrentFolderId(ListViews::WidgetType id);
  void setParentWindow(CopasiUI3Window* pPW);

  // sets the framework on the sliders dialog
  // This leads to changed sliders for metabolites
  // Because depending on the framework, we only allow sliders
  // for amount or concentration, but not both for the same metabolite
  void setFramework(int index);

  // This methods needs to be called by copasiui3window
  virtual void updateAllSliders();

  /**
   * Deletes all exisiting sliders.
   */
  void clear();

  /**
   * Resets the SliderDialog to its initial state.
   * It basically calls clear and readds the Label
   * for the task widgets that don't support sliders.
   */
  void reset();

  /**
   * Returns whether the slider dialog contains changes.
   */
  bool isChanged() const;

  /**
   * Sets the changed state of the SliderDialog.
   */
  void setChanged(bool changed);

  //return a pointer to this plot windows 'window' menu.
  virtual QMenu *getWindowMenu() const;

protected:
  virtual void changeEvent(QEvent *);
  virtual void showEvent(QShowEvent * pEvent);

  /**
   * Deletes all sliders that are no longer valid.
   */
  void deleteInvalidSliders();

  /**
   * Deletes all solders from the specified folder that are no longer valid
   * @param folderId the folder to delete sliders from
   * @return boolean indicating whether sliders have been deleted (true), or not
   */
  bool deleteInvalidSlidersFromFolder(ListViews::WidgetType folderId);

  ListViews::WidgetType mapFolderId2EntryId(ListViews::WidgetType folderId) const;

  void init();

  static size_t numMappings;
  static ListViews::WidgetType folderMappings[][2];

  virtual void contextMenuEvent(QContextMenuEvent* e);

  virtual void runTimeCourse();
  virtual void runScanTask();
  virtual void runSteadyStateTask();
  virtual void runMCATask();
  virtual void runLNATask();
  virtual void runParameterEstimationTask();
  virtual void runOptimizationTask();
  virtual void runCrossSectionTask();
  virtual void closeEvent(QCloseEvent* e);

  virtual CCopasiTask* getTaskForFolderId(ListViews::WidgetType folderId);
  std::vector<CSlider*>* getCSlidersForObject(CDataObject* pObject, std::vector<CSlider*>* pVector) const;
  CopasiSlider* findCopasiSliderForCSlider(CSlider* pCSlider);
  CSlider* equivalentSliderExists(CSlider* pCSlider);
  void clearSliderBox();
  void createSlidersForFolder(std::vector<QWidget*>& v);
  CopasiSlider *getCopasiSliderForCSlider(std::vector<QWidget*>& v, CSlider* slider);
  CSlider *getCSliderForCopasiSlider(std::vector<CSlider*>& v, QWidget* slider);
  void fillSliderBox();
  std::vector<CSlider*>* getCSlidersForCurrentFolderId();
  CopasiSlider* findCopasiSliderAtPosition(const QPoint& p);
  void setCurrentSlider(CopasiSlider* pSlider);
  virtual bool eventFilter(QObject*, QEvent* event);
  bool sliderObjectChanged(CSlider* pSlider) const;

  // This method check if the given object is a reference to the initial amount or the initial concentration
  // of a metabolite. Then it checks the current framework and the metabolite if a slider to the object
  // is actually allowed and if it isn't, it will return the correct object
  const CDataObject* determineCorrectObjectForSlider(const CDataObject* pObject);

  /**
   * Takes a CopasiSlider object and checks if the associated model object
   * fits the currently set framework. If not, the slider object and the values are adjusted.
   *
   * On success, true is returned.
   */
  bool setCorrectSliderObject(CopasiSlider* pSlider);

protected slots:
  void removeSlider(CopasiSlider* slider);
  void removeSlider(CopasiSlider* slider, ListViews::WidgetType folderId);
  void editSlider(CopasiSlider* slider);
  void restoreDefaults();
  void removeSlider();
  void removeSlider(ListViews::WidgetType folderId);
  void deleteSlider(CopasiSlider* pSlider);
  void deleteSlider(CopasiSlider* pSlider, ListViews::WidgetType folderId);
  void editSlider();
  void createNewSlider();
  void runTask();
  void sliderValueChanged();
  void sliderReleased();
  void sliderPressed();
  void resetValue();
  void setDefault();

protected:
  CopasiUI3Window* mpParentWindow;
  QMenu* mpContextMenu;
  QAction* mpaCreateNewSlider;
  QAction* mpaRemoveSlider;
  QAction* mpaEditSlider;
  QAction* mpaResetValue;
  QAction* mpaSetDefault;
  CopasiSlider* mpCurrSlider;
  std::map< ListViews::WidgetType, std::vector< QWidget* > > mSliderMap;
  std::map < ListViews::WidgetType, void(SliderDialog::*)() > mTaskMap;
  std::map< ListViews::WidgetType, std::vector< double > > mInitialValueMap;
  ListViews::WidgetType mCurrentFolderId;
  bool mSliderValueChanged;
  bool mSliderPressed;
  int mFramework;

  // stored whether the sliders have been changed
  bool mChanged;
};

#endif

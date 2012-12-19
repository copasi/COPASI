// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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

#include "qdialog.h"
//Added by qt3to4:
#include <QEvent>
#include <QContextMenuEvent>
#include <QCloseEvent>
#include "copasi.h"
#include <vector>
#include <map>
#include "report/CCopasiObjectName.h"

class QScrollArea;
class QCheckBox;
class QPushButton;
class QSlider;
class CCopasiObject;
class QMenu;
class QAction;
class QFrame;
class DataModelGUI;
class CopasiSlider;
class CCopasiTask;
class CSlider;
class CopasiUI3Window;

class SliderDialog: public QDialog
{
  Q_OBJECT

public:
  SliderDialog(QWidget* parent, const char* name = 0, bool modal = false, Qt::WFlags fl = 0);
  virtual ~SliderDialog();
  void addSlider(CSlider* slider);
  void setCurrentFolderId(size_t id);
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
protected:
  virtual void showEvent(QShowEvent * pEvent);

  /**
   * Deletes all sliders for the current folder id that
   * are no longer valid.
   */
  void deleteInvalidSliders();

  size_t mapFolderId2EntryId(size_t folderId) const;

  void init();

  static size_t numMappings;
  static size_t folderMappings[][2];
  //    static size_t knownTaskIDs[];
  //    static const char* knownTaskNames[];
  //    static size_t numKnownTasks;

  virtual void contextMenuEvent(QContextMenuEvent* e);

  virtual void runTimeCourse();
  virtual void runScanTask();
  virtual void runSteadyStateTask();
  virtual void runMCATask();
  virtual void runLNATask();
  virtual void runParameterEstimationTask();
  virtual void runOptimizationTask();
#ifdef COPASI_NONLIN_DYN
  virtual void runCrossSectionTask();
#endif
  virtual void closeEvent(QCloseEvent* e);

  virtual CCopasiTask* getTaskForFolderId(size_t folderId);
  std::vector<CSlider*>* getCSlidersForObject(CCopasiObject* pObject, std::vector<CSlider*>* pVector) const;
  CopasiSlider* findCopasiSliderForCSlider(CSlider* pCSlider);
  CSlider* equivalentSliderExists(CSlider* pCSlider);
  void clearSliderBox();
  void fillSliderBox();
  std::vector<CSlider*>* getCSlidersForCurrentFolderId();
  CopasiSlider* findCopasiSliderAtPosition(const QPoint& p);
  void setCurrentSlider(CopasiSlider* pSlider);
  virtual bool eventFilter(QObject*, QEvent* event);
  bool sliderObjectChanged(CSlider* pSlider) const;

  // This method check if the given object is a reference to the initial amount or the initial concentration
  // of a metabolite. Then it checks the current framework and the metabolite if a slider to the object
  // is actually allowed and if it isn't, it will return the correct object
  const CCopasiObject* determineCorrectObjectForSlider(const CCopasiObject* pObject);

  /**
   * Takes a CopasiSlider object and checks if the associated model object
   * fits the currently set framework. If not, the slider object and the values are adjusted.
   *
   * On success, true is returned.
   */
  bool setCorrectSliderObject(CopasiSlider* pSlider);

protected slots:
  void removeSlider(CopasiSlider* slider);
  void editSlider(CopasiSlider* slider);
  void removeSlider();
  void deleteSlider(CopasiSlider* pSlider);
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
  QPushButton* mpRunTaskButton;
  QPushButton* mpNewSliderButton;
  QCheckBox* mpAutoRunCheckBox;
  QCheckBox* mpAutoModifyRangesCheckBox;
  QScrollArea* mpScrollView;
  QFrame* mpSliderBox;
  QMenu* mpContextMenu;
  QAction* mpaCreateNewSlider;
  QAction* mpaRemoveSlider;
  QAction* mpaEditSlider;
  QAction* mpaResetValue;
  QAction* mpaSetDefault;
  CopasiSlider* mpCurrSlider;
  std::map< size_t, std::vector< QWidget* > > mSliderMap;
  std::map < size_t, void(SliderDialog::*)() > mTaskMap;
  size_t mCurrentFolderId;
  bool mSliderValueChanged;
  bool mSliderPressed;
  int mFramework;

  // stored whether the sliders have been changed
  bool mChanged;
};

#endif

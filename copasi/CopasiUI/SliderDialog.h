/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderDialog.h,v $
   $Revision: 1.33 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/08 10:25:01 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SLIDER_DIALOG_H__
#define SLIDER_DIALOG_H__

#include "qdialog.h"
#include "copasi.h"
#include <vector>
#include <map>
#include "report/CCopasiObjectName.h"

class QScrollView;
class QHBox;
class QVBox;
class QListBox;
class QCheckBox;
class QPushButton;
class QString;
class QSlider;
class CCopasiObject;
class QLabel;
class QPopupMenu;
class DataModelGUI;
class CopasiSlider;
class CCopasiTask;
class CSlider;
class CopasiUI3Window;

class SliderDialog: public QDialog
  {
    Q_OBJECT

  public:
    SliderDialog(QWidget* parent, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    virtual ~SliderDialog();
    void addSlider(CSlider* slider);
    void setCurrentFolderId(C_INT32 id);
    void setParentWindow(CopasiUI3Window* pPW);

  protected:
    CopasiUI3Window* pParentWindow;
    QPushButton* runTaskButton;
    QPushButton* newSliderButton;
    QCheckBox* autoRunCheckBox;
    QCheckBox* mpAutoModifyRangesCheckBox;
    QScrollView* scrollView;
    QVBox* sliderBox;
    QPopupMenu* contextMenu;
    CopasiSlider* currSlider;
    std::map<C_INT32 , std::vector< QWidget* > > sliderMap;
    std::map < C_INT32 , void(SliderDialog::*)() > taskMap;
    C_INT32 currentFolderId;

    C_INT32 mapFolderId2EntryId(C_INT32 folderId) const;

    bool mSliderValueChanged;
    bool mSliderPressed;

    void init();

    static C_INT32 numMappings;
    static C_INT32 folderMappings[][2];
    static C_INT32 knownTaskIDs[];
    static char* knownTaskNames[];
    static C_INT32 numKnownTasks;

    virtual void contextMenuEvent(QContextMenuEvent* e);

    virtual void runTimeCourse();
    virtual void runScanTask();
    virtual void runSteadyStateTask();
    virtual void closeEvent(QCloseEvent* e);

    virtual CCopasiTask* getTaskForFolderId(C_INT32 folderId);
    virtual void updateAllSliders();
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
  };

#endif

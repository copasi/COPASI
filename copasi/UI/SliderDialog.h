/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.h,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/14 13:13:45 $
   End CVS Header */

#ifndef SLIDER_DIALOG_H__
#define SLIDER_DIALOG_H__

#include "qdialog.h"
#include "copasi.h"
#include <vector>
#include <map>

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

class SliderDialog: public QDialog
  {
    Q_OBJECT

  public:
    SliderDialog(QWidget* parent);
    virtual ~SliderDialog();
    void addSlider(CSlider* slider);
    void setCurrentFolderId(C_INT32 id);

  protected:
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
    virtual void SliderDialog::runSteadyStateTask();
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

  protected slots:
    void removeSlider(CopasiSlider* slider);
    void editSlider(CopasiSlider* slider);
    void removeSlider();
    void editSlider();
    void createNewSlider();
    void runTask();
    void sliderValueChanged();
    void sliderReleased();
    void sliderPressed();
  };

#endif

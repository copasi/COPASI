/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/06 19:33:39 $
   End CVS Header */

#ifndef SLIDER_DIALOG_H__
#define SLIDER_DIALOG_H__

#include "qdialog.h"
#include "qvbox.h"
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
class CopasiSlider;
class QPopupMenu;

class SliderDialog: public QDialog
  {
    Q_OBJECT

  public:
    SliderDialog(QWidget* parent);
    virtual ~SliderDialog();
    void addSlider(CCopasiObject* object, C_INT32 folderId);
    void setCurrentFolderId(C_INT32 id);

  protected:
    QPushButton* runTaskButton;
    QCheckBox* autoRunCheckBox;
    QScrollView* scrollView;
    QVBox* sliderBox;
    QPopupMenu* contextMenu;
    CopasiSlider* currSlider;
    std::map<C_INT32 , std::vector< CopasiSlider* > > sliderMap;
    C_INT32 currentFolderId;

    C_INT32 mapFolderId2EntryId(C_INT32 folderId) const;

    void init();

    static C_INT32 numMappings;
    static C_INT32 folderMappings[][2];

    virtual void contextMenuEvent(QContextMenuEvent* e);

  public slots:
    void toggleRunButtonState(bool);

  protected slots:
    void removeSlider();
    void editSlider();
    void createNewSlider();
  };

class CopasiSlider: public QVBox
  {
    Q_OBJECT
  public:
    enum NumberType {undefined = 0, intType, doubleType};

    CopasiSlider(CCopasiObject* object, QWidget* parent = 0);
    virtual ~CopasiSlider();

    NumberType type() const;
    void setType(NumberType type);

    double value() const;
    void setValue(double value);
    double tickInterval() const;
    void setTickInterval(double tickInterval);
    CCopasiObject* object() const;
    void setObject(CCopasiObject* object);
    void setMinValue(double value);
    void setMaxValue(double value);
    double minValue() const;
    double maxValue() const;
    bool ensureConsistency();

  public slots:
    void sliderValueChanged(int value);

  protected:
    CCopasiObject* cobject;
    NumberType typeVar;
    double minValueVar;
    double maxValueVar;
    double factorVar;
    QSlider* slider;
    QLabel* label;

    void updateSliderData();
    void updateLabel();
    std::string numberToString(double number) const;
  };

#endif

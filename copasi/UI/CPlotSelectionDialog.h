/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CPlotSelectionDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/18 15:36:01 $
   End CVS Header */

#ifndef CPlotSelectionDialog_H__
#define CPlotSelectionDialog_H__

#include "qdialog.h"
#include <vector>

class QWidget;
class QPushButton;
class QSplitter;
class QCheckBox;
class SimpleSelectionWidget;
class ObjectBrowserWidget;
class QHBox;
class QVBox;
class QVBoxLayout;
class QLabel;
class CCopasiObject;
class CModel;

class CPlotSelectionDialog: public QDialog
  {
    Q_OBJECT

  public:
    CPlotSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE, WFlags f = 0);
    virtual ~CPlotSelectionDialog();
    void setOutputVectors(std::vector<CCopasiObject*>* outputVector1, std::vector<CCopasiObject*>* outputVector2);
    void setModel(CModel* model);

  protected slots:
    void slotOKButtonClicked();
    void slotCancelButtonClicked();
    void slotExpertCheckBoxToggled(bool checked);

  protected:
    void setTabOrder();

  protected:
    QPushButton* mpOKButton;
    QPushButton* mpCancelButton;
    QCheckBox* mpExpertCheckBox;
    SimpleSelectionWidget* mpXAxisSimpleSelectionWidget;
    SimpleSelectionWidget* mpYAxisSimpleSelectionWidget;
    ObjectBrowserWidget* mpXAxisObjectBrowserWidget;
    ObjectBrowserWidget* mpYAxisObjectBrowserWidget;
    QWidget* mpXAxisSelectionWidget;
    QWidget* mpYAxisSelectionWidget;
    QSplitter* mpSplitter;
    QHBox* mpButtonBox;
    QVBoxLayout* mpMainLayout;
    QLabel* mpXAxisLabel;
    QLabel* mpYAxisLabel;
    QVBox* mpXAxisSelectionBox;
    QVBox* mpYAxisSelectionBox;
    std::vector<CCopasiObject*>* mpXAxisOutputVector;
    std::vector<CCopasiObject*>* mpYAxisOutputVector;
    std::vector<CCopasiObject*>* mpXAxisTmpVector;
    std::vector<CCopasiObject*>* mpYAxisTmpVector;
  };

#endif // CPlotSelectionDialog_H__

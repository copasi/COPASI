/****************************************************************************
 **  $ CopasiUI/ScanWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Scan Widget
 *****************************************************************************/
#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include "copasi.h"
#include <qvariant.h>
#include <qwidget.h>
#include "copasiwidget.h"
#include <qscrollview.h>
class QVBox;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QTable;
class CScanTask;
class CScanProblem;
class CScanMethod;
class CModel;

class ScanWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ScanWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanWidget();
    //CScanTask *scanTask;
    void loadScan(CModel *model);

    QFrame* line7;
    QFrame* line6;
    QFrame* line8;
    QFrame* line8_2;
    QLabel* taskNameLabel;
    QCheckBox* taskJacobian;
    QLabel* taskDescriptionLabel;
    QLabel* parameterValueLabel;
    QCheckBox* taskStability;
    QCheckBox* bExecutable;
    QLineEdit* taskName;
    QTable* parameterTable, *parameterTable1;
    QPushButton* commitChange;
    QPushButton* cancelChange;
    QScrollView *scrollview;
    QVBox *vBox;

  protected:
    QGridLayout* ScanWidgetLayout;
    QHBoxLayout* Layout2;
    CModel *mModel;

  signals:
  public slots:
  };

#endif

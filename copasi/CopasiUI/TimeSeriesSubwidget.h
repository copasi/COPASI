/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesSubwidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/09/29 03:40:35 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Tue Sep 28 23:39:48 2004
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.h,v 1.3 2004/09/29 03:40:35 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef TIMESERIESSUBWIDGET_H
#define TIMESERIESSUBWIDGET_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTable;

class TimeSeriesSubWidget : public QWidget
  {
    Q_OBJECT

  public:
    TimeSeriesSubWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TimeSeriesSubWidget();

    QPushButton* pushButtonToggle;
    QPushButton* ButtonSaveData;
    QTable* dataTable;

  protected:
    QGridLayout* TimeSeriesSubWidgetLayout;
    QHBoxLayout* layout2;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

    void saveDataToFile();
    void toggleView();
  };

#endif // TIMESERIESSUBWIDGET_H

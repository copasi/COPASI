/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/cvs_admin/c++style,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Tue Apr 19 17:26:54 2005
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.h,v 1.5.6.1 2005/04/19 15:35:00 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef TIMESERIESSUBWIDGET_H
#define TIMESERIESSUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include "copasi.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CTimeSeriesTable;
class QComboBox;
class QPushButton;

class TimeSeriesSubWidget : public QWidget
  {
    Q_OBJECT

  public:
    TimeSeriesSubWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TimeSeriesSubWidget();

    QComboBox* comboBox;
    QPushButton* ButtonSaveData;
    CTimeSeriesTable* dataTable;

    virtual C_INT32 checkSelection(const QString& file);

  public slots:
    virtual CTimeSeriesTable * table();

  protected:
    QVBoxLayout* TimeSeriesSubWidgetLayout;
    QHBoxLayout* toplayout;
    QSpacerItem* spacer;

  protected slots:
    virtual void languageChange();

    void saveDataToFile();
    void toggleView();
    virtual void init();

  private:
    QPixmap image0;
  };

#endif // TIMESERIESSUBWIDGET_H

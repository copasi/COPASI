/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanContainerWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:26:30 $
   End CVS Header */

#ifndef CCONTAINERWIDGET_H
#define CCONTAINERWIDGET_H

#include <vector> 
//#include <qvariant.h>
#include <qtable.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLineEdit;
class QToolButton;
class QVBox;

class CUpDownSubwidget;

/**
 *  This widget is a table that contains other widgets (arranged vertically)
 *  it adds buttons to delete, move up or down the widgets
 */
class CScanContainerWidget : public QTable
  {
    Q_OBJECT

  public:
    CScanContainerWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CScanContainerWidget();

    std::vector<QWidget*> getWidgetList() const;
    void clearWidgetList();
    void addWidget(QWidget* widget, bool controls = true);

    //insert before row, if row=-1 insert before the last row
    void insertWidget(QWidget* widget, int row = -1);

  protected slots:
    void slotUp(int index);
    void slotDown(int index);
    void slotDel(int index);

  protected:
    void updateIndices();
  };

#endif

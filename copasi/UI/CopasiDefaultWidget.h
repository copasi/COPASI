/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CopasiDefaultWidget.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:44 $
   End CVS Header */

#ifndef COPASIDEFAULTW_H
#define COPASIDEFAULTW_H

//#include <qvariant.h>
//#include <qwidget.h>
//#include <qtextbrowser.h>
#include "copasiWidget.h" 
//class QVBoxLayout;
//class QHBoxLayout;
class QGridLayout;
class QLabel;
//class QLineEdit;

class CopasiDefaultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CopasiDefaultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CopasiDefaultWidget();

    //By G
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    QGridLayout* CopasiDefaultWidgetLayout;
    QLabel* TextLabel1;
    //std::string objKey; //By G
  };

#endif

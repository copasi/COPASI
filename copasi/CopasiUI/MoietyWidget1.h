/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MoietyWidget1.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:39 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/MoietyWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Moiety Widget, i.e the second level 
 ** of Moieties.
 *****************************************************************************/ 
/*
 reimplement UI to automatically change internal components size
 Author: Liang Xu
 */

#ifndef MOIETYWIDGET1_H
#define MOIETYWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
#include <qtextbrowser.h>
#include "copasiWidget.h"
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class CModel;
class CMoiety;

class MoietyWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    MoietyWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MoietyWidget1();

    //By G
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  protected:
    QGridLayout* MoietyWidget1Layout;
    QLabel* TextLabel1;
    QLineEdit* LineEdit2;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;
    QTextBrowser* textBrowser;

    bool loadFromMoiety(const CMoiety *);
    std::string objKey; //By G
  };

#endif // MOIETYWIDGET1_H

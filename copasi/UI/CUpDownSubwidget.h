/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CUpDownSubwidget.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 20:22:03 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CUpDownSubwidget.ui'
 **
 ** Created: Wed Oct 12 15:58:53 2005
 **      by: The User Interface Compiler ($Id: CUpDownSubwidget.h,v 1.6 2005/10/12 20:22:03 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CUPDOWNSUBWIDGET_H
 #define CUPDOWNSUBWIDGET_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QToolButton;

class CUpDownSubwidget : public QWidget
  {
    Q_OBJECT

  public:
    CUpDownSubwidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CUpDownSubwidget();

    QToolButton* toolButtonDel;
    QToolButton* toolButtonUp;
    QToolButton* toolButtonCopy;
    QToolButton* toolButtonDown;

    virtual int getIndex() const;
    void enableCopy(const bool &);

  public slots:
    virtual void setIndex(int, bool, bool);

  signals:
    void copy(int);
    void up(int);
    void down(int);
    void del(int);

  protected:
    int mIndex;

    QVBoxLayout* CUpDownSubwidgetLayout;
    QSpacerItem* spacer;
    QGridLayout* layout6;

  protected slots:
    virtual void languageChange();

    void slotUp();
    void slotDown();
    void slotDel();
    void slotCopy();

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;

    void init();
  };

#endif // CUPDOWNSUBWIDGET_H

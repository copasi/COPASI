/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/AboutDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:21 $
   End CVS Header */

#ifndef AboutDialog_H__
#define AboutDialog_H__

#include "qdialog.h"

class QTextEdit;
class QPushButton;
class QPixmap;
class QVBoxLayout;

class AboutDialog: public QDialog
  {
    Q_OBJECT

  public:
    AboutDialog(QWidget* parent,
                const char * text,
                const int & width,
                const int & heigth);
    virtual ~AboutDialog();

    static const char* text;

  protected slots:
    void closeButton_clicked();

  protected:
    QPushButton* closeButton;
    QTextEdit* textEdit;
    QPixmap* backgroundPixmap;
    QVBoxLayout* mainLayout;
  };

#endif

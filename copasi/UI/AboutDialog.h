/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/AboutDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/08 16:44:40 $
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
    AboutDialog(QWidget* parent);
    virtual ~AboutDialog();

  protected slots:
    void closeButton_clicked();

  protected:
    QPushButton* closeButton;
    QTextEdit* textEdit;
    QPixmap* backgroundPixmap;
    QVBoxLayout* mainLayout;

    static const char* text;
  };

#endif

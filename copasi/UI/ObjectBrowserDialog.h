/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ObjectBrowserDialog.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/07 15:41:08 $
   End CVS Header */

#ifndef OBJECTBROWSERDIALOG_H
#define OBJECTBROWSERDIALOG_H

#include <qdialog.h>
#include <vector>

class QPushButton;
class ObjectBrowserWidget;
class QGridLayout;
class QFrame;
class QSpacerItem;
class CopasiUI3Window;
class CCopasiObject;

class ObjectBrowserDialog : public QDialog
  {
    Q_OBJECT

  public:
    ObjectBrowserDialog(QWidget* parent = 0, const char* name = 0, bool modal = true);
    virtual ~ObjectBrowserDialog();
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);
    void selectObjects(std::vector<CCopasiObject*>* pObjectVector);

  protected:
    QPushButton* cancelButton;
    QPushButton* okButton;
    QFrame* Line1;
    QSpacerItem* spacer;
    ObjectBrowserWidget* objectBrowserWidget;
    QGridLayout* ObjectBrowserDialogLayout;

  public slots:
    void cancelClicked();
    void okClicked();

  private:
    //    CopasiUI3Window* mparent;
    void cleanup();

    //  protected:
    //    void closeEvent (QCloseEvent * e);
  };
#endif // OBJECTBROWSERDIALOG_H

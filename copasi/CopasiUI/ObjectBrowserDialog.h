/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ObjectBrowserDialog.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/08 07:11:23 $
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
    ObjectBrowserDialog(QWidget* parent = 0, const char* name = 0, bool modal = true, int state = 0);
    virtual ~ObjectBrowserDialog();
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);
    void selectObjects(std::vector<CCopasiObject*>* pObjectVector);

  protected:
    QPushButton* clearButton;
    QPushButton* toggleViewButton;
    QPushButton* cancelButton;
    QPushButton* okButton;
    QFrame* Line1;
    QSpacerItem* spacer;
    ObjectBrowserWidget* objectBrowserWidget;
    QGridLayout* ObjectBrowserDialogLayout;

  public slots:
    void cancelClicked();
    void okClicked();
    void toggleViewClicked();

  private:
    void cleanup();
  };
#endif // OBJECTBROWSERDIALOG_H

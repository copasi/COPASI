/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ObjectBrowserDialog.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/07 07:41:00 $
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

  protected:
    QPushButton* cancelButton;
    QPushButton* okButton;
    QFrame* Line1;
    QSpacerItem* spacer;
    QGridLayout* ObjectBrowserDialogLayout;
    ObjectBrowserWidget* objectBrowserWidget;

  public slots:
    virtual void cancelClicked();
    virtual void okClicked();

  public:
    ObjectBrowserDialog(QWidget* parent = 0, const char* name = 0, bool modal = true);
    virtual ~ObjectBrowserDialog();
    void cleanup();
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);
    void selectObjects(std::vector<CCopasiObject*>* pObjectVector);

  private:
    CopasiUI3Window* mparent;

  protected:
    void closeEvent (QCloseEvent * e);
  };
#endif // OBJECTBROWSERDIALOG_H

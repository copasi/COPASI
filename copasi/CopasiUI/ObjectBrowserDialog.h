/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ObjectBrowserDialog.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/06 16:29:20 $
   End CVS Header */

#ifndef OBJECTBROWSERDIALOG_H
#define OBJECTBROWSERDIALOG_H

#include <qdialog.h>
#include <vector>

class QGridLayout;
class CopasiUI3Window;
class ObjectBrowserWidget;
class CCopasiObject;

class ObjectBrowserDialog : public QDialog
  {
    Q_OBJECT
  private:
    CopasiUI3Window* mparent;

  public:
    ObjectBrowserDialog(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowserDialog();
    void cleanup();
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);
    ObjectBrowserWidget* objectBrowserWidget;

  public slots:
    virtual void nextClicked(int);

  protected:
    void closeEvent (QCloseEvent * e);
    QGridLayout* ObjectBrowserDialogLayout;
  };
#endif // OBJECTBROWSERDIALOG_H

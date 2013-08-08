#ifndef QANIMATION_WINDOW_H
#define QANIMATION_WINDOW_H

#include <QMainWindow>

#include <qlayout/ui_qanimationwindow.h>

class QLayoutScene;
class QCopasiAnimation;
class CCopasiDataModel;
class QAnimationWindow : public QMainWindow, public Ui::QAnimationWindow
{
  Q_OBJECT
public:
  QAnimationWindow ();
  virtual ~QAnimationWindow ();
  void setScene(QLayoutScene* scene, CCopasiDataModel* dataModel);
public slots:
  void slotShowStep(int);
protected:  
  QLayoutScene* mpScene;
  QCopasiAnimation* mAnimation;
};

#endif // QANIMATION_WINDOW_H
#ifndef QLAYOUT_VIEW_H
#define QLAYOUT_VIEW_H

#include <QGraphicsView>

class QLayoutScene;

class QLayoutView: public QGraphicsView
{
  Q_OBJECT
public:
  QLayoutView(QLayoutScene *scene);
  virtual ~QLayoutView();
protected:
  void wheelEvent ( QWheelEvent* event );
private: 
};

#endif
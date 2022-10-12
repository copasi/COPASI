// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQEXTENDER_H
#define CQEXTENDER_H


#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class CQExtender : public QWidget
{
  Q_OBJECT
private:
  QGridLayout mainLayout;
  QToolButton toggleButton;
  QFrame headerLine;
  QParallelAnimationGroup toggleAnimation;
  QScrollArea contentArea;
  int animationDuration {300};
  bool mIsExpanded {false};
  int collapsedHeight;
  int contentHeight;

public:
  explicit CQExtender(QWidget * parent = 0, const QString & title = "", const int animationDuration = 300);
  void setContentLayout(QLayout & contentLayout);

  /**
   * triggers the expanding of the area (should be used only after setContentLayout
   */
  void setExpanded();

  /**
   * changes the title of the push button
   */
  void setTitle(const QString& title);

  bool isExpanded();

  void updateHeights();

public slots:
  void toggle(bool collapsed);
};

#endif // CQEXTENDER_H

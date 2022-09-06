// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <QPropertyAnimation>
#include <QToolButton>
#include <QWidget>

#include "CQExtender.h"
#include <copasi/UI/qtUtilities.h>

// Extending content button.
//
// From: https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt
//
//

CQExtender::CQExtender(QWidget * parent, const QString & title, const int animationDuration)
  : QWidget(parent)
  , animationDuration(animationDuration)
{
  toggleButton.setStyleSheet("QToolButton { border: none; }");
  toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  toggleButton.setArrowType(Qt::ArrowType::RightArrow);
  toggleButton.setText(title);
  toggleButton.setCheckable(true);
  toggleButton.setChecked(false);

  headerLine.setFrameShape(QFrame::HLine);
  headerLine.setFrameShadow(QFrame::Sunken);
  headerLine.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

  if (!isDarkMode())
    contentArea.setStyleSheet("QScrollArea { background-color: white; border: none; }");

  contentArea.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  // start out collapsed
  contentArea.setMaximumHeight(0);
  contentArea.setMinimumHeight(0);

  // let the entire widget grow and shrink with its content
  toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
  toggleAnimation.addAnimation(new QPropertyAnimation(this, "maximumHeight"));
  toggleAnimation.addAnimation(new QPropertyAnimation(&contentArea, "maximumHeight"));
  // don't waste space
  mainLayout.setVerticalSpacing(0);
  mainLayout.setContentsMargins(0, 0, 0, 0);
  int row = 0;
  mainLayout.addWidget(&toggleButton, row, 0, 1, 1, Qt::AlignLeft);
  mainLayout.addWidget(&headerLine, row++, 2, 1, 1);
  mainLayout.addWidget(&contentArea, row, 0, 1, 3);
  setLayout(&mainLayout);

  connect(&toggleButton, &QToolButton::toggled, this, &CQExtender::toggle);
}

void
CQExtender::toggle(bool checked)
{
  toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
  toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
  toggleAnimation.start();

  mIsExpanded = checked;
}

void
CQExtender::setContentLayout(QLayout & contentLayout)
{
  delete contentArea.layout();
  contentArea.setLayout(&contentLayout);
  collapsedHeight = sizeHint().height() - contentArea.maximumHeight();
  contentHeight = contentLayout.sizeHint().height();

  updateHeights();
}

void CQExtender::setExpanded()
{
  toggleButton.toggle();
}

void CQExtender::setTitle(const QString& title)
{
  toggleButton.setText(title);
}

bool CQExtender::isExpanded()
{
  return mIsExpanded;
}


void CQExtender::updateHeights()
{
  collapsedHeight = sizeHint().height() - contentArea.maximumHeight();
  contentHeight = contentArea.layout()->sizeHint().height();

  for (int i = 0; i < toggleAnimation.animationCount() - 1; ++i)
    {
      QPropertyAnimation * spoilerAnimation = static_cast< QPropertyAnimation * >(toggleAnimation.animationAt(i));
      spoilerAnimation->setDuration(animationDuration);
      spoilerAnimation->setStartValue(collapsedHeight);
      spoilerAnimation->setEndValue(collapsedHeight + contentHeight);
    }

  QPropertyAnimation * contentAnimation = static_cast< QPropertyAnimation * >(toggleAnimation.animationAt(toggleAnimation.animationCount() - 1));
  contentAnimation->setDuration(animationDuration);
  contentAnimation->setStartValue(0);
  contentAnimation->setEndValue(contentHeight);

  toggleAnimation.setDirection(mIsExpanded ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
  toggleAnimation.start();
}

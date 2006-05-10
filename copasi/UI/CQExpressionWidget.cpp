/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpressionWidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/10 11:56:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQExpressionWidget.h"

CQExpressionHighlighter::CQExpressionHighlighter(CQExpressionWidget* ew)
    : QSyntaxHighlighter(ew)
{}

int CQExpressionHighlighter::highlightParagraph (const QString & text, int endStateOfLastPara)
{
  int pos = 0;
  int oldpos = -1;
  int delta;

  while (true)
    {
      pos = text.find("<", pos);
      if (pos == -1)
        delta = 0;
      else
        delta = pos - oldpos - 1;
      setFormat(oldpos + 1, delta, QColor(0, 0, 0));
      if (pos == -1) break;
      oldpos = pos;

      pos = text.find(">", pos);
      if (pos == -1)
        delta = 0;
      else
        delta = pos - oldpos + 1;
      setFormat(oldpos, delta, QColor(200, 0, 0));
      if (pos == -1) break;
      oldpos = pos;
    }
  return 0;
}

//***********************************************************************

CQExpressionWidget::CQExpressionWidget(QWidget * parent, const char * name)
    : QTextEdit(parent, name),
    mOldPar(0), mOldPos(0)
{
  setTextFormat(Qt::PlainText);
  new CQExpressionHighlighter(this);

  connect(this, SIGNAL(cursorPositionChanged(int, int)),
          this, SLOT(slotCursorPositionChanged(int, int)));
  connect(this, SIGNAL(selectionChanged()),
          this, SLOT(slotSelectionChanged()));
}

void CQExpressionWidget::keyPressEvent (QKeyEvent * e)
{
  //filter "<" and ">"
  if (e->text() == "<")
    return;
  if (e->text() == ">")
    return;

  QTextEdit::keyPressEvent(e);
}

#include <iostream>

void CQExpressionWidget::slotSelectionChanged()
{
  int par1, par2, pos1, pos2;
  getSelection(&par1, &pos1, &par2, &pos2);

  if (par1 == -1) //no selection, do nothing
    {
      getSelection(&mOldPar1, &mOldPos1, &mOldPar2, &mOldPos2);
      return;
    }

  //debug output
  //   std::cout << "sc:  " << par1 << ", "
  //                        << pos1 << ", "
  //                        << par2 << ", "
  //                        << pos2 << ", " << std::endl;

  //make sure a selection contains an object completely or not at all
  //TODO
  bool iio1 = isInObject(par1, pos1);
  bool iio2 = isInObject(par2, pos2);

  //   std::cout << iio1 << " " << iio2 << std::endl;

  //if both borders are outside do nothing.

  //if at least one is inside clear selection
  if (iio1 || iio2)
    removeSelection();

  //TODO: right now the any invalid selection is just cleared.
  //in some cases it would be nicer for the user if it would be
  //extended instead

  getSelection(&mOldPar1, &mOldPos1, &mOldPar2, &mOldPos2);
}

void CQExpressionWidget::slotCursorPositionChanged(int para, int pos)
{
  //debug output
  //std::cout << "cpc: " << para << ", " << pos << " . " << isInObject() << std::endl;

  //check if we are inside an object
  if (isInObject())
    {
      int newpos;
      //first decide in which direction we want to leave the object
      if (compareCursorPositions(mOldPar, mOldPos, para, pos))
        {
          //move right
          newpos = text(para).find(">", pos);
          if (newpos != -1)
            setCursorPosition(para, newpos + 1);
        }
      else
        {
          //move left
          newpos = text(para).findRev("<", pos);
          if (newpos != -1)
            setCursorPosition(para, newpos);
        }
    }

  getCursorPosition(&mOldPar, &mOldPos);
}

bool CQExpressionWidget::isInObject()
{
  int para, pos;
  getCursorPosition(&para, &pos);
  return isInObject(para, pos);

  /*  //the following code assumes the presence of the syntax highlighter
    if (color() == QColor(0,0,0)) return false;


    if (pos==0) return false;


    QString t = text(para);
    if (t[pos-1] == '>') return false;


    return true;*/
}

bool CQExpressionWidget::isInObject(int par, int pos)
{
  if (pos == 0) return false;

  bool result = false;

  QString tmp = text(par);
  //std::cout << "iio? " << par << " " << pos << std::endl;

  //first look to the left
  int lo, lc;
  lo = tmp.findRev('<', pos - 1);
  lc = tmp.findRev('>', pos - 1);
  //std::cout << "left:"  << lo << " " << lc  << std::endl;

  if ((lo == -1) and (lc == -1))
    result = false;
  else if (lc == -1)
    result = true;
  else if (lo == -1)
    {
      std::cout << "inconsistent expression!" << std::endl;
      result = false;
    }
  else if (lo < lc)
    result = false;
  else // lo > lc
    result = true;

  //TODO: we could implement a consistency check by trying to find the same
  //information from looking to the right.

  return result;
}

bool CQExpressionWidget::compareCursorPositions(int parold, int posold, int par, int pos)
{
  if (par > parold) return true;
  if (par < parold) return false;

  //we are in the same paragraph
  if (pos > posold) return true;
  return false;
}

void CQExpressionWidget::doKeyboardAction(QTextEdit::KeyboardAction action)
{
  int para, pos;
  getCursorPosition(&para, &pos);

  //handle backspace and delete. All other actions are ignored
  switch (action)
    {
    case QTextEdit::ActionBackspace:
      if (pos == 0) return;
      if (text(para)[pos - 1] == '>')
        {
          std::cout << "Backspace into object." << std::endl;
          //TODO
        }
      else
        QTextEdit::doKeyboardAction(action);
      break;

    case QTextEdit::ActionDelete:
      //TODO
      break;

    default:
      break;
    }
}

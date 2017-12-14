// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef PARAMETERTABLE_H
#define PARAMETERTABLE_H

#include <QTableWidget>

class CReactionInterface;
class CQComboDelegate;
class CModel;
class CReaction;

//class ColorTableItem : public Q3TableItem
//{
//public:
//  ColorTableItem(Q3Table *t, EditType et, QColor c, const QString txt);
//  ~ColorTableItem();
//  void setColor(QColor col) {color = col; table()->repaint();}

//private:
//  void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

//  QColor color;
//};

//class ColorCheckTableItem : public Q3CheckTableItem
//{
//public:
//  ColorCheckTableItem(Q3Table *t, QColor c, const QString txt);
//  ~ColorCheckTableItem();
//  void setColor(QColor col) {color = col; table()->repaint();}

//private:
//  void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

//  QColor color;
//};

//table used in the reactions widget

class ParameterTable : public QTableWidget
{
  Q_OBJECT

public:
  ParameterTable(QWidget * parent = 0);

  void initTable();

public slots:
  void updateTable(CReactionInterface & ri, CReaction * mpReaction);

private slots:
  void handleCurrentCell(int row, int col, int, int);
  void slotCellChanged(int row, int col);
  void slotCurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

signals:
  void signalChanged(int, int, QString);
  void parameterStatusChanged(int, bool);

protected:
  CQComboDelegate * mpComboDelegate;

private:
  QStringList mGlobalParameters;
  QStringList mSubstrates;
  QStringList mProducts;
  QStringList mModifiers;
  QStringList mVolumes;

  //convenience function. It gets a List of all metab names in the CMetabNameInterface format
  static const std::vector<std::string> getListOfAllMetabNames(const CModel & model,
      const CReactionInterface & ri);

  //convenience function.
  static QStringList getListOfAllGlobalParameterNames(const CModel & model);
  //convenience function.
  static QStringList getListOfAllCompartmentNames(const CModel & model);

  int mOldRow;

public:
  std::vector<size_t> mLine2Index;
  std::vector<size_t> mIndex2Line;
};

#endif
//********************************************************************************

/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/parametertable.h,v $
 $Revision: 1.14 $
 $Name:  $
 $Author: shoops $
 $Date: 2008/12/18 19:58:12 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef PARAMETERTABLE_H
#define PARAMETERTABLE_H

#include <q3table.h>
#include <qcombobox.h>

#include "copasi.h"
#include "model/CReaction.h"

class CReactionInterface;

class ColorTableItem : public Q3TableItem
  {
  public:
    ColorTableItem(Q3Table *t, EditType et, QColor c, const QString txt);
    ~ColorTableItem();
    void setColor(QColor col) {color = col; table()->repaint();}

  private:
    void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

    QColor color;
  };

class ColorCheckTableItem : public Q3CheckTableItem
  {
  public:
    ColorCheckTableItem(Q3Table *t, QColor c, const QString txt);
    ~ColorCheckTableItem();
    void setColor(QColor col) {color = col; table()->repaint();}

  private:
    void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

    QColor color;
  };

class ComboItem : public ColorTableItem
  {
  public:
    ComboItem(Q3Table *t, EditType et, QColor c, const QStringList & sl);
    QWidget *createEditor() const;
    void setContentFromEditor(QWidget *w);
    void setText(const QString &s);

  private:
    QComboBox *cb;
    QStringList mSL;
  };

//table used in the reactions widget

class ParameterTable : public Q3Table
  {
    Q_OBJECT

  public:
    ParameterTable(QWidget * parent = 0, const char * name = 0);

    void initTable();

  public slots:
    void updateTable(const CReactionInterface & ri, const CModel & model);

  private slots:
    void handleCurrentCell(int row, int col);
    void slotCellChanged(int row, int col);

  signals:
    void signalChanged(int, int, QString);
    void parameterStatusChanged(int, bool);

  private:
    //void initTable();

    //convenience function. It gets a List of all metab names in the CMetabNameInterface format
    static const std::vector<std::string> getListOfAllMetabNames(const CModel & model,
        const CReactionInterface & ri);

    //convenience function.
    static QStringList getListOfAllGlobalParameterNames(const CModel & model);
    //convenience function.
    static QStringList getListOfAllCompartmentNames(const CModel & model);

    int mOldRow;

  public:
    std::vector<C_INT32> mLine2Index;
    std::vector<C_INT32> mIndex2Line;
  };

#endif
//********************************************************************************

#ifndef PARAMETERTABLE_H
#define PARAMETERTABLE_H

#include <qtable.h>
#include <qcombobox.h>
#include "model/CReaction.h"

class CReactionInterface;

class ColorTableItem : public QTableItem
  {
  public:
    ColorTableItem(QTable *t, EditType et, QColor c, const QString txt);
    ~ColorTableItem();
    void setColor(QColor col) {color = col; table()->repaint();}

  private:
    void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

    QColor color;
  };

class ComboItem : public ColorTableItem
  {
  public:
    ComboItem(QTable *t, EditType et, QColor c, const QStringList & sl);
    QWidget *createEditor() const;
    void setContentFromEditor(QWidget *w);
    void setText(const QString &s);

  private:
    QComboBox *cb;
    QStringList mSL;
  };

class ParameterTable : public QTable
  {
    Q_OBJECT

  public:
    ParameterTable(QWidget * parent = 0, const char * name = 0);

    static void vectorOfStrings2QStringList(std::vector<std::string> vs, QStringList & qsl);

  public slots:
    void updateTable(const CReactionInterface & ri); // this will get a CReactionInterface & later

  private slots:
    void handleCurrentCell(int row, int col);
    void slotCellChanged(int row, int col);

  signals:
    void signalChanged(int, int, QString);

  private:
    void initTable();

    int mOldRow;

  public:
    std::vector<C_INT32> mLine2Index;
    std::vector<C_INT32> mIndex2Line;
  };

#endif 
//********************************************************************************

/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MoietyWidget.cpp,v $
   $Revision: 1.39 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:39 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/MoietyWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Moiety----It is Basically 
 ** the First level of Moieties.
 ********************************************************************/
#include <qapplication.h>
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>

#include "MoietyWidget.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "listviews.h"
#include "utilities/CMethodParameter.h"
#include "model/CMoiety.h"

/**
 *  Constructs a Widget for the Moiety subsection of the tree.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param model The CModel class which contains the moiety 
 *  to be displayed.
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */
MoietyWidget::MoietyWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mModel = NULL;
  binitialized = true;

  table = new MyTable(this, "tblMoieties");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  table->setNumCols(3);
  table->setNumRows(-1);

  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Number");
  tableHeader->setLabel(2, "Equation");

  table->setReadOnly(true);
  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->sortColumn(1, true, true);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setProtected(true);

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  //connect(this, SIGNAL(name(const QString &)), (ListViews*)parent, SLOT(slotMoietyTableChanged(const QString &)));
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));

  //connect(this, SIGNAL(leaf(CModel*)), (ListViews*)parent, SLOT(loadMoietiesNodes(CModel*)));
  //connect(this, SIGNAL(updated()), (ListViews*)parent, SLOT(dataModelUpdated()));

  pixelsWide0 = 0;
  pixelsWide1 = 0;
  pixelsWide2 = 0;
}

void MoietyWidget::fillTable() //By G
{
  const CMoiety *obj;
  const CCopasiVectorN < CMoiety > & objects = dataModel->getModel()->getMoieties();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  /*Calculate column spacing based on the choosen font*/
  QFont tablefont = QApplication::font(this);
  QFontMetrics fm(tablefont);
  pixelsWide0 = fm.width(objects[0]->getName().c_str());
  pixelsWide1 = fm.width(QString::number(objects[0]->getNumber()));
  pixelsWide2 = fm.width(objects[0]->getDescription().c_str());

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());
      table->setText(j, 1, QString::number(obj->getNumber()));
      table->setText(j, 2, obj->getDescription().c_str());

      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
}

void MoietyWidget::loadMoieties(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      //Emptying the table
      int numberOfRows = table->numRows();
      int i;
      for (i = 0; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }
      repaint_table();
    }
}

void MoietyWidget::repaint_table()
{
  if (!mModel)
    return;
  const CCopasiVectorN < CMoiety > &moieties = mModel->getMoieties();

  C_INT32 noOfMoietyRows = moieties.size();
  table->setNumRows (noOfMoietyRows);

  //Now filling the table.
  CMoiety *moiety;
  C_INT32 j;
  for (j = 0; j < noOfMoietyRows; j++)
    {
      moiety = moieties[j];
      table->setText(j, 0, moiety->getName().c_str());
      table->setText(j, 1, QString::number(moiety->getNumber()));
      table->setText(j, 2, moiety->getDescription().c_str());
    }
}

void MoietyWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void MoietyWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.

          //float weight0 = 1.0, weight1 = 2.0, weight2 = 6.0;
          float weight0 = pixelsWide0, weight1 = pixelsWide1, weight2 = pixelsWide2; //By G

          float weightSum = weight0 + weight1 + weight2;
          int w0, w1, w2;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth * (weight1 / weightSum);
          w2 = newWidth - w0 - w1;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          table->setColumnWidth(2, w2);
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width();
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > re->oldSize().width())
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < re->oldSize().width())
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / re->oldSize().width());
                  else
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                }
              else
                for (i = 0; i < table->numCols(); i++) // Do not expand
                  table->setColumnWidth(i, table->columnWidth(i));

              table->EnableColWidthUpdate();
              return;
            }
          //Zoom out
          //calculate total Width
          if (newWidth >= totalWidth)    //will not decrease any column width
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->columnWidth(i));
              table->EnableColWidthUpdate();
              return;
            }
          //will decrease only those larger than the minimum width
          //Less than the user specified total width
          if (newWidth <= minTotalWidth)
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->minColWidth[i]);
              table->EnableColWidthUpdate();
              return;
            }
          //Bigger than the user specified total width
          for (i = 0; i < table->numCols(); i++) // Do Expansion
            table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
          table->EnableColWidthUpdate();
          return;
        }
    }
  CopasiWidget::resizeEvent(re);
}

void MoietyWidget::slotTableCurrentChanged(int row, int col, int m , const QPoint & n)
{
  if (row >= table->numRows() || row < 0)
    return;
  QString x = table->text(row, 0);
  emit name(x);
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void MoietyWidget::showMessage(QString title, QString text)
{
  QMessageBox::about (this, title, text);
}

bool MoietyWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
      fillTable();
      break;
    case ListViews::STATE:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:

    default:
      break;
    }
  return true;
}

/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MetabolitesWidget.cpp,v $
   $Revision: 1.62 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2003/11/12 23:28:35 $
   End CVS Header */

/***********************************************************************
 **  $ CopasiUI/MetabolitesWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information
 ** obtained from the data model about the Metabolites----It is 
 ** the First level of Metabolites.
 ************************************************************************/
#include <math.h>

#include "MetabolitesWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a Widget for the Metabolites subsection of the tree for 
 *  displaying the Metabolites in model 'model'.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param model The CModel class which contains the metabolites 
 *  to be displayed.
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */
MetabolitesWidget::MetabolitesWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  binitialized = true;

  table = new MyTable(this, "tblMetabolites");
  table->setNumCols(5);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Initial Concentration");
  tableHeader->setLabel(2, "Concentration");
  tableHeader->setLabel(3, "Status");
  tableHeader->setLabel(4, "Compartment");

  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);
  btnSwitchCols = new QPushButton("&Show Numbers", this);
  btnDelete = new QPushButton("&Delete", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnSwitchCols);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnDelete);
  hBoxLayout->addSpacing(50);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()),
          this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()),
          this, SLOT(slotBtnCancelClicked()));
  connect(btnDelete, SIGNAL(clicked ()),
          this, SLOT(slotBtnDeleteClicked()));
  connect(btnSwitchCols, SIGNAL(clicked ()),
          this, SLOT(slotBtnSwitchColsClicked())); //By G
  connect(table, SIGNAL(currentChanged(int, int)),
          this, SLOT(CurrentValueChanged(int, int))); //By G

  m_SavedRow = 0;
  m_SavedCol = 0;
  prev_row = 0;
  prev_col = 0;
  btn_flag = 0;
}

void MetabolitesWidget::fillTable()
{
  const CMetab *obj;
  const CCopasiVector < CMetab > & objects = dataModel->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());

      if (btn_flag == 0) //By G
        {
          table->setText(j, 1, QString::number(obj->getInitialConcentration()));
          table->setText(j, 2, QString::number(obj->getConcentration()));
        }
      else
        {
          table->setText(j, 1, QString::number(obj->getInitialNumberDbl()));
          table->setText(j, 2, QString::number(obj->getNumberDbl()));
        }

      table->setText(j, 3, CMetab::StatusName[obj->getStatus()].c_str());
      table->setText(j, 4, obj->getCompartment()->getName().c_str());
      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
  table->setText(jmax, 2, "");
  table->setText(jmax, 3, "");
  table->setText(jmax, 4, "");
}

//**************************************************************************

void MetabolitesWidget::createNewObject()
{
  {
    std::string name = "metabolite_0";
    int i = 0;
    while (!dataModel->getModel()->addMetabolite(name))
      {
        i++;
        name = "metabolite_";
        name += QString::number(i).latin1();
      }
    table->setText(table->numRows() - 1, 0, name.c_str());
    table->setNumRows(table->numRows());
    //emit updated();
    //emit leaf(mModel);
    ListViews::notify(ListViews::METABOLITE, ListViews::ADD);
  }
}

void MetabolitesWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      //TODO: create a new Object
      createNewObject();
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void MetabolitesWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void MetabolitesWidget::CurrentValueChanged(int row, int col)
{
  //  at this point you know old values !
  prev_row = m_SavedRow;
  prev_col = m_SavedCol;

  m_SavedCol = col; // Save for a future use
  m_SavedRow = row; // Save for a future use
}

void MetabolitesWidget::slotBtnOKClicked()
{
  CMetab *obj;
  const CCopasiVector < CMetab > & objects = dataModel->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  int *renamed = new int[jmax];
  int *changed = new int[jmax];

  table->setCurrentCell(jmax, 0);
  double temp1;
  C_FLOAT64 temp2;

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      renamed[j] = 0;
      changed[j] = 0;

      //name
      QString name(table->text(j, 0));
      if (name.latin1() != obj->getName())
        {
          obj->setName(name.latin1());
          renamed[j] = 1;
        }

      //for Initial Concentration and Initial Number
      if (btn_flag == 0)
        {
          QString initialConcentration(table->text(j, 1));
          temp1 = initialConcentration.toDouble();
          if (fabs(temp1 - obj->getInitialConcentration()) > 1e-10)
            {
              obj->setInitialConcentration(temp1);

              QString Concentration(table->text(j, 2));
              temp1 = Concentration.toDouble();
              obj->setConcentration(temp1);

              changed[j] = 1;
            }
        }
      else
        {
          QString initialNumber(table->text(j, 1));
          temp2 = initialNumber.toDouble();
          if (fabs(temp2 - obj->getInitialNumberDbl()) > 1e-3) //TODO: this is extremely ugly
            {
              obj->setInitialNumberDbl(temp2);

              QString Number(table->text(j, 2));
              temp2 = Number.toDouble();
              obj->setNumberDbl(temp2);

              changed[j] = 1;
            }
        }

      //fixed?
      QString status(table->text(j, 3));
      if (status.latin1() != CMetab::StatusName[obj->getStatus()])
        {
          if (obj->getStatus() != CMetab::METAB_FIXED)
            obj->setStatus(CMetab::METAB_FIXED);
          else
            obj->setStatus(CMetab::METAB_VARIABLE);

          changed[j] = 1;
        }

      //compartment
      QString Compartment(table->text(j, 4));
      if (Compartment.latin1() != obj->getCompartment()->getName())
        {
          dataModel->getModel()->getCompartments()[Compartment.latin1()]->addMetabolite(*obj);
          dataModel->getModel()->getCompartments()[obj->getCompartment()->getName()]->getMetabolites().remove(obj->getName());
          dataModel->getModel()->initializeMetabolites();
          ListViews::notify(ListViews::COMPARTMENT, ListViews::CHANGE, "");

          changed[j] = 1;
        }
    }

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      if (renamed[j] == 1)
        ListViews::notify(ListViews::METABOLITE, ListViews::RENAME, obj->getKey());

      if (changed[j] == 1)
        ListViews::notify(ListViews::METABOLITE, ListViews::CHANGE, obj->getKey());
    }

  table->setCurrentCell(prev_row, prev_col);

  delete[] renamed;
  delete[] changed;

  return; //TODO: really check
}

void MetabolitesWidget::slotBtnSwitchColsClicked() //By G
{
  const CMetab *obj;
  const CCopasiVector < CMetab > & objects = dataModel->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  QHeader *tableHeader = table->horizontalHeader();

  if (btn_flag == 0)
    {
      tableHeader->setLabel(1, "Initial Number");
      tableHeader->setLabel(2, "Number");
      btnSwitchCols->setText("&Show Concentrations");
      btn_flag = 1;

      for (j = 0; j < jmax; ++j)
        {
          obj = objects[j];
          table->setText(j, 1, QString::number(obj->getInitialNumberDbl()));
          table->setText(j, 2, QString::number(obj->getNumberDbl()));
        }
    }
  else
    {
      tableHeader->setLabel(1, "Initial Concentration");
      tableHeader->setLabel(2, "Concentration");
      btnSwitchCols->setText("&Show Numbers");
      btn_flag = 0;

      for (j = 0; j < jmax; ++j)
        {
          obj = objects[j];
          table->setText(j, 1, QString::number(obj->getInitialConcentration()));
          table->setText(j, 2, QString::number(obj->getConcentration()));
        }
    }
}

void MetabolitesWidget::slotBtnCancelClicked()
{
  fillTable();
}

void MetabolitesWidget::slotBtnDeleteClicked()
{
  if (table->currentRow() < table->numRows() - 1) //To prevent from deleting last row.
    {
      int j = table->currentRow();
      if (table->isRowSelected(j, true)) //True for Completely selected rows.
        {
          int choice = QMessageBox::warning(this, "Confirm Delete",
                                            "Delete Selected Rows?",
                                            //"Only Fully Selected Rows will be deleted." ,
                                            "Yes", "No", 0, 0, 1);
          switch (choice)
            {
            case 0:     // Yes or Enter
              {
                QString name(table->text(j, 0));

                std::vector<std::string> effectedReacKeys = dataModel->getModel()->removeMetabReacKeys(mKeys[j]);

                if (effectedReacKeys.size() > 0)
                  {
                    QString effectedReac = "\nFollowing Reactions will be effected:\n";

                    CReaction* reac = (CReaction*)(CCopasiContainer*)CKeyFactory::get(effectedReacKeys[0]);
                    effectedReac.append(reac->getName().c_str());

                    for (int i = 1; i < effectedReacKeys.size(); i++)
                      {
                        effectedReac.append(", ");
                        reac = (CReaction*)(CCopasiContainer*)CKeyFactory::get(effectedReacKeys[i]);
                        effectedReac.append(reac->getName().c_str());
                      }

                    choice = QMessageBox::warning(this, "Confirm Delete",
                                                  effectedReac,
                                                  "Yes", "No", 0, 0, 1);
                  }

                if (choice == 0)
                  {
                    table->removeSelectedRows(true);
                    dataModel->getModel()->removeMetabolite(mKeys[j]);
                    ListViews::notify(ListViews::METABOLITE, ListViews::DELETE, mKeys[j]);
                  }

                break;
              }
            case 1:     // No or Escape
              break;
            }
        }
    }
}

void MetabolitesWidget::tableValueChanged(int C_UNUSED(row),
    int C_UNUSED(col))
{}

bool MetabolitesWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool MetabolitesWidget::leave()
{
  //does nothing.
  return true;
}

bool MetabolitesWidget::enter(const std::string & key)
{
  //does nothing.
  return true;
}

//*******************************************************************************************

void MetabolitesWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 , weight4 = 3.0;
          float weightSum = weight0 + weight1 + weight2 + weight3 + weight4;
          int w0, w1, w2, w3 , w4;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth * (weight1 / weightSum);
          w2 = newWidth * (weight2 / weightSum);
          w3 = newWidth * (weight3 / weightSum);
          w4 = newWidth - w0 - w1 - w2 - w3;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          table->setColumnWidth(2, w2);
          table->setColumnWidth(3, w3);
          table->setColumnWidth(4, w4);
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

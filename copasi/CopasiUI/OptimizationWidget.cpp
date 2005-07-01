/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationWidget.cpp,v $
   $Revision: 1.59 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/07/01 23:53:17 $
   End CVS Header */

#include <qfiledialog.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qtable.h>

#include "copasi.h"

#include "OptimizationWidget.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptMethod.h"
#include "optimization/COptItem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "OptimizationItemWidget.h"
#include "ObjectBrowserDialog.h"
#include "ObjectBrowserItem.h"
#include "CCopasiSelectionDialog.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"

//#include "CReportDefinitionSelect.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "utilities/CCopasiException.h"
#include "CScanContainerWidget.h"
#include "utilities/CopasiTime.h"

OptimizationWidget::OptimizationWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
    //    pParent(parent)
{
  if (!name)
    setName("OptimizationWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));

  buttonsSeparator = new QFrame(this, "buttonsSeparator");
  buttonsSeparator->setGeometry(QRect(11, 281, 558, 16));
  buttonsSeparator->setFrameShape(QFrame::HLine);
  buttonsSeparator->setFrameShadow(QFrame::Sunken);
  buttonsSeparator->setFrameShape(QFrame::HLine);

  paramsGroupBox = new QGroupBox(this, "paramsGroupBox");
  paramsGroupBox->setGeometry(QRect(11, 270, 558, 228));

  typeGroupBox = new QGroupBox(this, "typeGroupBox");
  typeGroupBox->setGeometry(QRect(330, 100 - 40, 230, 120 + 40));

  timeCheck = new QCheckBox(typeGroupBox, "timeCheck");
  timeCheck->setGeometry(QRect(30, 50 + 20, 84, 19));

  steadystateCheck = new QCheckBox(typeGroupBox, "steadystateCheck");
  steadystateCheck->setGeometry(QRect(30, 20 + 20, 90, 20));

  AddTaskButton = new QPushButton(this, "AddTaskButton");
  AddTaskButton->setGeometry(QRect(490, 230, 70, 30));
  AddTaskButton->setAutoMask(TRUE);
  AddTaskButton->setOn(FALSE);

  methodGroupBox = new QGroupBox(this, "methodGroupBox");
  methodGroupBox->setGeometry(QRect(10, 100 - 40, 300, 160 + 40));

  methodCombo = new QComboBox(FALSE, methodGroupBox, "methodCombo");
  methodCombo->setGeometry(QRect(30, 30, 220, 20));

  confirmButton = new QPushButton(this, "confirmButton");
  confirmButton->setGeometry(QRect(12, 504, 181, 24));

  runButton = new QPushButton(this, "runButton");
  runButton->setGeometry(QRect(199, 504, 182, 24));

  cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setGeometry(QRect(387, 504, 181, 24));

  selectParameterButton = new QPushButton(this, "selectParameterButton");
  selectParameterButton->setGeometry(QRect(489, 71 - 55, 50, 24));

  expressionEditlabel = new QLabel(this, "expressionEditlabel");
  expressionEditlabel->setGeometry(QRect(11, 71 - 55, 51, 24));

  expressionText = new QLineEdit(this, "expressionText");
  expressionText->setGeometry(QRect(68, 73 - 55, 415, 20));
  expressionText->setFrameShape(QLineEdit::LineEditPanel);
  expressionText->setFrameShadow(QLineEdit::Sunken);
  languageChange();
  resize(QSize(581, 447).expandedTo(minimumSizeHint()));

  parameterTable = new QTable(methodGroupBox, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setColumnStretchable(0, true);
  parameterTable->setGeometry(QRect(30, 60, 220, 90 + 40));

  // tab order

  setTabOrder(expressionText, steadystateCheck);
  setTabOrder(steadystateCheck, timeCheck);
  setTabOrder(timeCheck, parameterTable);
  setTabOrder(parameterTable, confirmButton);
  setTabOrder(confirmButton, cancelButton);

  //scrollview

  Layoutparams = new QHBoxLayout(paramsGroupBox, 0, 6, "Layout24");
  scrollview = new CScanContainerWidget(paramsGroupBox);
  Layoutparams->addWidget(scrollview);

  mObject = NULL;

  methodCombo->insertItem("Random Search");
  methodCombo->insertItem("RandomSearch Master");
  methodCombo->insertItem("Simulated Annealing");
  methodCombo->insertItem("Genetic Algorithm");
  methodCombo->insertItem("Evolutionary Program2");
  methodCombo->insertItem("Hybrid GA/SA");
  methodCombo->insertItem("Genetic Algorithm Stoch. Rank");

  // signals and slots connections

  // * connect the runButton with the respective slot
  connect(runButton, SIGNAL(clicked()), this, SLOT(runOptimizationTask()));
  // * connect the combo box with the respective slot
  connect(methodCombo, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));

  connect(timeCheck, SIGNAL(clicked()), this, SLOT(slotTimechecked()));
  connect(steadystateCheck, SIGNAL(clicked()), this, SLOT(slotSteadystatechecked()));
  connect(AddTaskButton , SIGNAL(clicked()), this, SLOT(slotAddItem()));
  connect(selectParameterButton , SIGNAL(clicked()), this, SLOT(slotChooseObject()));
  connect(confirmButton, SIGNAL(clicked()), this, SLOT(slotConfirm()));

  //reportDefinitionButton->setEnabled(false);

  // for the default option
  timeCheck->setChecked(true);
}

OptimizationWidget::~OptimizationWidget()
{}

void OptimizationWidget::CancelChangeButton()
{
  loadOptimization();
}

void OptimizationWidget::CheckBoxClicked()
{}

void OptimizationWidget::runOptimizationTask()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));

  if (!optimizationTask) return;

  // save the state of the widget
  saveOptimization();

  optimizationTask->initialize(NULL);

  setCursor(Qt::WaitCursor);

  CProgressBar* tmpBar = new CProgressBar();
  optimizationTask->setProgressHandler(tmpBar);
  tmpBar->show();

  CCopasiTimeVariable time = CCopasiTimeVariable::getCurrentWallTime();

  try
    {
      optimizationTask->process();
    }
  catch (CCopasiException Exception)
    {
      std::cout << std::endl << "exception in optimization task" << std::endl;
      //TODO: message box
    }

  std::cout << "*************** The optimization took "
  << (CCopasiTimeVariable::getCurrentWallTime() - time).isoFormat()
  << " ***************" << std::endl;

  //should be renamed?

  optimizationTask->restore();

  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();

  return;
}

bool OptimizationWidget::loadOptimization()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));

  if (!optimizationTask) return false;

  COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
  if (!optimizationProblem) return false;

  mModel = optimizationProblem->getModel();

  scrollview->clearWidgetList();

  //scrollview->updateFromWidgetList();

  //<todo>
  COptMethod *optimizationMethod = dynamic_cast<COptMethod*>(optimizationTask->getMethod());
  if (!optimizationMethod) return false;
  // for GA
  parameterTable->setNumRows(optimizationMethod->size());

  unsigned C_INT32 i;
  for (i = 0; i < optimizationMethod->size(); ++i)
    {
      QHeader *rowHeader = parameterTable->verticalHeader();
      rowHeader->setLabel(i, FROM_UTF8(optimizationMethod->getName(i)));
      CCopasiParameter::Type Type;
      QString value = getParameterValue(optimizationMethod, i, &Type);
      QTableItem * pItem = new QTableItem (parameterTable, QTableItem::Always, value);
      parameterTable->setItem(i, 0, pItem);
    }

  // the optimization items

  unsigned C_INT32 imax = optimizationProblem->getOptItemSize();

  for (i = 0; i < imax; ++i)
    {
      OptimizationItemWidget * tmp;
      const COptItem& item = optimizationProblem->getOptItem(i);
      tmp = new OptimizationItemWidget(scrollview);
      tmp->initFromOptItem(item);
      scrollview->addWidget(tmp);
    }

  // load the expression

  std::string objFunc = optimizationProblem->getObjectiveFunction();

  i = 0;

  std::string out_str = "";
  while (i < objFunc.length())
    {
      if (objFunc[i] == '<')
        {
          i++;
          std::string objectName = "";

          while (objFunc[i] != '>')
            {
              objectName += objFunc[i];
              i++;
            }

          CCopasiObjectName c1(objectName);
          out_str += "<" + RootContainer.getObject(c1)->getObjectDisplayName() + ">";
          continue;
        }

      else if (objFunc[i] == '>')
        {
          //do nothing
        }

      else
        {
          out_str += objFunc[i];
        }

      i++;
    }

  expressionText->setText(FROM_UTF8(out_str));

  // load the list of objects

  return true;
}

bool OptimizationWidget::slotAddItem()
{
  if (expressionText->text().length() > 0)
    {
      OptimizationItemWidget * tmp;
      tmp = new OptimizationItemWidget(scrollview);
      scrollview->addWidget(tmp);
      return true;
    }

  else
    return false;
}

bool OptimizationWidget::saveOptimization()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
  if (!optimizationTask) return false;

  COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
  if (!optimizationProblem) return false;

  COptMethod *optimizationMethod = dynamic_cast<COptMethod*>(optimizationTask->getMethod());
  if (!optimizationMethod) return false;

  unsigned C_INT32 i;
  QTableItem * pItem;
  QString value, strname;

  for (i = 0; i < optimizationMethod->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(optimizationMethod, i, value);
    }

  const std::vector<QWidget*> & widgetList = scrollview->getWidgetList();

  // clearing up the COptItems in COptProblem
  C_INT32 optItemSize = optimizationProblem->getOptItemSize(), numItem;

  for (numItem = optItemSize - 1; numItem >= 0;--numItem)
    optimizationProblem->removeOptItem(numItem);

  unsigned C_INT32 imax = widgetList.size();

  for (i = 0; i < imax; ++i)
    {
      const OptimizationItemWidget* tmp = dynamic_cast<OptimizationItemWidget*>(widgetList[i]);
      if (tmp)
        {
          tmp->saveToOptItem(optimizationProblem);
          continue;
        }
    }

  optItemSize = optimizationProblem->getOptItemSize();
  //CCopasiDataModel::Global->getModel()->compileIfNecessary();
  // optimizationProblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

  saveExpression(); // save objective function

  return true;
}

void OptimizationWidget::ReportDefinitionClicked()
{
  /*  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
    COptTask* optimizationTask = (COptTask*)(CCopasiContainer*)GlobalKeys.get(optimizationTaskKey);
    pSelectDlg->setReport(&(optimizationTask->getReport()));
    pSelectDlg->loadReportDefinitionVector();
    if (pSelectDlg->exec () == QDialog::Rejected)
      {
        return;
      }*/
}

//************* CCopasiWidget interface *******************************

bool OptimizationWidget::enter(const std::string & key)
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(key));
  if (!optimizationTask) return false;

  optimizationTaskKey = key;

  //pSteadyStateWidget->enter(SteadyStateKey);
  //pTrajectoryWidget->enter(TrajectoryKey);

  // ((COptProblem*)(optimizationTask->getProblem()))->createDebugOptimization(dataModel->getModel());

  loadOptimization();

  return true;
}

bool OptimizationWidget::leave()
{
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
  if (!optimizationTask) return false;

  return saveOptimization();
}

bool OptimizationWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      // check if there is a list of Report Defs
      /*CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = CCopasiDataModel::Global->getReportDefinitionList();
      if (pReportDefinitionVector)
        reportDefinitionButton->setEnabled(true);*/

      break;
    default:
      break;
    }
  return true;
}

std::string OptimizationWidget::getKey()
{
  return optimizationTaskKey;
}

bool OptimizationWidget::changeMethod(int index)
{
  saveOptimization();
  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));
  optimizationTask->setMethodType(index + 1);
  loadOptimization();
  return true;
}

void OptimizationWidget::languageChange()
{
  setCaption(tr("Optimization"));
  typeGroupBox->setTitle(tr("Type"));
  timeCheck->setText(tr("Time Course"));
  steadystateCheck->setText(tr("Steady State"));
  AddTaskButton->setText(tr("Add"));
  methodGroupBox->setTitle(tr("Optimization Technique"));
  //expressionNameLabel_2->setText(tr("Method"));
  confirmButton->setText(tr("confirm"));
  runButton->setText(tr("run"));
  cancelButton->setText(tr("cancel"));
  selectParameterButton->setText(tr("..."));
  //expressionNameLabel->setText(tr("Name"));
  expressionEditlabel->setText(tr("Expression"));
  expressionText->setText(QString::null);
}

/* function - slotChooseObject
 * Description -  parsing */ 
/* Author - stupe   */

void OptimizationWidget::slotChooseObject()
{
  std::string mPrevExpr;
  std::string mStr;
  std::string parseMe;
  CCopasiObject* mpObj;
  mModel = CCopasiDataModel::Global->getModel();
  CCopasiObjectName CN;

  CCopasiObject* tmpObject = mObject;
  // open a selection dialog with single selection mode
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);

  browseDialog->setModel(mModel);

  browseDialog->setSingleSelection(true);
  //browseDialog->enableExpertMode(false);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (mObject)
    selection->push_back(mObject);
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      mObject = selection->at(0);
      if (mObject)
        {
          parseList.push_back(mObject);
          mPrevExpr = (const char *) expressionText->text().utf8();
          parseMe = CRegisteredObjectName(mObject->getCN());
          mPrevExpr = mPrevExpr.append("<");
          mPrevExpr = mPrevExpr.append(mObject->getObjectDisplayName());
          mPrevExpr = mPrevExpr.append(">");
          //CN = CCopasiObjectName(mObject->getObjectName());
          mpObj = (CCopasiObject*)CCopasiContainer::Root->getObject(parseMe);
          //parseMe =
          //mpObj = (CCopasiObject*)CCopasiContainer::Root->getObject(CN.getRemainder());
          C_FLOAT64 value = *(C_FLOAT64*)mObject->getReference();
          //value = *(C_FLOAT64*)mpObj->getReference();
          /*/mStr = mObject->getObjectDisplayName();
          //const QString mPrevExpr(mStr.c_str());
          //expressionText->remove(expressionText->len
          //expressionText->append(mPrevExpr.truncate(mPrevExpr.lenght()-1));*/

          //mPrevExpr = mPrevExpr.append(mObject->getCN());
          expressionText->setText(FROM_UTF8(mPrevExpr));
          //rowCount = expressionText->numLines();
          //expressionText->setCursorPosition(rowCount ,1000);

          if (mObject != tmpObject)
            {
              if (mObject->isValueDbl())
                {
                  value = *(C_FLOAT64*)mObject->getReference();
                  //lineEditMin->setText(QString::number(value*0.5));
                  //lineEditMax->setText(QString::number(value*2));
                }
            }
        }

      //else
      //expressionName->setText("");
    }

  else
    {}}

/* function - slotParseExpression
 * Description -  parsing */ 
/* Author - stupe   */

bool OptimizationWidget::saveExpression()
{
  std::string DisplayName = "";
  std::string InfixCN = "";

  std::string InfixDispayName = (const char *)expressionText->text().utf8();
  std::vector<CCopasiObject *>::iterator it = parseList.begin();

  for (unsigned int i = 0; i < InfixDispayName.length(); i++)
    {
      InfixCN += InfixDispayName[i];
      DisplayName = "";

      if (InfixDispayName[i] == '<')
        {
          i++;
          while (i < InfixDispayName.length() && InfixDispayName[i] != '>')
            {
              if (InfixDispayName[i] == '\\') // '\' is an escape character.
                DisplayName += InfixDispayName[i++];

              DisplayName += InfixDispayName[i++];
            }

          it = parseList.begin();
          while (it < parseList.end())
            {
              if ((*it)->getObjectDisplayName() == DisplayName)
                {
                  InfixCN += (*it)->getCN();
                  break;
                }

              it++;
            }

          InfixCN += ">";
        }
    }

  COptTask* optimizationTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(optimizationTaskKey));

  if (!optimizationTask) return false;

  COptProblem *optimizationProblem = dynamic_cast<COptProblem *>(optimizationTask->getProblem());
  if (!optimizationProblem) return false;

  optimizationProblem->setObjectiveFunction(InfixCN);

  // :TODO: need to handle errors.
  return true;
}

void OptimizationWidget::slotSteadystatechecked()
{
  timeCheck->setChecked(false);
}

void OptimizationWidget::slotTimechecked()
{
  steadystateCheck->setChecked(false);
}

void OptimizationWidget::slotConfirm()
{
  saveOptimization();
}

//***********************************************************

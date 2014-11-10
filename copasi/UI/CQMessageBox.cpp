// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QStyle>
#include <QtGui/QApplication>

#include "copasiui3window.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"

CQMessageBox::CQMessageBox(Icon icon, const QString &title, const QString &text,
                           QMessageBox::StandardButtons buttons, QWidget *parent,
                           Qt::WindowFlags f):
  QMessageBox(icon, title, QString(), buttons, parent, f),
  mpTabWidget(NULL),
  mpPage1(NULL),
  mpVerticalLayoutPage1(NULL),
  mpText1(NULL),
  mpPage2(NULL),
  mpVerticalLayoutPage2(NULL),
  mpText2(NULL)
{
  if (CopasiUI3Window::getMainWindow() != NULL)
    {
      CopasiUI3Window::getMainWindow()->setMessageShown(true);
    }

  mpTabWidget = new QTabWidget(this);
  mpTabWidget->setObjectName(QString::fromUtf8("mpTabWidget"));
  mpTabWidget->setMinimumSize(QSize(400, 200));

  mpPage1 = new QWidget();
  mpPage1->setObjectName(QString::fromUtf8("mpPage1"));

  mpVerticalLayoutPage1 = new QVBoxLayout(mpPage1);
  mpVerticalLayoutPage1->setMargin(2);
  mpVerticalLayoutPage1->setObjectName(QString::fromUtf8("mpVerticalLayoutPage1"));

  mpText1 = new QTextEdit(mpPage1);
  mpText1->setObjectName(QString::fromUtf8("mpText1"));
  mpText1->setReadOnly(true);
  mpText1->setText(text);
  mpVerticalLayoutPage1->addWidget(mpText1);

  mpTabWidget->addTab(mpPage1, QString("Messages"));

  // The code below is derived from qt-4.4.3/src/gui/dialogs/qmessagebox.cpp
  static_cast<QGridLayout *>(layout())->addWidget(mpTabWidget, 0, 1, 1, 1);
  QLabel * pLabel = findChild<QLabel *>("qt_msgbox_label");

  if (pLabel != NULL)
    pLabel->hide();
}

CQMessageBox::~CQMessageBox()
{
  if (CopasiUI3Window::getMainWindow() != NULL)
    {
      CopasiUI3Window::getMainWindow()->setMessageShown(false);
    }
}

// static
QMessageBox::StandardButton CQMessageBox::information(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Information, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

QMessageBox::StandardButton CQMessageBox::question(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Question, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::warning(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Warning, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::critical(QWidget *parent, const QString &title,
    const QString &text, QMessageBox::StandardButtons buttons,
    QMessageBox::StandardButton defaultButton)
{
  if (!CopasiUI3Window::isMainThread())
    return defaultButton;

  CQMessageBox * pMessageBox = new CQMessageBox(QMessageBox::Critical, title, text, buttons, parent);
  pMessageBox->setDefaultButton(defaultButton);
  StandardButton choice = (StandardButton) pMessageBox->exec();
  delete pMessageBox;

  return choice;
}

// static
QMessageBox::StandardButton CQMessageBox::confirmDelete(QWidget *parent,
    const QString &objectType, const QString &objects,
    const std::set< const CCopasiObject * > & deletedObjects)
{
  if (deletedObjects.size() == 0)
    return QMessageBox::Ok;

  // Determine the affected data model
  const CCopasiDataModel * pDataModel = (*deletedObjects.begin())->getObjectDataModel();

  // Determine the affected function DB
  CFunctionDB * pFunctionDB =
    dynamic_cast< CFunctionDB * >((*deletedObjects.begin())->getObjectAncestor("FunctionDB"));

  if (pDataModel == NULL &&
      pFunctionDB == NULL)
    return QMessageBox::Ok;

  if (pFunctionDB != NULL)
    {
      // TODO In case a function is deleted we need to loop through all data models
      pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
    }
  else
    {
      pFunctionDB = CCopasiRootContainer::getFunctionList();
    }

  QString msg =
    QString("Do you want to delete the listed %1?\n  %2\n").arg(objectType, objects);

  std::set< const CCopasiObject * > Functions;
  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;
  std::set< const CCopasiObject * > Events;
  std::set< const CCopasiObject * > Tasks;

  bool Used = false;

  if (pFunctionDB != NULL)
    {
      Used |= pFunctionDB->appendDependentFunctions(deletedObjects, Functions);

      if (Functions.size() > 0)
        {
          msg.append("Following functions(s) reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Functions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  const CModel * pModel = NULL;

  if (pDataModel != NULL)
    {
      pModel = pDataModel->getModel();

      // We need to check the tasks
      Used |= pDataModel->appendDependentTasks(deletedObjects, Tasks);

      if (Tasks.size() > 0)
        {
          msg.append("Following task(s) reference above and will be modified:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Tasks.begin();
          std::set< const CCopasiObject * >::const_iterator end = Tasks.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  if (pModel != NULL)
    {
      Used |= pModel->appendDependentModelObjects(deletedObjects, Reactions, Metabolites,
              Compartments, Values, Events);

      if (Reactions.size() > 0)
        {
          msg.append("Following reactions(s) reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Reactions.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Metabolites.size() > 0)
        {
          msg.append("Following species reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Metabolites.begin();
          std::set< const CCopasiObject * >::const_iterator end = Metabolites.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Values.size() > 0)
        {
          msg.append("Following global quantities reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Values.begin();
          std::set< const CCopasiObject * >::const_iterator end = Values.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Compartments.size() > 0)
        {
          msg.append("Following compartment(s) reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Compartments.begin();
          std::set< const CCopasiObject * >::const_iterator end = Compartments.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }

      if (Events.size() > 0)
        {
          msg.append("Following event(s) reference above and will be deleted:\n  ");

          std::set< const CCopasiObject * >::const_iterator it = Events.begin();
          std::set< const CCopasiObject * >::const_iterator end = Events.end();

          for (; it != end; ++it)
            {
              msg.append(FROM_UTF8((*it)->getObjectName()));
              msg.append("\n  ");
            }

          msg.remove(msg.length() - 2, 2);
        }
    }

  StandardButton choice = QMessageBox::Ok;

  if (Used)
    {
      choice = CQMessageBox::question(parent, "CONFIRM DELETE", msg,
                                      QMessageBox::Ok | QMessageBox::Cancel,
                                      QMessageBox::Cancel);
    }

  return choice;
}

void CQMessageBox::setText(const QString & text)
{
  mpText1->setText(text);
}

void CQMessageBox::setFilteredText(const QString & text)
{
  if (!text.isEmpty() && mpPage2 == NULL)
    {
      mpPage2 = new QWidget();
      mpPage2->setObjectName(QString::fromUtf8("mpPage2"));

      mpVerticalLayoutPage2 = new QVBoxLayout(mpPage2);
      mpVerticalLayoutPage2->setMargin(2);
      mpVerticalLayoutPage2->setObjectName(QString::fromUtf8("mpVerticalLayoutPage2"));

      mpText2 = new QTextEdit(mpPage2);
      mpText2->setObjectName(QString::fromUtf8("mpText2"));
      mpText2->setReadOnly(true);
      mpVerticalLayoutPage2->addWidget(mpText2);
      mpTabWidget->addTab(mpPage2, QString("Minor Issues"));
    }

  mpText2->setText(text);
}

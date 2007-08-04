// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.cpp,v $
//   $Revision: 1.37 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/04 21:44:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qwidget.h>
#include <qscrollview.h>
#include <qlayout.h>
#include <qcursor.h>
#include <qregexp.h>
#include <qmessagebox.h>

#include <sstream>

//#include <qfont.h>
//#include <qtextbrowser.h>
//#include <qstylesheet.h>

#include "DifferentialEquations.h"
#include "listviews.h"
//#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"
//#include "model/CModel.h"
//#include "function/CExpression.h"
//#include "report/CKeyFactory.h"

#include "CopasiFileDialog.h"

#include "model/CMMLOutput.h"

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // Have_MML

DifferentialEquations::DifferentialEquations(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  //textBrowser = new QTextBrowser (this, "Text Browser");
  //QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  QGridLayout* layout = new QGridLayout(this, 1, 1, 11, 6, "DEWidgetLayout");

  //vBoxLayout->addWidget(textBrowser);

  /*QStyleSheet * Style = new QStyleSheet;
  QStyleSheetItem * lhs = new QStyleSheetItem(Style, "lhs");
  lhs->setDisplayMode(QStyleSheetItem::DisplayBlock);
  QStyleSheetItem * rhs = new QStyleSheetItem(Style, "rhs");
  rhs->setDisplayMode(QStyleSheetItem::DisplayBlock);
  rhs->setMargin(QStyleSheetItem::MarginLeft, 20);
  rhs->setMargin(QStyleSheetItem::MarginBottom, 10);
  QStyleSheetItem * emp = new QStyleSheetItem(Style, "emp");
  emp->setDisplayMode(QStyleSheetItem::DisplayInline);
  emp->setFontItalic(true);

  textBrowser->setStyleSheet(Style);
  textBrowser->setTextFormat(Qt::RichText);*/

  mScrollView = new QScrollView(this);
  layout->addWidget(mScrollView, 0, 0);

  mScrollView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mScrollView->setResizePolicy(QScrollView::AutoOneFit);

  mMmlWidget = new QtMmlWidget(mScrollView->viewport());
  mMmlWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mMmlWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mMmlWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());

  mScrollView->addChild(mMmlWidget);

  btnSaveToFile = new QPushButton("Save (MathML Presentation Markup)", this);
  connect(btnSaveToFile, SIGNAL(clicked()),
          this, SLOT(saveToFileClicked()));
  layout->addWidget(btnSaveToFile, 1, 0);

  //btnOK = new QPushButton("&OK", this);
  //btnCancel = new QPushButton("&Cancel", this);

  //QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  //hBoxLayout->addSpacing(32);

  /*hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);*/

  //connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  //connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

#include "utilities/copasimathml.h"

void DifferentialEquations::loadDifferentialEquations(CModel * model)
{
  bool hasContents = false;
  mml.str("");

  CMMLOutput::writeDifferentialEquations(mml, model, true, true, false);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());
  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mMmlWidget->setContent(FROM_UTF8(mml.str()));
  mScrollView->resizeContents(mMmlWidget->sizeHint().width(), mMmlWidget->sizeHint().height());
  //std::cout << mml.str() << std::endl;

  if (tmp) tmp->unsetCursor();

  btnSaveToFile->setEnabled(hasContents);
}

//void DifferentialEquations::slotBtnOKClicked()
//{}

//void DifferentialEquations::slotBtnCancelClicked()
//{}

bool DifferentialEquations::update(ListViews::ObjectType objectType,
                                   ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
    case ListViews::FUNCTION:
      loadDifferentialEquations(CCopasiDataModel::Global->getModel());
      break;

    default:
      break;
    }
  return true;
}

bool DifferentialEquations::enter(const std::string & C_UNUSED(key))
{
  loadDifferentialEquations(CCopasiDataModel::Global->getModel());
  return true;
}

void DifferentialEquations::saveToFileClicked()
{
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          QString::null,
                                          "MathML (*.mml);;XML (*.xml);;All Files (*);;",
                                          "Save Differential Equations to MathML File");

      if (!outfilename) return;

      if (!outfilename.endsWith(".mml") &&
          !outfilename.endsWith(".xml") &&
          !outfilename.endsWith("."))
        outfilename += ".mml";

      outfilename = outfilename.remove(QRegExp("\\.$"));

      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);
  ofile << mml.str();

  ofile.close();
}

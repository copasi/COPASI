// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRandom.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/18 12:37:05 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CScanWidgetRandom.h"

#include <iostream>

#include <qvalidator.h>

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/icons/Copasi16-Alpha.xpm"

//#include <qvariant.h>
//#include "CScanWidgetRandom.ui.h"

/*
 *  Constructs a CScanWidgetRandom as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRandom::CScanWidgetRandom(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  std::cout << "Constructor: A" << std::endl;
  setupUi(this);
  std::cout << "Constructor: B" << std::endl;

  lineEditMax->resize(112, 22);
  lineEditMin->resize(111, 22);

//  buttonObject->setPixmap(QPixmap(":/icons/Copasi16-Alpha_xpm"));
//  buttonObject->setPixmap(QPixmap(":/icons/Copasi.ico"));

//  QImage img;
//  img.loadFromData(":/icons/Copasi16-Alpha.xpm", sizeof(":/icons/Copasi16-Alpha.xpm"), "PNG");
//  buttonObject->setIcon(QIcon(QPixmap::fromImage(img)));

//    QIcon icon;
//    icon.addPixmap(QPixmap(QString::fromUtf8("icons/Copasi16-Alpha.xpm")), QIcon::Normal, QIcon::Off);
//    icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/Copasi16-Alpha.xpm")), QIcon::Normal, QIcon::Off);
//    buttonObject->setIcon(icon);

//    buttonObject->setIcon(QIcon(":/icons/copasi_icon.png"));
//  buttonObject->setIcon(QPixmap(":/icons/Copasi16-Alpha.xpm"));

  buttonObject->setIcon(QPixmap(Copasi16_Alpha_xpm));

//  icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/Copasi16-Alpha.xpm")), QIcon::Normal, QIcon::Off);

  init();
  retranslateUi(this);
  std::cout << "Constructor: C" << std::endl;
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetRandom::~CScanWidgetRandom()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetRandom::languageChange()
{
  retranslateUi(this);
}

void CScanWidgetRandom::init()
{
  /*  std::cout << "init: A" << std::endl;
    lineEditObject->setReadOnly(true);

    lineEditMin->setValidator(new QDoubleValidator(lineEditMin));
    lineEditMax->setValidator(new QDoubleValidator(lineEditMax));

    mpObject = NULL;
    std::cout << "init: B" << std::endl;
  */}

void CScanWidgetRandom::slotChooseObject()
{
  /*  std::cout << "sCO: A" << std::endl;
    const CCopasiObject * pObject =
      //    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::INITIAL_VALUE,
      CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::INITIAL_PARAMETER,
                                              mpObject);

    if (mpObject != pObject) // Object selection changed.
      {
        mpObject = pObject;

        if (mpObject)
          {
            lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));

            if (mpObject->isValueDbl())
              {
                C_FLOAT64 value = *(C_FLOAT64*)mpObject->getValuePointer();
                C_INT32 type = comboBoxType->currentItem();

                if (type == 0) //uniform
                  {
                    lineEditMin->setText(QString::number(value*0.5));
                    lineEditMax->setText(QString::number(value*2));
                  }

                if (type == 1) //normal
                  {
                    lineEditMin->setText(QString::number(value));
                    lineEditMax->setText(QString::number(value*0.1));
                  }

                if (type == 2) //poisson
                  {
                    lineEditMin->setText(QString::number(value));
                    lineEditMax->setText("");
                  }
              }
          }
        else
          {
            lineEditObject->setText("");
            lineEditMin->setText("");
            lineEditMax->setText("");
          }
      }
    std::cout << "sCO: B" << std::endl;
  */}

#include "report/CCopasiObjectName.h"
bool CScanWidgetRandom::initFromScanItem(CCopasiParameterGroup * pg, const CModel* model)
{
  /*  std::cout << "iFSI: A" << std::endl;
    if (!model) return false;
    mpModel = model;

    unsigned C_INT32 * tmp;

    if (!(tmp = pg->getValue("Type").pUINT)) return false;
    if (* (CScanProblem::Type *) tmp != CScanProblem::SCAN_RANDOM)
      return false;

    std::string *pString;
    if (!(pString = pg->getValue("Object").pSTRING)) return false;
    if (*pString == "")
      mpObject = NULL;
    else
      mpObject = CCopasiContainer::ObjectFromName(*pString);

    if (mpObject)
      lineEditObject->setText(FROM_UTF8(mpObject->getObjectDisplayName()));
    else
      lineEditObject->setText("");

    if (!(tmp = pg->getValue("Distribution type").pUINT)) return false;

    std::cout << "iFSI: B" << std::endl;

    comboBoxType->setCurrentItem(*tmp);
    changeType();

    lineEditMin->setText(getParameterValue(pg, "Minimum"));
    lineEditMax->setText(getParameterValue(pg, "Maximum"));

    bool * pBool;
    if (!(pBool = pg->getValue("log").pBOOL)) return false;
    checkBoxLog->setChecked(* pBool);

    std::cout << "iFSI: C" << std::endl;
    return true;
  */}

bool CScanWidgetRandom::saveToScanItem(CScanProblem * pg) const
{
  /*  std::cout << "sTSI: A" << std::endl;
      CScanProblem::Type type = CScanProblem::SCAN_RANDOM;

      unsigned C_INT32 steps = 1;

      CCopasiParameterGroup* tmp = pg->createScanItem(type, steps, mpObject);
      assert(tmp);

      tmp->setValue("Distribution type", (unsigned C_INT32)comboBoxType->currentItem());
      tmp->setValue("Minimum", lineEditMin->text().toDouble());
      tmp->setValue("Maximum", lineEditMax->text().toDouble());
      tmp->setValue("log", checkBoxLog->isChecked());

    std::cout << "sTSI: B" << std::endl;
      return true;
  */}

void CScanWidgetRandom::changeType()
{
  /*  C_INT32 type = comboBoxType->currentItem();
    C_FLOAT64 value = 0.0;

    if (mpObject != NULL)
      value = *(C_FLOAT64*)mpObject->getValuePointer();

    if (type == 0) //uniform
      {
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(true);

        labelMin->setText("min");
        labelMax->setText("max");

        if (mpObject != NULL)
          {
            lineEditMin->setText(QString::number(value*0.5));
            lineEditMax->setText(QString::number(value*2));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }
      }

    if (type == 1) //normal
      {
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(true);

        labelMin->setText("mean");
        labelMax->setText("standard deviation");

        if (mpObject != NULL)
          {
            lineEditMin->setText(QString::number(value));
            lineEditMax->setText(QString::number(value*0.1));
          }
        else
          {
            lineEditMin->setText("");
            lineEditMax->setText("");
          }
      }

    if (type == 2) //poisson
      {
        lineEditMin->setEnabled(true);
        lineEditMax->setEnabled(false);

        labelMin->setText("mean");
        labelMax->setText("");

        if (mpObject != NULL)
          lineEditMin->setText(QString::number(value));
        else
          lineEditMin->setText("");

        lineEditMax->setText("");
      }

    //TODO: handle log: rename standard deviation -> sd factor,
    //                  disable poisson?
  */}

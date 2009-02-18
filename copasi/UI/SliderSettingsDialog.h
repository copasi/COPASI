// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderSettingsDialog.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:49:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef SLIDERSETTINGSDIALOG_H
#define SLIDERSETTINGSDIALOG_H

#include <qvariant.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <Q3Frame>
#include <QLabel>
#include <Q3VBoxLayout>

class CModel;
class CSlider;

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
#include <vector>

class Ui_SliderSettingsDialog
  {
  public:
    Q3VBoxLayout *vboxLayout;
    Q3HBoxLayout *hboxLayout;
    QLabel *mpObjectLabel;
    QLineEdit *mpObjectNameLineEdit;
    QPushButton *mpObjectBrowseButton;
    Q3HBoxLayout *hboxLayout1;
    QLabel *mpMinValueLabel;
    QLineEdit *mpMinValueEdit;
    QSpacerItem *mpSpacer1;
    QLabel *mpMaxValueLabel;
    QLineEdit *mpMaxValueEdit;
    Q3HBoxLayout *hboxLayout2;
    QCheckBox *mpLogCheckBox;
    QSpacerItem *mpSpacer1_2_2;
    Q3HBoxLayout *hboxLayout3;
    QPushButton *mpExtendedOptionsButton;
    QSpacerItem *spacer6;
    Q3Frame *mpExtendedOptionsFrame;
    Q3GridLayout *gridLayout;
    QLabel *mpNumMinorTicksLabel;
    QLabel *mpMinorMajorFactorLabel;
    QLabel *mpObjectValueLabel;
    QLineEdit *mpNumMinorTicksEdit;
    QLineEdit *mpObjectValueEdit;
    QSpacerItem *mpSpacer1_3;
    QSpacerItem *mpSpacer1_2;
    QSpacerItem *mpSpacer1_3_2;
    QLineEdit *mpMinorMajorFactorEdit;
    QLabel *mpMinorTickSizeLabel;
    QLineEdit *mpOriginalValueEdit;
    QLineEdit *mpMinorTickSizeEdit;
    QLabel *mpOriginalValueLabel;
    Q3HBoxLayout *hboxLayout4;
    QPushButton *mpOkButton;
    QPushButton *mpCancelButton;

    void setupUi(QDialog *SliderSettingsDialog)
    {
      if (SliderSettingsDialog->objectName().isEmpty())
        SliderSettingsDialog->setObjectName(QString::fromUtf8("SliderSettingsDialog"));
      SliderSettingsDialog->resize(728, 387);
      vboxLayout = new Q3VBoxLayout(SliderSettingsDialog);
      vboxLayout->setSpacing(6);
      vboxLayout->setMargin(11);
      vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
      vboxLayout->setResizeMode(Q3VBoxLayout::Fixed);
      hboxLayout = new Q3HBoxLayout();
      hboxLayout->setSpacing(6);
      hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
      mpObjectLabel = new QLabel(SliderSettingsDialog);
      mpObjectLabel->setObjectName(QString::fromUtf8("mpObjectLabel"));
      QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(5));
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(mpObjectLabel->sizePolicy().hasHeightForWidth());
      mpObjectLabel->setSizePolicy(sizePolicy);
      mpObjectLabel->setWordWrap(false);

      hboxLayout->addWidget(mpObjectLabel);

      mpObjectNameLineEdit = new QLineEdit(SliderSettingsDialog);
      mpObjectNameLineEdit->setObjectName(QString::fromUtf8("mpObjectNameLineEdit"));
      mpObjectNameLineEdit->setEnabled(false);
      mpObjectNameLineEdit->setReadOnly(true);

      hboxLayout->addWidget(mpObjectNameLineEdit);

      mpObjectBrowseButton = new QPushButton(SliderSettingsDialog);
      mpObjectBrowseButton->setObjectName(QString::fromUtf8("mpObjectBrowseButton"));
      QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(mpObjectBrowseButton->sizePolicy().hasHeightForWidth());
      mpObjectBrowseButton->setSizePolicy(sizePolicy1);
      mpObjectBrowseButton->setMinimumSize(QSize(40, 0));

      hboxLayout->addWidget(mpObjectBrowseButton);

      vboxLayout->addLayout(hboxLayout);

      hboxLayout1 = new Q3HBoxLayout();
      hboxLayout1->setSpacing(6);
      hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
      mpMinValueLabel = new QLabel(SliderSettingsDialog);
      mpMinValueLabel->setObjectName(QString::fromUtf8("mpMinValueLabel"));
      mpMinValueLabel->setWordWrap(false);

      hboxLayout1->addWidget(mpMinValueLabel);

      mpMinValueEdit = new QLineEdit(SliderSettingsDialog);
      mpMinValueEdit->setObjectName(QString::fromUtf8("mpMinValueEdit"));
      mpMinValueEdit->setAlignment(Qt::AlignRight);

      hboxLayout1->addWidget(mpMinValueEdit);

      mpSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      hboxLayout1->addItem(mpSpacer1);

      mpMaxValueLabel = new QLabel(SliderSettingsDialog);
      mpMaxValueLabel->setObjectName(QString::fromUtf8("mpMaxValueLabel"));
      mpMaxValueLabel->setWordWrap(false);

      hboxLayout1->addWidget(mpMaxValueLabel);

      mpMaxValueEdit = new QLineEdit(SliderSettingsDialog);
      mpMaxValueEdit->setObjectName(QString::fromUtf8("mpMaxValueEdit"));
      mpMaxValueEdit->setAlignment(Qt::AlignRight);

      hboxLayout1->addWidget(mpMaxValueEdit);

      vboxLayout->addLayout(hboxLayout1);

      hboxLayout2 = new Q3HBoxLayout();
      hboxLayout2->setSpacing(6);
      hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
      mpLogCheckBox = new QCheckBox(SliderSettingsDialog);
      mpLogCheckBox->setObjectName(QString::fromUtf8("mpLogCheckBox"));

      hboxLayout2->addWidget(mpLogCheckBox);

      mpSpacer1_2_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      hboxLayout2->addItem(mpSpacer1_2_2);

      vboxLayout->addLayout(hboxLayout2);

      hboxLayout3 = new Q3HBoxLayout();
      hboxLayout3->setSpacing(6);
      hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
      mpExtendedOptionsButton = new QPushButton(SliderSettingsDialog);
      mpExtendedOptionsButton->setObjectName(QString::fromUtf8("mpExtendedOptionsButton"));

      hboxLayout3->addWidget(mpExtendedOptionsButton);

      spacer6 = new QSpacerItem(300, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      hboxLayout3->addItem(spacer6);

      vboxLayout->addLayout(hboxLayout3);

      mpExtendedOptionsFrame = new Q3Frame(SliderSettingsDialog);
      mpExtendedOptionsFrame->setObjectName(QString::fromUtf8("mpExtendedOptionsFrame"));
      mpExtendedOptionsFrame->setFrameShape(Q3Frame::NoFrame);
      mpExtendedOptionsFrame->setFrameShadow(Q3Frame::Raised);
      gridLayout = new Q3GridLayout(mpExtendedOptionsFrame);
      gridLayout->setSpacing(6);
      gridLayout->setMargin(11);
      gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
      mpNumMinorTicksLabel = new QLabel(mpExtendedOptionsFrame);
      mpNumMinorTicksLabel->setObjectName(QString::fromUtf8("mpNumMinorTicksLabel"));
      mpNumMinorTicksLabel->setWordWrap(false);

      gridLayout->addWidget(mpNumMinorTicksLabel, 0, 0, 1, 1);

      mpMinorMajorFactorLabel = new QLabel(mpExtendedOptionsFrame);
      mpMinorMajorFactorLabel->setObjectName(QString::fromUtf8("mpMinorMajorFactorLabel"));
      mpMinorMajorFactorLabel->setWordWrap(false);

      gridLayout->addWidget(mpMinorMajorFactorLabel, 1, 0, 1, 1);

      mpObjectValueLabel = new QLabel(mpExtendedOptionsFrame);
      mpObjectValueLabel->setObjectName(QString::fromUtf8("mpObjectValueLabel"));
      mpObjectValueLabel->setMargin(0);
      mpObjectValueLabel->setWordWrap(false);

      gridLayout->addWidget(mpObjectValueLabel, 2, 0, 1, 1);

      mpNumMinorTicksEdit = new QLineEdit(mpExtendedOptionsFrame);
      mpNumMinorTicksEdit->setObjectName(QString::fromUtf8("mpNumMinorTicksEdit"));
      mpNumMinorTicksEdit->setAlignment(Qt::AlignRight);

      gridLayout->addWidget(mpNumMinorTicksEdit, 0, 1, 1, 1);

      mpObjectValueEdit = new QLineEdit(mpExtendedOptionsFrame);
      mpObjectValueEdit->setObjectName(QString::fromUtf8("mpObjectValueEdit"));
      mpObjectValueEdit->setAlignment(Qt::AlignRight);

      gridLayout->addWidget(mpObjectValueEdit, 2, 1, 1, 1);

      mpSpacer1_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      gridLayout->addItem(mpSpacer1_3, 1, 2, 1, 1);

      mpSpacer1_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      gridLayout->addItem(mpSpacer1_2, 0, 2, 1, 1);

      mpSpacer1_3_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      gridLayout->addItem(mpSpacer1_3_2, 2, 3, 1, 1);

      mpMinorMajorFactorEdit = new QLineEdit(mpExtendedOptionsFrame);
      mpMinorMajorFactorEdit->setObjectName(QString::fromUtf8("mpMinorMajorFactorEdit"));
      mpMinorMajorFactorEdit->setAlignment(Qt::AlignRight);

      gridLayout->addWidget(mpMinorMajorFactorEdit, 1, 1, 1, 1);

      mpMinorTickSizeLabel = new QLabel(mpExtendedOptionsFrame);
      mpMinorTickSizeLabel->setObjectName(QString::fromUtf8("mpMinorTickSizeLabel"));
      mpMinorTickSizeLabel->setWordWrap(false);

      gridLayout->addWidget(mpMinorTickSizeLabel, 0, 3, 1, 1);

      mpOriginalValueEdit = new QLineEdit(mpExtendedOptionsFrame);
      mpOriginalValueEdit->setObjectName(QString::fromUtf8("mpOriginalValueEdit"));
      mpOriginalValueEdit->setAlignment(Qt::AlignRight);

      gridLayout->addWidget(mpOriginalValueEdit, 1, 4, 1, 1);

      mpMinorTickSizeEdit = new QLineEdit(mpExtendedOptionsFrame);
      mpMinorTickSizeEdit->setObjectName(QString::fromUtf8("mpMinorTickSizeEdit"));
      mpMinorTickSizeEdit->setAlignment(Qt::AlignRight);

      gridLayout->addWidget(mpMinorTickSizeEdit, 0, 4, 1, 1);

      mpOriginalValueLabel = new QLabel(mpExtendedOptionsFrame);
      mpOriginalValueLabel->setObjectName(QString::fromUtf8("mpOriginalValueLabel"));
      mpOriginalValueLabel->setWordWrap(false);

      gridLayout->addWidget(mpOriginalValueLabel, 1, 3, 1, 1);

      vboxLayout->addWidget(mpExtendedOptionsFrame);

      hboxLayout4 = new Q3HBoxLayout();
      hboxLayout4->setSpacing(6);
      hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
      mpOkButton = new QPushButton(SliderSettingsDialog);
      mpOkButton->setObjectName(QString::fromUtf8("mpOkButton"));
      mpOkButton->setDefault(true);

      hboxLayout4->addWidget(mpOkButton);

      mpCancelButton = new QPushButton(SliderSettingsDialog);
      mpCancelButton->setObjectName(QString::fromUtf8("mpCancelButton"));

      hboxLayout4->addWidget(mpCancelButton);

      vboxLayout->addLayout(hboxLayout4);

      QWidget::setTabOrder(mpObjectNameLineEdit, mpObjectBrowseButton);
      QWidget::setTabOrder(mpObjectBrowseButton, mpMinValueEdit);
      QWidget::setTabOrder(mpMinValueEdit, mpMaxValueEdit);
      QWidget::setTabOrder(mpMaxValueEdit, mpLogCheckBox);
      QWidget::setTabOrder(mpLogCheckBox, mpExtendedOptionsButton);
      QWidget::setTabOrder(mpExtendedOptionsButton, mpNumMinorTicksEdit);
      QWidget::setTabOrder(mpNumMinorTicksEdit, mpMinorTickSizeEdit);
      QWidget::setTabOrder(mpMinorTickSizeEdit, mpMinorMajorFactorEdit);
      QWidget::setTabOrder(mpMinorMajorFactorEdit, mpObjectValueEdit);
      QWidget::setTabOrder(mpObjectValueEdit, mpOkButton);
      QWidget::setTabOrder(mpOkButton, mpCancelButton);

      retranslateUi(SliderSettingsDialog);
      QObject::connect(mpCancelButton, SIGNAL(clicked()), SliderSettingsDialog, SLOT(cancelButtonPressed()));
      QObject::connect(mpOkButton, SIGNAL(clicked()), SliderSettingsDialog, SLOT(okButtonPressed()));
      QObject::connect(mpObjectValueEdit, SIGNAL(returnPressed()), SliderSettingsDialog, SLOT(objectValueChanged()));
      QObject::connect(mpObjectValueEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(objectValueChanged()));
      QObject::connect(mpObjectValueEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(valueTextChanged()));
      QObject::connect(mpMinorTickSizeEdit, SIGNAL(returnPressed()), SliderSettingsDialog, SLOT(minorTickSizeChanged()));
      QObject::connect(mpMinorTickSizeEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(minorTickSizeChanged()));
      QObject::connect(mpMinorTickSizeEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(tickSizeTextChanged()));
      QObject::connect(mpMinorMajorFactorEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(tickFactorTextChanged()));
      QObject::connect(mpNumMinorTicksEdit, SIGNAL(returnPressed()), SliderSettingsDialog, SLOT(numMinorTicksChanged()));
      QObject::connect(mpNumMinorTicksEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(numMinorTicksChanged()));
      QObject::connect(mpNumMinorTicksEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(numTicksTextChanged()));
      QObject::connect(mpMinValueEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(minValueChanged()));
      QObject::connect(mpMinValueEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(minValueTextChanged()));
      QObject::connect(mpMaxValueEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(maxValueChanged()));
      QObject::connect(mpMaxValueEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(maxValueTextChanged()));
      QObject::connect(mpObjectBrowseButton, SIGNAL(clicked()), SliderSettingsDialog, SLOT(browseButtonPressed()));
      QObject::connect(mpExtendedOptionsButton, SIGNAL(clicked()), SliderSettingsDialog, SLOT(extendedOptionsClicked()));
      QObject::connect(mpLogCheckBox, SIGNAL(toggled(bool)), SliderSettingsDialog, SLOT(logCheckBoxToggled(bool)));
      QObject::connect(mpOriginalValueEdit, SIGNAL(textChanged(QString)), SliderSettingsDialog, SLOT(origValueTextChanged()));
      QObject::connect(mpOriginalValueEdit, SIGNAL(lostFocus()), SliderSettingsDialog, SLOT(originalValueChanged()));
      QObject::connect(mpMinValueEdit, SIGNAL(returnPressed()), SliderSettingsDialog, SLOT(minValueChanged()));

      QMetaObject::connectSlotsByName(SliderSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SliderSettingsDialog)
    {
      SliderSettingsDialog->setWindowTitle(QApplication::translate("SliderSettingsDialog", "Slider Settings", 0, QApplication::UnicodeUTF8));
      mpObjectLabel->setText(QApplication::translate("SliderSettingsDialog", "Object:", 0, QApplication::UnicodeUTF8));
      mpObjectBrowseButton->setText(QApplication::translate("SliderSettingsDialog", "choose object", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpObjectBrowseButton->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Select an object for the slider", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpObjectBrowseButton->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "Clicking this button opens a dialog that\n"
                                        "lets the user choose the object that the \n"
                                        "slider will manipulate. The object has to \n"
                                        "represent either an integer value or a float\n"
                                        "value.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpMinValueLabel->setText(QApplication::translate("SliderSettingsDialog", "Minimum Value:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpMinValueLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Lowest value the slider can have", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpMinValueLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "Here the user can enter the lowest value the slider will take.\n"
                                   "For logarithmic sliders this has to be a positive value greater\n"
                                   "than 0.0.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpMinValueEdit->setText(QApplication::translate("SliderSettingsDialog", "0.0", 0, QApplication::UnicodeUTF8));
      mpMaxValueLabel->setText(QApplication::translate("SliderSettingsDialog", "Maximum Value:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpMaxValueLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Maximum value the slider will take.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpMaxValueLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "Here the user can enter the maximal value that\n"
                                   "the slider will take.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpMaxValueEdit->setText(QApplication::translate("SliderSettingsDialog", "100.0", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_WHATSTHIS
      mpMaxValueEdit->setProperty("whatsThis", QVariant(QString()));
#endif // QT_NO_WHATSTHIS

      mpLogCheckBox->setText(QApplication::translate("SliderSettingsDialog", "logarithmic", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpLogCheckBox->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Wether slider has logarithmic scale.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpLogCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "If checked, the slider will have a \n"
                                 "logarithmic scale. Minimum\n"
                                 "and maximum value must be \n"
                                 "greater than 0.0.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpExtendedOptionsButton->setText(QApplication::translate("SliderSettingsDialog", "more options", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpExtendedOptionsButton->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Displays or hides an extended set of options.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpExtendedOptionsButton->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "Clicking this button either displays or hides\n"
                                           "some more less often needed options.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpNumMinorTicksLabel->setText(QApplication::translate("SliderSettingsDialog", "Number of Minor Ticks:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpNumMinorTicksLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Number of steps for the slider.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpNumMinorTicksLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "This value determines how many steps\n"
                                        "the slider makes from minimum to \n"
                                        "maximum value.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpMinorMajorFactorLabel->setText(QApplication::translate("SliderSettingsDialog", "Ticksize factor:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpMinorMajorFactorLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "how many minor ticks make a major tick", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpMinorMajorFactorLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "This value determines how many minor \n"
                                           "ticks make up a major tick. Minor ticks\n"
                                           "are small steps on the slider whereas major\n"
                                           "ticks are larger steps.\n"
                                           "The user can make a minor step via the cursor\n"
                                           "keys and a major step via the page up/down keys.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpObjectValueLabel->setText(QApplication::translate("SliderSettingsDialog", "Object Value:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpObjectValueLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "The value of the underlying object.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpObjectValueLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "Here the user can change the actual value of the object\n"
                                      "when editing or creating a slider.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpNumMinorTicksEdit->setText(QApplication::translate("SliderSettingsDialog", "10.0", 0, QApplication::UnicodeUTF8));
      mpObjectValueEdit->setText(QApplication::translate("SliderSettingsDialog", "50.0", 0, QApplication::UnicodeUTF8));
      mpMinorMajorFactorEdit->setText(QApplication::translate("SliderSettingsDialog", "10.0", 0, QApplication::UnicodeUTF8));
      mpMinorTickSizeLabel->setText(QApplication::translate("SliderSettingsDialog", "Minor Ticksize:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpMinorTickSizeLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Value change corresponding to a minor step", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpMinorTickSizeLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "This value signifies the value change that\n"
                                        "corresponds to one minor step on the slider.\n"
                                        "The user can either set this directly or indirectly\n"
                                        "when setting the \"Number of Minor Ticks\".", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpOriginalValueEdit->setText(QApplication::translate("SliderSettingsDialog", "1.0", 0, QApplication::UnicodeUTF8));
      mpMinorTickSizeEdit->setText(QApplication::translate("SliderSettingsDialog", "1.0", 0, QApplication::UnicodeUTF8));
      mpOriginalValueLabel->setText(QApplication::translate("SliderSettingsDialog", "Original Value", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
      mpOriginalValueLabel->setProperty("toolTip", QVariant(QApplication::translate("SliderSettingsDialog", "Value change corresponding to a minor step", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP

#ifndef QT_NO_WHATSTHIS
      mpOriginalValueLabel->setProperty("whatsThis", QVariant(QApplication::translate("SliderSettingsDialog", "This value signifies the value change that\n"
                                        "corresponds to one minor step on the slider.\n"
                                        "The user can either set this directly or indirectly\n"
                                        "when setting the \"Number of Minor Ticks\".", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS

      mpOkButton->setText(QApplication::translate("SliderSettingsDialog", "OK", 0, QApplication::UnicodeUTF8));
      mpCancelButton->setText(QApplication::translate("SliderSettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
      Q_UNUSED(SliderSettingsDialog);
    } // retranslateUi
  };

namespace Ui
  {
  class SliderSettingsDialog: public Ui_SliderSettingsDialog {};
} // namespace Ui

class SliderSettingsDialog : public QDialog, public Ui::SliderSettingsDialog
  {
    Q_OBJECT

  public:
    SliderSettingsDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~SliderSettingsDialog();

    virtual CSlider * getSlider();
    virtual void setSlider(CSlider * slider);
    virtual void setDefinedSliders(std::vector<CSlider *> sliderVect);
    virtual void setModel(CModel * model);
    virtual void disableObjectChoosing(bool disableChoosing);
    virtual void updateSlider();

  signals:
    void sliderChanged(CSlider* slider);

  protected:
    enum CHANGETYPE {NONE, OBJECT, MIN, MAX, NUMTICKS, TICKSIZE, TICKFACTOR, ORIGVAL, VALUE, LOGARITHMIC};
    CHANGETYPE mChanged;
    double mMinorTickSize;
    double mMaxValue;
    double mMinValue;
    double mValue;
    double mOriginalValue;
    unsigned int mMinorMajorFactor;
    unsigned int mNumMinorTicks;
    std::vector< CSlider* > mDefinedSliders;
    CSlider* mpSlider;
    int mCurrentTaskId;
    CModel* mpModel;
    int mScaling;

    virtual void updateInputFieldsValues();
    virtual void updateInputFields();
    virtual void init();
    virtual void updateInternalValues();

  protected slots:
    virtual void languageChange();

    virtual void okButtonPressed();
    virtual void cancelButtonPressed();
    virtual void minorTickSizeChanged();
    virtual void numMinorTicksChanged();
    virtual void maxValueChanged();
    virtual void objectValueChanged();
    virtual void minorMajorFactorChanged();
    virtual void browseButtonPressed();
    virtual void extendedOptionsClicked();
    virtual void logCheckBoxToggled(bool on);
    virtual void globalCheckBoxToggled();
    virtual void originalValueChanged();
    virtual void minValueChanged();
    virtual void minValueTextChanged();
    virtual void maxValueTextChanged();
    virtual void numTicksTextChanged();
    virtual void tickSizeTextChanged();
    virtual void tickFactorTextChanged();
    virtual void origValueTextChanged();
    virtual void valueTextChanged();
  };

#endif // SLIDERSETTINGSDIALOG_H

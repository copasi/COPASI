// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.cpp,v $
//   $Revision: 1.231 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/09/17 17:23:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qapplication.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qtimer.h>
#include <qlabel.h>
#include <qhbox.h>
#include <qscrollview.h>
#include <qaction.h>
#include <qtextedit.h>
#include <qcombobox.h>

#include <vector>
#include <sstream>

extern const char * CopasiLicense;

#include "AboutDialog.h"
#include "CopasiFileDialog.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "ObjectBrowserDialog.h"
#include "qtUtilities.h"
#include "SliderDialog.h"
#include "CQMessageBox.h"
#include "CQPreferenceDialog.h"
#include "CQSBMLFileDialog.h"
#include "SteadyStateWidget.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"
#include "utilities/CCopasiException.h"
#include "utilities/CDirEntry.h"
#include "model/CModel.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "commandline/CConfigurationFile.h"
#include "wizard/wizard.h"
#include "report/CKeyFactory.h"
#include "sbml/SBMLIncompatibility.h"
#include "MIRIAM/CConstants.h"

#include "./icons/filenew.xpm"
#include "./icons/fileopen.xpm"
#include "./icons/filesave.xpm"
//#include "./icons/fileprint.xpm"
#include "./icons/showSliders.xpm"
#include "./icons/Copasi16-Alpha.xpm"
#include "./icons/checkModel.xpm"
#include "./icons/MIRIAM.xpm"
#include "./icons/istos.xpm"
#include "./icons/stois.xpm"
#include "./icons/photo.xpm"

#define AutoSaveInterval 10*60*1000

static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x03,
    0x1f, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x85, 0x93, 0x6b, 0x48, 0x54,
    0x09, 0x14, 0xc7, 0xcf, 0x75, 0xee, 0xf8, 0x68, 0xd0, 0x4c, 0xad, 0x29,
    0xb7, 0xed, 0x49, 0x46, 0x59, 0xd9, 0x46, 0x4a, 0xa5, 0x6d, 0x0f, 0x74,
    0xb7, 0x28, 0xa4, 0xa0, 0x2c, 0xc4, 0xad, 0xa8, 0x88, 0xa2, 0x68, 0x09,
    0xb4, 0x97, 0x59, 0xba, 0x6d, 0x0a, 0x91, 0x21, 0xd1, 0x16, 0x54, 0x8a,
    0x14, 0x11, 0x3d, 0xc6, 0x8c, 0x61, 0x62, 0x26, 0xc7, 0x9a, 0xa8, 0xac,
    0xed, 0x85, 0x65, 0x39, 0x3d, 0x74, 0x1c, 0xf3, 0x35, 0x77, 0x1e, 0xa2,
    0x73, 0xbd, 0xf7, 0xce, 0x78, 0xe7, 0xce, 0xbf, 0x2f, 0x23, 0xbb, 0xb8,
    0xdb, 0xee, 0x81, 0xf3, 0xed, 0xfc, 0x7e, 0xe7, 0xc3, 0x39, 0x7f, 0x06,
    0x00, 0xfd, 0x4f, 0x8d, 0x1a, 0x1c, 0x54, 0x96, 0x70, 0x9c, 0xf4, 0x73,
    0x67, 0x87, 0x38, 0x33, 0x66, 0x24, 0xdb, 0x3d, 0x69, 0x52, 0xc4, 0x3e,
    0x8d, 0x46, 0xe3, 0x20, 0x22, 0x62, 0xff, 0x03, 0x4c, 0xe8, 0xe9, 0x11,
    0x0a, 0xf5, 0xb5, 0x5d, 0x5b, 0xea, 0xeb, 0x1c, 0x23, 0x9b, 0xdf, 0xf5,
    0x33, 0x00, 0x43, 0x3f, 0x2e, 0x8d, 0x0f, 0x56, 0xfc, 0x91, 0x76, 0x83,
    0x88, 0x6e, 0x13, 0x11, 0x11, 0x80, 0x7f, 0xb4, 0x2c, 0xcb, 0xcb, 0xee,
    0xdc, 0xb6, 0xb7, 0xa5, 0xa6, 0xe8, 0xb1, 0x3c, 0xa3, 0x2e, 0x78, 0xfd,
    0x9a, 0xad, 0x9b, 0x73, 0x08, 0x17, 0x44, 0x51, 0x3e, 0x10, 0x08, 0x04,
    0xb2, 0x01, 0xa8, 0x87, 0x66, 0x87, 0xc3, 0x2a, 0x8f, 0x47, 0x2a, 0xfa,
    0xed, 0x68, 0xa3, 0x6f, 0xc2, 0x98, 0x5a, 0x54, 0x94, 0x37, 0xf3, 0x3c,
    0xef, 0x2f, 0x04, 0x10, 0xf3, 0x6f, 0x8b, 0x86, 0x0b, 0xa2, 0x5b, 0x5b,
    0xfb, 0xaf, 0xae, 0xcb, 0x7e, 0xa8, 0x4c, 0x9b, 0xa0, 0x87, 0xe9, 0x6e,
    0xe7, 0x27, 0x00, 0xf3, 0xbf, 0x05, 0x0e, 0x17, 0x44, 0xbe, 0x6f, 0x72,
    0x18, 0x52, 0xe7, 0xde, 0xc4, 0xaa, 0x2c, 0x4b, 0xf0, 0x5d, 0x53, 0xaf,
    0x11, 0xc0, 0xd8, 0x6f, 0x40, 0x4c, 0xa8, 0xff, 0x12, 0x78, 0x3c, 0x42,
    0xc9, 0xd2, 0x45, 0xb7, 0x82, 0xbf, 0xe4, 0xde, 0x54, 0x7a, 0x7b, 0xa5,
    0x52, 0x00, 0xe1, 0x7f, 0x03, 0xd4, 0xb2, 0x24, 0x2d, 0x97, 0x07, 0xdc,
    0x65, 0xbe, 0xf6, 0xd7, 0x06, 0xe9, 0x83, 0xfe, 0xad, 0xef, 0xb3, 0xe1,
    0xb5, 0x32, 0xc0, 0x15, 0x00, 0x50, 0x11, 0x80, 0x94, 0xb2, 0x13, 0xf5,
    0x42, 0xea, 0xdc, 0xeb, 0xe8, 0xea, 0x18, 0xa8, 0x04, 0x10, 0x16, 0x02,
    0xc3, 0x02, 0x7e, 0x71, 0xbd, 0xf7, 0x95, 0xb9, 0xd1, 0x56, 0x9c, 0xa7,
    0x3c, 0x5f, 0x35, 0x16, 0x57, 0xe6, 0xa8, 0x51, 0x32, 0x43, 0x8d, 0x43,
    0x33, 0xc2, 0xd1, 0x70, 0x64, 0x85, 0xa2, 0x78, 0x9d, 0x07, 0xc9, 0x6e,
    0xf7, 0x5c, 0x9c, 0x98, 0x58, 0x04, 0xe3, 0xdd, 0x96, 0xcf, 0x00, 0x62,
    0x43, 0x70, 0x9c, 0xcc, 0x59, 0x75, 0x5d, 0x27, 0x73, 0x14, 0xd3, 0x6c,
    0x35, 0x8e, 0xcf, 0x9c, 0x86, 0xd2, 0x5d, 0xc5, 0x81, 0xfa, 0x5a, 0xa3,
    0xbd, 0xb5, 0xb9, 0xd9, 0xf4, 0x51, 0x5f, 0xd9, 0x7f, 0x62, 0x41, 0x3c,
    0x3a, 0x1e, 0x54, 0x3b, 0x49, 0x77, 0xcd, 0xdc, 0x96, 0xbb, 0xb6, 0x2c,
    0xe8, 0xf7, 0x07, 0x36, 0x84, 0xe0, 0x28, 0xbe, 0xed, 0xc5, 0x43, 0xfb,
    0xbe, 0x29, 0x38, 0x9f, 0x9c, 0x88, 0xca, 0x92, 0x0a, 0x7f, 0x77, 0xa7,
    0xfb, 0x32, 0x80, 0xf4, 0xd0, 0xf9, 0x98, 0x01, 0xaf, 0x50, 0x55, 0x94,
    0x35, 0x1b, 0x86, 0xea, 0x2a, 0x89, 0x15, 0x79, 0x3e, 0x21, 0x69, 0x72,
    0x64, 0x90, 0x48, 0x69, 0x22, 0x52, 0x51, 0x50, 0x16, 0x37, 0x79, 0x75,
    0xf9, 0x8b, 0x6b, 0x2c, 0x51, 0x34, 0x7e, 0x7f, 0xb5, 0x7b, 0x6d, 0xee,
    0xc2, 0x1c, 0x96, 0x65, 0x2d, 0x44, 0x04, 0x22, 0x62, 0x04, 0xaf, 0xb4,
    0xf7, 0x54, 0xe1, 0xe9, 0xbc, 0x07, 0x7f, 0xb6, 0xd3, 0x9a, 0x63, 0xb3,
    0x1a, 0xe8, 0x9e, 0xa9, 0xf1, 0x69, 0x66, 0xc6, 0x41, 0xf8, 0x7c, 0x83,
    0x3b, 0x01, 0xd0, 0x20, 0xf7, 0xe6, 0x6a, 0xd3, 0x6e, 0x0d, 0x36, 0x67,
    0x5f, 0x82, 0x20, 0xf8, 0x8f, 0xb9, 0x5c, 0xae, 0x68, 0xde, 0xc1, 0x8f,
    0x11, 0x45, 0x31, 0xdd, 0xf9, 0xa5, 0xa5, 0xe6, 0xcc, 0x9e, 0xad, 0x81,
    0x85, 0x51, 0xd1, 0x38, 0x57, 0x7c, 0x5c, 0x94, 0x65, 0x39, 0x83, 0x5d,
    0x94, 0x9e, 0xa4, 0xf3, 0x89, 0xc2, 0x02, 0x93, 0xf1, 0xd3, 0xe1, 0xcc,
    0xac, 0xa4, 0x97, 0xaa, 0x88, 0xf8, 0xfe, 0x98, 0xb8, 0x28, 0x62, 0xee,
    0x9f, 0xa6, 0x56, 0xa3, 0x54, 0xf8, 0xfd, 0xb8, 0x88, 0x7c, 0x6f, 0x5f,
    0x1f, 0x5b, 0xf7, 0xd8, 0x16, 0xde, 0x50, 0xa3, 0x0b, 0xf3, 0x70, 0x7e,
    0x5a, 0xb9, 0xad, 0x40, 0xde, 0x5c, 0x90, 0xff, 0x2b, 0xcb, 0xb2, 0x8f,
    0x09, 0x40, 0xac, 0xc1, 0xf0, 0xd6, 0x3a, 0xf5, 0xbb, 0x1d, 0xf8, 0xbd,
    0xe4, 0x89, 0xcf, 0x6a, 0xf5, 0xb8, 0xfa, 0xac, 0x66, 0xbc, 0x39, 0xb2,
    0x04, 0x67, 0x17, 0x8f, 0xc6, 0xc9, 0x94, 0x58, 0x14, 0x25, 0x6b, 0xb1,
    0x3d, 0x3e, 0x01, 0x5b, 0x7f, 0x58, 0x89, 0x1b, 0x97, 0x2d, 0x3d, 0x92,
    0xe4, 0xcf, 0x1b, 0xfa, 0x05, 0x26, 0x94, 0xc6, 0xe9, 0x4f, 0x1e, 0xd9,
    0xae, 0x94, 0x97, 0x9b, 0xe7, 0x3f, 0x6b, 0xe8, 0x60, 0xd4, 0xe4, 0x26,
    0xa8, 0xe2, 0x48, 0x12, 0x88, 0x22, 0x23, 0x18, 0x9a, 0x97, 0x36, 0x1a,
    0x99, 0x3f, 0x25, 0xf3, 0x39, 0x1b, 0xd3, 0xaa, 0xb4, 0xda, 0x98, 0x52,
    0x22, 0x72, 0x0d, 0x25, 0x6e, 0x48, 0x40, 0x44, 0x14, 0xae, 0x28, 0xca,
    0x6a, 0x8e, 0xf3, 0xae, 0xb0, 0xb5, 0x38, 0x53, 0x82, 0x20, 0x76, 0x84,
    0x26, 0xd2, 0xa9, 0xd5, 0xc6, 0xb5, 0x27, 0x26, 0x8e, 0x30, 0xab, 0x54,
    0x2a, 0x0b, 0x11, 0xb9, 0x87, 0x47, 0xf6, 0x2b, 0x7b, 0xdd, 0x48, 0xf1,
    0x37, 0x6e, 0xda, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
    0xae, 0x42, 0x60, 0x82
  };

// This is a hack to enable the menus under Darwin on PowerPC (Bug 841)
#ifdef Darwin
# define resetMenus \
{\
 QMessageBox * pMessage = new QMessageBox(this); \
 pMessage->show(); \
 delete pMessage; \
}
#else
# define resetMenus
#endif // DARWIN

CopasiUI3Window * CopasiUI3Window::create()
{
  CopasiUI3Window * pWindow = new CopasiUI3Window;

#ifdef COPASI_LICENSE_COM
  if (!pWindow->checkRegistration())
    pdelete(pWindow);
#endif // COPASI_LICENSE_COM

  return pWindow;
}

/**
 *  Constructs a CopasiUI window which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *  @param parent The widget which this window is a child of.
 *  @param name The object name is a text that can be used to identify
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one
 *  using queryList().
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation
 *  for more information about these flags.
 */
CopasiUI3Window::CopasiUI3Window():
    QMainWindow(),
    dataModel(NULL),
    listViews(NULL),
    mpSliders(NULL),
    mpObjectBrowser(NULL),
    mSaveAsRequired(true),
    mpAutoSaveTimer(NULL),
    mSuspendAutoSave(false),
    mpMenuRecentFiles(NULL),
    mpMenuRecentSBMLFiles(NULL),
    mpMIRIAMResources(NULL)
{
  // set destructive close
  WFlags f = this->getWFlags();
  f |= Qt::WDestructiveClose;
  this->setWFlags(f);
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  QPixmap image0 = img;
  setIcon(image0);

  // Set the window caption/title
  newFlag = 0;
  FixedTitle = "COPASI ";
#ifdef COPASI_LICENSE_COM
  FixedTitle += "(commercial) ";
#endif // COPASI_LICENSE_COM
  FixedTitle += FROM_UTF8(CCopasiDataModel::Global->getVersion()->getVersion());
  updateTitle();

  createActions();
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  //mbObject_browser_open = false;

  mpaSave->setEnabled(false);
  mpaSaveAs->setEnabled(false);
  mpaExportSBML->setEnabled(false);
  mpaExportODE->setEnabled(false);

  if (!dataModel)
    {
      // create the data model
      dataModel = new DataModelGUI();
    }

  listViews = new ListViews(this);

  connect(listViews->folders, SIGNAL(currentChanged(QListViewItem*)), this, SLOT(listViewsFolderChanged(QListViewItem*)));

  ListViews::setDataModel(dataModel);
  listViews->show();
  this->setCentralWidget(listViews);

  this->mpSliders = new SliderDialog(NULL);
  this->mpSliders->setParentWindow(this);
  C_INT32 id = ((FolderListItem*)listViews->folders->currentItem())->getFolder()->getId();
  this->mpSliders->setCurrentFolderId(id);
  this->mpSliders->resize(350, 250);

  if (!COptions::compareValue("ImportSBML", std::string("")))
    {
      // Import the SBML File
      std::string ImportSBML;
      COptions::getValue("ImportSBML", ImportSBML);
      slotImportSBML(FROM_UTF8(ImportSBML));
    }
  else if (COptions::getNonOptions().size())
    {
      slotFileOpen(FROM_UTF8(COptions::getNonOptions()[0]));
    }
  else
    {
      newDoc();
    }

  listViews->switchToOtherWidget(0, "");

  resize(800, 600);
  show();

  checkPendingMessages();

  // Assure that the changed flag is still false;
  CCopasiDataModel::Global->changed(false);

  mpAutoSaveTimer = new QTimer(this);
  mpAutoSaveTimer->start(AutoSaveInterval); // every 10 minutes
  connect(mpAutoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
  // ListViews::notify(ListViews::FUNCTION, ListViews::ADD, "");
}

CopasiUI3Window::~CopasiUI3Window()
{
  pdelete(listViews);
  pdelete(dataModel);
}

void CopasiUI3Window::createActions()
{
  mpaNew = new QAction(QPixmap(filenew), "&New", CTRL + Key_N, this, "new");
  connect(mpaNew, SIGNAL(activated()), this, SLOT(newDoc()));

  mpaOpen = new QAction(QPixmap(fileopen), "&Open...", CTRL + Key_O, this, "open");
  connect(mpaOpen, SIGNAL(activated()), this, SLOT(slotFileOpen()));

  mpaSave = new QAction(QPixmap(filesave), "&Save", CTRL + Key_S, this, "save");
  connect(mpaSave, SIGNAL(activated()), this, SLOT(slotFileSave()));

  mpaSaveAs = new QAction(QPixmap(filesave), "Save &As...", SHIFT + CTRL + Key_S, this, "saveas");
  connect(mpaSaveAs, SIGNAL(activated()), this, SLOT(slotFileSaveAs()));

  mpaImportSBML = new QAction(QPixmap(fileopen), "&Import SBML...", CTRL + Key_I, this, "importsbml");
  connect(mpaImportSBML, SIGNAL(activated()), this, SLOT(slotImportSBML()));

  mpaExportSBML = new QAction(QPixmap(filesave), "&Export SBML...", CTRL + Key_E, this, "exportsbml");
  connect(mpaExportSBML, SIGNAL(activated()), this, SLOT(slotExportSBML()));

  mpaExportODE = new QAction(QPixmap(filesave), "Export ODEs...", CTRL + Key_M, this, "exportode");
  connect(mpaExportODE, SIGNAL(activated()), this, SLOT(slotExportMathModel()));

  mpaSliders = new QAction(QPixmap(toggleSliderDialog), "Show sliders", 0, this, "showsliders");
  mpaSliders->setToggleAction(true);
  connect(mpaSliders, SIGNAL(toggled(bool)), this, SLOT(slotShowSliders(bool)));

  mpaObjectBrowser = new QAction("Object &Browser", 0, this, "objectbrowser");
  mpaObjectBrowser->setToggleAction(true);
  connect(mpaObjectBrowser, SIGNAL(toggled(bool)), this, SLOT(slotShowObjectBrowserDialog(bool)));

  mpaCheckModel = new QAction(QPixmap(checkModel_xpm), "Check model", 0, this, "checkmodel");
  connect(mpaCheckModel, SIGNAL(activated()), this, SLOT(slotCheckModel()));

  mpaUpdateMIRIAM = new QAction(QPixmap(MIRIAM_xpm), "Update MIRIAM", 0, this, "updatemiriam");
  connect(mpaUpdateMIRIAM, SIGNAL(activated()), this, SLOT(slotUpdateMIRIAM()));

  mpaApplyInitialState = new QAction(QPixmap(istos_xpm), "Apply initial state", 0, this, "applyinitialstate");
  connect(mpaApplyInitialState, SIGNAL(activated()), this, SLOT(slotApplyInitialState()));

  mpaUpdateInitialState = new QAction(QPixmap(stois_xpm), "Update initial state from current state", 0, this, "updateinitialstate");
  connect(mpaUpdateInitialState, SIGNAL(activated()), this, SLOT(slotUpdateInitialState()));

  mpaCapture = new QAction(QPixmap(photo), "Capture the main window", 0, this, "capture");
  connect(mpaCapture, SIGNAL(activated()), this, SLOT(slotCapture()));

  //     QAction* mpaObjectBrowser;
}

void CopasiUI3Window::createToolBar()
{
  QToolBar *tbMain = new QToolBar(this, "MainToolBar");

  //new
  //   QWhatsThis::add(toolb, "Click this button to create a <em>new file</em>. <br>You can also select the <b>New</b> command from the <b>File</b> menu.</p>");
  mpaNew->addTo(tbMain);

  //open
  //   QWhatsThis::add(toolb, "Click this button to open a <em>new file</em>. <br>You can also select the <b>Open</b> command from the <b>File</b> menu.</p>");
  mpaOpen->addTo(tbMain);

  //save
  //   QWhatsThis::add(msave_button, "<p>Click this button to save the file you are editing. You will be prompted for a file name.\nYou can also select the <b>Save</b> command from the <b>File</b> menu.</p>");
  mpaSave->addTo(tbMain);

  // capture
  mpaCapture->addTo(tbMain);

  // add a toobar toggle button to display/hide slider dialog
  //   QWhatsThis::add(mpToggleSliderDialogButton, "<p>Click this button to show/hide the sliders dialog. This is the same as clicking on <b>show sliders</b> in the <b>Tools</b> menu.</p>");
  mpaSliders->addTo(tbMain);

  mpaCheckModel->addTo(tbMain);

  mpaApplyInitialState->addTo(tbMain);
  mpaUpdateInitialState->addTo(tbMain);

  mpaUpdateMIRIAM->addTo(tbMain);
  tbMain->addSeparator();

  mpBoxSelectFramework = new QComboBox(tbMain);
  mpBoxSelectFramework->insertItem("Concentrations");
  mpBoxSelectFramework->insertItem("Particle Numbers");

  tbMain->setCloseMode(QDockWindow::Never);

  connect(mpBoxSelectFramework, SIGNAL(activated(int)), this, SLOT(slotFrameworkChanged(int)));

  //What's this
  /*  toolb = QWhatsThis::whatsThisButton(tbMain);
    QWhatsThis::add(toolb, "This is a <b>What's This</b> button "
                    "It enables the user to ask for help "
                    "about widgets on the screen.");*/
}

void CopasiUI3Window::createMenuBar()
{
  const char* toolTip[7];

  toolTip[0] = "Click this button to create a <em>new file</em>. <br>"
               "You can also select the <b>New</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[1] = "Click this button to open a <em>file</em>. <br>"
               "You can also select the <b>Open</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[2] = "<p>Click this button to save the file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Save</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[3] = "<p>Click this button to save the file you are editing "
               "under a new name. You will be prompted for a file name.\n"
               "You can also select the <b>Save As</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[4] = "<p>Click this button to import a SBML file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Import SBML</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[5] = "<p>Click this button to export a SBML file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Export SBML</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[6] = "<p>Click this button to export the ODEs of the Mathematical Model. "
               "You will be prompted for a file name.\n"
               "You can also select the <b>Export </b> command "
               "from the <b>File</b> menu.</p>";

  QPopupMenu * pFileMenu = new QPopupMenu(this);
  menuBar()->insertItem("&File", pFileMenu);

  mpaNew->addTo(pFileMenu);
  mpaOpen->addTo(pFileMenu);
  mpaSave->addTo(pFileMenu);
  mpaSaveAs->addTo(pFileMenu);

  pFileMenu->insertSeparator();

  mpaImportSBML->addTo(pFileMenu);
  mpaExportSBML->addTo(pFileMenu);
  mpaExportODE->addTo(pFileMenu);

  pFileMenu->insertSeparator();

  mpMenuRecentFiles = new QPopupMenu(this);
  pFileMenu->insertItem("Recent Files", mpMenuRecentFiles);
  refreshRecentFileMenu();

  mpMenuRecentSBMLFiles = new QPopupMenu(this);
  pFileMenu->insertItem("Recent SBML Files", mpMenuRecentSBMLFiles);
  refreshRecentSBMLFileMenu();

  pFileMenu->insertSeparator();

  pFileMenu->insertItem("&Quit", this, SLOT(slotQuit()), CTRL + Key_Q);

  //****** tools menu **************

  QPopupMenu* tools = new QPopupMenu(this);
  menuBar()->insertItem("&Tools", tools);

  //tools->insertSeparator();
  tools->insertItem("&Convert to irreversible", this, SLOT(slotConvertToIrreversible()));
  //tools->insertItem("Object &Browser", this, SLOT(slotObjectBrowserDialog()), 0, 2);

  tools->insertSeparator();

  mpaCapture->addTo(tools);

  tools->insertSeparator();

  mpaObjectBrowser->addTo(tools);

  mpaSliders->addTo(tools);

  mpaCheckModel->addTo(tools);

  mpaApplyInitialState->addTo(tools);
  mpaUpdateInitialState->addTo(tools);

  mpaUpdateMIRIAM->addTo(tools);

  tools->insertSeparator();
  tools->insertItem("&Preferences...", this, SLOT(slotPreferences()), CTRL + Key_P, 3);

#ifdef COPASI_LICENSE_COM
  tools->insertSeparator();
  tools->insertItem("&Registration", this, SLOT(slotRegistration()));
#endif // COPASI_LICENSE_COM

  //*******  help menu *****************

  menuBar()->insertSeparator();

  QPopupMenu * help = new QPopupMenu(this);
  menuBar()->insertItem("&Help", help);

  help->insertItem("Simple &Wizard", this, SLOT(slotTutorialWizard()));
  help->insertSeparator();
  help->insertItem("&About", this, SLOT(about()), Key_F1);
  help->insertItem("&License", this, SLOT(license()));
  help->insertItem("About &Qt", this, SLOT(aboutQt()));
  help->insertSeparator();
  help->insertItem("What's &This", this, SLOT(whatsThis()), SHIFT + Key_F1);
}

/***************CopasiUI3Window::slotFileSaveAs()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as
 **              option in the menu File
 *******************************************************************************************/
bool CopasiUI3Window::slotFileSaveAs(QString str)
{
  bool success = true;
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp = "";

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          str, "COPASI Files (*.cps);;All Files (*.*);;",
                                          "Choose a filename to save under");

      if (!tmp) return false;

      if (!tmp.endsWith(".cps") &&
          !tmp.endsWith(".")) tmp += ".cps";
      tmp = tmp.remove(QRegExp("\\.$"));

      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return false;
    }

  if (dataModel && tmp)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (success = dataModel->saveModel((const char *) tmp.utf8(), true))
        {
          CCopasiDataModel::Global->changed(false);
          updateTitle();
        }
      else
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              CQMessageBox::critical(this, "Save File Error",
                                     CCopasiMessage::getAllMessageText().c_str(),
                                     QMessageBox::Ok | QMessageBox::Default,
                                     QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor); resetMenus;

      refreshRecentFileMenu();
    }

  mSaveAsRequired = false;

  return success;
}

/***************CopasiUI3Window::newDoc()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the new as
 **              option in the menu File
 **
 *******************************************************************************************/
void CopasiUI3Window::newDoc()
{
  if (newFlag == 0)
    newFlag = 1;
  else
    ListViews::commit();

  if (dataModel && CCopasiDataModel::Global->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:                                                                                     // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:                                                                                     // Discard clicked or Alt+D pressed
          break;

        case 2:                                                                                     // Cancel clicked or Escape pressed
          return;
          break;
        }

      ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                        CCopasiDataModel::Global->getModel()->getKey());
    }

  ListViews::switchAllListViewsToWidget(0, "");

  if (!dataModel)
    dataModel = new DataModelGUI(); // create the data model

  dataModel->createModel();
  ListViews::notify(ListViews::MODEL, ListViews::ADD, CCopasiDataModel::Global->getModel()->getKey());
  //if (!mbObject_browser_open)
  //mpFileMenu->setItemEnabled(nobject_browser, true);

  mpaSave->setEnabled(true);
  mpaSaveAs->setEnabled(true);
  mpaExportSBML->setEnabled(true);
  mpaExportODE->setEnabled(true);

  updateTitle();
  ListViews::switchAllListViewsToWidget(1, "");
  mSaveAsRequired = true;
}

/***************CopasiUI3Window::slotFileOpen()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on Open
 **              option in the menu File
 *******************************************************************************************/
void CopasiUI3Window::slotFileOpen(QString file)
{
  bool success = true;

  ListViews::commit();

  QString newFile = "";

  if (file == "")
    newFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog", QString::null,
                                        "COPASI Files (*.gps *.cps);;All Files (*.*);;",
                                        "Choose a file");
  else
    newFile = file;

  // gives the file information to the datamodel to handle it

  if (newFile)
    {
      if (dataModel && CCopasiDataModel::Global->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                                                     // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                                                     // Discard clicked or Alt+D pressed
              break;

            case 2:                                                                                     // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            CCopasiDataModel::Global->getModel()->getKey());
        }

      ListViews::switchAllListViewsToWidget(0, "");

      if (!dataModel)
        dataModel = new DataModelGUI; // create a new data model

      QCursor oldCursor = this->cursor();
      this->setCursor(Qt::WaitCursor);

      CCopasiMessage::clearDeque();

      try
        {
          success = dataModel->loadModel((const char *)newFile.utf8());
        }
      catch (...)
        {
          success = false;
        }
      setCursor(oldCursor); resetMenus;

      if (!success)
        {
          QString Message = "Error while loading file " + newFile + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("File Error"), Message,
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          dataModel->createModel();
        }

      CCopasiMessage msg = CCopasiMessage::getLastMessage();

      if (msg.getNumber() != MCCopasiMessage + 1)
        {
          QString Message = "Problem while loading file " + newFile + QString("!\n\n");
          Message += FROM_UTF8(msg.getText());

          msg = CCopasiMessage::getLastMessage();
          while (msg.getNumber() != MCCopasiMessage + 1)
            {
              Message += "\n";
              Message += FROM_UTF8(msg.getText());
              msg = CCopasiMessage::getLastMessage();
            }

          CQMessageBox::warning(this, QString("File Warning"), Message,
                                QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }

      if (strcasecmp(CDirEntry::suffix((const char *)newFile.utf8()).c_str(), ".cps") == 0 &&
          CDirEntry::isWritable((const char *)newFile.utf8()))
        mSaveAsRequired = false;
      else
        mSaveAsRequired = true;

      if (!CCopasiDataModel::Global->getModel())
        {
          newDoc();
          mSaveAsRequired = true;
        }

      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        CCopasiDataModel::Global->getModel()->getKey());

      mpaSave->setEnabled(true);
      mpaSaveAs->setEnabled(true);
      mpaExportSBML->setEnabled(true);
      mpaExportODE->setEnabled(true);

      updateTitle();
      ListViews::switchAllListViewsToWidget(1, "");

      refreshRecentFileMenu();
    }
}

/***************CopasiUI3Window::slotFileSave()*****************
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as
 **              option in the menu File and it is used to save the document information
 *******************************************************************************************/
bool CopasiUI3Window::slotFileSave()
{
  //  ListViews::commit(); --> remove to the line after checking the following condition (07.04.08)

  std::string FileName = CCopasiDataModel::Global->getFileName();
  if (mSaveAsRequired || FileName == "")
    {
      return slotFileSaveAs(FROM_UTF8(FileName));
    }

  ListViews::commit();

  std::ifstream File(utf8ToLocale(FileName).c_str());
  std::string Line;
  File >> Line;
  File.close();

  int choice = 0;

  if (!Line.compare(0, 8, "Version=") ||
      strcasecmp(FileName.c_str(), ".gps") == 0)
    {
      /* Ask for permision to overwrite write? */
      /* If no call slotFileSaveAs */
      choice =
        CQMessageBox::warning(this,
                              "Confirm File Version Update",
                              "You are to overwrite an existing Gepasi File.\n"
                              "This will render the file unreadable for Gepasi",
                              "Save As", "Overwrite", 0, 0, 1);

      if (!choice)
        {
          return slotFileSaveAs(FROM_UTF8(FileName));
        }
    }

  bool success = true;

  if (dataModel)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (success = dataModel->saveModel(FileName, true))
        {
          CCopasiDataModel::Global->changed(false);
        }
      else
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              CQMessageBox::critical(this, "Save File Error",
                                     CCopasiMessage::getAllMessageText().c_str(),
                                     QMessageBox::Ok | QMessageBox::Default,
                                     QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor); resetMenus;
    }

  refreshRecentFileMenu();
  return success;
}

void CopasiUI3Window::slotQuit()
{
  bool success = true;

  ListViews::commit();

  if (dataModel && CCopasiDataModel::Global->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:  // Save clicked or Alt+S pressed or Enter pressed.
          success = slotFileSave();
          break;

        case 1:  // Discard clicked or Alt+D pressed
          success = true;
          break;

        case 2:  // Cancel clicked or Escape pressed
          success = false;
          break;
        }
    }

  if (success)
    {
      CleanUp();
      qApp->quit();
    }
}

void CopasiUI3Window::closeEvent(QCloseEvent* ce)
{
  bool success = true;

  ListViews::commit();

  if (dataModel && CCopasiDataModel::Global->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:  // Save clicked or Alt+S pressed or Enter pressed.
          success = slotFileSave();
          break;

        case 1:  // Discard clicked or Alt+D pressed
          success = true;
          break;

        case 2:  // Cancel clicked or Escape pressed
          success = false;
          break;
        }
    }

  if (success)
    {
      CleanUp();
      ce->accept();
    }
  else
    ce->ignore();
}

// Cleanup all the temp .cps files created at runtime.
void CopasiUI3Window::CleanUp()
{
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);

  CDirEntry::removeFiles("*.cps", tempDir);
  CDirEntry::remove(tempDir);
}

/***************CopasiUI3Window::slotFilePrint()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the print as
 **              option in the menu File and is used to send the document ro
 **              printing
 *******************************************************************************************/
void CopasiUI3Window::slotFilePrint()
{}

/***************CopasiUI3Window::about()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is just to display the message
 **
 *******************************************************************************************/
void CopasiUI3Window::about()
{
  QString text =
    QString(AboutDialog::text).arg(FROM_UTF8(CCopasiDataModel::Global->getVersion()->getVersion()));
  AboutDialog* aboutDialog = new AboutDialog(this, text, 76, 30);
  aboutDialog->setCaption(FixedTitle);
  aboutDialog->exec();
}

void CopasiUI3Window::license()
{
  AboutDialog* aboutDialog = new AboutDialog(this, CopasiLicense, 76, 30);
  aboutDialog->setCaption(FixedTitle);
  aboutDialog->exec();
}

/***************CopasiUI3Window::aboutQt()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is help about the QT application
 *******************************************************************************************/
void CopasiUI3Window::aboutQt()
{
  QMessageBox::aboutQt(this, "Qt");
}

void CopasiUI3Window::slotShowObjectBrowserDialog(bool flag)
{

  if (flag /*tools->isItemEnabled(2)*/)
    {
      if (mpObjectBrowser)
        delete mpObjectBrowser;
      mpObjectBrowser = new ObjectBrowserDialog(this, 0, false, 1);
      mpObjectBrowser->show();
    }
  else
    {
      if (mpObjectBrowser)
        mpObjectBrowser->hide();
    }
}

void CopasiUI3Window::slotObjectBrowserDialogWasClosed()
{
  mpObjectBrowser = NULL;
  mpaObjectBrowser->setOn(false);
}

void CopasiUI3Window::slotPreferences()
{
  CQPreferenceDialog * preferenceDialog = new CQPreferenceDialog(this, 0, false, Qt::WDestructiveClose);
  preferenceDialog->setModal(true);
  preferenceDialog->show();
}

void CopasiUI3Window::slotTutorialWizard()
{
  WizardDialog* tutorialWizard = new WizardDialog();
  tutorialWizard->setCopasiMainWindow(this);
  tutorialWizard->show();
}

void CopasiUI3Window::importSBMLFromString(const std::string& sbmlDocumentText)
{
  bool success = true;

  ListViews::commit();

  if (!sbmlDocumentText.empty())
    {
      if (dataModel && CCopasiDataModel::Global->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                                                     // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                                                     // Discard clicked or Alt+D pressed
              break;

            case 2:                                                                                     // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            CCopasiDataModel::Global->getModel()->getKey());
        }

      ListViews::switchAllListViewsToWidget(0, "");

      if (!dataModel)
        {
          dataModel = new DataModelGUI(); // create a new data model
        }

      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);

      try
        {
          success = dataModel->importSBMLFromString(sbmlDocumentText);
        }

      catch (CCopasiException except)
        {
          success = false;
        }

      setCursor(oldCursor); resetMenus;

      if (!success)
        {
          QString Message = "Error while importing SBML model!\n\n";
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("Import Error"), Message,
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();

          dataModel->createModel();
        }

      /* still check for warnings.
       * Maybe events or rules were ignored while reading
       * the file.
       */
      if (success)
        {
          this->checkPendingMessages();
        }

      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        CCopasiDataModel::Global->getModel()->getKey());

      //if (!bobject_browser_open)
      //       mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      //       msave_button->setEnabled(true);
      //       mpFileMenu->setItemEnabled(nsave_menu_id, true);

      ListViews::switchAllListViewsToWidget(1, "");
    }
  updateTitle();

  mSaveAsRequired = true;
}

void CopasiUI3Window::slotImportSBML(QString file)
{
  bool success = true;

  ListViews::commit();

  QString SBMLFile;

  if (file == "")
    SBMLFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString::null, "XML Files (*.xml);;All Files (*.*);;",
                                        "Choose a file");
  else
    SBMLFile = file;

  if (SBMLFile)
    {
      if (dataModel && CCopasiDataModel::Global->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                                                     // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                                                     // Discard clicked or Alt+D pressed
              break;

            case 2:                                                                                     // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            CCopasiDataModel::Global->getModel()->getKey());
        }

      ListViews::switchAllListViewsToWidget(0, "");

      if (!dataModel)
        {
          dataModel = new DataModelGUI; // create a new data model
        }

      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);

      try
        {
          success = dataModel->importSBML((const char *)SBMLFile.utf8());
        }

      catch (...)
        {
          success = false;
        }

      setCursor(oldCursor); resetMenus;

      if (!success)
        {
          QString Message = "Error while loading file " + SBMLFile + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("File Error"), Message,
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          dataModel->createModel();
        }
      else
        // We check in all case for warnings. This will help also for unsuccessful imports
        this->checkPendingMessages();

      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        CCopasiDataModel::Global->getModel()->getKey());

      mpaSave->setEnabled(true);
      mpaSaveAs->setEnabled(true);
      mpaExportSBML->setEnabled(true);
      mpaExportODE->setEnabled(true);

      ListViews::switchAllListViewsToWidget(1, "");

      refreshRecentSBMLFileMenu();
    }
  updateTitle();

  mSaveAsRequired = true;
}

void CopasiUI3Window::slotExportSBML()
{
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;
  bool exportIncomplete = false;
  int sbmlLevel = 2;
  int sbmlVersion = 1;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;
      if (CCopasiDataModel::Global->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName(CCopasiDataModel::Global->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName(CCopasiDataModel::Global->getFileName())
                    + ".xml");

      // we need a new dialog the lets the user choose different levels of sbml as soon as support for export to those versions
      // has been implemented.
      CQSBMLFileDialog sbmlFileDialog(this, "Save SBML File Dialog", true);
      std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> > nameAndVersion =
        sbmlFileDialog.getSaveFileName(Default,
                                       "XML Files (*.xml);;All Files (*.*);;",
                                       "Choose a filename and SBML version for SBML export.");
      tmp = nameAndVersion.first;
      sbmlLevel = nameAndVersion.second.first;
      sbmlVersion = nameAndVersion.second.second;
      if (!tmp) return;

      if (!tmp.endsWith(".xml") && !tmp.endsWith("."))
        tmp += ".xml";

      tmp = tmp.remove(QRegExp("\\.$"));

      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (dataModel && tmp)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      bool success = false;
      try
        {
          success = dataModel->exportSBML((const char *) tmp.utf8(), true, sbmlLevel, sbmlVersion, exportIncomplete);
        }
      catch (CCopasiException except)
        {
          success = false;
          setCursor(oldCursor);
          resetMenus;
          //CQMessageBox::critical(this, QString("File Error"),
          //                       QString("Error. Could not export file ") + tmp + QString("!"),
          //                       QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }

      setCursor(oldCursor); resetMenus;

      /*
      if (!success)
        {
          QString Message = "Error while saving file " + tmp + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("File Error"), Message,
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
      else
        {
        */
      this->checkPendingMessages();
      /*
      }
      */
      refreshRecentSBMLFileMenu();
    }
}

void CopasiUI3Window::slotExportMathModel()
{
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;
  QString newFilter;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;
      if (CCopasiDataModel::Global->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName(CCopasiDataModel::Global->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName(CCopasiDataModel::Global->getFileName()));
      //+ ".c");

      // QString newFilter;
      tmp =
        CopasiFileDialog::getSaveFileNameAndFilter(newFilter,
            this, "Save File Dialog",
            Default,
            "C Files (*.c);;Berkeley Madonna Files (*.mmd);;XPPAUT (*.ode)",
            "Choose an export format.");

      if (!tmp) return;

      tmp = tmp.remove(QRegExp("\\.$"));

      if (!tmp.endsWith(".c") && !tmp.endsWith(".") && !tmp.endsWith(".mmd") && !tmp.endsWith(".ode"))
        if (newFilter == "C Files (*.c)")
          tmp += ".c";
        else
          if (newFilter == "Berkeley Madonna Files (*.mmd)")
            tmp += ".mmd";
          else
            if (newFilter == "XPPAUT (*.ode)")
              tmp += ".ode";

      if (tmp.endsWith(".c") && newFilter != "C Files (*.c)") newFilter = "C Files (*.c)";
      if (tmp.endsWith(".mmd") && newFilter != "Berkeley Madonna Files (*.mmd)") newFilter = "Berkeley Madonna Files (*.mmd)";
      if (tmp.endsWith(".ode") && newFilter != "XPPAUT (*.ode)") newFilter = "XPPAUT (*.ode)";

      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (dataModel && tmp)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (!dataModel->exportMathModel((const char *) tmp.utf8(), (const char *) newFilter.utf8(), true))
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              CQMessageBox::critical(this, "Export Error",
                                     CCopasiMessage::getAllMessageText().c_str(),
                                     QMessageBox::Ok | QMessageBox::Default,
                                     QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor); resetMenus;
    }
}

void CopasiUI3Window::slotConvertToIrreversible()
{
  CModel* model = CCopasiDataModel::Global->getModel();
  if (!model) return;

  ListViews::commit();
  ListViews::switchAllListViewsToWidget(114, "");

  CCopasiMessage::clearDeque();
  if (!model->convert2NonReversible())
    {
      // Display error messages.
      CQMessageBox::information(this, "Conversion Failed",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default,
                                QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  ListViews::notify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CopasiUI3Window::slotShowSliders(bool flag)
{
  mpaSliders->setOn(flag);
  this->mpSliders->setHidden(!flag);
}

// void CopasiUI3Window::enable_object_browser_menu()
// {
//   //mpFileMenu->setItemEnabled(nobject_browser, true);
//   mbObject_browser_open = false;
//}

// void CopasiUI3Window::disable_object_browser_menu()
// {
//   //mpFileMenu->setItemEnabled(nobject_browser, false);
//   mbObject_browser_open = true;
//}

DataModelGUI* CopasiUI3Window::getDataModel()
{return dataModel;}

void CopasiUI3Window::listViewsFolderChanged(QListViewItem* item)
{
  C_INT32 id = ((FolderListItem*)item)->getFolder()->getId();
  this->mpSliders->setCurrentFolderId(id);
}

// void CopasiUI3Window::saveFile()
// {
//   this->slotFileSave();
//}

CQTrajectoryWidget* CopasiUI3Window::getTrajectoryWidget()
{
  return listViews->trajectoryWidget;
}

SteadyStateWidget* CopasiUI3Window::getSteadyStateWidget()
{
  return listViews->steadystateWidget;
}

ScanWidget* CopasiUI3Window::getScanWidget()
{
  return listViews->scanWidget;
}

void CopasiUI3Window::checkPendingMessages()
{
  CCopasiMessage msg_pending = CCopasiMessage::getLastMessage();

  if (msg_pending.getNumber() != MCCopasiMessage + 1)
    {
      QString text;
      QString filteredText;
      unsigned int numMessages = 0;
      unsigned int numFilteredMessages = 0;
      while (msg_pending.getNumber() != MCCopasiMessage + 1)
        {
          if (msg_pending.getType() & 128)
            {
              ++numFilteredMessages;
              filteredText += "\n";
              filteredText += FROM_UTF8(msg_pending.getText());
            }
          else
            {
              ++numMessages;
              text += "\n";
              text += FROM_UTF8(msg_pending.getText());
            }
          msg_pending = CCopasiMessage::getLastMessage();
        }

      if (numFilteredMessages != 0)
        {
          CQMessageBox box(this);
          if (text.isEmpty())
            text = "There were no serious issues encountered during the import of SBML. "
                   "However some minor issues have occured, which can be viewed in the Minor "
                   "Issues tab.";
          box.configure(QString("COPASI Message"), text, QMessageBox::Information, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, QMessageBox::NoButton);
          box.enableFilteredMessages(true);
          box.setFilteredMessageText(filteredText);
          box.setMessageTabLabel(QString::number(numMessages) + QString(" Messages"));
          box.setFilteredTabLabel(QString::number(numFilteredMessages) + QString(" Minor Issues"));
          box.exec();
        }
      else
        {
          CQMessageBox::information(this, QString("COPASI Message"), text,
                                    QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }
    }
}

void CopasiUI3Window::updateTitle()
{
  QString FileName = FROM_UTF8(CCopasiDataModel::Global->getFileName());

#ifdef WIN32 // Windows allows mixxing of '/' and '\' as separator.
  FileName.replace("\\", "/");
#endif

  if (FileName.length() > 40)
    {
#ifdef WIN32
      QRegExp mask("^(([A-Z]:/)?[^/]+/).*(/[^/]+/[^/]+$)");
#else
      QRegExp mask("^((/*)[^/]+/).*(/[^/]+/[^/]+$)");
#endif

      mask.search(FileName);
      FileName = mask.cap(1) + "..." + mask.cap(3);
    }

  std::string BaseName;
  if (!FileName.isEmpty())
    BaseName = CDirEntry::baseName((const char *) FileName.utf8()) + " - ";

  setCaption(FROM_UTF8(BaseName) + FixedTitle + " " + FileName);
}

void CopasiUI3Window::autoSave()
{
  if (!mSuspendAutoSave)
    {
      mSuspendAutoSave = true;
      CCopasiDataModel::Global->autoSave();
      mSuspendAutoSave = false;
    }

  mpAutoSaveTimer->changeInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::suspendAutoSave(const bool & suspend)
{
  mSuspendAutoSave = suspend;
  if (!mSuspendAutoSave)
    mpAutoSaveTimer->changeInterval(AutoSaveInterval); // restart the timer
}

void CopasiUI3Window::slotOpenRecentFile(int index)
{
  std::string FileName =
    *CCopasiDataModel::Global->getConfiguration()->getRecentFiles().getGroup("Recent Files")->getValue(index).pSTRING;

  slotFileOpen(FROM_UTF8(FileName));
}

void CopasiUI3Window::slotOpenRecentSBMLFile(int index)
{
  std::string FileName =
    *CCopasiDataModel::Global->getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->getValue(index).pSTRING;

  slotImportSBML(FROM_UTF8(FileName));
}

void CopasiUI3Window::refreshRecentFileMenu()
{
  mpMenuRecentFiles->clear();

  CCopasiParameterGroup::index_iterator it =
    CCopasiDataModel::Global->getConfiguration()->getRecentFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CCopasiDataModel::Global->getConfiguration()->getRecentFiles().getGroup("Recent Files")->endIndex();

  C_INT Index = 0;
  for (; it != end; ++it, ++Index)
    mpMenuRecentFiles->insertItem(FROM_UTF8(*(*it)->getValue().pSTRING),
                                  this,
                                  SLOT(slotOpenRecentFile(int)),
                                  0,
                                  Index);
}

void CopasiUI3Window::refreshRecentSBMLFileMenu()
{
  mpMenuRecentSBMLFiles->clear();

  CCopasiParameterGroup::index_iterator it =
    CCopasiDataModel::Global->getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->beginIndex();
  CCopasiParameterGroup::index_iterator end =
    CCopasiDataModel::Global->getConfiguration()->getRecentSBMLFiles().getGroup("Recent Files")->endIndex();

  C_INT Index = 0;
  for (; it != end; ++it, ++Index)
    mpMenuRecentSBMLFiles->insertItem(FROM_UTF8(*(*it)->getValue().pSTRING),
                                      this,
                                      SLOT(slotOpenRecentSBMLFile(int)),
                                      0,
                                      Index);
}

std::string CopasiUI3Window::exportSBMLToString()
{
  ListViews::commit();

  std::string ret;

  if (dataModel)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      bool success = true;
      try
        {
          ret = dataModel->exportSBMLToString();
        }
      catch (CCopasiException except)
        {
          success = false;
          setCursor(oldCursor); resetMenus;
          CQMessageBox::critical(this, QString("File Error"),
                                 QString("Error. Could not do SBML export!"),
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        }

      setCursor(oldCursor); resetMenus;

      if (!success)
        {
          QString Message = "Error while SBML model!\n\n";
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          CQMessageBox::critical(this, QString("File Error"), Message,
                                 QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }
  return ret;
}

#include "model/CModelAnalyzer.h"
void CopasiUI3Window::slotCheckModel()
{
  CModelAnalyzer MA(CCopasiDataModel::Global->getModel());

  std::ostringstream ss;
  // MA.writeReport(ss, true, false);
  MA.writeReport(ss, true, true);

  QTextEdit* pTE = new QTextEdit(FROM_UTF8(ss.str()));
  pTE->setReadOnly(true);
  pTE->resize(512, 640);
  pTE->show();
}

void CopasiUI3Window::slotUpdateMIRIAM()
{
  bool success = true;

  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);

  CCopasiMessage::clearDeque();
  if (!dataModel)
    dataModel = new DataModelGUI; // create a new data model

  try
    {
      success = dataModel->updateMIRIAM(
                  CCopasiDataModel::Global->getConfiguration()->getRecentMIRIAMResources());
    }
  catch (...)
    {
      success = false;
    }

  if (!success)
    {
      setCursor(oldCursor);
      QString Message = "Error while updating MIRIAM" + QString("!\n\n");
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());
      CQMessageBox::critical(this, QString("MIRIAM Error"), Message,
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  /* still check for warnings.
   * Maybe events or rules were ignored while reading
   * the file.
   */
  if (success)
    {
      CCopasiDataModel::Global->getConfiguration()->save();
      CMIRIAMResourceObject::setMIRIAMResources(
        &CCopasiDataModel::Global->getConfiguration()->getRecentMIRIAMResources());
      ListViews::updateMIRIAMResourceContents();
      this->checkPendingMessages();
    }

  CCopasiMessage::clearDeque();
  ListViews::switchAllListViewsToWidget(0, "");
  setCursor(oldCursor);
}

void CopasiUI3Window::slotApplyInitialState()
{
  CModel *pModel = CCopasiDataModel::Global->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->applyInitialValues();
      pModel->updateNonSimulatedValues();

      ListViews::notify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());
    }
}

void CopasiUI3Window::slotUpdateInitialState()
{
  CModel *pModel = CCopasiDataModel::Global->getModel();

  if (pModel != NULL)
    {
      pModel->compileIfNecessary(NULL);
      pModel->setInitialState(pModel->getState());
      pModel->updateInitialValues();

      ListViews::notify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());
    }
}

void CopasiUI3Window::slotFrameworkChanged(int index)
{ListViews::setFramework(index);}

void CopasiUI3Window::slotCapture()
{
  QPixmap pixmap = QPixmap::grabWidget(listViews->getCurrentWidget());

  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      QString filter;
      fileName = CopasiFileDialog::getSaveFileNameAndFilter(filter, this, "Save File Dialog",
                 QString::null, "PNG Files (*.png);;", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      /*
            QFileInfo fileInfo(fileName);
            extensionName = fileInfo.extension();

            if (extensionName != "png")
              fileName.replace("." + extensionName, ".png");

            fileInfo.setFile(fileName);
            extensionName = fileInfo.extension();

            if (extensionName == "")
              fileName += ".png";
      */
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  pixmap.save(fileName, "PNG");
}

#ifdef COPASI_LICENSE_COM

#include "CQRegistrationDialog.h"
#include "commercial/CRegistration.h"

bool CopasiUI3Window::checkRegistration()
{
  CRegistration * pRegistration =
    elevate< CRegistration, CCopasiParameterGroup >(CCopasiDataModel::Global->getConfiguration()->assertGroup("Registration"));

  bool RegistrationChanged = false;
  std::string RegistrationValue;

  if (!COptions::compareValue("RegistrationCode", std::string("")))
    {
      COptions::getValue("RegistrationCode", RegistrationValue);
      pRegistration->setRegistrationCode(RegistrationValue);
      RegistrationChanged = true;
    }

  if (!COptions::compareValue("RegisteredEmail", std::string("")))
    {
      COptions::getValue("RegisteredEmail", RegistrationValue);
      pRegistration->setRegisteredEmail(RegistrationValue);
      RegistrationChanged = true;
    }

  if (!COptions::compareValue("RegisteredUser", std::string("")))
    {
      COptions::getValue("RegisteredUser", RegistrationValue);
      pRegistration->setRegisteredUser(RegistrationValue);
      RegistrationChanged = true;
    }

  if ((!RegistrationChanged && !pRegistration->isValidSignature()) ||
      !pRegistration->isValidRegistration())
    return slotRegistration();

  return true;
}

bool CopasiUI3Window::slotRegistration()
{
  CQRegistrationDialog *pDialog = new CQRegistrationDialog(this);

  if (pDialog->exec() == QDialog::Accepted)
    return true;
  else
    return false;
}
#endif // COPASI_LICENSE_COM

#ifndef COPASI_LICENSE_COM
bool CopasiUI3Window::slotRegistration()
{return true;}
#endif // not COPASI_LICENSE_COM

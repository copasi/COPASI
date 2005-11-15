/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiui3window.cpp,v $
   $Revision: 1.161 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/11/15 14:49:32 $
   End CVS Header */

#include <qapplication.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qtimer.h>

#include <vector>

#include "AboutDialog.h"
#include "CopasiFileDialog.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "ObjectBrowserDialog.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CVersion.h"

#include "utilities/CCopasiException.h"
#include "utilities/CDirEntry.h"
#include "model/CModel.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "qtUtilities.h"
#include "wizard/wizard.h"
#include "report/CKeyFactory.h"
#include "SliderDialog.h"

#include "./icons/filenew.xpm"
#include "./icons/fileopen.xpm"
#include "./icons/filesave.xpm"
#include "./icons/fileprint.xpm"
#include "./icons/showSliders.xpm"
#include "./icons/Copasi16-Alpha.xpm"

#define AutoSaveInterval 10*60*1000

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
    //    splitter(NULL),
    listViews(NULL),
    //    gpsFile(),
    msave_button(NULL),
    mpFileMenu(NULL),
    sliders(NULL),
    mpToggleSliderDialogButton(NULL),
    mSaveAsRequired(true),
    mpAutoSaveTimer(NULL),
    mSuspendAutoSave(false)
{
  setIcon(QPixmap((const char **) Copasi16_Alpha_xpm));

  // Set the window caption/title
  newFlag = 0;
  FixedTitle = "COPASI (";
  FixedTitle += FROM_UTF8(CCopasiDataModel::Global->getVersion()->getVersion());
  FixedTitle += " test version) ";
  updateTitle();
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  //  mpFileMenu = new QPopupMenu;
  //mpFileMenu->setItemEnabled(nobject_browser, false);
  bobject_browser_open = false;
  mpFileMenu->setItemEnabled(nexport_menu_SBML, false);
  mpFileMenu->setItemEnabled(nexport_menu_MathModel, false);

  //disable menu option
  mpFileMenu->setItemVisible(nexport_menu_MathModel, false);

  mpFileMenu->setItemEnabled(nsave_menu_id, false);
  mpFileMenu->setItemEnabled(nsaveas_menu_id, false);
  msave_button->setEnabled(false);

  if (!dataModel)
    {
      // create the data model
      dataModel = new DataModelGUI();

      //splitter = new QSplitter(QSplitter::Vertical, this , "main");
      //splitter->show();
      //this->setCentralWidget(splitter);
    }

  listViews = new ListViews(this /*splitter*/);

  connect(listViews->folders, SIGNAL(currentChanged(QListViewItem*)), this, SLOT(listViewsFolderChanged(QListViewItem*)));

  ListViews::setDataModel(dataModel);
  listViews->show();
  this->setCentralWidget(listViews);

  this->sliders = new SliderDialog(this);
  C_INT32 id = ((FolderListItem*)listViews->folders->currentItem())->getFolder()->getId();
  this->sliders->setCurrentFolderId(id);
  this->sliders->resize(350, 250);

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

/***************CopasiUI3Window::slotFileSaveAs()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File 
 *******************************************************************************************/
void CopasiUI3Window::slotFileSaveAs(QString str)
{
  bool mSuccess;
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp = "";

  while (Answer == QMessageBox::No)
    {
      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          str, "COPASI Files (*.gps *cps);;All Files (*.*)",
                                          "Choose a filename to save under.");

      if (!tmp) return;

      if (!tmp.endsWith(".cps") &&
          !tmp.endsWith(".")) tmp += ".cps";
      tmp = tmp.remove(QRegExp("\\.$"));

      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (dataModel && tmp)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (mSuccess = dataModel->saveModel((const char *) tmp.utf8(), true))
        {
          CCopasiDataModel::Global->changed(false);
          updateTitle();
        }
      else
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              QMessageBox::critical(this, "Save File Error",
                                    CCopasiMessage::getAllMessageText().c_str(),
                                    QMessageBox::Ok | QMessageBox::Default,
                                    QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor);
    }

  mSaveAsRequired = false;
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
  if (newFlag == 0) newFlag = 1;
  else ListViews::commit();

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
    }

  ListViews::switchAllListViewsToWidget(0, "");

  if (!dataModel)
    dataModel = new DataModelGUI(); // create the data model

  dataModel->createModel();
  ListViews::notify(ListViews::MODEL, ListViews::ADD, CCopasiDataModel::Global->getModel()->getKey());
  if (!bobject_browser_open)
    //mpFileMenu->setItemEnabled(nobject_browser, true);
    mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
  mpFileMenu->setItemEnabled(nexport_menu_MathModel, true);
  mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  msave_button->setEnabled(true);
  mpFileMenu->setItemEnabled(nsave_menu_id, true);
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
      catch (CCopasiException except)
        {
          success = false;
          setCursor(oldCursor);
          QMessageBox::critical(this, QString("File Error"), QString("Error while loading file ") + newFile + QString("!"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          dataModel->createModel();
        }
      setCursor(oldCursor);

      if (!success)
        {
          QString Message = "Error while loading file " + newFile + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          QMessageBox::critical(this, QString("File Error"), Message,
                                QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
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

          QMessageBox::warning(this, QString("File Warning"), Message,
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

      //if (!bobject_browser_open)
      //  mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nexport_menu_MathModel, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);
      updateTitle();
      ListViews::switchAllListViewsToWidget(1, "");
    }
}

/***************CopasiUI3Window::slotFileSave()*****************
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File and it is used to save the document information
 *******************************************************************************************/
void CopasiUI3Window::slotFileSave()
{
  ListViews::commit();
  std::string FileName = CCopasiDataModel::Global->getFileName();
  if (mSaveAsRequired || FileName == "")
    {
      slotFileSaveAs(FROM_UTF8(FileName));
      return;
    }

  std::ifstream File(FileName.c_str());
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
        QMessageBox::warning(this,
                             "Confirm File Version Update",
                             "You are to overwrite an existing Gepasi File.\n"
                             "This will render the file unreadable for Gepasi",
                             "Save As", "Overwrite", 0, 0, 1);

      if (!choice)
        {
          slotFileSaveAs(FROM_UTF8(FileName));
          return;
        }
    }

  if (dataModel)
    {
      bool mSuccess;
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (mSuccess = dataModel->saveModel(FileName, true))
        {
          CCopasiDataModel::Global->changed(false);
        }
      else
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              QMessageBox::critical(this, "Save File Error",
                                    CCopasiMessage::getAllMessageText().c_str(),
                                    QMessageBox::Ok | QMessageBox::Default,
                                    QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor);
    }
}

void CopasiUI3Window::slotQuit()
{
  ListViews::commit();

  if (dataModel && CCopasiDataModel::Global->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:  // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:  // Discard clicked or Alt+D pressed
          break;

        case 2:  // Cancel clicked or Escape pressed
          return;
          break;
        }
    }

  CleanUp();
  qApp->quit();
}

void CopasiUI3Window::closeEvent(QCloseEvent* ce)
{
  ListViews::commit();

  if (dataModel && CCopasiDataModel::Global->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:  // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:  // Discard clicked or Alt+D pressed
          break;

        case 2:  // Cancel clicked or Escape pressed
          ce->ignore();
          return;
          break;
        }
    }

  CleanUp();
  ce->accept();
}

// Cleanup all the temp .cps files created at runtime.
void CopasiUI3Window::CleanUp()
{
  std::string tempDir;
  COptions::getValue("Tmp", tempDir);

  CDirEntry::removeFiles("tmp_*.cps", tempDir);
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
  AboutDialog* aboutDialog = new AboutDialog(this);
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

/***************CopasiUI3Window::createToolBar()******
 **
 ** Parameters:- Void
 ** Returns  :-  Void
 ** Descripton:- This method is called to create the toolbar
 *******************************************************************************************/
void CopasiUI3Window::createToolBar()
{
  QToolBar *tbMain = new QToolBar(this, "MainToolBar");
  QToolButton* toolb;

  //new
  toolb = new QToolButton(QPixmap(filenew), "New", QString::null,
                          this, SLOT(newDoc()), tbMain);
  QWhatsThis::add(toolb, "Click this button to create a <em>new file</em>. <br>You can also select the <b>New</b> command from the <b>File</b> menu.</p>");

  //open
  toolb = new QToolButton(QPixmap(fileopen), "Open", QString::null,
                          this, SLOT(slotFileOpen()), tbMain);
  QWhatsThis::add(toolb, "Click this button to open a <em>new file</em>. <br>You can also select the <b>Open</b> command from the <b>File</b> menu.</p>");

  //save
  msave_button = new QToolButton(QPixmap(filesave), "Save", QString::null,
                                 this, SLOT(slotFileSave()), tbMain);
  QWhatsThis::add(msave_button, "<p>Click this button to save the file you are editing. You will be prompted for a file name.\nYou can also select the <b>Save</b> command from the <b>File</b> menu.</p>");

  // add a toobar toggle button to display/hide slider dialog
  mpToggleSliderDialogButton = new QToolButton(QPixmap(toggleSliderDialog), "Toggle slider dialog", QString::null,
                               this, SLOT(slotToggleSliders()), tbMain);
  QWhatsThis::add(mpToggleSliderDialogButton, "<p>Click this button to show/hide the sliders dialog. This is the same as clicking on <b>show sliders</b> in the <b>Tools</b> menu.</p>");
  this->mpToggleSliderDialogButton->setToggleButton(true);

  //What's this
  toolb = QWhatsThis::whatsThisButton(tbMain);
  QWhatsThis::add(toolb, "This is a <b>What's This</b> button "
                  "It enables the user to ask for help "
                  "about widgets on the screen.");
}

/***************CopasiUI3Window::createMenuBar()**********************************
 **
 ** Parameters:- Void
 ** Returns  :-  Void
 ** Descripton:- This method is to create the Menu Bar
 *************************************************************************************/
void CopasiUI3Window::createMenuBar()
{
  //modified on 5th feb : Ankur (left for further modification...later
  QPixmap icon[8] = {filenew, fileopen, filesave, filesave, fileopen, filesave, filesave, fileopen};
  const char* toolTip[9];

  toolTip[0] = "Click this button to create a <em>new file</em>. <br>"
               "You can also select the <b>New</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[1] = "Click this button to open a <em>new file</em>. <br>"
               "You can also select the <b>Open</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[2] = "<p>Click this button to save the file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Save</b> command "
               "from the <b>File</b> menu.</p>";
  toolTip[3] = "<p>Click this button to save the file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Save</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[4] = "Click this button to import a SBML file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Import SBML</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[5] = "Click this button to export a SBML file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Export SBML</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[6] = "Click this button to select the output objects "
               ".\n You can also select the only numeric value ";

  toolTip[7] = "Click this button to export the Mathematical Model. "
               "You will be prompted for a file name.\n"
               "You can also select the <b>Export MathModel</b> command "
               "from the <b>File</b> menu.</p>";

  const char* iconName[7] = {"&New", "&Open", "&Save", "Save&As", "&Import SBML", "&Export SBML", "&Export MathModel"};
  const char* slotFileName[7] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFileSaveAs()), SLOT(slotImportSBML()), SLOT(slotExportSBML()), SLOT(slotExportMathModel())};
  QKeySequence hotKey[7] = {CTRL + Key_N, CTRL + Key_O, CTRL + Key_S, CTRL + Key_A, CTRL + Key_I, CTRL + Key_E, CTRL + Key_M};
  int fileSeparator[7] = {0, 0, 0, 0, 0, 0, 0};

  mpFileMenu = new QPopupMenu(this);
  menuBar()->insertItem("&File", mpFileMenu);
  int j;
  for (j = 0; j < 7; j++)
    {
      if (fileSeparator[j] == 1)
        mpFileMenu->insertSeparator();

      int id;

      id = mpFileMenu->insertItem(icon[j], iconName[j],
                                  this, slotFileName[j], hotKey[j]);

      mpFileMenu->setWhatsThis(id, toolTip[j]);
      if (j == 2)
        nsave_menu_id = id;
      if (j == 3)
        nsaveas_menu_id = id;
      if (j == 5)
        nexport_menu_SBML = id;
      if (j == 6)
        nexport_menu_MathModel = id;
    }
  mpFileMenu->insertSeparator();
  mpFileMenu->insertItem("&Close", this, SLOT(newDoc()), CTRL + Key_W);
  mpFileMenu->insertItem("&Quit", this, SLOT(slotQuit()), CTRL + Key_Q);

  tools = new QPopupMenu(this);
  menuBar()->insertItem("&Tools", tools);

  tools->insertSeparator();
  tools->insertItem("&Convert to irreversible", this, SLOT(slotConvertToIrreversible()));
  tools->insertSeparator();
  tools->insertItem("Object &Browser", this, SLOT(slotObjectBrowserDialog()), 0, 2);
  this->mShowSlidersMenuEntry = tools->insertItem("Show Sliders", this, SLOT(slotToggleSliders()));
  tools->setItemChecked(this->mShowSlidersMenuEntry, false);
  menuBar()->insertSeparator();

  QPopupMenu * help = new QPopupMenu(this);
  menuBar()->insertItem("&Help", help);

  help->insertItem("Simple &Wizard", this, SLOT(slotTutorialWizard()));
  help->insertSeparator();
  help->insertItem("&About", this, SLOT(about()), Key_F1);
  help->insertItem("About &Qt", this, SLOT(aboutQt()));
  help->insertSeparator();
  help->insertItem("What's &This", this, SLOT(whatsThis()), SHIFT + Key_F1);
}

void CopasiUI3Window::slotObjectBrowserDialog()
{
  if (tools->isItemEnabled(2))
    {
      ObjectBrowserDialog * objectBrowserDialog = new ObjectBrowserDialog(this, 0, false, 1);
      tools->setItemEnabled(2, FALSE);
      objectBrowserDialog->show();
    }
  else
    {
      tools->setItemEnabled(2, TRUE);
    }
}

void CopasiUI3Window::slotTutorialWizard()
{
  WizardDialog* tutorialWizard = new WizardDialog();
  tutorialWizard->setCopasiMainWindow(this);
  tutorialWizard->show();
}

void CopasiUI3Window::slotImportSBML(QString file)
{
  bool success = true;

  ListViews::commit();

  QString SBMLFile;

  if (file == "")
    SBMLFile =
      CopasiFileDialog::getOpenFileName(this, "Open File Dialog",
                                        QString::null, "XML Files (*.xml)",
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

      catch (CCopasiException except)
        {
          success = false;
          setCursor(oldCursor);
          QMessageBox::critical(this, QString("File Error"), QString("Error. Could not import file ") + SBMLFile + QString("!"), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          dataModel->createModel();
        }

      setCursor(oldCursor);

      if (!success)
        {
          QString Message = "Error while loading file " + SBMLFile + QString("!\n\n");
          Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

          QMessageBox::critical(this, QString("File Error"), Message,
                                QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
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
      //  mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nexport_menu_MathModel, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);

      ListViews::switchAllListViewsToWidget(1, "");
    }
  updateTitle();

  mSaveAsRequired = true;
}

void CopasiUI3Window::slotExportSBML()
{
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;
      if (CCopasiDataModel::Global->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName(CCopasiDataModel::Global->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName(CCopasiDataModel::Global->getFileName())
                    + ".xml");

      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          Default,
                                          "XML Files (*.xml)",
                                          "Choose a filename for SBML export.");
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
      if (!dataModel->exportSBML((const char *) tmp.utf8(), true))
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              QMessageBox::critical(this, "Export Error",
                                    CCopasiMessage::getAllMessageText().c_str(),
                                    QMessageBox::Ok | QMessageBox::Default,
                                    QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor);
    }
}

void CopasiUI3Window::slotExportMathModel()
{
  ListViews::commit();

  C_INT32 Answer = QMessageBox::No;
  QString tmp;

  while (Answer == QMessageBox::No)
    {
      QString Default = QString::null;
      if (CCopasiDataModel::Global->getFileName() != "")
        Default
        = FROM_UTF8(CDirEntry::dirName(CCopasiDataModel::Global->getFileName())
                    + CDirEntry::Separator
                    + CDirEntry::baseName(CCopasiDataModel::Global->getFileName())
                    + ".out");

      tmp =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          Default,
                                          "ASCII Files (*.out)",
                                          "Choose a filename for MathModel export.");

      if (!tmp) return;

      if (!tmp.endsWith(".cps") && !tmp.endsWith("."))
        tmp += ".out";

      tmp = tmp.remove(QRegExp("\\.$"));

      Answer = checkSelection(tmp);

      if (Answer == QMessageBox::Cancel) return;
    }

  if (dataModel && tmp)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      if (!dataModel->exportMathModel((const char *) tmp.utf8(), true))
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              QMessageBox::critical(this, "Export Error",
                                    CCopasiMessage::getAllMessageText().c_str(),
                                    QMessageBox::Ok | QMessageBox::Default,
                                    QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      setCursor(oldCursor);
    }
}

void CopasiUI3Window::slotConvertToIrreversible()
{
  CModel* model = CCopasiDataModel::Global->getModel();
  if (!model) return;

  ListViews::commit();
  ListViews::switchAllListViewsToWidget(114, "");

  model->convert2NonReversible();
  ListViews::notify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CopasiUI3Window::slotToggleSliders()
{
  bool isChecked = menuBar()->isItemChecked(mShowSlidersMenuEntry);
  menuBar()->setItemChecked(mShowSlidersMenuEntry, !isChecked);
  this->mpToggleSliderDialogButton->setOn(!isChecked);
  this->sliders->setHidden(isChecked);
}

void CopasiUI3Window::enable_object_browser_menu()
{
  //mpFileMenu->setItemEnabled(nobject_browser, true);
  bobject_browser_open = false;
}

void CopasiUI3Window::disable_object_browser_menu()
{
  //mpFileMenu->setItemEnabled(nobject_browser, false);
  bobject_browser_open = true;
}

DataModelGUI* CopasiUI3Window::getDataModel()
{return dataModel;}

void CopasiUI3Window::listViewsFolderChanged(QListViewItem* item)
{
  C_INT32 id = ((FolderListItem*)item)->getFolder()->getId();
  this->sliders->setCurrentFolderId(id);
}

void CopasiUI3Window::saveFile()
{
  this->slotFileSave();
}

TrajectoryWidget* CopasiUI3Window::getTrajectoryWidget()
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
      while (msg_pending.getNumber() != MCCopasiMessage + 1)
        {
          text += "\n";
          text += FROM_UTF8(msg_pending.getText());
          msg_pending = CCopasiMessage::getLastMessage();
        }

      QMessageBox::warning(this, QString("File Warning"), text,
                           QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
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

  setCaption(FixedTitle + FileName);
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

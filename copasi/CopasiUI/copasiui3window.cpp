/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/copasiui3window.cpp,v $
   $Revision: 1.116 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/05 18:06:06 $
   End CVS Header */

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include "AboutDialog.h"

#include "copasiui3window.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "ObjectBrowserDialog.h"
#include <vector>
#include "utilities/CGlobals.h"
#include "utilities/CCopasiException.h"
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
    gpsFile(),
    msave_button(NULL),
    mpFileMenu(NULL),
    sliders(NULL)

{
  // Set the window caption/title
  closeFlag = 0;
  newFlag = 0;
  QString Title = "COPASI (";
  Title += FROM_UTF8(Copasi->ProgramVersion.getVersion());
  Title += " test version)";
  setCaption(Title);
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  //  mpFileMenu = new QPopupMenu;
  //mpFileMenu->setItemEnabled(nobject_browser, false);
  bobject_browser_open = false;
  mpFileMenu->setItemEnabled(nexport_menu_SBML, false);
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

  this->sliders = new SliderDialog(this, this->dataModel);
  C_INT32 id = ((FolderListItem*)listViews->folders->currentItem())->getFolder().getId();
  this->sliders->setCurrentFolderId(id);

  const COptions::nonOptionType & Files = COptions::getNonOptions();

  if (Files.size())
    slotFileOpen(FROM_UTF8(Files[0]));
  else
    {
      newDoc();
    }

  listViews->switchToOtherWidget(0, "");

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
  ListViews::commit();

  QString tmp = QFileDialog::getSaveFileName(str, "COPASI Files (*.cps)",
                this, "save file dialog",
                "Choose a filename to save under.");

  if (dataModel && tmp)
    {
      if (!tmp.endsWith(".cps") &&
          !tmp.endsWith(".")) tmp += ".cps";

      tmp = tmp.remove(QRegExp("\\.$"));

      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      dataModel->saveModel(tmp.utf8());
      setCursor(oldCursor);

      dataModel->changed(false);

      gpsFile = tmp;
    }
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

  if (dataModel && dataModel->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:                                                    // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:                                                    // Discard clicked or Alt+D pressed
          break;

        case 2:                                                    // Cancel clicked or Escape pressed
          return;
          break;
        }
    }

  ListViews::switchAllListViewsToWidget(0, "");

  if (!dataModel)
    dataModel = new DataModelGUI(); // create the data model

  gpsFile = "";
  dataModel->createModel();
  ListViews::notify(ListViews::MODEL, ListViews::ADD, dataModel->getModel()->getKey());
  if (!bobject_browser_open)
    //mpFileMenu->setItemEnabled(nobject_browser, true);
    mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
  mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  msave_button->setEnabled(true);
  mpFileMenu->setItemEnabled(nsave_menu_id, true);

  ListViews::switchAllListViewsToWidget(1, "");
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

  QString newFile;

  if (file == "")
    newFile = QFileDialog::getOpenFileName(QString::null, "Files (*.gps *.cps)",
                                           this, "open file dialog",
                                           "Choose a file");
  else
    newFile = file;

  // gives the file information to the datamodel to handle it

  if (newFile)
    {
      if (dataModel && dataModel->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                    // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                    // Discard clicked or Alt+D pressed
              break;

            case 2:                                                    // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            dataModel->getModel()->getKey());
        }

      ListViews::switchAllListViewsToWidget(0, "");

      if (!dataModel)
        dataModel = new DataModelGUI; // create a new data model

      gpsFile = newFile;
      QCursor oldCursor = this->cursor();
      this->setCursor(Qt::WaitCursor);

      CCopasiMessage::clearStack();

      try
        {
          success = dataModel->loadModel((const char *)gpsFile.utf8());
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

      if (!dataModel->getModel())
        {
          newDoc();
          gpsFile = newFile;
        }

      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        dataModel->getModel()->getKey());

      //if (!bobject_browser_open)
      //  mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);

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

  if (gpsFile.isEmpty())
    {
      slotFileSaveAs();
      return;
    }

  std::ifstream File(gpsFile.utf8());
  std::string Line;
  File >> Line;
  File.close();

  int choice = 0;

  if (!Line.compare(0, 8, "Version=") || gpsFile.endsWith(".gps"))
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
          slotFileSaveAs(gpsFile.replace(QRegExp("\\.gps$"), ".cps"));
          return;
        }
    }

  if (dataModel)
    {
      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      dataModel->saveModel(gpsFile.utf8());
      setCursor(oldCursor);

      dataModel->changed(false);
    }
}

void CopasiUI3Window::slotQuit()
{
  ListViews::commit();

  if (dataModel && dataModel->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:                                                    // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:                                                    // Discard clicked or Alt+D pressed
          break;

        case 2:                                                    // Cancel clicked or Escape pressed
          return;
          break;
        }
    }

  closeFlag = 1;

  qApp->quit();
}

void CopasiUI3Window::closeEvent(QCloseEvent* C_UNUSED(ce))
{
  if (closeFlag == 0)
    {
      if (dataModel && dataModel->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                    // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                    // Discard clicked or Alt+D pressed
              break;

            case 2:                                                    // Cancel clicked or Escape pressed
              return;
              break;
            }
        }
      qApp->quit();
    }
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
  QString Title = "COPASI (";
  Title += FROM_UTF8(Copasi->ProgramVersion.getVersion());
  Title += ")";
  AboutDialog* aboutDialog = new AboutDialog(this);
  aboutDialog->setCaption(Title);
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
  const int numofIcons = 3;

  // put something in it
  QPixmap icon[numofIcons ] = {filenew, fileopen, filesave};
  const char* iconName[numofIcons ] = {"New", "Open", "Save"};
  const char* slotFileName[numofIcons ] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave())};

  const char* toolTip[numofIcons ];

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

  QToolButton* toolb;
  int j;
  for (j = 0; j < numofIcons; j++)
    {
      toolb = new QToolButton(icon[j], iconName[j], QString::null,
                              this, slotFileName[j], tbMain);

      QWhatsThis::add(toolb, toolTip[j]);

      if (j == numofIcons - 1)
        msave_button = toolb;
    }

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
  QPixmap icon[7] = {filenew, fileopen, filesave, filesave, fileopen, filesave, fileopen};
  const char* toolTip[8];

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

  const char* iconName[6] = {"&New", "&Open", "&Save", "Save&As", "&Import SBML", "&Export SBML"};
  const char* slotFileName[6] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFileSaveAs()), SLOT(slotImportSBML()), SLOT(slotExportSBML())};
  QKeySequence hotKey[6] = {CTRL + Key_N, CTRL + Key_O, CTRL + Key_S, CTRL + Key_A, CTRL + Key_I, CTRL + Key_E};
  int fileSeparator[6] = {0, 0, 0, 0, 0, 0};

  mpFileMenu = new QPopupMenu(this);
  menuBar()->insertItem("&File", mpFileMenu);
  int j;
  for (j = 0; j < 6; j++)
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

void CopasiUI3Window::slotImportSBML()
{
  bool success = true;

  ListViews::commit();

  QString SBMLFile = QFileDialog::getOpenFileName(
                       QString::null, "XML Files (*.xml)",
                       this, "import file dialog",
                       "Choose a file");

  if (SBMLFile)
    {
      if (dataModel && dataModel->isChanged())
        {
          switch (QMessageBox::information(this, "COPASI",
                                           "The document contains unsaved changes\n"
                                           "Do you want to save the changes before exiting?",
                                           "&Save", "&Discard", "Cancel", 0, 2))
            {
            case 0:                                                    // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:                                                    // Discard clicked or Alt+D pressed
              break;

            case 2:                                                    // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            dataModel->getModel()->getKey());
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
        }

      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        dataModel->getModel()->getKey());

      //if (!bobject_browser_open)
      //  mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);

      ListViews::switchAllListViewsToWidget(1, "");
    }
}

void CopasiUI3Window::slotExportSBML()
{
  ListViews::commit();

  QString tmp = QFileDialog::getSaveFileName(
                  QString::null, "XML Files (*.xml)",
                  this, "export file dialog",
                  "Choose a filename for SBML export.");
  if (dataModel && tmp)
    {
      if (!tmp.endsWith(".xml") && !tmp.endsWith("."))
        tmp += ".xml";

      tmp = tmp.remove(QRegExp("\\.$"));

      QCursor oldCursor = cursor();
      setCursor(Qt::WaitCursor);
      dataModel->exportSBML(tmp.utf8());
      setCursor(oldCursor);
    }
}

void CopasiUI3Window::slotConvertToIrreversible()
{
  CModel* model = dataModel->getModel();
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
  C_INT32 id = ((FolderListItem*)item)->getFolder().getId();
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

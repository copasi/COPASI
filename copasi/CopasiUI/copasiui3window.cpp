/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/copasiui3window.cpp,v $
   $Revision: 1.70 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/11 14:50:37 $
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

#include "copasiui3window.h"
#include "listviews.h"
#include "ObjectBrowser.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CGlobals.h" 
//#include "output/COutputList.h"
//#include "output/COutput.h"
#include "model/CModel.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"
#include "qtUtilities.h"

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
    splitter(NULL),
    listViews(NULL),
    gpsFile(),
    msave_button(NULL),
    mpFileMenu(NULL)
{
  // Set the window caption/title
  closeFlag = 0;
  newFlag = 0;

  QString Title = "COPASI (";
  Title += FROM_UTF8(Copasi->ProgramVersion.getVersion());
  Title += ")";
  setCaption(Title);
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  //  mpFileMenu = new QPopupMenu;
  mpFileMenu->setItemEnabled(nobject_browser, false);
  bobject_browser_open = false;
  mpFileMenu->setItemEnabled(nexport_menu_SBML, false);
  mpFileMenu->setItemEnabled(nsave_menu_id, false);
  mpFileMenu->setItemEnabled(nsaveas_menu_id, false);
  msave_button->setEnabled(false);

  if (!dataModel)
    {
      // create the data model
      dataModel = new DataModel();

      splitter = new QSplitter(QSplitter::Vertical, this , "main");
      splitter->show();
      this->setCentralWidget(splitter);
    }

  listViews = new ListViews(splitter);
  listViews->setDataModel(dataModel);
  listViews->show();

  const COptions::nonOptionType & Files = COptions::getNonOptions();
  if (Files.size())
    slotFileOpen(FROM_UTF8(Files[0]));
  else
    newDoc();

  // ListViews::notify(ListViews::FUNCTION, ListViews::ADD, "");
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

      dataModel->saveModel(tmp.utf8());
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
        case 0:      // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:      // Discard clicked or Alt+D pressed
          break;

        case 2:      // Cancel clicked or Escape pressed
          return;
          break;
        }
    }

  if (!dataModel)
    dataModel = new DataModel(); // create the data model

  gpsFile = "";
  dataModel->createModel();
  ListViews::notify(ListViews::MODEL, ListViews::ADD, dataModel->getModel()->getKey());
  if (!bobject_browser_open)
    mpFileMenu->setItemEnabled(nobject_browser, true);
  mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
  mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
  msave_button->setEnabled(true);
  mpFileMenu->setItemEnabled(nsave_menu_id, true);
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
  ListViews::commit();

  QString newFile;
  int choice = 0;

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
            case 0:      // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:      // Discard clicked or Alt+D pressed
              break;

            case 2:      // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            dataModel->getModel()->getKey());
        }

      if (!dataModel)
        dataModel = new DataModel; // create a new data model

      gpsFile = newFile;

      dataModel->loadModel((const char *)gpsFile.utf8());
      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        dataModel->getModel()->getKey());

      if (!bobject_browser_open)
        mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);
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
      dataModel->saveModel(gpsFile.utf8());
      dataModel->changed(false);
    }
}

void CopasiUI3Window::slotQuit()
{
  ListViews::commit();

  int choice = 0;

  if (dataModel && dataModel->isChanged())
    {
      switch (QMessageBox::information(this, "COPASI",
                                       "The document contains unsaved changes\n"
                                       "Do you want to save the changes before exiting?",
                                       "&Save", "&Discard", "Cancel", 0, 2))
        {
        case 0:      // Save clicked or Alt+S pressed or Enter pressed.
          slotFileSave();
          break;

        case 1:      // Discard clicked or Alt+D pressed
          break;

        case 2:      // Cancel clicked or Escape pressed
          return;
          break;
        }
    }

  closeFlag = 1;

  qApp->quit();
}

void CopasiUI3Window::closeEvent(QCloseEvent* ce)
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
            case 0:      // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:      // Discard clicked or Alt+D pressed
              break;

            case 2:      // Cancel clicked or Escape pressed
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
  QMessageBox::about(this, Title,
                     "It is a Biochemical path simulator for complex pathways");
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

  // put something in it
  QPixmap icon[2] = {fileopen, filesave};
  const char* iconName[2] = {"Open", "Save"};
  const char* slotFileName[2] = {SLOT(slotFileOpen()), SLOT(slotFileSave())};

  const char* toolTip[2];

  toolTip[0] = "Click this button to open a <em>new file</em>. <br>"
               "You can also select the <b>Open</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[1] = "<p>Click this button to save the file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Save</b> command "
               "from the <b>File</b> menu.</p>";

  QToolButton* toolb;
  int j;
  for (j = 0; j < 2; j++)
    {
      toolb = new QToolButton(icon[j], iconName[j], QString::null,
                              this, slotFileName[j], tbMain);

      QWhatsThis::add(toolb, toolTip[j]);

      if (j == 1)
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
  QPixmap icon[7] = {fileopen, fileopen, filesave, filesave, fileopen, filesave, fileopen};
  const char* toolTip[8];

  toolTip[0] = "Click this button to open a <em>new file</em>. <br>"
               "You can also select the <b>Open</b> command "
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

  const char* iconName[7] = {"&New", "&Open", "&Save", "Save&As", "&Import SBML", "&Export SBML", "Object &Browser"};
  const char* slotFileName[7] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFileSaveAs()), SLOT(slotImportSBML()), SLOT(slotExportSBML()), SLOT(slotObjectBrowser())};
  QKeySequence hotKey[7] = {CTRL + Key_N, CTRL + Key_O, CTRL + Key_S, CTRL + Key_A, CTRL + Key_I, CTRL + Key_E, CTRL + Key_B};
  int fileSeperator[7] = {0, 0, 0, 0, 0, 0, 1};

  mpFileMenu = new QPopupMenu(this);
  menuBar()->insertItem("&File", mpFileMenu);
  int j;
  for (j = 0; j < 7; j++)
    {
      if (fileSeperator[j] == 1)
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
      if (j == 7)
        nobject_browser = id;
    }

  mpFileMenu->insertSeparator();
  mpFileMenu->insertItem("&Close", this, SLOT(slotQuit()), CTRL + Key_W);
  mpFileMenu->insertItem("&Quit", this, SLOT(slotQuit()), CTRL + Key_Q);
  //mpFileMenu->insertItem("&Quit", qApp, SLOT(closeAllWindows()), CTRL + Key_Q);

  menuBar()->insertSeparator();

  QPopupMenu * help = new QPopupMenu(this);
  menuBar()->insertItem("&Help", help);

  help->insertItem("&About", this, SLOT(about()), Key_F1);
  help->insertItem("About &Qt", this, SLOT(aboutQt()));
  help->insertSeparator();
  help->insertItem("What's &This", this, SLOT(whatsThis()), SHIFT + Key_F1);
}

void CopasiUI3Window::slotObjectBrowser()
{
  ObjectBrowser* objectBrowser = new ObjectBrowser(this);
  objectBrowser->show();
}

void CopasiUI3Window::slotImportSBML()
{
  ListViews::commit();

  QString SBMLFile = QFileDialog::getOpenFileName(
                       QString::null, "SBML Files (*.sbml *.xml)",
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
            case 0:      // Save clicked or Alt+S pressed or Enter pressed.
              slotFileSave();
              break;

            case 1:      // Discard clicked or Alt+D pressed
              break;

            case 2:      // Cancel clicked or Escape pressed
              return;
              break;
            }

          ListViews::notify(ListViews::MODEL, ListViews::DELETE,
                            dataModel->getModel()->getKey());
        }

      if (!dataModel)
        {
          dataModel = new DataModel; // create a new data model
        }

      dataModel->importSBML((const char *)SBMLFile.utf8());
      ListViews::notify(ListViews::MODEL, ListViews::ADD,
                        dataModel->getModel()->getKey());

      if (!bobject_browser_open)
        mpFileMenu->setItemEnabled(nobject_browser, true);
      mpFileMenu->setItemEnabled(nexport_menu_SBML, true);
      mpFileMenu->setItemEnabled(nsaveas_menu_id, true);
      msave_button->setEnabled(true);
      mpFileMenu->setItemEnabled(nsave_menu_id, true);
    }
}

void CopasiUI3Window::slotExportSBML()
{
  ListViews::commit();

  QString SBMLFile = QFileDialog::getSaveFileName(
                       QString::null, "SBML Files (*.sbml)",
                       this, "export file dialog",
                       "Choose a file");
  if (gpsFile && SBMLFile)
    {
      std::ofstream outputfile((const char *)SBMLFile.utf8());
      dataModel->getModel()->saveSBML(outputfile);
    }
}

void CopasiUI3Window::enabled_object_browser_menu()
{
  mpFileMenu->setItemEnabled(nobject_browser, true);
  bobject_browser_open = false;
}

void CopasiUI3Window::disable_object_browser_menu()
{
  mpFileMenu->setItemEnabled(nobject_browser, false);
  bobject_browser_open = true;
}

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>

#include "copasiui3window.h"
#include "listviews.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"

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
CopasiUI3Window::CopasiUI3Window(QWidget* parent, const char* name, WFlags f)
    : QMainWindow(parent, name, f)
{
  // Set the window caption/title
  setCaption("Copasi ");
  createToolBar(); // creates a tool bar
  createMenuBar();  // creates a menu bar
  file->setItemEnabled(nexport_menu_SBML, false);
  file->setItemEnabled(nsave_menu_id, false);
  file->setItemEnabled(nsaveas_menu_id, false);
  msave_button->setEnabled(false);
  dataModel = NULL; // the datamodel tobe used
  splitter = NULL;  // the splittler for sepearting diff views

  resize(766, 400); // to resize the screen..to fit this size

  if (!dataModel) // if the datamodel doesnot exist than this is done for the first time only
    {
      // QString fileName = QFileDialog::getOpenFileName(QString::null, "*.txt",this, "open file dialog",
      //"Choose a file");
      QString fileName = "DataModel.txt";

      if (fileName)
        {
          // create the data model
          dataModel = new DataModel<Folder>((char *)fileName.ascii());

          splitter = new QSplitter(QSplitter::Vertical, this , "main");
          splitter->show();
          this->setCentralWidget(splitter);
        }
    }

  if (dataModel)
    {
      listViews = new ListViews(splitter);
      listViews->setDataModel(dataModel);
      listViews->show();
    }
}

/***************CopasiUI3Window::slotFileSaveAs()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File 
 *******************************************************************************************/
void CopasiUI3Window::slotFileSaveAs()
{
  gpsFile = QFileDialog::getSaveFileName(
              QString::null, "GPS Files (*.gps)",
              this, "save file dialog",
              "Choose a file");

  if (dataModel && gpsFile)
    {
      gpsFile += ".gps";
      dataModel->saveModel((const char *)gpsFile.utf8());
      //the below are to reopen the file and created the relative objects
      dataModel->loadModel((const char *)gpsFile.utf8());
      CReadConfig inbuf((const char *)gpsFile.utf8());
      if (inbuf.getVersion() < "4.0")
        {
          msave_button->setEnabled(false);
          file->setItemEnabled(nsave_menu_id, false);
        }
      else
        {
          msave_button->setEnabled(true);
          file->setItemEnabled(nsave_menu_id, true);
        }
    }
} //cout<<"it comes in filesave as...";}

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
  // this one creates one more view of the same code
  // and assigns only one dataModel to all the views
  // hence maintaning doc/view architecture

  /* if (!dataModel) // if the datamodel doesnot exist than this is done for the first time only
     {
       // QString fileName = QFileDialog::getOpenFileName(QString::null, "*.txt",this, "open file dialog",
       //"Choose a file");
       QString fileName = "DataModel.txt";

       if (fileName)
         {
           dataModel = new DataModel<Folder>((char *)fileName.ascii()); // create the data model
           splitter = new QSplitter(QSplitter::Vertical, this , "main");
           splitter->show();
           this->setCentralWidget(splitter);
         }
     }

   if (dataModel)
     {
       listViews = new ListViews(splitter);
       listViews->setDataModel(dataModel);
       listViews->show();
     }*/
}

/***************CopasiUI3Window::slotFileOpen()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File 
 *******************************************************************************************/
void CopasiUI3Window::slotFileOpen()
{
  gpsFile = QFileDialog::getOpenFileName(
              QString::null, "GPS Files (*.gps)",
              this, "open file dialog",
              "Choose a file");
  // gives the file information to the datamodel to handle it

  if (dataModel && gpsFile)
    {
      dataModel->loadModel((const char *)gpsFile.utf8());
      CReadConfig inbuf((const char *)gpsFile.utf8());
      if (inbuf.getVersion() < "4.0")
        {
          msave_button->setEnabled(false);
          file->setItemEnabled(nsave_menu_id, false);
        }
      else
        {
          msave_button->setEnabled(true);
          file->setItemEnabled(nsave_menu_id, true);
        }
      file->setItemEnabled(nexport_menu_SBML, true);
      file->setItemEnabled(nsaveas_menu_id, true);
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
  if (dataModel && gpsFile)
    {
      dataModel->saveModel((const char *)gpsFile.utf8());
      //the below are to reopen the file and created the relative objects
      dataModel->loadModel((const char *)gpsFile.utf8());
      CReadConfig inbuf((const char *)gpsFile.utf8());
      if (inbuf.getVersion() < "4.0")
        {
          msave_button->setEnabled(false);
          file->setItemEnabled(nsave_menu_id, false);
        }
      else
        {
          msave_button->setEnabled(true);
          file->setItemEnabled(nsave_menu_id, true);
        }
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
  QMessageBox::about(this, "COPASI HELP",
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
  QPixmap icon[3] = {fileopen, filesave, fileprint};
  const char* iconName[3] = {"Open", "Save", "Print"};
  const char* slotFileName[3] = {SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFilePrint())};

  const char* toolTip[3];

  toolTip[0] = "Click this button to open a <em>new file</em>. <br>"
               "You can also select the <b>Open</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[1] = "<p>Click this button to save the file you "
               "are editing. You will be prompted for a file name.\n"
               "You can also select the <b>Save</b> command "
               "from the <b>File</b> menu.</p>";

  toolTip[2] = "Click this button to print the file you "
               "are editing.\n You can also select the Print "
               "command from the File menu.";

  QToolButton* toolb;

  for (int j = 0; j < 3; j++)
    {
      toolb = new QToolButton(icon[j], iconName[j], QString::null,
                              this, slotFileName[j], tbMain);

      QWhatsThis::add
      (toolb, toolTip[j]);

      if (j == 1)
        msave_button = toolb;
    }

  toolb = QWhatsThis::whatsThisButton(tbMain);

  QWhatsThis::add
  (toolb, "This is a <b>What's This</b> button "
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
  QPixmap icon[7] = {fileopen, fileopen, filesave, filesave, fileopen, filesave, fileprint};
  const char* toolTip[7];

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

  toolTip[6] = "Click this button to print the file you "
               "are editing.\n You can also select the Print "
               "command from the File menu.";

  const char* iconName[7] = {"&New", "&Open", "&Save", "&SaveAs", "&Import SBML", "&Export SBML", "&Print"};
  const char* slotFileName[7] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFileSaveAs()), SLOT(slotImportSBML()), SLOT(slotExportSBML()), SLOT(slotFilePrint())};
  QKeySequence hotKey[7] = {CTRL + Key_N, CTRL + Key_O, CTRL + Key_S, CTRL + Key_A, CTRL + Key_I, CTRL + Key_E, CTRL + Key_P};
  int fileSeperator[7] = {0, 0, 0, 0, 0, 0, 1};

  file = new QPopupMenu(this);
  menuBar()->insertItem("&File", file);

  for (int j = 0; j < 7; j++)
    {
      if (fileSeperator[j] == 1)
        file->insertSeparator();

      int id;

      id = file->insertItem(icon[j], iconName[j],
                            this, slotFileName[j], hotKey[j]);

      file->setWhatsThis(id, toolTip[j]);
      if (j == 2)
        nsave_menu_id = id;
      if (j == 3)
        nsaveas_menu_id = id;
      if (j == 5)
        nexport_menu_SBML = id;
    }

  file->insertSeparator();
  file->insertItem("&Close", this, SLOT(close()), CTRL + Key_W);
  file->insertItem("&Quit", qApp, SLOT(closeAllWindows()), CTRL + Key_Q);

  menuBar()->insertSeparator();

  QPopupMenu * help = new QPopupMenu(this);
  menuBar()->insertItem("&Help", help);

  help->insertItem("&About", this, SLOT(about()), Key_F1);
  help->insertItem("About &Qt", this, SLOT(aboutQt()));
  help->insertSeparator();
  help->insertItem("What's &This", this, SLOT(whatsThis()), SHIFT + Key_F1);
}

void CopasiUI3Window::slotImportSBML()
{
  QString SBMLFile = QFileDialog::getOpenFileName(
                       QString::null, "SBML Files (*.sbml)",
                       this, "import file dialog",
                       "Choose a file");

  if (SBMLFile)
    {
      CReadConfig inbuf((const char *)SBMLFile.utf8());
    }
}

void CopasiUI3Window::slotExportSBML()
{
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

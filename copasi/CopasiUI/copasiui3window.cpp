
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

  dataModel = NULL; // the datamodel tobe used
  splitter = NULL;  // the splittler for sepearting diff views

  resize(766, 400); // to resize the screen..to fit this size
}

/***************CopasiUI3Window::slotFileSaveAs()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File 
 *******************************************************************************************/
void CopasiUI3Window::slotFileSaveAs(){} //cout<<"it comes in filesave as..."; }

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

  if (!dataModel) // if the datamodel doesnot exist than this is done for the first time only
    {
      QString fileName = QFileDialog::getOpenFileName(
                           QString::null, "sample.txt",
                           this, "open file dialog",
                           "Choose a file");
      //QString fileName="sample.txt";

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
    }
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
  QString gpsFile = QFileDialog::getOpenFileName(
                      QString::null, "GPS Files (*.gps)",
                      this, "open file dialog",
                      "Choose a file");
  // gives the file information to the datamodel to handle it

  if (dataModel && gpsFile)
    dataModel->loadModel((const char *)gpsFile.utf8());
}

/***************CopasiUI3Window::slotFileSave()*****************
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is called when the users clicks on the save as 
 **              option in the menu File and it is used to save the document information
 *******************************************************************************************/
void CopasiUI3Window::slotFileSave()
{}

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
  QMessageBox::about(this, "Qt Application Example",
                     "This example demonstrates simple use of "
                     "QMainWindow,\nQMenuBar and QToolBar.");
}

/***************CopasiUI3Window::aboutQt()******
 **
 ** Parameters:- Void
 ** Returns  :- void
 ** Descripton:- This method is help about the QT application
 *******************************************************************************************/
void CopasiUI3Window::aboutQt()
{
  QMessageBox::aboutQt(this, "Qt Application Example");
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
  QPixmap icon[5] = {fileopen, fileopen, filesave, filesave, fileprint};
  const char* toolTip[5];

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

  toolTip[4] = "Click this button to print the file you "
               "are editing.\n You can also select the Print "
               "command from the File menu.";
  const char* iconName[5] = {"&New", "&Open", "&Save", "&SaveAs", "&Print"};
  const char* slotFileName[5] = {SLOT(newDoc()), SLOT(slotFileOpen()), SLOT(slotFileSave()), SLOT(slotFileSaveAs()), SLOT(slotFilePrint())};
  QKeySequence hotKey[5] = {CTRL + Key_N, CTRL + Key_O, CTRL + Key_S, CTRL + Key_A, CTRL + Key_P};
  int fileSeperator[5] = {0, 0, 0, 0, 1};

  QPopupMenu * file = new QPopupMenu(this);
  menuBar()->insertItem("&File", file);

  for (int j = 0; j < 5; j++)
    {
      if (fileSeperator[j] == 1)
        file->insertSeparator();

      int id;

      id = file->insertItem(icon[j], iconName[j],
                            this, slotFileName[j], hotKey[j]);

      file->setWhatsThis(id, toolTip[j]);
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

/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiFileDialog.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/08/23 00:48:48 $
   End CVS Header */

#include <qapplication.h>
#include <qlayout.h>
#include <qbuttongroup.h>
#include <qpixmap.h>
#include <qimage.h>

#include "copasi.h"

#include "commandline/COptions.h"
#include "CopasiFileDialog.h"
#include "qtUtilities.h"

static const char* const home_data[] =
  {
    "31 30 51 1",
    "g c #040205",
    "x c #0b2a34",
    "f c #0c280b",
    "o c #2d2914",
    "e c #2d2d2e",
    "W c #2e4b54",
    "B c #2f0809",
    "O c #363848",
    "k c #473631",
    "z c #4c1813",
    "F c #4f2c13",
    "h c #555553",
    "v c #655169",
    "N c #6a2d0a",
    "y c #6a5951",
    "r c #6c6f6c",
    "n c #7b7d89",
    "q c #7e7b77",
    "C c #837a58",
    "j c #848284",
    "K c #865127",
    "S c #8bb0cb",
    "p c #8ca79f",
    "J c #8da9b5",
    "Q c #9b551e",
    "I c #a06638",
    "U c #a52a26",
    "G c #a96f55",
    "M c #ac6a30",
    "m c #ac9eb0",
    "l c #b1aa92",
    ". c #b7b7b6",
    "b c #bbc3c5",
    "c c #bbc4b9",
    "a c #c4c2c4",
    "# c #c5c3bb",
    "d c #c7bcc7",
    "w c #c8bcba",
    "T c #c9874f",
    "A c #ceb494",
    "P c #d07b20",
    "L c #d0ad72",
    "i c #d5d6d2",
    "t c #d5d8ed",
    "H c #e7b08c",
    "V c #ead9ce",
    "D c #efd5b7",
    "R c #f7d3f2",
    "s c #f8f3d4",
    "E c #fad496",
    "u c #fcfefc",
    ".#a.#a.#ba.#a##aaaa.aac.aaba.ac",
    "ab.aabab.a#bda.baaaca.aba.a.cba",
    ".aab#a.#a#a.aab#.aa.aaaaaa#ba#.",
    "aa.a.aaa.aaaa.#b#aaaa.a.aaa.ab#",
    "b#aaaa.aaaa.aaba.a.baaaac.aaaa.",
    ".ab.aab#.b.aab.#aaaa.caaaaa.aaa",
    "b.a#aa.ab#aaaaef.a.aaaa.a.aaaaa",
    "#ab.aaaa.afgahijkbaba.cbaaa.a.c",
    "a.aac.aaaaeghclmnea.aa.#c.aaaba",
    "ba#ba#a.##ohpjhhhneaaaabdcaa.#.",
    "aaa.a.abadh.nq.mhhjf.aa.#b.a#ba",
    "a.aab#b.aharqmstihhje.#ab#ba.aa",
    "b#b#a.#aharrmuuutmvhno#a.#.aaaa",
    ".a.abaah.qh.usuuuulhhjfdaab.#.a",
    "aaa#a.#woxmtu.yzAuiAfBdaa.a#aaa",
    ".ca.aab#aemiuCDEFuimeaa.aa#.b.a",
    "a.aab#a.ae.iuGHIFuiJobaaa.ba#aa",
    "baa.a.aaakmiuKLMNuimeaaaaa#.aa.",
    "aaaaaaaabO.isKPQFuRSo#b.a.ba.b#",
    "a.aa.a.#.kpiuKTQNsiledbaaaa#ba.",
    "aabaaaabbkmiDzKUFVtmfba.aaa.baa",
    "a.a.caa.abWOeFoooeoeedaba.aa#.a",
    "aaaaa.babadddadadddddaa.b#b#baa",
    "a.caaaa.abadad#.aabba.aa#.a.aaa",
    "aba.a.baaa.ba.aaa.a.aaa.baaa.aa",
    "aaaaaaa.abaabaa.aa#a#.aa#.abaaa",
    "aa.aa.b#a.ada.aaa.ba.aaaaaaaaa.",
    "aaaa.a#b.aaaaaaaa#a.aba.aa.ab.b",
    "ba.aca.aaaaa.aa.b.#baaac.aaaaaa",
    "a.cabacaa.aaa.ca#ab.#.b#ba.a.ca"
  };

static const char* const example_data[] =
  {
    "27 25 43 1",
    "e c #040205",
    "O c #08082f",
    "D c #0a160d",
    "n c #0c280b",
    "E c #134c53",
    "g c #2d2914",
    "m c #2d2d2e",
    "C c #2d676b",
    "G c #2e4b54",
    "o c #473631",
    "B c #486d51",
    "F c #51716e",
    "f c #555553",
    "N c #568f50",
    "x c #5c7884",
    "k c #6a5951",
    "q c #6b6555",
    "z c #6c6f6c",
    "H c #6e8576",
    "M c #708688",
    "r c #70a095",
    "y c #7b7d89",
    "u c #7e7b77",
    "w c #837a58",
    "l c #8ca79f",
    "I c #94875e",
    "h c #959898",
    "K c #ace2cc",
    "J c #b1aa92",
    "a c #b7b7b6",
    "# c #bbc3c5",
    "b c #bbc4b9",
    ". c #c4c2c4",
    "c c #c5c3bb",
    "v c #c6c691",
    "i c #c7bcc7",
    "d c #c8bcba",
    "A c #ceb494",
    "L c #d5d6d2",
    "t c #ead9ce",
    "s c #efd5b7",
    "p c #f8f3d4",
    "j c #fcfefc",
    "..#a..........a#a...a..a...",
    ".....ab.a.ab.a....ab..#....",
    "..a..b..#b.ac#..ba....a.a.b",
    "....a#.ac#..#a.accdab......",
    "#.a.c#ec.a.ac.c.fgdb..ba.a#",
    ".ab#.ehfgi..c.fgjkdc.a#c...",
    "....#elkjmcdnopjjqdc..a#ba.",
    "b.a.#erkjjggstjjjud...c.#c.",
    "..c##elkjjjkvttjjweee#.a.a.",
    "a#..#exyjjjzAtjjjutBeb#.c#.",
    ".ca##erfjjpuApsjjutCD#a..a.",
    "..#c#exujsjwttpjjwjEe#.....",
    "..a.#eFqptpwvsjjjwpGe##a..a",
    "a.#c#eFHsppwstpjjIjEe.#c...",
    "..a##DBHbp.wvtpJuJtBD#.a#.a",
    "b..ca#ezHsswtAwAJAjGe##c...",
    ".a....#exuvwJuv.KjLBe#...a.",
    "...a...#eFMHNxBFzBFCe#.ab..",
    ".a.......eFGBeeODOeee#.....",
    "...#a.a###eeeb.####bb..a.#a",
    ".ba..c#c.c....##....b..ba..",
    "....a#a.a.#c#ica....a#.....",
    "..a.#c..#..ac.a...a..ca.ba.",
    "ab#ca..a...#.#..ab#........",
    "#.a.....ca.aca...a..a.a..a."
  };

void CopasiFileDialog::addLocation(QWidget* w)
{
  addLeftWidget(w);
}

CopasiFileDialog::CopasiFileDialog(QWidget * parent , const char * name , bool modal)
    : QFileDialog(parent , name , modal)
{
  const C_INT32 width = 30, length = 30;

  QButtonGroup * grp = new QButtonGroup(this);

  exampleDirButton = new QPushButton("Examples directory", grp, "exampleDirButton");
  QImage example_img((const char **) example_data);
  exampleDirButton->setPixmap(example_img);

  homeDirButton = new QPushButton("home directory", grp, "homeDirButton");
  directoryValue = new QDir();
  QImage home_img((const char **) home_data);
  homeDirButton->setPixmap(home_img);

  /*
  copasiDirButton = new QPushButton("copasi directory", grp, "copasiDirButton");
  QImage copasiDirImage;
  copasiDirImage.load("./icons/copasi_icon_small.png");
  QPixmap * copasiDirPixmap = new QPixmap(copasiDirImage.scale(width, length));
  copasiDirButton->setPixmap(*copasiDirPixmap);
  */
  QVBoxLayout *layout = new QVBoxLayout(grp);

  QSpacerItem * spacer = new QSpacerItem(width, 50);

  layout->setMargin(2);

  layout->addWidget(exampleDirButton);
  layout->addWidget(homeDirButton);
  //  layout->addWidget(copasiDirButton);
  layout->addItem(spacer);

  addLocation(grp);

  connect(exampleDirButton, SIGNAL(pressed()), this, SLOT(slotExampleDir()));
  connect(homeDirButton, SIGNAL(pressed()), this, SLOT(slotHomeDir()));
  //  connect(copasiDirButton, SIGNAL(pressed()), this, SLOT(slotCopasiDir()));
}

void CopasiFileDialog::slotExampleDir()
{
  std::string exampleDir;
  COptions::getValue("ExampleDir", exampleDir);
  QString examplePath = exampleDir.c_str();
  if (directoryValue->exists(examplePath))
    {
      setDir(FROM_UTF8(exampleDir));
    }
  else
    {
      QMessageBox::warning(this, "Directory Not Found", examplePath, QMessageBox::Ok, 0);
      exampleDirButton->setDown(false);
    }
}

void CopasiFileDialog::slotHomeDir()
{
  std::string homeDir;
  COptions::getValue("Home", homeDir);
  QString homePath = homeDir.c_str();
  if (directoryValue->exists(homePath))
    {
      setDir(FROM_UTF8(homeDir));
    }
  else
    {
      QMessageBox::warning(this, "Directory Not Found", homePath, QMessageBox::Ok, 0);
      homeDirButton->setDown(false);
    }
}

void CopasiFileDialog::slotCopasiDir()
{
  std::string CopasiDir;
  COptions::getValue("CopasiDir", CopasiDir);
  setDir(FROM_UTF8(CopasiDir));
}

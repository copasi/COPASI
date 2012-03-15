// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/resourcesUI/CQIconResource.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/15 17:01:30 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQIconResource.cpp
 *
 *  Created on: Mar 12, 2012
 *      Author: shoops
 */

#include "CQIconResource.h"

#define LOAD_ICON(_id, _name) \
  Icons[ _id ].addFile(QString::fromUtf8(":/images/" #_name ".png"), QSize(), QIcon::Normal, QIcon::On)

// static
bool CQIconResource::needInit(true);

// static
QVector< QIcon > CQIconResource::Icons;

void CQIconResource::init()
{
  if (!needInit) return;

  Q_INIT_RESOURCE(copasi);

  Icons.resize(_size);

  Icons[captureImage].addFile(QString::fromUtf8(":/images/captureImage.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[copasi].addFile(QString::fromUtf8(":/images/copasi.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[checkMark].addFile(QString::fromUtf8(":/images/checkMark.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[edit].addFile(QString::fromUtf8(":/images/edit.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[editAdd].addFile(QString::fromUtf8(":/images/editAdd.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[editCopy].addFile(QString::fromUtf8(":/images/editCopy.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[editDelete].addFile(QString::fromUtf8(":/images/editDelete.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileExport].addFile(QString::fromUtf8(":/images/fileExport.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileNew].addFile(QString::fromUtf8(":/images/fileNew.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileOpen].addFile(QString::fromUtf8(":/images/fileOpen.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[filePrint].addFile(QString::fromUtf8(":/images/filePrint.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileSave].addFile(QString::fromUtf8(":/images/fileSave.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileSaveas].addFile(QString::fromUtf8(":/images/fileSaveas.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[locked].addFile(QString::fromUtf8(":/images/locked.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[moveDown].addFile(QString::fromUtf8(":/images/moveDown.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[moveUp].addFile(QString::fromUtf8(":/images/moveUp.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[playerKill].addFile(QString::fromUtf8(":/images/playerKill.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[playerPause].addFile(QString::fromUtf8(":/images/playerPause.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[playerStart].addFile(QString::fromUtf8(":/images/playerStart.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[playerStop].addFile(QString::fromUtf8(":/images/playerStop.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[preferences].addFile(QString::fromUtf8(":/images/preferences.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[reactionModifier].addFile(QString::fromUtf8(":/images/reactionModifier.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[reactionProduct].addFile(QString::fromUtf8(":/images/reactionProduct.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[reactionSubstrate].addFile(QString::fromUtf8(":/images/reactionSubstrate.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[renderMarkup].addFile(QString::fromUtf8(":/images/renderMarkup.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[renderMathML].addFile(QString::fromUtf8(":/images/renderMathML.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[separator].addFile(QString::fromUtf8(":/images/separator.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[slider].addFile(QString::fromUtf8(":/images/slider.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[tool].addFile(QString::fromUtf8(":/images/tool.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[unlocked].addFile(QString::fromUtf8(":/images/unlocked.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[zoomOut].addFile(QString::fromUtf8(":/images/zoomOut.png"), QSize(), QIcon::Normal, QIcon::On);

  needInit = false;
}

// static
const QIcon & CQIconResource::icon(const CQIconResource::IconID & id)
{
  init();

  if (id < _size)
    return Icons[id];

  return Icons[unknown];
}



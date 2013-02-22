// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
  Icons[fileAdd].addFile(QString::fromUtf8(":/images/fileAdd.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileExport].addFile(QString::fromUtf8(":/images/fileExport.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileNew].addFile(QString::fromUtf8(":/images/fileNew.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileOpen].addFile(QString::fromUtf8(":/images/fileOpen.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[filePrint].addFile(QString::fromUtf8(":/images/filePrint.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileSave].addFile(QString::fromUtf8(":/images/fileSave.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[fileSaveas].addFile(QString::fromUtf8(":/images/fileSaveas.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[isToS].addFile(QString::fromUtf8(":/images/isToS.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[locked].addFile(QString::fromUtf8(":/images/locked.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[miriam].addFile(QString::fromUtf8(":/images/miriam.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[moveDown].addFile(QString::fromUtf8(":/images/moveDown.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[moveUp].addFile(QString::fromUtf8(":/images/moveUp.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[parameterConflict].addFile(QString::fromUtf8(":/images/parameterConflict.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[parameterMissing].addFile(QString::fromUtf8(":/images/parameterMissing.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[parameterModified].addFile(QString::fromUtf8(":/images/parameterModified.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[parameterObsolete].addFile(QString::fromUtf8(":/images/parameterObsolete.png"), QSize(), QIcon::Normal, QIcon::On);
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
  Icons[sToIs].addFile(QString::fromUtf8(":/images/sToIs.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[tool].addFile(QString::fromUtf8(":/images/tool.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[unlocked].addFile(QString::fromUtf8(":/images/unlocked.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[zoomOut].addFile(QString::fromUtf8(":/images/zoomOut.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[play].addFile(QString::fromUtf8(":/images/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[pause].addFile(QString::fromUtf8(":/images/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[stop].addFile(QString::fromUtf8(":/images/media-playback-stop.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[backward].addFile(QString::fromUtf8(":/images/media-seek-backward.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[forward].addFile(QString::fromUtf8(":/images/media-seek-forward.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[skipBackward].addFile(QString::fromUtf8(":/images/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[skipForward].addFile(QString::fromUtf8(":/images/media-skip-forward.png"), QSize(), QIcon::Normal, QIcon::On);
  Icons[roll].addFile(QString::fromUtf8(":/images/roll.png"), QSize(), QIcon::Normal, QIcon::On);

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

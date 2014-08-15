// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoReactionData.h
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#ifndef UNDOREACTIONDATA_H_
#define UNDOREACTIONDATA_H_

#include "UndoData.h"

class CReactionInterface;

class UndoReactionData: public UndoData
{
public:
  UndoReactionData();
  virtual ~UndoReactionData();
  CReactionInterface *getRi() const;
  void setRi(CReactionInterface *mpRi);

private:
  CReactionInterface* mpRi;
};

#endif /* UNDOREACTIONDATA_H_ */

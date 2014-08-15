/*
 * UndoReactionData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include "UndoReactionData.h"

UndoReactionData::UndoReactionData() {
	// TODO Auto-generated constructor stub

}

UndoReactionData::~UndoReactionData() {
	// TODO Auto-generated destructor stub
}

CReactionInterface *UndoReactionData::getRi() const
{
    return mpRi;
}

void UndoReactionData::setRi(CReactionInterface *mpRi)
{
    this->mpRi = mpRi;
}

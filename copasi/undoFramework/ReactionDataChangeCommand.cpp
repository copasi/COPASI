/*
 * ReactionDataChangeCommand.cpp
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */
#include "report/CCopasiRootContainer.h"

#include "ReactionDataChangeCommand.h"
#include "CQReactionDM.h"
#include <QDebug>
#include "qtUtilities.h"

ReactionDataChangeCommand::ReactionDataChangeCommand(QModelIndex index, const QVariant value, int role, CQReactionDM *pReactionDM) {
	// stores the data
	mOld = index.data(Qt::DisplayRole);
	mNew = value;
	mpReactionDM = pReactionDM;
	mIndex = index;
	mRole = role;
	assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
	CReaction *pRea = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getReactions()[index.row()];
	mOldFunctionName = FROM_UTF8(pRea->getFunction()->getObjectName());
	mNewFunctionName = "";

	//mPathIndex = pathFromIndex(index);
	this->setText(reactionDataChangeText());
}

ReactionDataChangeCommand::~ReactionDataChangeCommand() {
	// TODO Auto-generated destructor stub
}

void ReactionDataChangeCommand::redo(){
		mpReactionDM->reactionDataChange(mIndex, mNew, mRole, mNewFunctionName);
}
void ReactionDataChangeCommand::undo(){
	//mIndex = pathToIndex(mPathIndex, mpReactionDM);
	mpReactionDM->reactionDataChange(mIndex, mOld, mRole, mOldFunctionName);
}
QString ReactionDataChangeCommand::reactionDataChangeText() const{
	return QObject::tr(": Changed Reaction Data");
}

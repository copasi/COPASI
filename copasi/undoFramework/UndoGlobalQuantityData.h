/*
 * UndoGlobalQuantityData.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef UNDOGLOBALQUANTITYDATA_H_
#define UNDOGLOBALQUANTITYDATA_H_

#include "qtUtilities.h"
#include "UndoData.h"

class UndoReactionData;

class UndoGlobalQuantityData: public UndoData {
public:
	UndoGlobalQuantityData();
	virtual ~UndoGlobalQuantityData();
    double getInitialValue() const;
    CModelEntity::Status getStatus() const;
    void setInitialValue(double initialValue);
    void setStatus(CModelEntity::Status status);
    QList<UndoReactionData*> *getReactionDependencyObjects() const;
    void setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects);

private:
    /**
	 *  Initial value of the global quantity as double
	 */
    double mInitialValue;
    /**
	 * The status of the quantity
	 */
    CModelEntity::Status mStatus;

    /**
     * Pointer to species dependency objects
     */
    QList<UndoReactionData*> *mReactionDependencyObjects;
};

#endif /* UNDOGLOBALQUANTITYDATA_H_ */

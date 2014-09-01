/*
 * UndoSpecieData.h
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#ifndef UNDOSPECIEDATA_H_
#define UNDOSPECIEDATA_H_

#include <string>

#include "qtUtilities.h"
#include "UndoData.h"

class CMetab;
class UndoReactionData;

class UndoSpecieData: public UndoData {
public:
	UndoSpecieData();
	virtual ~UndoSpecieData();

    std::string getCompartment() const;
    double getIConc() const;
    void setCompartment(std::string compartment);
    void setIConc(double iConc);
    CMetab *getSpecie() const;
    void setSpecie(CMetab *mpSpecies);
    CModelEntity::Status getStatus() const;
    void setStatus(CModelEntity::Status status);
    QList<UndoReactionData*> getDependencyObjects() const;
    void setDependencyObjects(QList<UndoReactionData*> dependencyObjects);


private:
    /**
     *  Initial concentration of the species as double
     */
    double mIConc;
    /**
     *  The compartment the species is located in.
     */
    std::string mCompartment;
    /**
     * The status of the metabolite
     */
    CModelEntity::Status mStatus;
    /**
     * Pointer to species dependency objects
     */
    QList<UndoReactionData*> mDependencyObjects;
    /**
     * Pointer to the metabolite itself needed by some UNDO command
     */
    CMetab *mpSpecie;
};

#endif /* UNDOSPECIEDATA_H_ */

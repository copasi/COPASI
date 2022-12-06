// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CMIRIAMInfo: Stores all MIRIAM info for a Model.
 *
 */

#ifndef COPASI_CMODELMIRIAMINFO
#define COPASI_CMODELMIRIAMINFO

#include <map>

#include "copasi/MIRIAM/CCreator.h"
#include "copasi/MIRIAM/CReference.h"
#include "copasi/MIRIAM/CModified.h"
#include "copasi/MIRIAM/CBiologicalDescription.h"
#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFObject.h"

#include "copasi/core/CDataVector.h"
#include "copasi/core/CDataContainer.h"

class CAnnotation;

class CMIRIAMInfo : public CDataContainer
{
  // Attributes
private:
  CDataContainer * mpObject;
  CAnnotation * mpAnnotation;
  CDataVector <CCreator> mCreators;
  CDataVector <CReference> mReferences;
  CDataVector <CModification> mModifications;
  CDataVector <CBiologicalDescription> mBiologicalDescriptions;
  CRDFObject mCreatedObj;
  CRDFGraph * mpRDFGraph;
  CRDFTriplet mTriplet;
  CRDFTriplet mCreated;

  // Operations
public:
  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  CMIRIAMInfo();
  ~CMIRIAMInfo();
  void load(CDataContainer * pObject);
  bool save();
  CRDFGraph* getRDFGraph();
  bool empty() const;

  CDataVector <CCreator> & getCreators();
  const CDataVector <CCreator> & getCreators() const;
  CCreator* createCreator(const std::string& objectName);
  bool removeCreator(CCreator * pCreator);
  void loadCreators();

  /**
   * SMethod to add a creator based on user preferences. If the preferences
   * or not set NULL is returned
   * @return CCreator * pCreator
   */
  CCreator * addDefaultCreator(bool force = false);

  CDataVector <CReference> & getReferences();
  const CDataVector <CReference> & getReferences() const;
  CReference* createReference(const std::string& objectName);
  bool removeReference(CReference * pReference);
  void loadReferences();

  const std::string getCreatedDT() const;
  void setCreatedDT(const std::string& dt);
  bool addDefaultCreatedDT();

  CDataVector <CModification> & getModifications();
  const CDataVector <CModification> & getModifications() const;
  CModification* createModification(const std::string& objectName);
  bool removeModification(CModification * pModified);
  void loadModifications();

  CDataVector <CBiologicalDescription> & getBiologicalDescriptions();
  const CDataVector <CBiologicalDescription> & getBiologicalDescriptions() const;
  CBiologicalDescription* createBiologicalDescription();
  bool removeBiologicalDescription(CBiologicalDescription * pBiologicalDescription);
  void loadBiologicalDescriptions();

  virtual const std::string & getKey() const;
};

#endif //COPASI_CMODELMIRIAMINFO

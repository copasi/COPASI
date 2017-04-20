// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

class CMIRIAMInfo : public CDataContainer
{
  // Attributes
private:
  std::string mKey;
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
  CMIRIAMInfo();
  ~CMIRIAMInfo();
  void load(const std::string& key = "");
  bool save();
  CRDFGraph* getRDFGraph();

  CDataVector <CCreator> & getCreators();
  const CDataVector <CCreator> & getCreators() const;
  CCreator* createCreator(const std::string& objectName);
  bool removeCreator(int position);
  void loadCreators();

  CDataVector <CReference> & getReferences();
  const CDataVector <CReference> & getReferences() const;
  CReference* createReference(const std::string& objectName);
  bool removeReference(int position);
  void loadReferences();

  const std::string getCreatedDT() const;
  void setCreatedDT(const std::string& dt);

  CDataVector <CModification> & getModifications();
  const CDataVector <CModification> & getModifications() const;
  CModification* createModification(const std::string& objectName);
  bool removeModification(int position);
  void loadModifications();

  CDataVector <CBiologicalDescription> & getBiologicalDescriptions();
  const CDataVector <CBiologicalDescription> & getBiologicalDescriptions() const;
  CBiologicalDescription* createBiologicalDescription();
  bool removeBiologicalDescription(int position);
  void loadBiologicalDescriptions();

  virtual const std::string & getKey() const;
};

#endif //COPASI_CMODELMIRIAMINFO

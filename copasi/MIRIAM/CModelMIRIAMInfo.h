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

#include "copasi/utilities/CCopasiVector.h"
#include "copasi/report/CCopasiContainer.h"

class CMIRIAMInfo : public CCopasiContainer
{
  // Attributes
private:
  std::string mKey;
  CCopasiVector <CCreator> mCreators;
  CCopasiVector <CReference> mReferences;
  CCopasiVector <CModification> mModifications;
  CCopasiVector <CBiologicalDescription> mBiologicalDescriptions;
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

  CCopasiVector <CCreator> & getCreators();
  const CCopasiVector <CCreator> & getCreators() const;
  CCreator* createCreator(const std::string& objectName);
  bool removeCreator(int position);
  void loadCreators();

  CCopasiVector <CReference> & getReferences();
  const CCopasiVector <CReference> & getReferences() const;
  CReference* createReference(const std::string& objectName);
  bool removeReference(int position);
  void loadReferences();

  const std::string getCreatedDT() const;
  void setCreatedDT(const std::string& dt);

  CCopasiVector <CModification> & getModifications();
  const CCopasiVector <CModification> & getModifications() const;
  CModification* createModification(const std::string& objectName);
  bool removeModification(int position);
  void loadModifications();

  CCopasiVector <CBiologicalDescription> & getBiologicalDescriptions();
  const CCopasiVector <CBiologicalDescription> & getBiologicalDescriptions() const;
  CBiologicalDescription* createBiologicalDescription();
  bool removeBiologicalDescription(int position);
  void loadBiologicalDescriptions();

  virtual const std::string & getKey() const;
};

#endif //COPASI_CMODELMIRIAMINFO

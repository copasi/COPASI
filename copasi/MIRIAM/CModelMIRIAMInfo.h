// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/09 21:05:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

    const CCopasiVector <CCreator> & getCreators() const;
    CCreator* createCreator(const std::string& objectName);
    bool removeCreator(const std::string& key);
    bool removeCreator(int position);
    void loadCreators();

    const CCopasiVector <CReference> & getReferences() const;
    CReference* createReference(const std::string& objectName);
    bool removeReference(const std::string& key);
    bool removeReference(int position);
    void loadReferences();

    const std::string getCreatedDT() const;
    void setCreatedDT(const std::string& dt);

    const CCopasiVector <CModification> & getModifications() const;
    CModification* createModification(const std::string& objectName);
    bool removeModification(const std::string& key);
    bool removeModification(int position);
    void loadModifications();

    const CCopasiVector <CBiologicalDescription> & getBiologicalDescriptions() const;
    CBiologicalDescription* createBiologicalDescription();
    bool removeBiologicalDescription(const std::string& key);
    void loadBiologicalDescriptions();

    virtual const std::string & getKey() const;
  };

#endif //COPASI_CMODELMIRIAMINFO

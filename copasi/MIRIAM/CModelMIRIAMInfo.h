// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/04/21 20:12:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CModelMIRIAMInfo: Stores all MIRIAM info for a Model.
 *
 */

#ifndef COPASI_CMODELMIRIAMINFO
#define COPASI_CMODELMIRIAMINFO

#include <map>

#include "utilities/CCopasiVector.h"
#include "report/CCopasiContainer.h"

#include "CCreator.h"
#include "CReference.h"
#include "CModified.h"
#include "CBiologicalDescription.h"
#include "CRDFGraph.h"
#include "CRDFObject.h"

class CModelMIRIAMInfo : public CCopasiContainer
  {
    // Attributes
  private:
    CCopasiVector <CCreator> mCreators;
    CCopasiVector <CReference> mReferences;
    bool mOldReferencesMoved;
    CRDFObject mCreatedObj;
    CCopasiVector <CModified> mModifieds;
    CCopasiVector <CBiologicalDescription> mBiologicalDescriptions;

    CRDFGraph* mpRDFGraph;
    CCopasiObject* mpCopasiObject;

  protected:
    bool fillInfoFromGraph();
    void fillObjects(std::string tableName);
    void clearMembers();

    // Operations
  public:
    CModelMIRIAMInfo();
    ~CModelMIRIAMInfo();
    void loadGraph(const std::string& key = "");
    bool saveGraph();
    CRDFGraph* getRDFGraph();
    CCopasiVector <CCreator> & getCreators();
    CCreator* createCreator(const std::string& objectName);
    bool removeCreator(const std::string& key);
    CCopasiVector <CReference> & getReferences();
    CReference* createReference(const std::string& objectName);
    bool removeReference(const std::string& key);
    const std::string getCreatedDT() const;
    void setCreatedDT(const std::string& dt);
    CCopasiVector <CModified> & getModifieds();
    CModified* createModified(const std::string& objectName);
    bool removeModified(const std::string& key);
    CCopasiVector <CBiologicalDescription> & getBiologicalDescriptions();
    CBiologicalDescription* createBiologicalDescription(const std::string& objectName, std::string parentTable = "");
    bool removeBiologicalDescription(const std::string& key);
    std::map<std::string, std::string> moveOldReferences();
    std::string moveBiologicalDescription(const std::string key, const std::string newTable);
  };

#endif //COPASI_CMODELMIRIAMINFO

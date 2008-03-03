// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/03 16:58:28 $
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

#include "CCreator.h"
#include "CReference.h"
#include "CModified.h"
#include "CRDFGraph.h"
#include "CRDFObject.h"

class CModelMIRIAMInfo
  {
    // Attributes
  private:
    CCopasiVector <CCreator> mCreators;
    CRDFObject mCreatorsObj;
    CCopasiVector <CReference> mReferences;
	std::map<std::string, CRDFObject> mReferenceObjs;
	bool mOldReferencesMoved;
    CRDFObject mCreatedObj;
    CCopasiVector <CModified> mModifieds;
    CRDFObject mModifiedsObj;

    CRDFGraph* mpRDFGraph;
    CModelEntity* mpEntity;

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
	std::map<std::string, std::string> moveOldReferences();
  };

#endif //COPASI_CMODELMIRIAMINFO

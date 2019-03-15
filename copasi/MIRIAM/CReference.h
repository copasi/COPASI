// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CReference
#define COPASI_CReference

#include <string>

#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CConstants.h"

#include "copasi/core/CDataContainer.h"

/**
 *  CReferences: Stores publication details such as PubMed Id and DOI.
 */
class CReference : public CDataContainer
{
  // Attributes
private:
  /**
   * Triplet in the RDF graph representing the reference.
   */
  CRDFTriplet mTriplet;

  /**
   * The predicate path to the node.
   */
  CRDFPredicate::Path mNodePath;

  /**
   * The key of the object needed for the COPASI tables.
   */
  std::string mKey;

  /**
   * Triplet in the RDF graph representing the reference.
   */
  CRDFTriplet mIdTriplet;

  /**
   * MIRIAM resource for holding database and Id.
   */
  CMIRIAMResourceObject mResource;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CReference * pDataObject
   */
  static CReference * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Destruct the object
   */
  virtual void destruct();

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

  // Operations
  /**
   * Default constructor
   * @param const std::string & objectName
   * @param const CDataContainer * pParent (default: NULL)
   */
  CReference(const std::string & objectName,
             const CDataContainer * pParent = NO_PARENT);

  /**
   * Specific constructor
   * @param const CRDFTriplet & triplet
   * @param const std::string & objectName (default: "")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CReference(const CRDFTriplet & triplet,
             const std::string & objectName = "",
             const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CReference &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CReference(const CReference & src,
             const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CReference();

  /**
   * Retrieve the RDF triplet holding the information for this reference.
   * @return const CRDFTriplet & triplet
   */
  const CRDFTriplet & getTriplet() const;

  /**
   * Retrieve the MIRIAM resource object for this reference
   */
  const CMIRIAMResourceObject & getMIRIAMResourceObject() const;

  /**
   * Retrieve the key for the object
   * @return const std::string & key
   */
  virtual const std::string & getKey() const;

  /**
   * Retrieve the MIRIAM resource for the reference.
   * @return std::string resource
   */
  std::string getResource() const;

  /**
   * Retrieve the id of the reference in the MIRIAM resource.
   * @return const std::string & id
   */
  const std::string & getId() const;

  /**
   * Retrieve the description for the reference.
   * @return std::string description
   */
  const std::string & getDescription() const;

  /**
   * Retrieve the URI (comprised of resource an id) specifying this reference.
   * @return std::string uri
   */
  std::string getURI() const;

  /**
   * Set the MIRIAM resource for the reference
   * @param const std::string & resource
   */
  void setResource(const std::string & resource);

  /**
   * Set the id of the reference in the MIRIAM resource.
   * @param const std::string & id
   */
  void setId(const std::string & id);

  /**
   * Set the description for the reference.
   * @param std::string description
   */
  void setDescription(const std::string & description);

  /**
   * Remove invalid combinations of resource and id
   */
  void clearInvalidEntries();
};

#endif //COPASI_CReference

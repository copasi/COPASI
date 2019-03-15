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

#ifndef COPASI_CBiologicalDescription
#define COPASI_CBiologicalDescription

#include <string>

#include "copasi/MIRIAM/CRDFTriplet.h"
#include "copasi/MIRIAM/CConstants.h"

#include "copasi/core/CDataContainer.h"

class CBiologicalDescription : public CDataContainer
{
  // Attributes
private:
  /**
   * Triplet in the RDF graph representing the description.
   */
  CRDFTriplet mTriplet;

  /**
   * The key of the object needed for the COPASI tables.
   */
  std::string mKey;

  /**
   * MIRIAM resource for holding the database and Id.
   */
  CMIRIAMResourceObject mResource;

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CBiologicalDescription * pDataObject
   */
  static CBiologicalDescription * fromData(const CData & data, CUndoObjectInterface * pParent);

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
  CBiologicalDescription(const std::string & objectName,
                         const CDataContainer * pParent = NO_PARENT);

  /**
   * Specific constructor
   * @param const CRDFTriplet & triplet
   * @param const std::string & objectName (default: "")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CBiologicalDescription(const CRDFTriplet & triplet,
                         const std::string & objectName = "",
                         const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CBiologicalDescription &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CBiologicalDescription(const CBiologicalDescription & src,
                         const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CBiologicalDescription();

  /**
   * Retrieve the MIRIAM resource object for this reference
   */
  const CMIRIAMResourceObject & getMIRIAMResourceObject() const;

  /**
   * Retrieve the RDF triplet holding the description.
   * @return const CRDFTriplet & triplet
   */
  const CRDFTriplet & getTriplet() const;

  /**
   * Retrieve the key of the object.
   * @return const std::string & key
   */
  virtual const std::string & getKey() const;

  /**
   * Retrieve the predicate, i.e. the relationship between the subject.
   * and the MIRIAM resource.
   * @return std::string predicate
   */
  std::string getPredicate() const;

  /**
   * Retrieve the MIRIAM resource (database) describing the subject.
   * @return std::string resource
   */
  std::string getResource() const;

  /**
   * Retrieve the identifier of the subject in the MIRIAM resource.
   * @return const std::string id
   */
  const std::string & getId() const;

  /**
   * Retrieve the URI comprised of MIRIAM resource and id.
   * @return std::string uri
   */
  std::string getURI() const;

  /**
   * Set the predicate, i.e., relationship between the subject and the
   * MIRIAM resource.
   * @param const std::string & predicate
   */
  void setPredicate(const std::string & predicate);

  /**
   * Set the MIRIAM resource (database) describing the subject.
   * @param const std::string & predicate
   */
  void setResource(const std::string & resource);

  /**
   * Set the identifier of the subject in the MIRIAM resource.
   * @param const std::string & id
   */
  void setId(const std::string & id);

  /**
   * Convenience method removing invalid predicate, resource, and id combinations
   */
  void clearInvalidEntries();
};

#endif //COPASI_CBiologicalDescription

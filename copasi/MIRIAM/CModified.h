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

/**
 *  CModified: Stores Modification dates.
 */

#ifndef COPASI_CMODIFIED
#define COPASI_CMODIFIED

#include <string>

#include "copasi/MIRIAM/CRDFTriplet.h"
#include "copasi/MIRIAM/CRDFPredicate.h"

class CModification : public CCopasiContainer
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
   * The key of the object needed for the copasi tables.
   */
  std::string mKey;

  // Operations
public:
  static CModification * create(const CData & data);

  /**
   * Default constructor
   * @param const std::string & objectName
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModification(const std::string & objectName,
                const CCopasiContainer * pParent = NO_PARENT);

  /**
   * Specific constructor
   * @param const CRDFTriplet & triplet
   * @param const std::string & objectName (default: "")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModification(const CRDFTriplet & triplet,
                const std::string & objectName = "",
                const CCopasiContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CModification &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModification(const CModification & src,
                const CCopasiContainer * pParent);

  /**
   * Destructor
   */
  ~CModification();

  const CRDFTriplet & getTriplet() const;

  virtual const std::string & getKey() const;

  void setDate(const std::string & date);

  const std::string & getDate() const;
};

#endif //COPASI_CMODIFIED

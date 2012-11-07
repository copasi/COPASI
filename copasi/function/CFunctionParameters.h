// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameters
 *
 * Created for COPASI by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionParameters
#define COPASI_CFunctionParameters

#include "copasi/utilities/CReadConfig.h"
#include "copasi/utilities/CCopasiVector.h"
#include "copasi/function/CFunctionParameter.h"
#include "copasi/report/CCopasiContainer.h"

/** @dia:pos 10.7176,6.51973 */
class CFunctionParameters : public CCopasiContainer
{
  // Attributes

private:
  /**
   *  A vector of parameters
   *  @supplierCardinality 0..*
   *  @associates <{CFunctionParameter}>
   */
  /** @dia:route 0,3; h,15.1888,24.6765,8.71728,7.21973,10.7176 */
  CCopasiVectorNS < CFunctionParameter > mParameters;

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CFunctionParameters(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CFunctionParameters &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CFunctionParameters(const CFunctionParameters & src,
                      const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor
   */
  ~CFunctionParameters();

  /**
   *  Cleanup
   */
  void cleanup();

  /**
   *  Assignment operator. Performs deep copy.
   */
  CFunctionParameters & operator=(const CFunctionParameters & src);

  /**
   *  Add a parameter to the parameter list
   *  @param "const CFunctionParameter &" parameter
   */

  void add(const CFunctionParameter & parameter);

  /**
   * Add a parameter to the parameter list
   * @param "CFunctionParameter *" parameter
   * @param const bool & adopt (Default: false)
   * @return bool success
   */
  bool add(CFunctionParameter * parameter, const bool & adopt = false);

  /**
   * Add a parameter to the parameter list
   * @param "const string & name
   * @param "const CFunctionParameter::DataType &" type
   * @param "const string &" usage
   * @return bool success
   */
  bool add(const std::string & name,
           const CFunctionParameter::DataType & type,
           CFunctionParameter::Role usage);

  /**
   *  Remove a parameter from the parameter list
   *  @param "const CFunctionParameter &" parameter
   */
  void remove(const std::string & name);

  /**
   *
   */
  CFunctionParameter * operator[](size_t index);
  const CFunctionParameter * operator[](size_t index) const;

  /**
   *
   */
  CFunctionParameter * operator[](const std::string &name);
  const CFunctionParameter * operator[](const std::string &name) const;

  /**
   * number of parameters
   */
  size_t size() const;

  /**
   * Swap parameters
   * @param const size_t & from
   * @param const size_t & to
   */
  void swap(const size_t & from, const size_t & to);

  /**
   * tells whether there is a parameter with vector type and the given role
   * (if there is one it is assumed it is the only one with this role)
   */
  bool isVector(CFunctionParameter::Role role) const;

  /**
   *  Retrieves the first parameter with the specified usage after pos
   *  In a normal situation pos is set to 0 for the first call.
   *  It is increment by the method to allow subsequent searches to start
   *  after the last found item. This is usefull if several parameters
   *  with the same usage exist.
   *  @param "const string &" usage
   *  @param "size_t &" pos (first call should be with 0)
   *  @return "CFunctionParameter &" usageRange
   */
  const CFunctionParameter * getParameterByUsage(CFunctionParameter::Role usage,
      size_t & pos) const;

  /**
   * gets the number of Parameters with a specific usage
   */
  size_t getNumberOfParametersByUsage(CFunctionParameter::Role usage) const;

  /**
   * find a parameter by its name and return its index
   */
  size_t findParameterByName(const std::string & name,
                             CFunctionParameter::DataType & dataType) const;

  bool operator==(const CFunctionParameters & rhs) const;

  /**
   * insert operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CFunctionParameters & d);
};

#endif // COPASI_CFunctionParameters

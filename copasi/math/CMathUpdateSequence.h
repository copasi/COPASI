// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathUpdateSequence
#define COPASI_CMathUpdateSequence

#include <vector>
#include <cstddef>

template <class CType> class CVectorCore;
class CMathContainer;
class CObjectInterface;
class CMathObject;

class CMathUpdateSequence : public std::vector< CObjectInterface * >
{
public:
  /**
   * Default Constructor
   * @param CMathContainer * pContainer (default: NULL)
   */
  CMathUpdateSequence(CMathContainer * pContainer = NULL);

  /**
   * Copy Constructor
   * @param const CMathUpdateSequence & src
   * @param CMathContainer * pContainer (default: NULL)
   */
  CMathUpdateSequence(const CMathUpdateSequence & src, CMathContainer * pContainer = NULL);

  /**
   * Destructor
   */
  virtual ~CMathUpdateSequence();

  /**
   * Assignment operator
   * @param const CMathUpdateSequence & rhs
   */
  CMathUpdateSequence & operator = (const CMathUpdateSequence & rhs);

  /**
   * Set the math container
   * @param CMathContainer * pContainer
   */
  void setMathContainer(CMathContainer * pContainer);

private:
  CMathContainer * mpContainer;
};

#endif // CMathUpdateSequence

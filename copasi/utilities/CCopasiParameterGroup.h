/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameterGroup.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/23 14:22:32 $
   End CVS Header */

#ifndef COPASI_CCopasiParameterGroup
#define COPASI_CCopasiParameterGroup

#include <string>
#include <vector>

#include "CCopasiParameter.h"

/**
 *  CCopasiParameterGroup class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */
class CCopasiParameterGroup: public CCopasiParameter
  {
    typedef std::vector< CCopasiParameter *> parameterGroup;
    typedef parameterGroup::iterator index_iterator;
    typedef CCopasiContainer::objectMap::iterator name_iterator;

    // Operations
  private:
    /**
     * Default constructor
     */
    CCopasiParameterGroup();

  public:
    /**
     * Copy constructor
     * @param "const CCopasiParameterGroup &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiParameterGroup(const CCopasiParameterGroup & src,
                          const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const string & name
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "ParameterGroup")
     */
    CCopasiParameterGroup(const std::string & name,
                          const CCopasiContainer * pParent = NULL,
                          const std::string & objectType = "ParameterGroup");

    /**
     * Destructor
     */
    virtual ~CCopasiParameterGroup();

    name_iterator beginName() const;
    name_iterator nameEnd() const;

    index_iterator beginIndex() const;
    index_iterator endIndex() const;

    bool addParameter(const std::string & name,
                      const CCopasiParameter::Type type);
    bool addGroup(const std::string & name);

    bool removeParameter(const std::string & name);
    bool removeParameter(const unsigned C_INT32 & index);

    CCopasiParameter * getParameter(const std::string & name);
    CCopasiParameter * getParameter(const unsigned C_INT32 & index);

    const void * getValue(const std::string & name) const;
    const void * getValue(const unsigned C_INT32 & index) const;

    void * getValue(const std::string & name);
    void * getValue(const unsigned C_INT32 & index);

    CCopasiParameter::Type getType(const std::string & name) const;
    CCopasiParameter::Type getType(const unsigned C_INT32 & index) const;

    template <class CType>
    bool setValue(const std::string & name,
                  const CType & value);
    template <class CType>
    bool setValue(const unsigned C_INT32 & index,
                  const CType & value);

    bool swap(const unsigned C_INT32 & index,
              const unsigned C_INT32 & index);

    bool swap(parameterGroup::iterator & from,
              parameterGroup::iterator & to);

    unsigned C_INT32 size() const;

    unsigned C_INT32 getIndex(const std::string & name) const;

  private:
    void createGroup(const parameterGroup * pGroup = NULL);
    void deleteGroup();
    void addParameter(CCopasiParameter * pParameter);
  };

#endif // COPASI_CCopasiParameterGroup

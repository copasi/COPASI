// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLInterface.h,v $
//   $Revision: 1.33 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/24 15:34:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXMLInterface class.
 * The class CCopasiXMLInterface is the interface to various XML document
 * containing Copasi relevant informtion.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiXMLInterface
#define COPASI_CCopasiXMLInterface

#include <vector>
#include <string>
#include <sstream>

#include "copasi.h"

template <class CType> class CCopasiVector;
template <class CType> class CCopasiVectorN;
class CXMLAttributeList;
class CSlider;
class CCopasiParameter;

/**
 * The class CCopasiXMLInterface specifies an interface to various XML formats
 * related to COPASI relevant information.
 * Derived classes have to implement the following two methods:
 * @see bool load(std::istream & is)
 * @see bool save(std::ostream & os)
 *
 * Note: the responsibilty to free allocated memory during load is handed to the
 *       user.
 */
class SCopasiXMLGUI
  {
    // Operations
  public:
    /**
     * Constructor
     */
    SCopasiXMLGUI();

    /**
     * Constructor
     */
    ~SCopasiXMLGUI();

    // Attributes
  public:
    /**
     * Pointer to a vector of sliders which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVector< CSlider > * pSliderList;
  };

class CCopasiXMLInterface
  {
  public:
    /**
     * Enumeration of encoding tyoe.
     */
    enum EncodingType
    {
      none = 0,
      std,
      attribute,
      character
    };

    class DBL
      {
        // Operations
      public:
        DBL(const C_FLOAT64 & value = 0.0);

        DBL(const char * value);

        ~DBL();

        operator const C_FLOAT64 & () const;

        friend std::ostream & operator << (std::ostream & os, const DBL & dbl);

        // Attributes
      private:
        C_FLOAT64 mValue;
      };

    // Attributes
  protected:
    /**
     * A pointer to the input stream
     */
    std::istream *mpIstream;

    /**
     * A pointer to the output stream
     */
    std::ostream *mpOstream;

    /**
     * Indent
     */
    std::string mIndent;

    /**
     * The filename if available
     */
    std::string mFilename;

    // Operations
  public:
    /**
     * Constructor.
     */
    CCopasiXMLInterface();

    /**
     * Destructor.
     */
    virtual ~CCopasiXMLInterface();

    /**
     * Load information from a given istream.
     * @param std::istream & is
     * @param const std::string & relativeTo
     * @return bool success
     */
    virtual bool load(std::istream & is,
                      const std::string & relativeTo) = 0;

    /**
     * Load information from a file.
     * @param const std::string & fileName
     * @param const std::string & relativeTo
     * @return bool success
     */
    bool load(const std::string & fileName,
              const std::string & relativeTo);

    /**
     * Save information to a given ostream.
     * @param std::ostream & os
     * @param const std::string & relativeTo
     * @return bool success
     */
    virtual bool save(std::ostream & os,
                      const std::string & relativeTo) = 0;

    /**
     * Save information to a file.
     * @param const std::string & fileName
     * @param const std::string & relativeTo
     * @return bool success
     */
    bool save(const std::string & fileName,
              const std::string & relativeTo);

    /**
     * Encode a given string to a valid XML string
     * @param const std::string & str
     * @return std::string encoded
     */
    static std::string encode(const std::string & str, const EncodingType & type = std);

    /**
     * Encode a given string to a valid XML string
     * @param const C_FLOAT64 & dbl
     * @return std::string encoded
     */
    //    static std::string encodeDBL(const C_FLOAT64 & dbl);

    /**
    * Encode a given string to a utf-8 string
    * @param const std::string & str
    * @return std::string encoded
    */
    static std::string utf8(const std::string & str);

  protected:
    /**
     * Save CDATA  to the ostream
     * @param const std::string & data
     * @return bool success
     */
    bool saveData(const std::string & data);

    /**
     * Save xhtml to the ostream
     * @param const std::string & xhtml
     * @return bool success
     */
    bool saveXhtml(const std::string & xhtml);

    /**
     * Save an XML element to the ostream
     * @param const std::string & name
     * @param CXMLAttributeList & attributeList
     * @return bool success
     */
    bool saveElement(const std::string & name,
                     CXMLAttributeList & attributeList);

    /**
     * Start saving an XML element to the ostream. Call endSaveElement to
     * conclude.
     * @param const std::string & name
     * @return bool success
     */
    bool startSaveElement(const std::string & name);

    /**
     * Start saving an XML element to the ostream. Call endSaveElement to
     * conclude.
     * @param const std::string & name
     * @param CXMLAttributeList & attributeList
     * @return bool success
     */
    bool startSaveElement(const std::string & name,
                          CXMLAttributeList & attributeList);

    /**
     * End saving an XML element to the ostream started by startSaveElement.
     * @param const std::string & name
     * @return bool success
     */
    bool endSaveElement(const std::string & name);

    /**
     * Save a Parameter.
     * @param const CCopasiParameter & parameter
     * @return bool success
     */
    bool saveParameter(const CCopasiParameter & parameter);

    /**
     * Save a Parameter Group.
     * @param const CCopasiParameterGroup::parameterGroup & group
     * @return bool success
     */
    bool saveParameterGroup(const std::vector< CCopasiParameter * > & group);
  };

/**
 * A list of XML attributes used by saveElement and startSaveElement.
 */
class CXMLAttributeList
  {
    // Attributes
  private:
    /**
     * The attribute list.
     */
    std::vector< std::string > mAttributeList;

    /**
     * The list wheter an attribute is to be saved.
     */
    std::vector< bool > mSaveList;

    // Operations
  public:
    /**
     * Constructor.
     */
    CXMLAttributeList();

    /**
     * Copy constructor.
     * @param const CXMLAttributeList & src
     */
    CXMLAttributeList(const CXMLAttributeList & src);

    /**
     * Destructor.
     */
    ~CXMLAttributeList();

    /**
     * Erase the content of the attribute list.
     * @return bool success
     */
    bool erase();

    /**
     * Add an attribute to the end of the list.
     * Note: the value will be XML encoded
     * @param const std::string & name
     * @param const CType & value
     * @return bool success
     */
    template <class CType> inline bool add(const std::string & name,
                                           const CType & value)
    {return add(name, value, CCopasiXMLInterface::attribute);}

    /**
     * Add an attribute to the end of the list.
     * Note: the value will be XML encoded
     * @param const std::string & name
     * @param const C_FLOAT64 & value
     * @return bool success
     */
    bool add(const std::string & name, const C_FLOAT64 & value);

    /**
     * Add an attribute to the end of the list.
     * Note: the value will be XML encoded
     * @param const std::string & name
     * @param const CType & value
     * @param const CCopasiXMLInterface::EncodingType & encodingType
     * @return bool success
     */
    template <class CType> bool add(const std::string & name,
                                    const CType & value,
                                    const CCopasiXMLInterface::EncodingType & encodingType)
    {
      std::ostringstream Value;
      try
        {
          Value << value;
        }

      catch (...)
        {
          Value << "";
        }

      mAttributeList.push_back(name);
      mAttributeList.push_back(CCopasiXMLInterface::encode(Value.str(),
                               encodingType));

      mSaveList.push_back(true);

      return true;
    }

    /**
     * Retreive the size of the list.
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 size();

    /**
     * Set the name of the indexed attribute
     * @param const unsigned C_INT32 & index
     * @param const std::string & name
     * @return bool success
     */
    bool setName(const unsigned C_INT32 & index,
                 const std::string & name);

    /**
     * Retreive the name of the indexed attribute.
     * @param const unsigned C_INT32 & index
     * @return const std::string & name
     */
    const std::string & getName(const unsigned C_INT32 & index) const;

    /**
     * Set the name and value of the indexed attribute
     * Note: the value will be XML encoded
     * @param const unsigned C_INT32 & index
     * @param const std::string & name
     * @param const CType & value
     * @return bool success
     */
    template <class CType> inline bool set(const unsigned C_INT32 & index,
                                           const std::string & name,
                                           const CType & value)
    {return set(index, name, value, CCopasiXMLInterface::attribute);}
    /**
    * Set the name and value of the indexed attribute
    * Note: the value will be XML encoded
    * @param const unsigned C_INT32 & index
    * @param const std::string & name
    * @param const CType & value
    * @param const CCopasiXMLInterface::EncodingType & encodingType
    * @return bool success
    */
    template <class CType> bool set(const unsigned C_INT32 & index,
                                    const std::string & name,
                                    const CType & value,
                                    const CCopasiXMLInterface::EncodingType & encodingType)
    {
      mAttributeList[2 * index] = name;

      std::ostringstream Value;
      try
        {
          Value << value;
        }

      catch (...)
        {
          Value << "";
        }

      mAttributeList[2 * index + 1] =
        CCopasiXMLInterface::encode(Value.str(),
                                    encodingType);
      mSaveList[index] = true;

      return true;
    }

    /**
     * Set the value of the indexed attribute
     * Note: the value will be XML encoded
     * @param const unsigned C_INT32 & index
     * @param const CType & value
     * @return bool success
     */
    template <class CType> inline bool setValue(const unsigned C_INT32 & index,
        const CType & value)
    {return setValue(index, value, CCopasiXMLInterface::attribute);}

    /**
     * Set the value of the indexed attribute
     * Note: the value will be XML encoded
     * @param const unsigned C_INT32 & index
     * @param const CType & value
     * @param const CCopasiXMLInterface::EncodingType & encodingType
     * @return bool success
     */
    template <class CType> bool setValue(const unsigned C_INT32 & index,
                                         const CType & value,
                                         const CCopasiXMLInterface::EncodingType & encodingType)
    {
      std::ostringstream Value;
      try
        {
          Value << value;
        }

      catch (...)
        {
          Value << "";
        }

      mAttributeList[2 * index + 1] =
        CCopasiXMLInterface::encode(Value.str(),
                                    encodingType);
      mSaveList[index] = true;

      return true;
    }

    /**
     * Retreive the value of the indexed attribute.
     * @param const unsigned C_INT32 & index
     * @return const std::string & value
     */
    const std::string & getValue(const unsigned C_INT32 & index) const;

    /**
     * Set whether the indexed attribute shall be skipped during save.
     * @param const unsigned C_INT32 & index
     * @return bool sucess
     */
    bool skip(const unsigned C_INT32 & index);

    /**
     * Retreive the indexed attribute (' name="value"' or '' if skipped).
     * @param const unsigned C_INT32 & index
     * @return std::string attribute
     */
    std::string getAttribute(const unsigned C_INT32 & index) const;

    friend std::ostream &operator<<(std::ostream &os, const CXMLAttributeList & attr);
  };

#endif // COPASI_CCopasiXMLInterface

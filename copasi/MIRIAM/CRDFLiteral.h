// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFLiteral.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRDFLiteral
#define COPASI_CRDFLiteral

#include <string>

class CRDFLiteral
  {
    // Enumerations
  public:
    /**
     * The two different types possible for literals
     */
    enum eLiteralType {PLAIN = 0, TYPED};

    // Operations
  public:
    /**
     * Default Constructor
     */
    CRDFLiteral();

    /**
     * Copy Constructor
     * @param const CRDFLiteral & src
     */
    CRDFLiteral(const CRDFLiteral & src);

    /**
     * Destructor
     */
    ~CRDFLiteral();

    /**
     * Set the type of the literal
     * @param const eLiteralType & type
     */
    void setType(const eLiteralType & type);

    /**
     * Retrieve the type of the literal
     * @return const eLiteralType & type
     */
    const eLiteralType & getType() const;

    /**
     * Set the language of the literal
     * @param const std::string & language
     */
    void setLanguage(const std::string & language);

    /**
     * Retrieve the language of the literal
     * @return const std::string & language
     */
    const std::string & getLanguage() const;

    /**
     * Set the data type of the literal
     * @param const std::string & dataType
     */
    void setDataType(const std::string & dataType);

    /**
     * Retrieve the data type of the literal
     * @return const std::string & dataType
     */
    const std::string & getDataType() const;

    /**
     * Set the lexical data of the literal
     * @param const std::string & lexicalData
     */
    void setLexicalData(const std::string & lexicalData);

    /**
     * Retrieve the lexical data of the literal
     * @return const std::string & lexicalData
     */
    const std::string & getLexicalData() const;

    // Attributes
  private:
    /**
     * The type of the literal
     */
    eLiteralType mType;

    /**
     * The language tag for literals of type PLAIN
     */
    std::string mLanguage;

    /**
     * The data type describing URI for literals of type TYPED.
     */
    std::string mDataType;

    /**
     * The lical form of the data
     */
    std::string mLexicalData;
  };

std::ostream & operator << (std::ostream & os, const CRDFLiteral & literal);

#endif // COPASI_CRDFLiteral

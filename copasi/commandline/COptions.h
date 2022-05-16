// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  COptions class.
 *  The class retrieves the options from the commandline and various files.
 *  The options as well as their type can be retrieved by name.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_COptions
#define COPASI_COptions

#include <string>
#include <map>
#include <vector>

#include "copasi/commandline/CLocaleString.h"

class COptions
{
  class COptionValue
  {
  public:
    typedef void valueType;

    // Attributes
  protected:
    valueType * mpValue;

    //Operations
  protected:
    COptionValue():
      mpValue(NULL)
    {CONSTRUCTOR_TRACE;}

  public:
    virtual ~COptionValue() {DESTRUCTOR_TRACE;}

    template< class CType > void setValue(const CType & value)
    {*(CType *) mpValue = value;}

    template< class CType > void getValue(CType & value) const
    {
      if (mpValue) value = *(CType *) mpValue;
      else value = CType();
    }

    template< class CType > bool compareValue(CType & value) const
    {
      if (mpValue) return (value == *(CType *) mpValue);
      else return false;
    }
  };

  template< class CType > class COptionValueTemplate : public COptionValue
  {
  public:
    typedef CType valueType;

    //Operations
  private:
    COptionValueTemplate():
      COptionValue()
    {
      CONSTRUCTOR_TRACE;
      mpValue = new valueType;
    }

  public:
    COptionValueTemplate(const valueType & value):
      COptionValue()
    {
      CONSTRUCTOR_TRACE;
      mpValue = new valueType;
      *(valueType *) mpValue = value;
    }

    virtual ~COptionValueTemplate()
    {
      if (mpValue) {delete (valueType *) mpValue; mpValue = NULL;}

      DESTRUCTOR_TRACE;
    }
  };

public:
  typedef std::map< std::string, COptionValue * > optionType;
  typedef std::vector< std::string > nonOptionType;
  typedef std::map< std::string, std::string > defaultType;

  //Attributes
private:
  static optionType mOptions;
  static nonOptionType mNonOptions;

  //Operations
private:
  COptions();

public:
  ~COptions();

  template< class CType > static void getValue(const std::string & name,
      CType & value)
  {
    if (!isSet(name)) return;

    mOptions[name]->getValue(value);
  }

  template< class CType > static bool compareValue(const std::string & name,
      const CType & value)
  {
    if (!isSet(name)) return false;

    return mOptions[name]->compareValue(value);
  }

  static void init(C_INT argc = 0, char *argv[] = NULL);

  static void cleanup();

  static bool isSet(const std::string & name);

  static const nonOptionType & getNonOptions();

  static std::string getEnvironmentVariable(const std::string & name);

  static std::string getPWD(void);

  static std::string getConfigDir(void);

private:
  template< class CType > static void setValue(const std::string & name,
      const CType & value)
  {
    if (mOptions[name])
      mOptions[name]->setValue(value);
    else
      mOptions[name] = new COptionValueTemplate< CType >(value);

    return;
  }

  static std::string getCopasiDir(void);

  static std::string getHome(void);
  static std::string getTemp(void);

  static std::string getConfigFile(void);
};

#endif // COPASI_COptions

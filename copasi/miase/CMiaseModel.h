// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseModel.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/03/20 18:33:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASEMODEL
#define CMIASEMODEL

#include "CMiaseBase.h"

class CMiaseChange : public CMiaseBase
  {

  public:

    CMiaseChange();

    ~CMiaseChange();

    std::string returnTarget();

    void setTarget(std::string target);

    enum TYPE{ATTRIBUTE, MATH };

    virtual TYPE getType() = 0;

    TYPE mType;

  private:

    std::string mTarget;
  };

class CMiaseChangeAttribute : public CMiaseChange
  {

  public:

    CMiaseChangeAttribute();

    ~CMiaseChangeAttribute();

    std::string returnNewValue();

    void setNewValue(std::string newValue);

    virtual CMiaseChange::TYPE getType();

  private:

    std::string mNewValue;
  };

class CMiaseChangeMath : public CMiaseChange
  {

  public:

    CMiaseChangeMath();

    ~CMiaseChangeMath();

    std::string returnNewMath();

    void setNewMath(std::string newMath);

    virtual CMiaseChange::TYPE getType();

  private:

    std::string mNewMath;
  };

class CMiaseModel : public CMiaseBaseEnhanced
  {

  public:

    CMiaseModel();

    ~CMiaseModel();

    std::string getType();
    std::string getSource();

    void setType(std::string type);
    void setSource(std::string source);

    void addChange (CMiaseChange* chnage);

    CMiaseChange* getChange(int num);
    CMiaseChange* getLastChange();

  private:

    std::string mType;
    std::string mSource;

    std::vector < CMiaseChange* > mListOfChanges;
  };

#endif //CMIASEMODEL

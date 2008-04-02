// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseBase.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASEBASE
#define CMIASEBASE

#include <string>
#include <vector>

class CMiaseNotes
  {

  public:

    CMiaseNotes();

    ~CMiaseNotes();

    std::string getNotes();
    std::string getXmlNs();

    void setNotes(std::string notes);
    void setXmlNs(std::string xmlNs);

  private:

    std::string mNotes;
    std::string mXmlNs;
  };

class CMiaseAnnotation
  {

  public:

    CMiaseAnnotation();

    ~CMiaseAnnotation();

    std::string getAnyNote();
    std::string getXmlNs();

    void setAnyNote(std::string anyAnnotation);
    void setXmlNs(std::string xmlNs);

  private:

    std::string mAnyAnnotation;
    std::string mXmlNs;
  };

class CMiaseBase
  {

  public:

    CMiaseBase();

    ~CMiaseBase();

    std::string getMetaId();

    void setMetaId(std::string metaId);

    void addAnnotation (CMiaseAnnotation* ann);
    void addNotes (CMiaseNotes* notes);

    void setAnyNote(std::string anyAnnotation);
    void setXmlNs(std::string xmlNs);

    CMiaseAnnotation* getAnnotation();
    CMiaseNotes* getNotes();

  private:

    std::string mMetaId;

    CMiaseAnnotation* mpAnnotation;
    CMiaseNotes* mpNotes;
  };

class CMiaseBaseEnhanced : public CMiaseBase
  {

  public:

    CMiaseBaseEnhanced();

    ~CMiaseBaseEnhanced();

    std::string getId();
    std::string getName();

    void setId(std::string id);
    void setName(std::string name);

  private:

    std::string mId;
    std::string mName;
  };
#endif //CMIASEBASE

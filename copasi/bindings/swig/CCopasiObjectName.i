
%{

#include "report/CCopasiObjectName.h"

%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


class CCopasiObjectName : public std::string
{
   public:
#ifdef COPASI_DEBUG
     CCopasiObjectName();
     
     CCopasiObjectName(const std::string& name);

     CCopasiObjectName(const CCopasiObjectName& src);
     
     ~CCopasiObjectName();
#endif /* COPASI_DEBUG */

     CCopasiObjectName getPrimary() const;

     CCopasiObjectName getRemainder() const;

     std::string getObjectType() const;

     std::string getObjectName() const;

     unsigned C_INT32 getElementIndex(const unsigned C_INT32 & pos = 0) const;

     std::string getElementName(const unsigned C_INT32 & pos, const bool & unescape = true) const;
  
     static std::string escape(const std::string & name);

     static std::string unescape(const std::string & name);
};


class CRegisteredObjectName: public CCopasiObjectName
{
  public:
    CRegisteredObjectName();

    CRegisteredObjectName(const std::string & name);

    CRegisteredObjectName(const CRegisteredObjectName & src);

    ~CRegisteredObjectName();

    // static const std::set<CRegisteredObjectName*> & getSet();

};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */



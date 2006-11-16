
%{

#include "report/CCopasiObjectName.h"

%}


class CCopasiObjectName : public std::string
{
   public:
     CCopasiObjectName();
     
     CCopasiObjectName(const std::string& name);

     CCopasiObjectName(const CCopasiObjectName& src);
     
     ~CCopasiObjectName();

     CCopasiObjectName getPrimary() const;

     CCopasiObjectName getRemainder() const;

     std::string getObjectType() const;

     std::string getObjectName() const;

     std::string getElementName(const unsigned C_INT32 & pos, const bool & unescape = true) const;
  
     static std::string escape(const std::string & name);

     static std::string unescape(const std::string & name);

     %extend
     {
       std::string getString()
       {
        return *self;
       }
     }
};


class CRegisteredObjectName: public CCopasiObjectName
{
  public:
    CRegisteredObjectName();

    CRegisteredObjectName(const std::string & name);

    CRegisteredObjectName(const CRegisteredObjectName & src);

    ~CRegisteredObjectName();


};



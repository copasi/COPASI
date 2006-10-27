%{

#include "report/CCopasiContainer.h"

%}


#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


%ignore CCopasiContainer::CCopasiContainer(const std::string& name,
                                           const CCopasiContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);

class CCopasiContainer: public CCopasiObject
{
  private:
    CCopasiContainer();

  public:
    static CCopasiContainer* Root;
    static CCopasiObject* ObjectFromName(const CCopasiObjectName& objName);
    static void init();

#ifdef COPASI_DEBUG
    CCopasiContainer(const std::string& name,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "CN",
                     const unsigned C_INT32 & flag = CCopasiObject::Container);

    virtual ~CCopasiContainer();
#endif /* COPASI_DEBUG */    
    

};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */



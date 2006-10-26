
%{

#include "utilities/CCopasiVector.h"

%}

template < class CType > class CCopasiVector:
        protected std::vector< CType * >, public CCopasiContainer
{
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      CCopasiVector(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL,
                    const unsigned C_INT32 &
                    flag = CCopasiObject::Vector);

      CCopasiVector(const CCopasiVector < CType > & src,
                    const CCopasiContainer * pParent = NULL);

      virtual ~CCopasiVector();
      
      virtual void swap(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo);
      virtual bool add(CType * src, bool adopt = false);
      virtual void remove(const unsigned C_INT32 & index);
      virtual bool remove(CCopasiObject * pObject);
      virtual const CCopasiObject * getObject(const CCopasiObjectName &name) const;
      virtual unsigned C_INT32 size() const;
      virtual unsigned C_INT32 getIndex(const CCopasiObject * pObject) const;


};


template < class CType > class CCopasiVectorN: public CCopasiVector < CType >
{
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      CCopasiVectorN(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL);

      CCopasiVectorN(const CCopasiVectorN < CType > & src,
                     const CCopasiContainer * pParent = NULL);

      virtual ~CCopasiVectorN();

      virtual bool add(CType * src, bool adopt = false);
      virtual void remove(const std::string & name);
      virtual const CCopasiObject * getObject(const CCopasiObjectName &name) const;
      virtual unsigned C_INT32 getIndex(const std::string &name) const;
};

%template(TaskListBase) CCopasiVector<CCopasiTask>;
%template(TaskList) CCopasiVectorN<CCopasiTask>;

typedef CCopasiVectorN<CCopasiTask> TaskList;

#ifndef COPASIVECTOR_H
#define COPASIVECTOR_H

#include <vector>

#include "CReadConfig.h"
#include "CWriteConfig.h"

template < class CType > 
class CCopasiVector
{
// Attributes
private:
    /**
     *
     */
    vector < CType > mTypes;
    
// Operations
public:
    /**
     *
     */
    CCopasiVector() {}


    /**
     *
     */
    ~CCopasiVector() {}

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig & configbuffer, long size)
        {
            CType c;
            long Fail = 0;
    
            for (long i = 0; i < size; i++)
            {
                if (Fail = c.Load(configbuffer)) return Fail;
                mTypes.push_back(c);
            }
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    long Save(CWriteConfig & configbuffer)
        {
            long Fail = 0;

            for (long i = 0; i < Size(); i++)
                if (Fail = mTypes[i].Save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    long Add(CType & metab)
        {
            if ( Get(metab.GetName()) ) return 1;

            mTypes.push_back(metab);
        }

    /**
     *
     */
    long Delete(long index)
        {
            if ( 0 <= index && index < Size() )
            {
                mTypes.erase(&mTypes[index], &mTypes[index+1]);
                return 0;
            }
    
            return 1;
        }

    /**
     *
     */
    long Delete(const string & name)
        {
            long i;
    
            for ( i = 0; i < Size(); i++ )
                if ( name == mTypes[i].GetName() ) 
                    break;

            return Delete(i);
        }

    /**
     *
     */
    CType * Get(long index)
        {
            if ( 0 <= index && index < Size() )
                return &mTypes[index];
            
            return NULL;
        }

    /**
     *
     */
    CType * Get(const string & name)
        {
            for (long i = 0; i < Size(); i++ )
                if ( name == mTypes[i].GetName() ) 
                    return &mTypes[i];
        
            return NULL;
        }

    /**
     *
     */
    long Size() {return mTypes.size();}
};

#endif

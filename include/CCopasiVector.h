#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#include <vector>

#include "CCopasiMessage.h"
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
    CCopasiVector() {DefinedInsertAllowed = NULL;}


    /**
     *
     */
    ~CCopasiVector() {cout << "~CCopasiVector " << endl;}

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig & configbuffer, long size)
        {
            long Fail = 0;
            
            mTypes.resize(size);
            for (long i = 0; i < size; i++)
                if (Fail = mTypes[i].Load(configbuffer)) break;
    
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
    long Add(CType src)
        {
            if ( DefinedInsertAllowed ) 
            {
                if ( ! (*DefinedInsertAllowed)(src) ) FatalError();
            }
            else 
            {
                if ( ! DefaultInsertAllowed(src) ) FatalError();
            }
                
            mTypes.push_back(src);
        }

    /**
     *
     */
    long Delete() {mTypes.clear();}
    
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
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
    
            return Delete(Index);
        }

    /**
     *
     */
    SetInsertAllowed(short (*function)(CType src))
        {
            DefinedInsertAllowed = function;
        }

    CType &operator[](long index) 
        {
            if ( 0 <= index && index < Size() ) return mTypes[index];
            FatalError();
        }   
    CType operator[](long index) const    
        {
            if ( 0 <= index && index < Size() ) return mTypes[index];
            FatalError();
        }   

    CType &operator[](const string &name) 
        {
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return mTypes[Index];
        }   

    CType operator[](const string &name) const
        {
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return mTypes[Index];
        }   


    /**
     *
     */
    long Size() {return mTypes.size();}

private:
    /**
     *
     */
    short DefaultInsertAllowed(CType src)
        {return ( GetIndex(src.GetName()) == -1 );}
    
    /**
     *
     */
    short (*DefinedInsertAllowed)(CType src);
    
    /**
     *
     */
    long GetIndex(const string &name)
        {
            long i;
            
            for (i = 0; i < Size(); i++)
                if ( name == mTypes[i].GetName() ) 
                    return i;
            
            return -1;
        }
};

#endif // COPASI_CCopasiVector







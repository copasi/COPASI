#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#include <vector>
#include <iostream>

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
    vector < CType > *mTypes;

// Operations
public:
    /**
     *
     */
    CCopasiVector() {mTypes = new vector < CType >;}

    /**
     *
     */
    ~CCopasiVector() 
        {
            delete mTypes;
            cout << "~CCopasiVector " << endl;
        }

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig & configbuffer, long size)
        {
            long Fail = 0;
            
            mTypes->resize(size);
            for (long i = 0; i < size; i++)
                if (Fail = (*mTypes)[i].Load(configbuffer)) break;
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    long Save(CWriteConfig & configbuffer)
        {
            long Fail = 0;

            for (long i = 0; i < Size(); i++)
                if (Fail = (*mTypes)[i].Save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    void Add(CType src)
        {
	    if ( ! IsInsertAllowed(src) ) FatalError();
                
            mTypes->push_back(src);
        }

    /**
     *
     */
    void Delete() 
        {
            for (long i = 0; i < mTypes->size(); i++)
               (*mTypes)[i].Delete();
            mTypes->clear();
        }
    
    /**
     *
     */
    void Delete(long index)
        {
            if ( 0 <= index && index < Size() )
                (*mTypes)[index].Delete();
                mTypes->erase(&(*mTypes)[index], &(*mTypes)[index+1]);
        }

    /**
     *
     */
    void Delete(const string & name)
        {
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
    
            return Delete(Index);
        }

    CType &operator[](long index) 
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }   

    CType operator[](long index) const    
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }
    
    CType &operator[](const string &name) 
        {
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    CType operator[](const string &name) const
        {
            long Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    /**
     *
     */
    long Size() {return mTypes->size();}

private:
    /**
     *
     */
    virtual short IsInsertAllowed(CType src)
        {return (GetIndex(src.GetName()) == -1);}
 
    /**
     *
     */
    long GetIndex(const string &name)
        {
            long i;
            
            for (i = 0; i < Size(); i++)
                if ( name == (*mTypes)[i].GetName() ) 
                    return i;
            
            return -1;
        }
};

// template < class CType > short DefaultIsInsertAllowed(CType src)
// {return ( GetIndex(src.GetName()) == -1 );}

#endif // COPASI_CCopasiVector







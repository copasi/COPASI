#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#include <vector>
#include <iostream>
#include <typeinfo>

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
    CCopasiVector() 
    {mTypes = new vector < CType >;}

    /**
     *
     */
    ~CCopasiVector() {delete mTypes;}

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer, C_INT32 size)
        {
            C_INT32 Fail = 0;
            
            mTypes->resize(size);
            for (C_INT32 i = 0; i < size; i++)
                if (Fail = (*mTypes)[i].Load(configbuffer)) break;
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 Save(CWriteConfig & configbuffer)
        {
            C_INT32 Fail = 0;

            for (C_INT32 i = 0; i < Size(); i++)
                if (Fail = (*mTypes)[i].Save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    void Add(const CType & src)
        {
	    if ( ! IsInsertAllowed(src) ) FatalError();
            // This is not very efficient !!!
            // It results in a lot of resizing of the vector !!!
            mTypes->push_back(src);
        }

    /**
     *
     */
    void Delete() 
        {
            for (C_INT32 i = 0; i < mTypes->size(); i++)
                (*mTypes)[i].Delete();
            mTypes->clear();
        }
    
    /**
     *
     */
    void Delete(C_INT32 index)
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
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
    
            return Delete(Index);
        }

    CType &operator[](C_INT32 index) 
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }   

    CType operator[](C_INT32 index) const    
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }
    
    CType &operator[](const string &name) 
        {
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    CType operator[](const string &name) const
        {
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    /**
     *
     */
    C_INT32 Size() const {return mTypes->size();}

private:
    /**
     *
     */
    virtual C_INT16 IsInsertAllowed(const CType & src)
        {return (GetIndex(src.GetName()) == -1);}
 
    /**
     *
     */
    C_INT32 GetIndex(const string &name) const
        {
            C_INT32 i;
            
            for (i = 0; i < Size(); i++)
                if ( name == (*mTypes)[i].GetName() ) 
                    return i;
            
            return -1;
        }
};

template < class CType > 
class CCopasiVectorP
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
    CCopasiVectorP() {mTypes = new vector < CType >;}

    /**
     *
     */
    ~CCopasiVectorP() {delete mTypes;}

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer, C_INT32 size)
        {
            // This is broken
            FatalError();
            
            C_INT32 Fail = 0;
            
            mTypes->resize(size);
            for (C_INT32 i = 0; i < size; i++)
                if (Fail = (*mTypes)[i]->Load(configbuffer)) break;
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 Save(CWriteConfig & configbuffer)
        {
            C_INT32 Fail = 0;

            for (C_INT32 i = 0; i < Size(); i++)
                if (Fail = (*mTypes)[i]->Save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    void Add(const CType & src)
        {
	    if ( ! IsInsertAllowed(src) ) FatalError();
            // This is not very efficient !!!
            // It results in a lot of resizing of the vector !!!
            mTypes->push_back(src);
        }

    /**
     *
     */
    void Delete() 
        {
            for (C_INT32 i = 0; i < mTypes->size(); i++)
            {
                (*mTypes)[i]->Delete();
                delete (*mTypes)[i];
            }
            
            mTypes->clear();
        }
    
    /**
     *
     */
    void Delete(C_INT32 index)
        {
            if ( 0 <= index && index < Size() )
            {
                (*mTypes)[index]->Delete();
                delete (*mTypes)[i];
                
                mTypes->erase(&(*mTypes)[index], &(*mTypes)[index+1]);
            }
        }

    /**
     *
     */
    void Delete(const string & name)
        {
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
    
            return Delete(Index);
        }

    CType &operator[](C_INT32 index) 
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }   

    CType operator[](C_INT32 index) const    
        {
            if (index < 0 || Size() <= index) FatalError();
            return (*mTypes)[index];
        }
    
    CType &operator[](const string &name) 
        {
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    CType operator[](const string &name) const
        {
            C_INT32 Index = GetIndex(name);
            if ( Index == -1 ) FatalError();
            
            return (*mTypes)[Index];
        }   

    /**
     *
     */
    C_INT32 Size() const {return mTypes->size();}

private:
    /**
     *
     */
    virtual C_INT16 IsInsertAllowed(const CType & src)
        {return (GetIndex(src->GetName()) == -1);}
 
    /**
     *
     */
    C_INT32 GetIndex(const string &name) const
        {
            C_INT32 i;
            
            for (i = 0; i < Size(); i++)
                if ( name == (*mTypes)[i]->GetName() ) 
                    return i;
            
            return -1;
        }
};
#endif // COPASI_CCopasiVector

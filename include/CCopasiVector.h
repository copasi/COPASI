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
    C_INT32 load(CReadConfig & configbuffer, C_INT32 size)
        {
            C_INT32 Fail = 0;
            
            mTypes->resize(size);
            for (C_INT32 i = 0; i < size; i++)
                if (Fail = (*mTypes)[i].load(configbuffer)) break;
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 save(CWriteConfig & configbuffer)
        {
            C_INT32 Fail = 0;

            for (C_INT32 i = 0; i < size(); i++)
                if (Fail = (*mTypes)[i].save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    void add(const CType & src)
        {
	    if ( ! isInsertAllowed(src) ) fatalError();
            // This is not very efficient !!!
            // It results in a lot of resizing of the vector !!!
            mTypes->push_back(src);
        }

    /**
     *
     */
    void cleanup() 
        {
            for (C_INT32 i = 0; i < mTypes->size(); i++)
                (*mTypes)[i].cleanup();
            mTypes->clear();
        }
    
    /**
     *
     */
    void cleanup(C_INT32 index)
        {
            if ( 0 <= index && index < size() )
                (*mTypes)[index].cleanup();
            mTypes->erase(&(*mTypes)[index], &(*mTypes)[index+1]);
        }

    /**
     *
     */
    void cleanup(const string & name)
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
    
            return cleanup(Index);
        }

    CType &operator[](C_INT32 index) 
        {
            if (index < 0 || size() <= index) fatalError();
            return (*mTypes)[index];
        }   

    CType operator[](C_INT32 index) const    
        {
            if (index < 0 || size() <= index) fatalError();
            return (*mTypes)[index];
        }
    
    CType &operator[](const string &name) 
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
            
            return (*mTypes)[Index];
        }   

    CType operator[](const string &name) const
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
            
            return (*mTypes)[Index];
        }   

    /**
     *
     */
    C_INT32 size() const {return mTypes->size();}

private:
    /**
     *
     */
    virtual C_INT16 isInsertAllowed(const CType & src)
        {return (getIndex(src.getName()) == -1);}
 
    /**
     *
     */
    C_INT32 getIndex(const string &name) const
        {
            C_INT32 i;
            
            for (i = 0; i < size(); i++)
                if ( name == (*mTypes)[i].getName() ) 
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
    C_INT32 load(CReadConfig & configbuffer, C_INT32 size)
        {
            // This is broken
            fatalError();
            
            C_INT32 Fail = 0;
            
            mTypes->resize(size);
            for (C_INT32 i = 0; i < size; i++)
                if (Fail = (*mTypes)[i]->load(configbuffer)) break;
    
            return Fail;
        }

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 save(CWriteConfig & configbuffer)
        {
            C_INT32 Fail = 0;

            for (C_INT32 i = 0; i < size(); i++)
                if (Fail = (*mTypes)[i]->save(configbuffer)) return Fail;
    
            return Fail;
        }

    /**
     *
     */
    void add(const CType & src)
        {
	    if ( ! isInsertAllowed(src) ) fatalError();
            // This is not very efficient !!!
            // It results in a lot of resizing of the vector !!!
            mTypes->push_back(src);
        }

    /**
     *
     */
    void cleanup() 
        {
            for (C_INT32 i = 0; i < mTypes->size(); i++)
            {
                (*mTypes)[i]->cleanup();
                delete (*mTypes)[i];
            }
            
            mTypes->clear();
        }
    
    /**
     *
     */
    void cleanup(C_INT32 index)
        {
            if ( 0 <= index && index < size() )
            {
                (*mTypes)[index]->cleanup();
                delete (*mTypes)[i];
                
                mTypes->erase(&(*mTypes)[index], &(*mTypes)[index+1]);
            }
        }

    /**
     *
     */
    void cleanup(const string & name)
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
    
            return cleanup(Index);
        }

    CType &operator[](C_INT32 index) 
        {
            if (index < 0 || size() <= index) fatalError();
            return (*mTypes)[index];
        }   

    CType operator[](C_INT32 index) const    
        {
            if (index < 0 || size() <= index) fatalError();
            return (*mTypes)[index];
        }
    
    CType &operator[](const string &name) 
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
            
            return (*mTypes)[Index];
        }   

    CType operator[](const string &name) const
        {
            C_INT32 Index = getIndex(name);
            if ( Index == -1 ) fatalError();
            
            return (*mTypes)[Index];
        }   

    /**
     *
     */
    C_INT32 size() const {return mTypes->size();}

private:
    /**
     *
     */
    virtual C_INT16 isInsertAllowed(const CType & src)
        {return (getIndex(src->getName()) == -1);}
 
    /**
     *
     */
    C_INT32 getIndex(const string &name) const
        {
            C_INT32 i;
            
            for (i = 0; i < size(); i++)
                if ( name == (*mTypes)[i]->getName() ) 
                    return i;
            
            return -1;
        }
};
#endif // COPASI_CCopasiVector

/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/CNodeO.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:55 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: CNodeO.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Define the node object in user defined function
 *****************************************************************************/
#ifndef COPASI_CNodeO
#define COPASI_CNodeO

#include <string>

#include "copasi.h" 
//#include "model/model.h"
#include "function/CNodeK.h"
#include "CDatum.h"

class CReadConfig;

class CNodeO: public CNodeK
  {
    // Attributes
  private:
    /**
     *  A datum needed to specify the identifiers
     */
    CDatum mDatum;
    /**
     *  The left branch of the tree originating from this node
     */
    CNodeO * mLeft;

    /**
     *  The right branch of the tree originating from this node
     */
    CNodeO * mRight;

  public:
    /**
     * Default constructor
     */
    CNodeO();

    /**
     * Constructor for operator
     * @param "const char" type
     * @param "const char" subtype
     */
    CNodeO(char type, char subtype);

    /**
     * Constructor for identifier
     * @param "const string" &name
     */
    CNodeO(const std::string & name);

    /**
     * Constructor for a constant
     * @param "const C_FLOAT64" constant
     */
    CNodeO(C_FLOAT64 constant);

    /**
     * Destructor
     */
    virtual ~CNodeO();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Retreives the datum of an identifier node
     *  @return "const CDatum &" datum
     */
    const CDatum & getDatum() const;

    virtual C_FLOAT64 value();

    /**
     * Retrieving mLeft the left branch of a node
     * @return CNodeO
     */
    CNodeO & getLeft() const;

    /**
     * Retrieving mRight the left branch of a node
     * @return CNodeO
     */
    CNodeO & getRight() const;
    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeO &left
     */
    void setLeft(CNodeO & left);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeO *pleft
     */
    void setLeft(CNodeO * pleft);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeO &right
     */
    void setRight(CNodeO & right);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeO *pright
     */
    void setRight(CNodeO * pright);

    C_INT16 isLeftValid() const;

    C_INT16 isRightValid() const;
  };
#endif

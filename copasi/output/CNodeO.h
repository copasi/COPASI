/*****************************************************************************
* PROGRAM NAME: CNodeO.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Define the node object in user defined function
*****************************************************************************/
#ifndef COPASI_CNodeO
#define	COPASI_CNodeO

#include <string>
#include <vector>

#include "copasi.h"
#include "model/model.h"
#include "utilities/utilities.h"
#include "function/function.h"
#include "CDatum.h"

class CNodeO: public CNodeK
{
private:
	/**
	 * pointer to a datum object (if an identifier)
	 */
	CDatum *mDatum;
	/**
	 *  The left branch of the tree originating from tyhis node
	 */
	CNodeO * mLeft;

	/**
	 *  The right branch of the tree originating from tyhis node
	 */
	CNodeO * mRight;


public:
	/**
     * Default constructor
     */
    CNodeO();
	/**
	 * Constructor for operator
	 * @param datum points to a CDatum
	 */
	CNodeO(CDatum &datum);

	/**
	 * Destructor
	 */
	~CNodeO();

	/**
	 * Delete
	 */
	void cleanup();
    
	/**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig & configbuffer);

	/**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 save(CWriteConfig & configbuffer) const;

   /**
    * Calculates the value of this sub-tree
	*/
   C_FLOAT64 value(CModel *model);

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

  /**
   * Return Datum in each node
   */
  CDatum *getDatum();

  C_INT16 isLeftValid() const;

  C_INT16 isRightValid() const; 

};
#endif


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

class CNodeO: public CNodeK
{
private:
	/**
	 *  Title of the node.
	 */
	string mTitle; 
	/**
     *  Type of the node's Datum.
	 */
	C_INT32 mDatumType;
	/**
	 * I String of the node
	 */
	string mI;
	/**
	 * J String of the node
	 */
	string mJ;

public:
	/**
     * Default constructor
     */
    CNodeO();
	/**
	 * Constructor for operator
	 * @param "const string" title
	 * @param "const C_INT32" type
	 * @param "const string" i_str
	 * @param "const string" j_str
	 */
	CNodeO(string title, C_INT32 type, string i_str, string j_str);

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
     * Retrieving the Title of a node
     * @return string
     */
    string getTitle() const;

   /**
    * Retrieving I String of a node
    * @return string
    */
   string getIString() const;

   /**
    * Retrieving J String of a node
    * @return string
    */
   string getJString() const;
  

   /**
    * Setting Title of the node
    * @param "const string" &title
    */
   void setTitle(const string& title);

   /**
    * Setting I String of the node
    * @param "const string" &i_string
    */

   void setIString(const string & i_string);

   /**
    * Setting I String of the node
    * @param "const string" &j_string
    */
   void setJString(const string & j_string);

   /**
    * Get the node's Datum type
	*/
   C_INT32 getDatumType() const;

   /**
    * Set the node's Datum Type
	*/
   void setDatumType(const C_INT32 datumType);
};
#endif


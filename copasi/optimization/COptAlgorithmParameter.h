/**
 *  File name: COptAlgorithmParameter.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the implementation (.cpp file) of the 
 *           COptAlgorithmParameter class. 
 *           It contains an optimization algorithm parameter with its name
 *           and value.
 */

#ifndef COPTALGORITHMPARAMETER_H
#define COPTALGORITHMPARAMETER_H

#include <string>

//
class COptAlgorithmParameter
{

  //data members
 private:

  string mName;
  double mValue;

  //implementation
 public:

   /**
    * Default constructor
    */
   COptAlgorithmParameter();

   /**
    * Destructor
    */
   ~COptAlgorithmParameter();

  /**
   * Copy constructor
   * @param source a COptAlgorithmParameter object for copy
   */
  COptAlgorithmParameter(const COptAlgorithmParameter& source);

  /**
   * Object assignment overloading
   * @param source a COptAlgorithmParameter object for copy
   * @return an assigned COptAlgorithmParameter object
   */
  COptAlgorithmParameter& operator=(const COptAlgorithmParameter& source);



   /**
    * set name
    * @param aName a string to be set as mName
    */
  void setName(string aName);

   /**
    * get the private member mName
    * @return mName
    */
  string getName();

   /**
    * set the value
    * @param aValue the double to be set as the private member mValue
    */
  void setValue(double aValue);

   /**
    * get the private member mValue
    * @return the mValue, the private member
    */
  double getValue();

};


#endif  // the end 



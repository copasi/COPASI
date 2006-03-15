/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDimension.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/15 23:35:43 $
   End CVS Header */

#ifndef COPASI_DIMENSION
 #define COPASI_DIMENSION

#include <string>
 #include <vector>
 #include "copasi.h"

/**
 * CDimension class.
 * The class describes the dimension of a value, usually a CFunctionParameter.
 * 
 * The dimension is given as a triple of real numbers: (amount of substance, volume, time).
 * It can also be "unknown" or "contradiction". The actual unit can be constructed from the 
 * dimension and the three basic units from the CModel class (which is done in the 
 * getDisplayString() method).
 */
class CDimension
  {
  public:

    CDimension();

    void setUnknown();
    bool isUnknown() const;

    void setContradiction();
    bool isContradiction() const;

    void setDimension(const C_FLOAT64 & d1, const C_FLOAT64 & d2, const C_FLOAT64 & d3);

    std::string getDisplayString() const;
    std::string getDebugString() const;

    bool operator==(const CDimension & rhs) const;
    CDimension operator+(const CDimension & rhs) const;
    CDimension operator-(const CDimension & rhs) const;
    CDimension compare(const CDimension & rhs) const;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CDimension & d);

  private:

    C_FLOAT64 mD1;
    C_FLOAT64 mD2;
    C_FLOAT64 mD3;

    bool mUnknown;
    bool mContradiction;

    static std::string constructDisplayElement(const std::string & base, C_FLOAT64 exponent);
  };

//******************************************************************+

class CFunction;
class CReaction;
class CEvaluationNode;

/**
 * CFindDimensions class.
 * The class tries to find the dimensions of the "PARAMETER" variable nodes 
 * in a function tree.
 * 
 * The function is specified in the constructor. After that the dimension of the root node
 * has to be specified. This can be done with either of the two public findDimensions() 
 * methods. 
 * The result can be retrieved using the getDimensions() method.
 */
class CFindDimensions
  {
  public:

    /**
     * construct the class for a given function
     */
    CFindDimensions(const CFunction* function);

    /**
     * initialize the known dimensions (from the parameter roles) and 
     * set the others to "unknown". This is called by the constructor.
     */
    void setupDimensions();

    /**
     * find the dimensions from explicitly given root node dimension
     */
    void findDimensions(CDimension rootDim);

    /**
     * find the dimensions for a function that is used in a reaction
     * the dimension of the root node depends on the number of compartments
     * that are involved in the reaction 
     */
    void findDimensions(bool isMulticompartment);

    /**
     * find the dimensions for both a one-compartment and a multi-compartment reaction
     */
    std::vector<std::string> findDimensionsBoth();

    const std::vector<CDimension> & getDimensions() const;

    //print the content of mDimensions to cout
    void printDebugOutput() const;

    void setUseHeuristics(bool flag);

  private:

    const CFunction * mpFunction;
    std::vector<CDimension> mDimensions;
    CDimension mRootDimension;
    bool mUseHeuristics;

    //find dim for all parameters
    void findDimensions();

    //find dim for one parameter
    void findDimension(unsigned C_INT32 index);

    CDimension findDimension(const CEvaluationNode * node,
                             const CEvaluationNode * requestingNode = NULL);
  };

#endif

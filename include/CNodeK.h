/*  CNodeK
 *  
 *  CNodeK.cpp based on UDKType.cpp from
 *  (C) Pedro Mendes 1995-2000
 * 
 *  Created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CNodeK
#define COPASI_CNodeK

#include <string>
#include <vector>

#include "CReadConfig.h"
#include "CWriteConfig.h"

// symbols for CNodeK types and values
#define N_NOP '@'

#define N_ROOT '%'       // the root note
#define N_OPERATOR 'O'   // operator: + - * / ^ ( )
#define N_IDENTIFIER 'I' // see specific subtypes
#define N_FUNCTION 'F'   // see specific subtypes
#define N_NUMBER 'N'     // a C_FLOAT64 constant

// subtypes for N_FUNCTION
#define N_LOG10 'L'
#define N_LOG 'l'
#define N_EXP 'e'
#define N_SIN 'S'
#define N_COS 'C'
#define N_RND 'R'
#define N_GAUSS 'G'
#define N_BOLTZ 'B'

// subtypes for N_IDENTIFIER
#define N_SUBSTRATE 's'
#define N_PRODUCT 'p'
#define N_MODIFIER 'm'
#define N_KCONSTANT 'k'

class CNodeK 
{
    // Attributes
private:
    /**
     *  The type of the node. One of N_ROOT, N_OPERATOR, N_IDENTIFIER,
     *  N_FUNCTION, N_NUMBER
     */
    char mType;

    /**
     *  The subtype of a node.
     *  for type N_FUNCTION one of: N_LOG10, N_LOG, N_EXP, N_SIN, N_COS,
     *  N_RND, N_GAUSS, N_BOLTZ
     *  for type N_IDENTIFIER one of:N_SUBSTRATE, N_PRODUCT, N_MODIFIER,
     *  N_KCONSTANT
     *  for type N_OPERATOR one of: + - * / ^ ( ) ...
     */
    char mSubtype;

    /**
     *  The left branch of the tree originating from tyhis node
     */
    CNodeK * mLeft;

    /**
     *  The right branch of the tree originating from tyhis node
     */
    CNodeK * mRight;

    /**
     *  The value of a node of type N_NUMBER
     */
    C_FLOAT64 mConstant;

    /**
     *  The name of the node for type N_IDENTIFIER
     */
    string mName;

    /**
     *  The index of the node for type N_IDENTIFIER
     */
    C_INT32 mIndex;
    // Operations
public:
    /**
     * Default constructor
     */
    CNodeK();

    /**
     * Constructor for operator
     * @param "const char" type
     * @param "const char" subtype
     */
    CNodeK(char type, char subtype);

    /**
     * Constructor for identifier
     * @param "const string" &name
     */
    CNodeK(const string & name);

    /**
     * Constructor for a constant
     * @param "const C_FLOAT64" constant
     */
    CNodeK(C_FLOAT64 constant);

    /**
     * Destructor
     */
    ~CNodeK();

    /**
     * Delete
     */
    void Delete();
    
    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 Save(CWriteConfig & configbuffer);

    /**
     * Retrieving mType the type of a node
     * @return char
     */
    char GetType();

    /**
     * Retrieving mSubtype the subtype of a node
     * @return char
     */
    char GetSubtype();

    /**
     * Retrieving mLeft the left branch of a node
     * @return CNodeK
     */
    CNodeK & GetLeft();

    /**
     * Retrieving mName the name of a node
     * @return string
     */
    CNodeK & GetRight();

    /**
     * Retrieving mName the name of a node
     * @return string
     */
    string GetName() const;

    /**
     * Retrieving value of a node
     * @return C_FLOAT64
     */
    C_FLOAT64 GetConstant();

    /**
     * Retrieving index the name of a node
     * @return C_INT32
     */
    C_INT32 GetIndex();

    /**
     * Setting mType the subtype of a node
     * @param "const char" type
     */
    void SetType(const char ype);

    /**
     * Setting mSubtype the subtype of a node
     * @param "const char" subtype
     */
    void SetSubtype(const char subtype);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK &left
     */
    void SetLeft(CNodeK & left);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK *pleft
     */
    void SetLeft(CNodeK * pleft);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK &right
     */
    void SetRight(CNodeK & right);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK *pright
     */
    void SetRight(CNodeK * pright);

    /**
     * Setting mName the name of an identifier
     * @param "const string" &name
     */
    void SetName(const string & name);

    /**
     * Setting the value of a number
     * @param C_FLOAT64 &constant
     */
    void SetConstant(C_FLOAT64 & constant);

    /**
     * Setting the index of an identifier
     * @param C_INT32 &index
     */
    void SetIndex(C_INT32 index);

    /**
     *  This checks whether mLeft points to a valid CNodeK
     *  @return int 1 or 0
     */
    C_INT16 IsLeftValid();

    /**
     *  This checks whether mRight points to a valid CNodeK
     *  @return int 1 or 0
     */
    C_INT16 IsRightValid();

    /**
     *  This checks whether the node is a number (mType = N_NUMBER)
     *  @return int 1 or 0
     */
    C_INT16 IsNumber();

    /**
     *  This checks whether the node is an identifier (mType = N_IDENTIFIER)
     *  @return int 1 or 0
     */
    C_INT16 IsIdentifier() const;

    /**
     *  This checks whether the node is a operator (mType = N_OPERATOR)
     *  @return int 1 or 0
     */
    C_INT16 IsOperator();

    /**
     *  This returns the left precedence value of a node
     *  @return int
     */
    C_INT16 LeftPrecedence();

    /**
     *  This returns the right precedence value of a node
     *  @return int
     */
    C_INT16 RightPrecedence();

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param "vector < C_FLOAT64 * >" &identifiers
     *  @return C_FLOAT64
     */
    C_FLOAT64 Value(vector < void * > &identifiers);
};

#endif // COPASI_CNodeK

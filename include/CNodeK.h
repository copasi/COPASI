// CNodeK
// 
// CNodeK.cpp based on UDKType.cpp from
// (C) Pedro Mendes 1995-2000
//
// Created for Copasi by Stefan Hoops
// (C) Stefan Hoops 2001

#ifndef COPASI_CNodeK
#define COPASI_CNodeK

#include <vector>
#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"

// symbols for CNodeK types and values
#define N_NOP '@'

#define N_ROOT '%'       // the root note
#define N_OPERATOR 'O'   // operator: + - * / ^ ( )
#define N_IDENTIFIER 'I' // see specific subtypes
#define N_FUNCTION 'F'   // see specific subtypes
#define N_NUMBER 'N'     // a double constant

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

class CModel;        // This should not be here !

class CNodeK
{
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
    CNodeK(const char type, const char subtype);

    /**
     * Constructor for identifier
     * @param "const string" &name
     */
    CNodeK(const string &name);

    /**
     * Constructor for a constant
     * @param "const double" constant
     */
    CNodeK(const double constant);

    /**
     * Destructor
     */
    ~CNodeK();

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK &left
     */
    void SetLeft(CNodeK &left);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK &pleft
     */
    void SetLeft(CNodeK *pleft);


    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK &right
     */
    void SetRight(CNodeK &right);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK &pright
     */
    void SetRight(CNodeK *pright);

    /**
     * Setting mSubtype the subtype of a node
     * @param "const char" subtype
     */
    void SetSubtype(const char subtype);
    
    /**
     * Setting mIndex the index of a node
     * @param "const int" index
     */
    void SetIndex(const int index);
    
    /**
     * Setting mName the name of a node
     * @param "const string" &name
     */
    void SetName(const string &name);

    /**
     * Retrieving mLeft the left branch of a node
     * @return CNodeK
     */
    CNodeK &GetLeft(void);

    /**
     * Retrieving mRight the right branch of a node
     * @return CNodeK
     */
    CNodeK &GetRight(void);

    /**
     * Retrieving mName the name of a node
     * @return string
     */
    string GetName(void);

    /**
     * Retrieving mType the type of a node
     * @return char
     */
    char GetType(void);

    /**
     * Retrieving mSubtype the subtype of a node
     * @return char
     */
    char GetSubtype(void);

    /**
     * Transforming a node to a number (mType = N_NUMBER) 
     * and setting the value
     * @param "const double" constant
     */
    void Constant(const double constant);

    /**
     * Transforming a node to a operator (mType = N_OPERATOR) and 
     * setting the operation
     * @param "const char" operation
     */
    void Operator(const char operation); //operator is not allowed

    /**
     * Transforming a node to a function (mType = N_FUNCTION)
     */
    void Function(void);

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param "const CModel" &model
     *  @param double *s
     *  @param int r
     *  @return double
     */
    double Value(const CModel &model, 
                 double *s,            // what is s ???
                 int r);               // what is r ???

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    int Load(CReadConfig &configbuffer);

    /**
     *  This checks whether mLeft points to a valid CNodeK
     *  @return int 1 or 0
     */
    int IsLeftValid(void);

    /**
     *  This checks whether mRight points to a valid CNodeK
     *  @return int 1 or 0
     */
    int IsRightValid(void);

    /**
     *  This checks whether the node is a number (mType = N_NUMBER)
     *  @return int 1 or 0
     */
    int IsNumber(void);

    /**
     *  This checks whether the node is an identifier (mType = N_IDENTIFIER)
     *  @return int 1 or 0
     */
    int IsIdentifier(void);

    /**
     *  This checks whether the node is a operator (mType = N_OPERATOR)
     *  @return int 1 or 0
     */
    int IsOperator(void);

    /**
     *  This returns the right precedence value of a node
     *  @return int
     */
    int RightPrecedence(void);

    /**
     *  This returns the left precedence value of a node
     *  @return int
     */
    int LeftPrecedence(void);

private:
    /**
     *  The type of the node. One of N_ROOT, N_OPERATOR, N_IDENTIFIER,
     *  N_FUNCTION, N_NUMBER
     */
    char mType;       // type of node

    /**
     *  The subtype of a node.
     *  for type N_FUNCTION one of: N_LOG10, N_LOG, N_EXP, N_SIN, N_COS,
     *  N_RND, N_GAUSS, N_BOLTZ
     *  for type N_IDENTIFIER one of:N_SUBSTRATE, N_PRODUCT, N_MODIFIER,
     *  N_KCONSTANT
     *  for type N_OPERATOR one of: + - * / ^ ( ) ...
     */
    char mSubtype;    // what operator or function

    /**
     *  The left branch of the tree originating from tyhis node
     */
    CNodeK *mLeft;    // pointer to the node on the left on this tree

    /**
     *  The right branch of the tree originating from tyhis node
     */
    CNodeK *mRight;   // pointer to the node on the right on this tree

    /**
     *  The value of a node of type N_NUMBER
     */
    double mConstant; // value of the constant (if one)

    /**
     *  The index of the node for type N_IDENTIFIER
     */
    int mIndex;       // index for the identitifier in its class

    /**
     *  The name of the node for type N_IDENTIFIER
     */
    string mName;     // name of the identifier (if one)
};

class CNodeKVector : public vector< CNodeK >
{
public:
    /**
     *  Default constructor. 
     *  Creates an empty vector with size 0.
     */
    CNodeKVector();

    /**
     *  Specific constructor. 
     *  Creates a vector with size CNodeK objects.
     *  @param size number of CNodeK objects in the vector.
     */
    CNodeKVector(int size);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    int Load(CReadConfig &configbuffer);
    
};

#endif // COPASI_CNodeK

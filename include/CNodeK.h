// CNodeK.h based on UDKType.h
//
/////////////////////////////////////////////////////////////////////////////

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
     *
     */
    CNodeK();

    /**
     *
     */
    CNodeK(const char type, const char subtype);

    /**
     *
     */
    CNodeK(const string &name);

    /**
     *
     */
    CNodeK(const double constant);

    /**
     *
     */
    ~CNodeK();

    /**
     *
     */
    void SetLeft(CNodeK &pt);
    void SetLeft(CNodeK *pt);

    /**
     *
     */
    void SetRight(CNodeK &pt);
    void SetRight(CNodeK *pt);

    /**
     *
     */
    void SetSubtype(const char subtype);
    
    /**
     *
     */
    void SetIndex(const int index);
    
    /**
     *
     */
    void SetName(const string &name);

    /**
     *
     */
    CNodeK &GetLeft(void);

    /**
     *
     */
    CNodeK &GetRight(void);

    /**
     *
     */
    string GetName(void);

    /**
     *
     */
    char GetType(void);

    /**
     *
     */
    char GetSubtype(void);

    /**
     *
     */
    void Constant(const double constant);

    /**
     *
     */
    void Operator(const char operation); //operator is not allowed

    /**
     *
     */
    void Function(void);

    /**
     *
     */
    double Value(const CModel &model, 
                 double *s,            // what is s ???
                 int r);               // what is r ???

    /**
     *
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *
     */
    int Load(CReadConfig &configbuffer);

    /**
     *
     */
    int IsLeftValid(void);

    /**
     *
     */
    int IsRightValid(void);

    /**
     *
     */
    int IsNumber(void);

    /**
     *
     */
    int IsIdentifier(void);

    /**
     *
     */
    int IsOperator(void);

    /**
     *
     */
    int RightPrecedence(void);

    /**
     *
     */
    int LeftPrecedence(void);

private:
    /**
     *
     */
    char mType;       // type of node

    /**
     *
     */
    char mSubtype;    // what operator or function

    /**
     *
     */
    CNodeK *mLeft;    // pointer to the node on the left on this tree

    /**
     *
     */
    CNodeK *mRight;   // pointer to the node on the right on this tree

    /**
     *
     */
    double mConstant; // value of the constant (if one)

    /**
     *
     */
    int mIndex;       // index for the identitifier in its class

    /**
     *
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
     *  Creates a vector with size CNodeK.
     *  @param size number of CNodeK objectss in the vector.
     */
    CNodeKVector(int size);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     */
    int Load(CReadConfig &configbuffer);
    
};

#endif // COPASI_CNodeK

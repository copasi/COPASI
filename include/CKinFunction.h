// CKinFunction.h based on UDKType.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CNodeK.h"

class CModel; // this should not be hear

// a class of kinetic functions
class CKinFunction
{
// Implementation
public:
    /**
     *
     */
    CKinFunction();

    /**
     *
     */
    CKinFunction(const string &name, const string &description);

    /**
     *
     */
    ~CKinFunction();

    /**
     *
     */
    int AddNode(const char type, const char subtype);

    /**
     *
     */
    int AddNode(const double constant);

    /**
     *
     */
    int AddNode(const string &name);

    /**
     *
     */
    double CalcValue(CModel &model, double *s, int r);

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
    int Parse(void);

    /**
     *
     */
    int FindId(const string &name);

    /**
     *
     */
    short IsReversible(void);

    /**
     *
     */
    string GetName(void);

    /**
     *
     */
    int SubstratesNo(void);

    /**
     *
     */
    int ProductsNo(void);

    /**
     *
     */
    int ModifiersNo(void);

    /**
     *
     */
    int ParametersNo(void);

    /**
     *
     */
    string GetParameterName(int i);

    /**
     *
     */
    string GetModifierName(int i);

    /**
     *
     */
    void SetParameterName(const string &name, int index);

    /**
     *
     */
    void SetModifierName(const string &name, int index);
    
    /**
     *
     */
    vector < CNodeK * > *Substrates(void);
    
    /**
     *
     */
    vector < CNodeK * > *Products(void);
    
    /**
     *
     */
    vector < CNodeK * > *Modifiers(void);
    
    /**
     *
     */
    vector < CNodeK * > *Parameters(void);
    
    /**
     *
     */
    void SetIdentifierType(string &Id, int type);

    /**
     *
     */
    int GetIdentifierType(string &Id);

    /**
     *
     */
    void ResetModfsParams(void);

private:
    /**
     *
     */
    void ClearNodes(void);

    /**
     *
     */
    int ConnectNodes(void);

    /**
     *
     */
    CNodeK *ParseExpression(int priority);

    /**
     *
     */
    CNodeK *ParsePrimary(void);

    /**
     *
     */
    string mName;         // a name for the function

    /**
     *
     */
    string mDescription;  // string representation of the function

    /**
     *
     */
    CNodeKVector mNodes;  // an array of NodeK (the binary tree)

    /**
     *
     */
    int mReversible;      // TRUE if this is a reversible type


    /**
     *
     */
    int nidx;             // index to the node being analysed (+/-)


    /**
     *
     */
    vector < CNodeK * > mSubstrates;  // number of substrates

    /**
     *
     */
    vector < CNodeK * > mProducts;  // number of products

    /**
     *
     */
    vector < CNodeK * > mModifiers;    // number of modifiers

    /**
     *
     */
    vector < CNodeK * > mParameters;          // number of parameters

#ifdef XXXX
    int NodeSize;         // the number of nodes in the tree

    int errfl;            // error flag (0=no error)
    int errnode;          // the node that generated an error
    int TotSub;           // number of substrates in the equation
    int SubIdx;           // Index for substrates in the equation

    int TotProd;          // number of products in the equation
    int ProdIdx;          // Index for products in the equation

    int TotModf;          // number of modifiers in the equation
    vector <string> Modf; // array of modifier names

    int TotParm;          // number of kinetic constants in the equation
    vector <string> Parm; // array of kinetic constants
#endif // XXXX
};

#endif // COPASI_CKinFunction

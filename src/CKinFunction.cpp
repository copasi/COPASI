// UDKType.cpp : classes for user-defined kinetic types
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "globals.h"
#include "CKinFunction.h"
#include "lexkk.h"


////////////////////////////////////
// CKinFunction implementation

CKinFunction::CKinFunction()
{
//    Node.SetSize(10, 10);
//    NodeSize = 0;
    mReversible = FALSE;
//    TotSub = TotProd = TotModf = TotParm = 0;
//    Parm.SetSize(10, 10);
//    Modf.SetSize(2, 2);
}

CKinFunction::CKinFunction(const string &name, const string &description)
{
    mName = name;
    mDescription = description;
    mReversible = FALSE;
//    Node.SetSize(10, 10);
//    NodeSize = 0;
//    TotSub = TotProd = TotModf = TotParm = 0;
//    Parm.SetSize(10, 10);
//    Modf.SetSize(2, 2);
}


CKinFunction::~CKinFunction()
{
    // delete the node objects
//    ClearNodes();
    // frees the space taken up by the node pointers
//    Node.RemoveAll();
}

// a new node (operator | function)
int CKinFunction::AddNode(const char type, const char subtype)
{
    if (type == N_IDENTIFIER) FatalError()
    mNodes.push_back(CNodeK(type, subtype));
    return mNodes.size();
}

// a new node (numeric constant)
int CKinFunction::AddNode(const double constant)
{
    mNodes.push_back(CNodeK(constant));
    return mNodes.size();
}

// a new node (identifier)
int CKinFunction::AddNode(const string &name)
{
    // we need to check wheter a identifier with this name already exists
    for (int i=0; i<mNodes.size(); i++)
        if( mNodes[i].GetName() == name ) FatalError();
    
    mNodes.push_back(CNodeK(name));
    return mNodes.size();
}

// this evaluates the function
double CKinFunction::CalcValue(CModel &model, double *s, int r)
{
    return mNodes[0].GetLeft().Value(model, s, r);
}

string CKinFunction::GetName(void) {return mName;}

vector < CNodeK * > *CKinFunction::Substrates(void) {return &mSubstrates;}
    
vector < CNodeK * > *CKinFunction::Products(void) {return &mProducts;}
    
vector < CNodeK * > *CKinFunction::Modifiers(void) {return &mModifiers;}
    
vector < CNodeK * > *CKinFunction::Parameters(void) {return &mParameters;}

int CKinFunction::Save(CWriteConfig &configbuffer)
{
    int Fail = 0;
    
    if (Fail = configbuffer.SetVariable("FunctionName", "string", &mName))
        return Fail;
    
    if (Fail = configbuffer.SetVariable("Description", "string", &mDescription))
        return Fail;

    if (Fail = mNodes.Save(configbuffer))
        return Fail;
    
    return Fail;
}

int CKinFunction::Load(CReadConfig &configbuffer)
{
    int Fail = 0;
    
    configbuffer.SetMode(CReadConfig_SEARCH);
    configbuffer.SetMode(CReadConfig_LOOP);

    if (Fail = configbuffer.GetVariable("FunctionName", "string", &mName))
        return Fail;

    configbuffer.SetMode(-CReadConfig_SEARCH);
    configbuffer.SetMode(-CReadConfig_LOOP);

    if (Fail = configbuffer.GetVariable("Description", "string", &mDescription))
        return Fail;

    if (Fail = mNodes.Load(configbuffer))
        return Fail;
    
    //Initialize the identifier arrays
    for (int i=0; i<mNodes.size(); i++)
    {
        if (mNodes[i].GetType() == N_IDENTIFIER)
            switch (mNodes[i].GetSubtype())
            {
            case N_SUBSTRATE: 
                mSubstrates.push_back(&mNodes[i]); 
                break;

            case N_PRODUCT: 
                mProducts.push_back(&mNodes[i]); 
                break;

            case N_MODIFIER: 
                mModifiers.push_back(&mNodes[i]); 
                break;

            case N_KCONSTANT: 
                mParameters.push_back(&mNodes[i]); 
                break;

            default: 
                assert(FALSE);
                break;
            }
    }
    
    return Fail;
}

// this function deletes the elements in the node tree
void CKinFunction::ClearNodes(void)
{
    mNodes.resize(0);
}

// parse the function into a binary tree through successive calls to lexkk
int CKinFunction::Parse(void)
{
    int i;
    char *buffer;
    YY_BUFFER_STATE kkbuff;
    // create a buffer big enough to contain the function string
    buffer = new char[mDescription.length()+1];
    // copy it into the buffer
    strcpy(buffer, mDescription.c_str());
    // input for the scanner is from the buffer
    kkbuff = kk_scan_string(buffer);
    // add the root node
    AddNode(N_ROOT, N_NOP);
    // call the lexical analyser successively until done
    for (i=1; i!=0;)
    {
        i = kklex();
        switch (i)
        {
        case N_IDENTIFIER: AddNode(kktext); break;
        case N_NUMBER:     AddNode(atof(kktext)); break;
        case '+':          AddNode(N_OPERATOR, '+'); break;
        case '-':          AddNode(N_OPERATOR, '-'); break;
        case '*':          AddNode(N_OPERATOR, '*'); break;
        case '/':          AddNode(N_OPERATOR, '/'); break;
        case '^':          AddNode(N_OPERATOR, '^'); break;
        case '(':          AddNode(N_OPERATOR, '('); break;
        case ')':          AddNode(N_OPERATOR, ')'); break;
        case N_LOG:        AddNode(N_FUNCTION, N_LOG); break;
        case N_LOG10:      AddNode(N_FUNCTION, N_LOG10); break;
        case N_EXP:        AddNode(N_FUNCTION, N_EXP); break;
        case N_SIN:        AddNode(N_FUNCTION, N_SIN); break;
        case N_COS:        AddNode(N_FUNCTION, N_COS); break;
        case N_NOP:        // this is an error
            ClearNodes();
            delete [] buffer;
            kk_delete_buffer(kkbuff);
            // should return the position for the erroneous character
            return 1;
        }
    }
    // release allocated memory
    delete [] buffer;
    kk_delete_buffer(kkbuff);
    // connect the nodes
    return ConnectNodes();
}

// builds the binary tree using recursion 
// (this was taken from a compiler's book very long ago!)
int CKinFunction::ConnectNodes(void)
{
    int errfl = 0;     // !!! do we need this?
    int errnode = -1;  // !!! do we need this?
    int i;
    // initialise the control variables
    nidx = 1;

    // point all Left & Right to the root node
    for (i=1; i<mNodes.size(); i++)
    {
        mNodes[i].SetLeft(mNodes[0]);
        mNodes[i].SetRight(mNodes[0]);
    }
    
    // update pointers and references in the tree
    mNodes[0].SetLeft(ParseExpression(0));

    // further checking for errors
    if (mNodes[0].IsLeftValid() && 
        mNodes[0].GetLeft().IsOperator() && 
        mNodes[0].GetLeft().GetSubtype() == '(')
    {
//  sprintf(errstr, "ERROR - missing operand");
//  errnode should index the node in error 
//  but we don't know its index (pointer only)
        FatalError();
        errnode = -1;
        errfl++;
    }

    for (i=1; i<mNodes.size() && !errfl; i++)
    {
        switch (mNodes[i].GetType())
        {
        case N_OPERATOR:
            if (!mNodes[i].IsLeftValid()      ||
                !mNodes[i].IsRightValid()     ||
                &mNodes[i].GetLeft()  == &mNodes[0] || 
                &mNodes[i].GetRight() == &mNodes[0])
                if (mNodes[i].GetSubtype() != '(' &&
                    mNodes[i].GetSubtype() != ')')
                {
                    if (!errfl)
                    {
//            sprintf(errstr, "ERROR - incorrect number of operands");
                        FatalError();
                        errnode = i;
                    }
                    errfl++;
                }
            if (!errfl)
            {
                if (mNodes[i].IsLeftValid()    && 
                    mNodes[i].GetLeft().IsOperator() && 
                    mNodes[i].GetLeft().GetSubtype() == '(' )
                {
//           sprintf(errstr, "ERROR - missing operand");
                    FatalError();
                    errnode = -1;
                    errfl++;
                }
                if (mNodes[i].IsRightValid()    && 
                    mNodes[i].GetRight().IsOperator() && 
                    mNodes[i].GetRight().GetSubtype() == ')' )
                {
//           sprintf(errstr, "ERROR - missing operand");
                    FatalError();
                    errnode = -1;
                    errfl++;
                }
            }
            break;
        case N_IDENTIFIER:
            if (&mNodes[i].GetLeft()  == &mNodes[0] || 
                &mNodes[i].GetRight() == &mNodes[0])
            {
                if (!errfl)
                {
//           sprintf(errstr, "ERROR - unexpected identifier");
                    FatalError();
                    errnode = -1;
                }
                ++errfl;
            }
            break;
        case N_NUMBER:
            if (&mNodes[i].GetLeft()  == &mNodes[0] || 
                &mNodes[i].GetRight() == &mNodes[0])
            {
                if (!errfl)
                {
//           sprintf(errstr, "ERROR - unexpected constant");
                    FatalError();
                    errnode = -1;
                }
                ++errfl;
            }
            break;
        }
    }
    // return 
    return errfl;
}

// this function is part of the algorithm that builds the binary tree
CNodeK *CKinFunction::ParseExpression(int priority)
{
    int errfl = 0;     // !!! do we need this?
    int errnode = -1;  // !!! do we need this?

    CNodeK *lhs, *rhs;
    int op;

    lhs = ParsePrimary();
    if (!lhs) return NULL;

    while( nidx < mNodes.size() && 
           mNodes[nidx].IsOperator() && 
           priority < mNodes[nidx].LeftPrecedence())
    {
        op = nidx;
        rhs = NULL;
        ++nidx;
        rhs = ParseExpression(mNodes[op].RightPrecedence());
        if (!rhs)
        {
            if (!errfl)
            {
//    sprintf(errstr, "ERROR - unexpected operator");
                FatalError();
                errnode = op;
            }
            ++errfl;
        }
        else
        {
            mNodes[op].SetLeft(*lhs);
            mNodes[op].SetRight(*rhs);
            lhs = &mNodes[op] ;
        }
    }
    return lhs;
}

// this function is part of the algorithm that builds the binary tree
CNodeK *CKinFunction::ParsePrimary(void)
{
    int errfl = 0;     // !!! do we need this?
    int errnode = -1;  // !!! do we need this?

    CNodeK *npt, *primary;
    char t;
    int op;
    npt = NULL;

//    if (Node[nidx]==NULL)
    if (nidx >= mNodes.size())
    {
//  if (!errfl) // execute only if no previous error
//   errnode = nidx-1;
//  errfl++;
        return NULL;
    } 
    
    if (mNodes[nidx].IsNumber() || 
        mNodes[nidx].IsIdentifier())
    {
        t = 'K';
    }
    else 
    {
        t = mNodes[nidx].GetSubtype();
    }
    
    switch (t)
    {
    case 'K':
        mNodes[nidx].SetLeft(NULL);
        mNodes[nidx].SetRight(NULL);
        npt = &mNodes[nidx];
        ++nidx;
        return npt;
    case '(': ++nidx;
        npt = ParseExpression(0);
        if (nidx < mNodes.size()      && 
            mNodes[nidx].IsOperator() && 
            mNodes[nidx].GetSubtype() == ')')
        {
            ++nidx;
            return npt;
        }
        else
        {
            if (!errfl) // execute only if no previous error
            {
                //             sprintf(errstr, "ERROR - right bracket missing");
                errnode = nidx;
            }
            errfl++;
        }
    case '+':
    case '-':
    case N_LOG:
    case N_LOG10:
    case N_EXP:
    case N_SIN:
    case N_COS:   op = nidx; primary = NULL;
        ++nidx;
        primary = ParsePrimary();
        if (primary==NULL)
        {
            if (!errfl)
            {
//                  sprintf(errstr, "ERROR - missing operator");
                errnode = op;
            }
            ++errfl;
        }
        else
        {
            npt = &mNodes[op];
            // unary operators are taken as functions
            mNodes[op].Function();
            mNodes[op].SetLeft(primary);
            mNodes[op].SetRight(NULL);
            return &mNodes[op];
        }
    default:  return NULL;
    }
    if (nidx < mNodes.size()      &&
        mNodes[nidx].IsOperator() &&
        mNodes[nidx].GetSubtype() == '(')
    {
        ++nidx;
        if (nidx < mNodes.size()      &&
            mNodes[nidx].IsOperator() &&
            mNodes[nidx].GetSubtype() == ')')
        {
            mNodes[nidx].SetLeft(npt);
            mNodes[nidx].SetRight(NULL);
            return &mNodes[nidx];
        }
        else ParseExpression(0);
    }
}

// finds the first occurrence of ID as an identifier name 
int CKinFunction::FindId(const string &Id)
{
    for (int i=0; i<mNodes.size(); i++)
        if (mNodes[i].IsIdentifier() &&
            mNodes[i].GetName() == Id)
            return i;
    return -1;
}

short CKinFunction::IsReversible(void)
{
    return (short) mReversible;
}

// returns the number of substrates in the equation
int CKinFunction::SubstratesNo(void) {return mSubstrates.size();}

// returns the number of products in the equation
int CKinFunction::ProductsNo(void) {return mProducts.size();}

// returns the number of modifiers in the equation
int CKinFunction::ModifiersNo(void) {return mModifiers.size();}

// returns the number of kinetic constants in the equation
int CKinFunction::ParametersNo(void) {return mParameters.size();}

// returns the name of a parameter
string CKinFunction::GetParameterName(int index)
{
    assert(0 <= index && index < mParameters.size());
    return mParameters[index]->GetName();
}

// returns the name of a parameter
string CKinFunction::GetModifierName(int index)
{
    assert(0 <= index && index < mModifiers.size());
    return mModifiers[index]->GetName();
}

// returns the name of a parameter
void CKinFunction::SetParameterName(const string &name, int index)
{
    // we need to check wheter a identifier with this name already exists
    for (int i=0; i<mNodes.size(); i++)
        if( mNodes[i].GetName() == name ) FatalError();
    
    assert(0 <= index && index < mParameters.size());
    mParameters[index]->SetName(name);
}

// returns the name of a parameter
void CKinFunction::SetModifierName(const string &name, int index)
{
    // we need to check wheter a identifier with this name already exists
    for (int i=0; i<mNodes.size(); i++)
        if( mNodes[i].GetName() == name ) FatalError();
    
    assert(0 <= index && index < mModifiers.size());
    mModifiers[index]->SetName(name);
}

// sets the type of an Identifier
void CKinFunction::SetIdentifierType(string &name, int type)
{
    char Type;
    vector <CNodeK *> Array;
    
    switch (type)
    {
    case 0: 
        Type = N_SUBSTRATE;
        Array = mSubstrates;
        break;
        
    case 1: 
        Type = N_PRODUCT;
        Array = mProducts;
        break;
        
    case 2: 
        Type = N_MODIFIER;
        Array = mModifiers;
        break;
        
    case 3: 
        Type = N_KCONSTANT;
        Array = mParameters;
        break;

    default:
        FatalError();
        break;
    }
    
    for (int i=1; i<mNodes.size(); i++)
        if (mNodes[i].GetName() == name)
        {
            assert(mNodes[i].GetSubtype() == N_NOP);
            
            // set the type
            mNodes[i].SetSubtype(Type);
            // add it to the apropriate array
            Array.push_back(&mNodes[i]);
            // update the index
            mNodes[i].SetIndex(Array.size());
        }
}

// returns the type of an Identifier
int CKinFunction::GetIdentifierType(string &name)
{
    // search for the first node with this identifier
    for (int i=1; i<mNodes.size(); i++)
        if (mNodes[i].GetName() == name)
        {
            switch (mNodes[i].GetSubtype())
            {
            case N_SUBSTRATE: 
                return 0; 
                break;

            case N_PRODUCT: 
                return 1; 
                break;

            case N_MODIFIER: 
                return 2; 
                break;

            case N_KCONSTANT: 
                return 3; 
                break;

            default: 
                assert(FALSE);
                break;
            }
        }
    return -1;
}



// UDKType.cpp : classes for user-defined kinetic types
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "CKinFunction.h"
#include "lexkk.h"

short DefinedInsertAllowed(CNodeK src);

CKinFunction::CKinFunction() 
{
    SetReversible(FALSE);
    mCallParameters = new vector < CCallParameter >[1];
    (*mCallParameters)[0].SetType(CBaseCallParameter::VECTOR_DOUBLE);
    (*mCallParameters)[0].SetCount(-1);
    (*mCallParameters)[0].IdentifierTypes().resize(5);
    (*mCallParameters)[0].IdentifierTypes()[0] = 0;
    (*mCallParameters)[0].IdentifierTypes()[1] = N_SUBSTRATE;
    (*mCallParameters)[0].IdentifierTypes()[2] = N_PRODUCT;
    (*mCallParameters)[0].IdentifierTypes()[3] = N_MODIFIER;
    (*mCallParameters)[0].IdentifierTypes()[4] = N_KCONSTANT;
}

CKinFunction::CKinFunction(const string & name,
                           const string & description)
{
    SetReversible(FALSE);
    mCallParameters = new vector < CCallParameter >[1];
    (*mCallParameters)[0].SetType(CBaseCallParameter::VECTOR_DOUBLE);
    (*mCallParameters)[0].SetCount(-1);
    (*mCallParameters)[0].IdentifierTypes().resize(5);
    (*mCallParameters)[0].IdentifierTypes()[0] = 0;
    (*mCallParameters)[0].IdentifierTypes()[1] = N_SUBSTRATE;
    (*mCallParameters)[0].IdentifierTypes()[2] = N_PRODUCT;
    (*mCallParameters)[0].IdentifierTypes()[3] = N_MODIFIER;
    (*mCallParameters)[0].IdentifierTypes()[4] = N_KCONSTANT;

    SetName(name);
    SetDescription(description);
}

long CKinFunction::Load(CReadConfig & configbuffer)
{
    string TmpString;
    long Size = 0;
    long Index = 0;
    long Fail = 0;
    
    if (Fail = configbuffer.GetVariable("FunctionName", "string", &TmpString,
                                        CReadConfig::LOOP))
        return Fail;
    SetName(TmpString);
    
    if (Fail = configbuffer.GetVariable("Description", "string", &TmpString))
        return Fail;
    SetDescription(TmpString);

    if (Fail = configbuffer.GetVariable("Nodes", "long", &Size))
        return Fail;

    if (Fail = mNodes.Load(configbuffer,Size))
        return Fail;

    ConnectNodes();
    InitIdentifiers();
    
    return Fail;
}

long CKinFunction::Save(CWriteConfig & configbuffer)
{
    string TmpString;
    long TmpLong;
    long Fail = 0;
    
    TmpString = GetName();
    if (Fail = configbuffer.SetVariable("FunctionName", "string", &TmpString))
        return Fail;
    
    TmpString = GetDescription();
    if (Fail = configbuffer.SetVariable("Description", "string", &TmpString))
        return Fail;

    TmpLong = mNodes.Size();
    if (Fail = configbuffer.SetVariable("Nodes", "long", &TmpLong))
        return Fail;

    if (Fail = mNodes.Save(configbuffer))
        return Fail;
    
    return Fail;
}

CCopasiVector < CNodeK > & CKinFunction::Nodes() {return mNodes;}

void CKinFunction::SetIdentifierType(const string & name,
                                     char identifierType)
{
    pair < long, long > Index(0, 0);
    
    Index = FindIdentifier(name);
    
    if ( Index.first < 0 || Index.second < 0 ) FatalError();
    for (long i = 0; 
         i < (*(*mCallParameters)[Index.first].
              mIdentifiers)[Index.second].mNodes->size();
         i++)
        (*(*(*mCallParameters)[Index.first].
         mIdentifiers)[Index.second].mNodes)[i]->SetSubtype(identifierType);
}

long CKinFunction::Parse()
{
    long i;
    char *buffer;
    YY_BUFFER_STATE kkbuff;
    // create a buffer big enough to contain the function string
    buffer = new char[GetDescription().length()+1];
    // copy it into the buffer
    strcpy(buffer, GetDescription().c_str());
    // input for the scanner is from the buffer
    kkbuff = kk_scan_string(buffer);
    // add the root node
    mNodes.Add(CNodeK(N_ROOT, N_NOP));
    // call the lexical analyser successively until done
    for (i=1; i!=0;)
    {
        i = kklex();
        switch (i)
        {
        case N_IDENTIFIER: mNodes.Add(CNodeK(kktext)); break;
        case N_NUMBER:     mNodes.Add(CNodeK(atof(kktext))); break;
        case '+':          mNodes.Add(CNodeK(N_OPERATOR, '+')); break;
        case '-':          mNodes.Add(CNodeK(N_OPERATOR, '-')); break;
        case '*':          mNodes.Add(CNodeK(N_OPERATOR, '*')); break;
        case '/':          mNodes.Add(CNodeK(N_OPERATOR, '/')); break;
        case '^':          mNodes.Add(CNodeK(N_OPERATOR, '^')); break;
        case '(':          mNodes.Add(CNodeK(N_OPERATOR, '(')); break;
        case ')':          mNodes.Add(CNodeK(N_OPERATOR, ')')); break;
        case N_LOG:        mNodes.Add(CNodeK(N_FUNCTION, N_LOG)); break;
        case N_LOG10:      mNodes.Add(CNodeK(N_FUNCTION, N_LOG10)); break;
        case N_EXP:        mNodes.Add(CNodeK(N_FUNCTION, N_EXP)); break;
        case N_SIN:        mNodes.Add(CNodeK(N_FUNCTION, N_SIN)); break;
        case N_COS:        mNodes.Add(CNodeK(N_FUNCTION, N_COS)); break;
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
    InitIdentifiers();
    
    return ConnectNodes();
}

double CKinFunction::CalcValue(vector < double * > & identifiers)
{
    return mNodes[0].GetLeft().Value(identifiers);
}

void CKinFunction::ClearNodes() {mNodes.Delete();}

long CKinFunction::ConnectNodes()
{
    long errfl = 0;     // !!! do we need this?
    long errnode = -1;  // !!! do we need this?
    long i;

    // initialise the control variables
    mNidx = 1;

    // point all Left & Right to the root node
    for (i=1; i<mNodes.Size(); i++)
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

    for (i=1; i<mNodes.Size() && !errfl; i++)
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
            if (mNodes[i].IsLeftValid() || 
                mNodes[i].IsRightValid()  )
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
            if (mNodes[i].IsLeftValid() || 
                mNodes[i].IsRightValid()  )
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

CNodeK * CKinFunction::ParseExpression(short priority)
{
    long errfl = 0;     // !!! do we need this?
    long errnode = -1;  // !!! do we need this?

    CNodeK *lhs, *rhs;
    long op;

    lhs = ParsePrimary();
    if (!lhs) return NULL;

    while( mNidx < mNodes.Size() && 
           mNodes[mNidx].IsOperator() && 
           priority < mNodes[mNidx].LeftPrecedence())
    {
        op = mNidx;
        rhs = NULL;
        ++mNidx;
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

CNodeK * CKinFunction::ParsePrimary()
{
    long errfl = 0;     // !!! do we need this?
    long errnode = -1;  // !!! do we need this?

    CNodeK *npt, *primary;
    char t;
    long op;
    npt = NULL;

//    if (Node[mNidx]==NULL)
    if (mNidx >= mNodes.Size())
    {
//  if (!errfl) // execute only if no previous error
//   errnode = mNidx-1;
//  errfl++;
        return NULL;
    } 
    
    if (mNodes[mNidx].IsNumber() || 
        mNodes[mNidx].IsIdentifier())
    {
        t = 'K';
    }
    else 
    {
        t = mNodes[mNidx].GetSubtype();
    }
    
    switch (t)
    {
    case 'K':
        mNodes[mNidx].SetLeft(NULL);
        mNodes[mNidx].SetRight(NULL);
        npt = &mNodes[mNidx];
        ++mNidx;
        return npt;
    case '(': ++mNidx;
        npt = ParseExpression(0);
        if (mNidx < mNodes.Size()      && 
            mNodes[mNidx].IsOperator() && 
            mNodes[mNidx].GetSubtype() == ')')
        {
            ++mNidx;
            return npt;
        }
        else
        {
            if (!errfl) // execute only if no previous error
            {
                //             sprintf(errstr, "ERROR - right bracket missing");
                errnode = mNidx;
            }
            errfl++;
        }
    case '+':
    case '-':
    case N_LOG:
    case N_LOG10:
    case N_EXP:
    case N_SIN:
    case N_COS:   op = mNidx; primary = NULL;
        ++mNidx;
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
            mNodes[op].SetType(N_FUNCTION);
            mNodes[op].SetLeft(primary);
            mNodes[op].SetRight(NULL);
            return &mNodes[op];
        }
    default:  return NULL;
    }
    if (mNidx < mNodes.Size()      &&
        mNodes[mNidx].IsOperator() &&
        mNodes[mNidx].GetSubtype() == '(')
    {
        ++mNidx;
        if (mNidx < mNodes.Size()      &&
            mNodes[mNidx].IsOperator() &&
            mNodes[mNidx].GetSubtype() == ')')
        {
            mNodes[mNidx].SetLeft(npt);
            mNodes[mNidx].SetRight(NULL);
            return &mNodes[mNidx];
        }
        else ParseExpression(0);
    }
}

void CKinFunction::InitIdentifiers()
{
    CCallParameter::CIdentifier Identifier;
    pair < long, long > Index;

    (*(*mCallParameters)[0].mIdentifiers).clear();
    
    for(long i = 0; i < mNodes.Size(); i++)
    {
        if (mNodes[i].IsIdentifier())
        {
            Index = FindIdentifier(mNodes[i].GetName());
            if ( Index.first == -1 )
            {
                Identifier.GetName() = mNodes[i].GetName();
                (*(*mCallParameters)[0].mIdentifiers).push_back(Identifier);
                Index.second = (*mCallParameters)[0].mIdentifiers->size() - 1;
            }
            mNodes[i].SetIndex(Index.second);
            (*(*mCallParameters)[0].mIdentifiers)[Index.second].
                mNodes->push_back(&mNodes[i]);
        }
    }
    (*mCallParameters)[0].SetCount((*mCallParameters)[0].Identifiers(0).size());
}

CKinFunction::CCallParameter::CCallParameter()
{
    mIdentifiers = new vector < CIdentifier >;
}

CKinFunction::CCallParameter::~CCallParameter()
{
    delete [] mIdentifiers;
}

CKinFunction::CCallParameter::CIdentifier::CIdentifier()
{
    mNodes = new vector < CNodeK * >;
}

CKinFunction::CCallParameter::CIdentifier::~CIdentifier()
{
    delete [] mNodes;
}

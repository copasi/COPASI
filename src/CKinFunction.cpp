// UDKType.cpp : classes for user-defined kinetic types
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "CGlobals.h"
#include "CKinFunction.h"
#include "lexkk.h"
#include "utilities.h"

C_INT16 DefinedInsertAllowed(CNodeK src);

CKinFunction::CKinFunction()
{
    SetType(CBaseFunction::USERDEFINED);
    mNodes = NULL;
}

CKinFunction::CKinFunction(const string & name,
                           const string & description)
{
    SetType(CBaseFunction::USERDEFINED);
    mNodes = NULL;

    SetName(name);
    SetDescription(description);
}

void CKinFunction::Init() {mNodes = new CKinNodes;}

CKinFunction::~CKinFunction() {}

void CKinFunction::Delete() 
{
    if (mNodes) delete mNodes;
    mNodes = NULL;
    
    CBaseFunction::Delete();
}

void CKinFunction::Copy(const CKinFunction & in)
{
    CBaseFunction::Copy(in);

    for (C_INT32 i = 0; i < in.mNodes->Size(); i++)
        mNodes->Add((*in.mNodes)[i]);
    
    mNidx = in.mNidx;    

    ConnectNodes();
    InitIdentifiers();

}

C_INT32 CKinFunction::Load(CReadConfig & configbuffer,
                           CReadConfig::Mode mode)
{
    string TmpString;
    C_INT32 Size = 0;
    C_INT32 Index = 0;
    C_INT32 Fail = 0;
    
    if (Fail = CBaseFunction::Load(configbuffer,mode)) return Fail;
    
    Init();
    
    if (Fail = configbuffer.GetVariable("Nodes", "C_INT32", &Size))
        return Fail;

    if (Fail = mNodes->Load(configbuffer,Size))
        return Fail;

    ConnectNodes();
    InitIdentifiers();

    return Fail;
}

C_INT32 CKinFunction::Save(CWriteConfig & configbuffer)
{
    string TmpString;
    C_INT32 TmpLong;
    C_INT32 Fail = 0;
    
    if (Fail = CBaseFunction::Save(configbuffer)) return Fail;

#ifdef XXXX    
    TmpString = GetName();
    if (Fail = configbuffer.SetVariable("FunctionName", "string", &TmpString))
        return Fail;
    
    TmpString = GetDescription();
    if (Fail = configbuffer.SetVariable("Description", "string", &TmpString))
        return Fail;
#endif // XXXX

    TmpLong = mNodes->Size();
    if (Fail = configbuffer.SetVariable("Nodes", "C_INT32", &TmpLong))
        return Fail;

    if (Fail = mNodes->Save(configbuffer))
        return Fail;
    
    return Fail;
}

CKinFunction::CKinNodes & CKinFunction::Nodes() {return *mNodes;}

void CKinFunction::SetIdentifierType(const string & name,
                                     char identifierType)
{
    pair < C_INT32, C_INT32 > Index(0, 0);
    
    Index = FindIdentifier(name);
    
    if ( Index.first < 0 || Index.second < 0 )
        CCopasiMessage(CCopasiMessage::ERROR, MCKinFunction + 1, name.c_str(), 
                       GetName().c_str());

    for (C_INT32 i = 0; 
         i < ((CKinIdentifier *) CallParameters()[Index.first]->
              Identifiers()[Index.second])->mNodes.size();
         i++)
        ((CKinIdentifier *) CallParameters()[Index.first]->
           Identifiers()[Index.second])->mNodes[i]->SetSubtype(identifierType);
}

C_INT32 CKinFunction::Parse()
{
    C_INT32 i;
    char *buffer;
    YY_BUFFER_STATE kkbuff;
    // create a buffer big enough to contain the function string
    buffer = new char[GetDescription().length()+1];
    // copy it into the buffer
    strcpy(buffer, GetDescription().c_str());
    // input for the scanner is from the buffer
    kkbuff = kk_scan_string(buffer);
    // add the root node
    mNodes->Add(CNodeK(N_ROOT, N_NOP));
    // call the lexical analyser successively until done
    for (i=1; i!=0;)
    {
        i = kklex();
        switch (i)
        {
        case N_IDENTIFIER: mNodes->Add(CNodeK(kktext)); break;
        case N_NUMBER:     mNodes->Add(CNodeK(atof(kktext))); break;
        case '+':          mNodes->Add(CNodeK(N_OPERATOR, '+')); break;
        case '-':          mNodes->Add(CNodeK(N_OPERATOR, '-')); break;
        case '*':          mNodes->Add(CNodeK(N_OPERATOR, '*')); break;
        case '/':          mNodes->Add(CNodeK(N_OPERATOR, '/')); break;
        case '^':          mNodes->Add(CNodeK(N_OPERATOR, '^')); break;
        case '(':          mNodes->Add(CNodeK(N_OPERATOR, '(')); break;
        case ')':          mNodes->Add(CNodeK(N_OPERATOR, ')')); break;
        case N_LOG:        mNodes->Add(CNodeK(N_FUNCTION, N_LOG)); break;
        case N_LOG10:      mNodes->Add(CNodeK(N_FUNCTION, N_LOG10)); break;
        case N_EXP:        mNodes->Add(CNodeK(N_FUNCTION, N_EXP)); break;
        case N_SIN:        mNodes->Add(CNodeK(N_FUNCTION, N_SIN)); break;
        case N_COS:        mNodes->Add(CNodeK(N_FUNCTION, N_COS)); break;
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

C_FLOAT64 
CKinFunction::CalcValue(vector < CCallParameter > & callParameters) const
{
    return (*mNodes)[0].GetLeft().Value(callParameters[0].Identifiers());
}

void CKinFunction::ClearNodes() {mNodes->Delete();}

C_INT32 CKinFunction::ConnectNodes()
{
    C_INT32 errfl = 0;     // !!! do we need this?
    C_INT32 errnode = -1;  // !!! do we need this?
    C_INT32 i;

    // initialise the control variables
    mNidx = 1;

    // point all Left & Right to the root node
    for (i=1; i<mNodes->Size(); i++)
    {
        (*mNodes)[i].SetLeft((*mNodes)[0]);
        (*mNodes)[i].SetRight((*mNodes)[0]);
    }
    
    // update pointers and references in the tree
    (*mNodes)[0].SetLeft(ParseExpression(0));

    // further checking for errors
    if ((*mNodes)[0].IsLeftValid() && 
        (*mNodes)[0].GetLeft().IsOperator() && 
        (*mNodes)[0].GetLeft().GetSubtype() == '(')
    {
//  sprintf(errstr, "ERROR - missing operand");
//  errnode should index the node in error 
//  but we don't know its index (pointer only)
        CCopasiMessage(CCopasiMessage::ERROR, MCKinFunction + 2, 
                       GetName().c_str());
        errnode = -1;
        errfl++;
    }

    for (i=1; i<mNodes->Size() && !errfl; i++)
    {
        switch ((*mNodes)[i].GetType())
        {
        case N_OPERATOR:
            if (!(*mNodes)[i].IsLeftValid()      ||
                !(*mNodes)[i].IsRightValid()     ||
                &(*mNodes)[i].GetLeft()  == &(*mNodes)[0] || 
                &(*mNodes)[i].GetRight() == &(*mNodes)[0])
                if ((*mNodes)[i].GetSubtype() != '(' &&
                    (*mNodes)[i].GetSubtype() != ')')
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
                if ((*mNodes)[i].IsLeftValid()    && 
                    (*mNodes)[i].GetLeft().IsOperator() && 
                    (*mNodes)[i].GetLeft().GetSubtype() == '(' )
                {
//           sprintf(errstr, "ERROR - missing operand");
                    FatalError();
                    errnode = -1;
                    errfl++;
                }
                if ((*mNodes)[i].IsRightValid()    && 
                    (*mNodes)[i].GetRight().IsOperator() && 
                    (*mNodes)[i].GetRight().GetSubtype() == ')' )
                {
//           sprintf(errstr, "ERROR - missing operand");
                    FatalError();
                    errnode = -1;
                    errfl++;
                }
            }
            break;
        case N_IDENTIFIER:
            if ((*mNodes)[i].IsLeftValid() || 
                (*mNodes)[i].IsRightValid()  )
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
            if ((*mNodes)[i].IsLeftValid() || 
                (*mNodes)[i].IsRightValid()  )
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

CNodeK * CKinFunction::ParseExpression(C_INT16 priority)
{
    C_INT32 errfl = 0;     // !!! do we need this?
    C_INT32 errnode = -1;  // !!! do we need this?

    CNodeK *lhs, *rhs;
    C_INT32 op;

    lhs = ParsePrimary();
    if (!lhs) return NULL;

    while( mNidx < mNodes->Size() && 
           (*mNodes)[mNidx].IsOperator() && 
           priority < (*mNodes)[mNidx].LeftPrecedence())
    {
        op = mNidx;
        rhs = NULL;
        ++mNidx;
        rhs = ParseExpression((*mNodes)[op].RightPrecedence());
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
            (*mNodes)[op].SetLeft(*lhs);
            (*mNodes)[op].SetRight(*rhs);
            lhs = &(*mNodes)[op] ;
        }
    }
    return lhs;
}

CNodeK * CKinFunction::ParsePrimary()
{
    C_INT32 errfl = 0;     // !!! do we need this?
    C_INT32 errnode = -1;  // !!! do we need this?

    CNodeK *npt, *primary;
    char t;
    C_INT32 op;
    npt = NULL;

//    if (Node[mNidx]==NULL)
    if (mNidx >= mNodes->Size())
    {
//  if (!errfl) // execute only if no previous error
//   errnode = mNidx-1;
//  errfl++;
        return NULL;
    } 
    
    if ((*mNodes)[mNidx].IsNumber() || 
        (*mNodes)[mNidx].IsIdentifier())
    {
        t = 'K';
    }
    else 
    {
        t = (*mNodes)[mNidx].GetSubtype();
    }
    
    switch (t)
    {
    case 'K':
        (*mNodes)[mNidx].SetLeft(NULL);
        (*mNodes)[mNidx].SetRight(NULL);
        npt = &(*mNodes)[mNidx];
        ++mNidx;
        return npt;
    case '(': ++mNidx;
        npt = ParseExpression(0);
        if (mNidx < mNodes->Size()      && 
            (*mNodes)[mNidx].IsOperator() && 
            (*mNodes)[mNidx].GetSubtype() == ')')
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
            npt = &(*mNodes)[op];
            // unary operators are taken as functions
            (*mNodes)[op].SetType(N_FUNCTION);
            (*mNodes)[op].SetLeft(primary);
            (*mNodes)[op].SetRight(NULL);
            return &(*mNodes)[op];
        }
    default:  return NULL;
    }
    if (mNidx < mNodes->Size()      &&
        (*mNodes)[mNidx].IsOperator() &&
        (*mNodes)[mNidx].GetSubtype() == '(')
    {
        ++mNidx;
        if (mNidx < mNodes->Size()      &&
            (*mNodes)[mNidx].IsOperator() &&
            (*mNodes)[mNidx].GetSubtype() == ')')
        {
            (*mNodes)[mNidx].SetLeft(npt);
            (*mNodes)[mNidx].SetRight(NULL);
            return &(*mNodes)[mNidx];
        }
        else ParseExpression(0);
    }
}

void CKinFunction::InitIdentifiers()
{
    CKinIdentifier* pIdentifier;
    CBaseCallParameter* pCallParameter = new CBaseCallParameter;
    
    pCallParameter->IdentifierTypes().push_back(N_SUBSTRATE);
    pCallParameter->IdentifierTypes().push_back(N_PRODUCT);
    pCallParameter->IdentifierTypes().push_back(N_MODIFIER);
    pCallParameter->IdentifierTypes().push_back(N_KCONSTANT);
    
    C_INT32 i;

    pair < C_INT32, C_INT32 > Index;

    for (i = 0; i < CallParameters().size(); i++)
    {
        CallParameters()[i]->Delete();
        delete CallParameters()[i];
    }

    CallParameters().clear();
    CallParameters().push_back(pCallParameter);
    
    for(i = 0; i < mNodes->Size(); i++)
    {
        if ((*mNodes)[i].IsIdentifier())
        {
            Index = FindIdentifier((*mNodes)[i].GetName());
            if ( Index.first == -1 )
            {
                pIdentifier = new CKinIdentifier;
                pIdentifier->SetName((*mNodes)[i].GetName());
                pIdentifier->SetType((*mNodes)[i].GetSubtype());
                Index.second = CallParameters()[0]->Identifiers().size();
                CallParameters()[0]->Identifiers().push_back(pIdentifier);
            }
            (*mNodes)[i].SetIndex(Index.second);
            ((CKinIdentifier *) CallParameters()[0]->
             Identifiers()[Index.second])->
                mNodes.push_back(&(*mNodes)[i]);
        }
    }
    CallParameters()[0]->SetCount(CallParameters()[0]->Identifiers().size());
}

CKinIdentifier::CKinIdentifier() {}

CKinIdentifier::~CKinIdentifier() {} 

CKinFunction::CKinNodes::CKinNodes() {}

CKinFunction::CKinNodes::~CKinNodes() {}

C_INT16 CKinFunction::CKinNodes::IsInsertAllowed(const CNodeK & src)
{return TRUE;}

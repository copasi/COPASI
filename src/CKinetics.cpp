// ckinetics.cpp : implementation of the CKinetics class
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "globals.h"
#include "CKinetics.h"

double UDKin(void *M, double *s, int r);

/////////////////////////////////////////////////////////////////////////////
// CKinetics

// the default constructor
CKinetics::CKinetics()
{
    // SubstrateNo = 0;
    // ProductNo = 0;
    // ModifierNo = 0;
    // ParameterNo = 0;
    mFunction = NULL;
    mReversible = FALSE;
    // Param = NULL;
    // Modf = NULL;
    mUserDefined = FALSE;
}

// this constructor is for built-in kinetic types
CKinetics::CKinetics( const string &kiname, 
                      int subs, 
                      int prods, 
                      int mods, 
                      int prm, 
                      double (*ratefunc)(void *,double *, int), 
                      short rev )
{
    mName = kiname;
    // SubstrateNo = subs;
    // ProductNo = prods;
    // ModifierNo = mods;
    // ParameterNo = prm;
    mFunction = ratefunc;
    mReversible = rev;
    // Param = new string[ParameterNo];
    // Modf = new string[ModifierNo];
    mUserDefined = FALSE;
}

// this constructor is for user-defined types
CKinetics::CKinetics( CKinFunction &function )
{
    int i;
    mFunct = &function;
    mName = mFunct->GetName();
    mSubstrates = mFunct->Substrates();
    mProducts = mFunct->Products();
    mModifiers = mFunct->Modifiers();
    mParameters = mFunct->Parameters();
    
    mFunction = UDKin;
    mReversible = mFunct->IsReversible();
    mUserDefined = TRUE;
}

CKinetics::~CKinetics()
{
    // if( UserDefined && (Funct!=NULL) ) delete Funct;
    // if( Param!=NULL ) delete [] Param;
    // if( Modf!=NULL ) delete [] Modf;
}

void CKinetics::SetParameterName( const string &name, int index )
{
    mFunct->SetParameterName(name, index);
}

void CKinetics::SetModifierName( const string &name, int index )
{
    mFunct->SetModifierName(name, index);
}

// returns the index of the parameter specified
int CKinetics::FindParameter(const string &name)
{
    for(int i=0; i<(*mParameters).size(); i++)
        if((*mParameters)[i]->GetName() == name) return i;
    return -1;
}

// this function loads an object from the character buffer
int CKinetics::Load( char **buffer, int *line )
{
    char *pt;
    int i,lin, fields, dummy;
    string Err;
 
    lin = *line;
    pt = *buffer;
    // read the name
    if( ReadStringAfterEquals( pt, Name, lin ) == NULL ) return lin;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // user-defined status
    fields = sscanf( pt, "User-defined=%d\n", &dummy );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    UserDefined = (short) dummy;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // if not user defined we return and signal error
    if( !UserDefined ) return lin;
    // reversible status
    fields = sscanf( pt, "Reversible=%d\n", &dummy );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    Reversible = (short) dummy;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // number of substrates
    fields = sscanf( pt, "Substrates=%d\n", &SubstrateNo );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // number of products
    fields = sscanf( pt, "Products=%d\n", &ProductNo );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // number of modifiers
    fields = sscanf( pt, "Modifiers=%d\n", &ModifierNo );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // number of constants
    fields = sscanf( pt, "Constants=%d\n", &ParameterNo );
    if( ScanfFailed( fields, 1, lin ) ) return lin;
    if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
    lin++;
    // create the arrays
    Param = new string[ParameterNo];
    Modf = new string[ModifierNo];
    // array of modifier names
    for( i=0; i<ModifierNo; i++ )
    {
        if( ReadStringAfterEquals( pt, Modf[i], lin ) == NULL ) return lin;
        if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
        lin++;
    }
    // the array of parameter names
    for( i=0; i<ParameterNo; i++ )
    {
        if( ReadStringAfterEquals( pt, Param[i], lin ) == NULL ) return lin;
        if( (pt = PointPastNewLine( pt, lin )) == NULL ) return lin;
        lin++;
    }
    // create the CKinFunction object 
    Funct = new CKinFunction;
    // load it
    if( Funct->Load( &pt, &lin ) != 0 ) return lin;
    // set the function pointer to the right handler
    Function = UDKin;
    // update the line count
    *line = lin;
    // and the buffer pointer
    *buffer = pt;
    return 0;
}

// this function saves the object to to the CStdioFile
void CKinetics::Save( CStdioFile *fout )
{
    string StrOut;
    int i;

    // the file has already been opened
    // we don't care about exceptions here.
    // They should be caught by the calling function

    // the name
    StrOut = "UDKType=" + Name + "\n";
    fout->WriteString(LPCTSTR(StrOut));
    // the user-defined status
    StrOut.Format("User-defined=%d\n",(int)UserDefined);
    fout->WriteString(LPCTSTR(StrOut));
    if( UserDefined )
    {
        // the reversible status
        StrOut.Format("Reversible=%d\n",(int)Reversible);
        fout->WriteString(LPCTSTR(StrOut));
        // the number of substrates
        StrOut.Format("Substrates=%d\n", SubstrateNo);
        fout->WriteString(LPCTSTR(StrOut));
        // the number of products
        StrOut.Format("Products=%d\n", ProductNo);
        fout->WriteString(LPCTSTR(StrOut));
        // the number of modifiers
        StrOut.Format("Modifiers=%d\n", ModifierNo);
        fout->WriteString(LPCTSTR(StrOut));
        // the number of constants
        StrOut.Format("Constants=%d\n", ParameterNo);
        fout->WriteString(LPCTSTR(StrOut));
        // the array of modifier names
        for( i=0; i<ModifierNo; i++ )
        {
            StrOut.Format("Modifier%d=%s\n",i, LPCTSTR(Modf[i]) );
            fout->WriteString(LPCTSTR(StrOut));
        }
        // the array of parameter names
        for( i=0; i<ParameterNo; i++ )
        {
            StrOut.Format("Constant%d=%s\n",i, LPCTSTR(Param[i]) );
            fout->WriteString(LPCTSTR(StrOut));
        }
        // the CKinFunction object 
        Funct->Save( fout );
    }
}

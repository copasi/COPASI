// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CMetab

#include "copasi.h"

#include "CModel.h"
void CModel::AllocModel(C_INT32 nstep, 
                        C_INT32 nmetab, 
                        C_INT32 ingmet, 
                        C_INT32 nmoiety, 
                        C_INT32 ncompart)
{
    C_INT32 i;

    // allocate the arrays
    mMetabolite.resize(nmetab);
    mMoiety.resize(nmoiety);
    mStep.resize(nstep);
    mCompartment.resize(ncompart);

    mRow.resize(nmetab);
    mCol.resize(nstep);
    mIRow.resize(nmetab);
    mICol.resize(nstep);
    mKernelP.resize(nstep);

    // allocate the matrizes
    // allocate the colums
    mStoichiometry.resize(nmetab);
    mRedStoi.resize(nmetab);
    mConsRel.resize(nmetab);
    mReactStruct.resize(nstep);
    mML.resize(nmetab);

    // allocate each row
    for (i=0; i<nmetab; i++)
    {
        mStoichiometry[i].resize(nstep);
        mRedStoi[i].resize(nstep);
        mConsRel[i].resize(nmetab);
        mML[i].resize(nmetab);
    }
    for (i=0; i<nstep; i++)
        mReactStruct[i].resize(nmetab);

    // allocate the null-space matrix if needed
    if ((mKernelI>0) && (mKernelJ>0))
    {
        mKernel.resize(mKernelI);
        for (i=0; i<mKernelI; i++)
            mKernel[i].resize(mKernelJ);
    }
    mIntMetab = intmet;
}


void CModel::DeAlloc(void)
{
    C_INT32 i;

    //delete vectors
    mMetabolite.clear();
    mMoiety.clear();
    mStep.clear();
    mCompartment.clear();

    mRow.clear();
    mCol.clear();
    mIRow.clear();
    mICol.clear();
    mKernelP.clear();

    // delete matrizes
    mStoichiometry.clear();
    mRedStoi.clear();
    mConsRel.clear();
    mReactStruct.clear();
    mML.clear();
    mKernel.clear();

    // reset the kernel's dimensions
    mKernelI = mKernelJ = 0;
    mIntMetab = 0;
}


CModel::CModel()
{
    // no kernel matrix yet
    mKernelI = mKernelJ = 0;
    // allocate memory and set the pointers
    AllocModel(0, 0, 0, 0, 1);
    // default model name
    mTitle = "Untitled";
    // reset the transition time
    mTransTime = 0.0;
}


CModel::~CModel()
{
    // deallocate the memory in use and free pointers
    DeAlloc();
}


void CModel::Reset(C_INT32 nstep, 
                   C_INT32 nmetab, 
                   C_INT32 intmet, 
                   C_INT32 nmoiety, 
                   C_INT32 ncompart, 
                   const string &Title)
{
    // first deallocate the memory in use and free pointers
    DeAlloc();
    // then allocate new memory and set the pointers
    AllocModel(nstep, nmetab, intmet, nmoiety, ncompart);
    mTitle = Title;
    // reset the transition time
    mTransTime = 0.0;
}


void CModel::ResetStepMetab(C_INT32 nstep, C_INT32 nmetab, C_INT32 intmet, C_INT32 nmoiety)
{
    C_INT32 i;

    // delete matrizes
    mStoichiometry.clear();
    mRedStoi.clear();
    mConsRel.clear();
    mML.clear();
    mReactStruct.clear();

    // then the vectors of objects
    mMetabolite.clear();
    mMoiety.clear();
    mStep.clear();

    mRow.clear();
    mCol.clear();
    mIRow.clear();
    mICol.clear();
    mKernelP.clear();

    // allocate the arrays
    mMetabolite.resize(nmetab);
    mMoiety.resize(nmoiety);
    mStep.resize(nstep);

    mRow.resize(nmetab);
    mCol.resize(nstep);
    mIRow.resize(nmetab);
    mICol.resize(nstep);
    mKernelP.resize(nstep);

    // allocate the matrizes
    // allocate the colums
    mStoichiometry.resize(nmetab);
    mRedStoi.resize(nmetab);
    mConsRel.resize(nmetab);
    mReactStruct.resize(nstep);
    mML.resize(nmetab);

    // allocate each row
    for (i=0; i<nmetab; i++)
    {
        mStoichiometry[i].resize(nstep);
        mRedStoi[i].resize(nstep);
        mConsRel[i].resize(nmetab);
        mML[i].resize(nmetab);
    }
    for (i=0; i<nstep; i++)
        mReactStruct[i].resize(nmetab);
}


// overload assignment operator
CModel &CModel::operator=(CModel &ptRHS)
{
    // copy types that have an assignment operator that deals with copying the data
    mTitle = ptRHS.mTitle;
    mComments = ptRHS.mComments;
    mTransTime = ptRHS.mTransTime;
    
    // set the dimensions of the kernel before allocation
    mKernelI = ptRHS.mKernelI;
    mKernelJ = ptRHS.mKernelJ;
    mIntMetab = ptRHS.mIntMetab;

    // assign vectors
    mMetabolite = ptRHS.mMetabolite;
    mMoiety = ptRHS.mMoiety;
    mStep = ptRHS.mStep;
    mCompartment = ptRHS.mCompartment;
    mKernelP = ptRHS.mKernelP;

    mRow = ptRHS.mRow;
    mIRow = ptRHS.mIRow;
    mCol = ptRHS.mCol;
    mICol = ptRHS.mICol;
    
    // assign matrices
    mStoichiometry = ptRHS.mStoichiometry;
    mRedStoi = ptRHS.mRedStoi;
    mConsRel = ptRHS.mConsRel;
    mReactStruct = ptRHS.mReactStruct;
    mML = ptRHS.mML;

    mKernel = ptRHS.mKernel;
    
    return *this;  // Assignment operator returns left side.
}


void CModel::Clear(void)
{
    string temp = "Untitled";
    Reset(0, 0, 0, 0, 1, temp);
}

// this function updates the strings containing the
// chemical equations of each CStep object. This is
// called after the metabolites dialog box, to take
// care of possible metabolite renaming.

void CModel::UpdateChemEq(void)
{
    C_INT32 i, j;
    string TempStr;

    for (i=0; i<mStep.size(); i++)
    {
        // clear the exisiting string
        mStep[i].GetChemEq().erase();
        // the substrates
        for (j=0; j<mStep[i].SubstrateNo(); j++)
        {
            if (j!=0) mStep[i].GetChemEq() += " + ";
            mStep[i].GetChemEq() += mMetabolite[mStep[i].Substrate[j]].Name;
        }
        if (mStep[i].Reversible)
            mStep[i].ChemEq += " = ";
        else
            mStep[i].ChemEq += " -> ";
        // the products
        for (j=0; j<mStep[i].ProductNo; j++)
        {
            if (j!=0) mStep[i].ChemEq += " + ";
//   if (mStoichiometry[mStep[i].Product[j]][i]>(C_FLOAT32)1)
//   {
//    TempStr.Format("%i*%s", mStoichiometry[mStep[i].Product[j]][i],
//              LPCTSTR(mMetabolite[mStep[i].Product[j]].Name));
//    TempStr.Format("%.1f*", mStoichiometry[mStep[i].Product[j]][i]);
// mStep[i].ChemEq += TempStr;
// mStep[i].ChemEq += mMetabolite[mStep[i].Product[j]].Name;
//   }
//   else
            mStep[i].ChemEq += mMetabolite[mStep[i].Product[j]].Name;
        }
    }
}

// clears the existing moiety array and
// builds a new on (we have new metabolites, etc.)

void CModel::SetupMoiety(void)
{
    C_INT32 DimMoiety;  // dimension of the array
    C_INT32 i,j,k,idx;
    string TmpStr;

    // first delete the existing array
    delete [] mMoiety;
    // set the number of moieties
    TotMoieties = DepMetab;
    // initialize the dimension
    if (TotMoieties == 0) DimMoiety = 1;
    else DimMoiety = TotMoieties;
    // allocate the array
    mMoiety = new CMetab[DimMoiety];
    // set up each moiety
    for (i=0; i<TotMoieties; i++)
    {
        // the index for accessing ConsRel
        idx = i+IndMetab;
        // description string in the Name
        mMoiety[i].Name.Empty();
        for (j=0, k=0; j<TotMetab; j++)
            if (mMetabolite[j].Status != METAB_FIXED)
                if (mConsRel[idx][mIRow[j]] != 0.0)
                {
                    TmpStr.Format("%s ", k ? "+" : " ");
                    if ((mConsRel[idx][mIRow[j]] != 1.0) && (mConsRel[idx][mIRow[j]] != -1))
                    {
                        if (mConsRel[idx][mIRow[j]] > 0.0)
                            TmpStr.Format("%s %3.1f*", k ? "+" : " ", mConsRel[idx][mIRow[j]]);
                        else
                            TmpStr.Format("- %3.1f*", fabs(mConsRel[idx][mIRow[j]]));
                    }
                    if (mConsRel[idx][mIRow[j]] == -1.0) TmpStr = "- ";
                    mMoiety[i].Name += TmpStr;
                    TmpStr.Format("%s ", LPCTSTR(mMetabolite[j].Name));
                    mMoiety[i].Name += TmpStr;
                    k++;
                }
        // mark status as moiety total
        mMoiety[i].Status = METAB_MOIETY;
        // set a (fake) compartment
        mMoiety[i].Compart = 0; // the actual value does not matter as C_INT32 as >=0
        // set the rate
        mMoiety[i].Rate = 0; // and will always be!
    }
    // calculate the moieties total mass
    CalculateMoieties();
}

// calculates the moeieties total mass

void CModel::CalculateMoieties(void)
{
    C_INT32 i,j,idx;
    // iterate over all the moieties
    for (i=0; i<TotMoieties; i++)
    {
        // the index for accessing ConsRel
        idx = i+IndMetab;
        // the total mass of this moiety
        mMoiety[i].IConc = 0.0;
        for (j=0; j<IntMetab; j++)
            mMoiety[i].IConc += mConsRel[idx][j] * mMetabolite[mRow[j]].IConc *
                mCompartment[mMetabolite[mRow[j]].Compart].Volume;
    }
}

// recalcultates the moieties total mass (from time-dependent concentrations)

void CModel::UpdateMoieties(void)
{
    C_INT32 i,j,idx;
    // iterate over all the moieties
    for (i=0; i<TotMoieties; i++)
    {
        // the index for accessing ConsRel
        idx = i+IndMetab;
        // the total mass of this moiety
        mMoiety[i].IConc = 0.0;
        for (j=0; j<IntMetab; j++)
            mMoiety[i].IConc += mConsRel[idx][j] * mMetabolite[mRow[j]].Conc *
                mCompartment[mMetabolite[mRow[j]].Compart].Volume;
    }
}

// clears the Stoichiometry matrix

void CModel::ClearStoi(void)
{
    C_INT32 DimMetab, DimStep;  // dimension of arrays
    C_INT32 i,j;

    // initialize the dimensions
    if (TotMetab == 0) DimMetab = 1;
    else DimMetab = TotMetab;
    if (TotStep == 0) DimStep = 1;
    else DimStep = TotStep;

    for (i=0; i<DimMetab; i++)
        for (j=0; j<DimStep; j++)
        {
            mStoichiometry[i][j] = 0.0F;
            mRedStoi[i][j]  = 0.0F;
        }
}


// this function adds one entry in the stoichiometry matrix
// and in the appropriate step (for the substrate or product)

void CModel::AddToStoi(C_INT32 StepNo, C_INT32 MetabNo, C_INT32 Sign, C_INT32 Value)
{
    C_INT32 DimMetab, i;

    if (TotMetab == 0) DimMetab = 1;
    else DimMetab = TotMetab;

    // update the stoicheiometry coefficient
    mStoichiometry[MetabNo][StepNo] += Sign*Value;
    // store an index to Substrate or Product in the CStep object
    // in fact add one entry per unit of stoichiometry (2*X be comes X+X)
    if (Sign < 0) // substrate
        for (i=0; i<Value; i++)
            mStep[StepNo].AddSubstrate(MetabNo);
    else // product
        for (i=0; i<Value; i++)
            Step[StepNo].AddProduct(MetabNo);
    // look for the first empty position of ReactStruct[StepNo]
    //for (i=0; (i<DimMetab) && (Data->ReactStruct[StepNo][i]!=0) ; i++);
    // now assign it and the following to the relevant metabolite
    //for (j=st; j>0; j--, i++)
    // Data->ReactStruct[StepNo][i] = Sign*(MetabNo+1);
}

// this function saves a model to the CStdioFile
void CModel::Save(CStdioFile *fout)
{
    string StrOut, StrEl;
    C_INT32 i,j;

    // the file has already been opened
    // we don't care about exceptions here.
    // They should be caught by the calling function

    // first write the scalars
    StrOut = "Title=" + mTitle + "\n";
    fout->WriteString(LPCTSTR(StrOut));
    StrOut.Format("TotalMetabolites=%d\n",TotMetab);
    fout->WriteString(LPCTSTR(StrOut));
    StrOut.Format("TotalSteps=%d\n",TotStep);
    fout->WriteString(LPCTSTR(StrOut));
    StrOut.Format("TotalMoieties=%d\n",TotMoieties);
    fout->WriteString(LPCTSTR(StrOut));
    StrOut.Format("TotalCompartments=%d\n",TotCompart);
    fout->WriteString(LPCTSTR(StrOut));
    // then the matrices
    // Stoichiometry
// StrOut = "Stoichiometry\n";
// fout->WriteString(LPCTSTR(StrOut));
// for (i=0; i<TotMetab; i++)
// {
//  StrOut.Empty();
//  for (j=0; j< TotStep; j++)
//  {
//   StrEl.Format("%f ", mStoichiometry[i][j]);
//   StrOut += StrEl;
//  }
//  StrOut += "\n";
//  fout->WriteString(LPCTSTR(StrOut));
// }
    // save all the user-defined kinetic types in this model
    SaveUDKin(fout);
    // save all the metabolites
    for (i=0; i<TotMetab; i++)
        mMetabolite[i].Save(fout);
    // save all the moieties
    for (i=0; i<TotMoieties; i++)
        mMoiety[i].Save(fout);
    // save all the steps
    for (i=0; i<TotStep; i++)
        Step[i].Save(fout);
    // save all the compartments
    for (i=0; i<TotCompart; i++)
        mCompartment[i].Save(fout);
    // save the comments
    // multi-line entry followed by a line "EndComments"
    StrOut.Format("Comments\n");
    fout->WriteString(LPCTSTR(StrOut));
    fout->WriteString(LPCTSTR(mComments));
    StrOut.Format("\nEndComments\n");
    fout->WriteString(LPCTSTR(StrOut));
}

// this function writes the user-defined kinetic types to a file
void CModel::SaveUDKin(CStdioFile *fout)
{
    C_INT32 udkintot, i, j, newtype;
    CKinetics **ukin;
    string StrOut;
    // we can't have more unique kinetic types than steps
    ukin = new CKinetics*[TotStep];
    // build a list of the UD types in ukin, total in udkintot
    for (udkintot=0, i=0;i<TotStep; i++)
        if (Step[i].Kinetics->UserDefined)
        {
            for (newtype=1, j=0;j<udkintot; j++)
                if (Step[i].Kinetics==ukin[j])
                {
                    newtype = 0;
                    break;
                }
            if (newtype) ukin[udkintot++] = Step[i].Kinetics;
        }
    // write their total to the file
    StrOut.Format("TotalUDKinetics=%d\n",udkintot);
    fout->WriteString(LPCTSTR(StrOut));
    // write out each one
    for (i=0; i<udkintot; i++)
        ukin[i]->Save(fout);
    // release the memory used here
    delete [] ukin;
}

// this function loads a model from the buffer
C_INT32 CModel::Load(char **buffer, C_INT32 *line, C_INT32 getstoi)
{
    char *pt;
    C_INT32 lin, fields, i, j, err, TotTypes;
    C_INT32 nStep, nMetab, nMoiety, nCompart;
    string tTitle, TmpStr;
    CKinetics *pKin, *pKin2;

    lin = *line;
    pt = *buffer;
    // read the title of the model
    if (ReadStringAfterEquals(pt, tTitle, lin) == NULL)  return lin;
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    fields = sscanf(pt, "TotalMetabolites=%d\n", &nMetab);
    if (ScanfFailed(fields, 1, lin)) return lin;
    // sanity check
    if (nMetab < 0)
    {
        PMMessageBox(IDS_NEGMETAB, MB_ICONINFORMATION | MB_OK);
        return lin;
    }
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    fields = sscanf(pt, "TotalSteps=%d\n", &nStep);
    if (ScanfFailed(fields, 1, lin)) return lin;
    // sanity check
    if (nStep < 0)
    {
        PMMessageBox(IDS_NEGSTEP, MB_ICONINFORMATION | MB_OK);
        return lin;
    }
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    fields = sscanf(pt, "TotalMoieties=%d\n", &nMoiety);
    if (ScanfFailed(fields, 1, lin)) return lin;
    // sanity check
    if ((nMoiety < 0) || (nMoiety > nMetab))
    {
        PMMessageBox(IDS_INVALID_NMOIETY, MB_ICONINFORMATION | MB_OK);
        return lin;
    }
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    fields = sscanf(pt, "TotalCompartments=%d\n", &nCompart);
    if (ScanfFailed(fields, 1, lin)) return lin;
    // sanity check
    if (nCompart < 1)
    {
        PMMessageBox(IDS_INVALID_NCOMPART, MB_ICONINFORMATION | MB_OK);
        return lin;
    }
    // define the model and create the matrices
    Reset(nStep, nMetab, 0, nMoiety, nCompart, tTitle);
    // Stoichiometry
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    if (getstoi)
    {
        // jump the line with "Stoichiometry\n"
        if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
        lin++;
        for (i=0; i<TotMetab; i++)
        {
//  for (j=0; j< TotStep; j++)
//  {
            // read one matrix element
//   fields = sscanf(pt, " %f ", &(mStoichiometry[i][j]));
            // check if any error
//   if (ScanfFailed(fields, 1, lin)) return lin;
            // point pt to the first char after whitespace
//   pt = PointPastSpaceTab(pt);
//  }
            // skip the newline
            if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
            lin++;
        }
    }
    // the number of user-defined types stored in the file
    fields = sscanf(pt, "TotalUDKinetics=%d\n", &TotTypes);
    if (ScanfFailed(fields, 1, lin)) return 0;
    // sanity check
    if (TotTypes < 0)
    {
        PMMessageBox(IDS_BAD_UDKIN, MB_ICONINFORMATION | MB_OK);
        return lin;
    }
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;
    // read each kinetic type and add them to the database
    for (i=0; i<TotTypes; i++)
    {
        // create a new kinetic type
        pKin = new CKinetics();
        // load it with the next type in the file
        if ((err=pKin->Load(&pt, &lin)) != 0)
        {
            // we must delete this one as it does not go into the database
            delete pKin;
            return err;
        }
        // check if another type exists with this name
        if (KinDB.Lookup(LPCTSTR(pKin->Name), pKin2))
        {
            // it cannot be built-in or have a different function
            if (!pKin2->UserDefined || (pKin->Funct->Description!=pKin2->Funct->Description))
            {
                // we cannot load this type
                PMMessageBox(IDS_UDKIN_DUPL, MB_ICONEXCLAMATION | MB_OK);
                TmpStr.Format("Suggestion: Delete the kinetic type '%s' from the database before loading this file.", LPCTSTR(pKin->Name));
                PMMessageBox(LPCTSTR(TmpStr), MB_ICONINFORMATION | MB_OK);
                delete pKin;
                return lin;
            }
            // otherwise it already exists in the database
            delete pKin;
        }
        else
        {
            // this is a new type, so add it to the database
            KinDB[pKin->Name] = pKin;
            // increase the counter
            ++TotUDK;
        }
    }
    // load all the metabolites
    for (i=0; i<TotMetab; i++)
        if ((err = mMetabolite[i].Load(&pt, &lin)) != 0) return err;
    // load all the moieties
    for (i=0; i<TotMoieties; i++)
        if ((err = mMoiety[i].Load(&pt, &lin)) != 0) return err;
    // load all the steps
    for (i=0; i<TotStep; i++)
        if ((err = Step[i].Load(&pt, &lin)) != 0) return err;
    // load all the compartments
    for (i=0; i<TotCompart; i++)
        if ((err = mCompartment[i].Load(&pt, &lin)) != 0) return err;

    // jump the line with "Comments\n"
    for (i=0;;i++)
    {
        if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
        lin++;
        // read one line of the comment
        if (ReadStringToEOL(pt, tTitle, lin) == NULL)  return lin;
        if (! tTitle.Compare("EndComments")) break;
        else
        {
            if (i) mComments += "\r\n";
            mComments += tTitle;
        }
    }
    // skip the EndComments line
    if ((pt = PointPastNewLine(pt, lin)) == NULL) return lin;
    lin++;

    // build the stoichiometry matrix
    RebuildStoi(1);
    // work out the structural properties
    Structural();
    // update the line number
    *line = lin;
    // and the buffer pointer
    *buffer = pt;
    return 0;
}

C_INT32 CModel::ResetCompartments(C_INT32 ncompart)
{
    // check for legal values of the parameter
    if (ncompart < 1) return 1;
    // first delete the existing array
    delete [] mCompartment;
    // now set the size of the new array
    TotCompart = ncompart;
    // create the new array
    mCompartment = new CCompart[TotCompart];
    if (!mCompartment)
    {
#ifdef _DEBUG
        ASSERT(mCompartment);
#endif
        return 2;
    }
    // all went well
    return 0;
}

void CModel::InitIndex(void)
{
    C_INT32 i;

    for (i=0;i<TotMetab;i++) mRow[i] = i;
    for (i=0;i<TotStep;i++) mCol[i] = i;
}

void CModel::InitRedStoi(void)
{
    C_INT32 DimMetab, DimStep;  // dimension of arrays
    C_INT32 i,j;

    // check dimensions
    if (IntMetab == 0) DimMetab = 1;
    else DimMetab = IntMetab;
    if (TotStep == 0) DimStep = 1;
    else DimStep = TotStep;

    for (i=0; i<DimMetab; i++)
        for (j=0; j<DimStep; j++)
            mRedStoi[i][j] = mStoichiometry[mRow[i]][mCol[j]];
}

// returns the index of the metabolite with this name
C_INT32 CModel::FindMetab(string &Target)
{
    C_INT32 i;
    for (i=0; i<TotMetab; i++)
        if (mMetabolite[i].Name == Target) return i;
    return -1;
}

// returns the index of the step with this name
C_INT32 CModel::FindStep(string &Target)
{
    C_INT32 i;
    for (i=0; i<TotStep; i++)
        if (Step[i].Name == Target) return i;
    return -1;
}

// returns the index of the moiety with this name
C_INT32 CModel::FindMoiety(string &Target)
{
    C_INT32 i;
    for (i=0; i<TotMoieties; i++)
        if (mMoiety[i].Name == Target) return i;
    return -1;
}

// updates the references to compartments
void CModel::UpdateCompartments(void)
{
    C_INT32 i;
    // check all metabolites
    for (i=0; i<TotMetab; i++)
        // if it points to a non-existant compartment
        if (mMetabolite[i].Compart>=TotCompart)
            // set it to the first compartment (must exist)
            mMetabolite[i].Compart = 0;
}

// returns the index of the compartment with this name
C_INT32 CModel::FindCompartment(string &Target)
{
    C_INT32 i;
    for (i=0; i<TotCompart; i++)
        if (mCompartment[i].Name == Target) return i;
    return -1;
}

// finds the substrate molecularity of the step st
C_INT32 CModel::SubstrateMolecularity(C_INT32 st)
{
    return Step[st].SubstrateNo;
    //C_INT32 i, molec;
    // check if step is legal
    //if (st>=TotStep) return -1;
    //molec=0;
    //for (i=0; i<Step[st].SubstrateNo; i++)
    // molec -= (C_INT32) mStoichiometry[Step[st].Substrate[i]][st];
    //return molec;
}

// finds the product molecularity of the step st
C_INT32 CModel::ProductMolecularity(C_INT32 st)
{
    return Step[st].ProductNo;
    //C_INT32 i, molec;
    // check if step is legal
    //if (st>=TotStep) return -1;
    //molec=0;
    //for (i=0; i<Step[st].ProductNo; i++)
    // molec += (C_INT32) mStoichiometry[Step[st].Product[i]][st];
    //return molec;
}

// this function sorts the metabolites, putting all the
// internal at the beggining and the external at the end.
// This applies only to secondary matrices as RedStoi.

void CModel::SortMetabolites(void)
{
    C_INT32 i,ct;

    // reset the counter
    ct = 0;
    // first the internal
    for (i=0; i<TotMetab; i++)
        if (mMetabolite[i].Status == METAB_VARIABLE) mRow[ct++] = i;
    // then the dependent
    for (i=0; i<TotMetab; i++)
        if (mMetabolite[i].Status == METAB_DEPENDENT) mRow[ct++] = i;
    // last the external
    for (i=0; i<TotMetab; i++)
        if (mMetabolite[i].Status == METAB_FIXED) mRow[ct++] = i;
}

// this function builds the mapping from secondary to primary
// matrices.
//
// this allows calls of the type,
// mStoichiometry[mIRow[i]][mICol[j]]
// accessing a primary matrix, following the order in the secondary
//
// the opposite would be done using mRow[] and mCol[]:
// mRedStoi[mRow[i]][mCol[j]]

void CModel::MapSecondary(void)
{
    C_INT32 i,j;

    // first map the metabolites
    for (i=0; i<TotMetab; i++)
        for (j=0; j<TotMetab; j++)
            if (mRow[j]==i)
            {
                mIRow[i] = j;
                break;
            }
    // then the steps
    for (i=0; i<TotStep; i++)
        for (j=0; j<TotStep; j++)
            if (mCol[j]==i)
            {
                mICol[i] = j;
                break;
            }
}

// checks if a row in RedStoi is empty

C_INT32 CModel::EmptyRow(C_INT32 r)
{
    C_INT32 j, a;

    for (a=j=0; j<TotStep; j++)
        if (fabs(mRedStoi[r][j]) > ALMOST_ZERO) a++;
    return a;
}

// this function identifies metabolites that are
// external even though the user might not have
// flagged them as such

void CModel::SpotExternal(void)
{
    C_INT32 i,j,ct;

    // empty rows in Stoi are external metabolites
    for (i=0; i<TotMetab; i++)
    {
        // check if the rwo is empty
        for (ct=0, j=0; j<TotStep; j++)
            if (fabs(mStoichiometry[i][j]) > ALMOST_ZERO) ct++;
        if (!ct) mMetabolite[i].Status = METAB_FIXED;
    }
}


// this function marks the status of internal metabolites

void CModel::MarkStatus(void)
{
    C_INT32 i;

    // mark the independent metabolites
    for (i=0; i<IndMetab; i++)
//  Metabolite[Metabolite[i].index].Status = METAB_VARIABLE;
        mMetabolite[mRow[i]].Status = METAB_VARIABLE;
    // mark the dependent metabolites
    for (i=IndMetab; i<IntMetab; i++)
//  Metabolite[Metabolite[i].index].Status = METAB_DEPENDENT;
        mMetabolite[mRow[i]].Status = METAB_DEPENDENT;
}


// this function counts the various classes of metabolites

void CModel::CountMetabolites()
{
    C_INT32 i;

    IntMetab = DepMetab = ExtMetab = 0;
    for (i=0; i<TotMetab; i++)
    {
        switch (mMetabolite[i].Status)
        {
        case METAB_VARIABLE:  IntMetab++; break;
        case METAB_DEPENDENT: DepMetab++; IntMetab++; break;
        case METAB_FIXED:  ExtMetab++; break;
        }
    }
}


// set up the mML and mLM matrices

C_INT32 CModel::CreateLM(void)
{
    C_INT32 i,j,DimMetab;

    if (TotMetab==0) DimMetab = 1;
    else DimMetab = TotMetab;
    // allocate the mLM array
    mLM = new C_FLOAT32 *[IntMetab];
    // allocate each row
    for (i=0; i<IntMetab; i++)
        mLM[i] = new C_FLOAT32[IntMetab];
    // set all entries of mLM and mML to zero
    for (i=0; i<IntMetab; i++)
        for (j=0; j<IntMetab; j++)
            mLM[i][j] = (C_FLOAT32) 0.0;
    for (i=0; i<DimMetab; i++)
        for (j=0; j<DimMetab; j++)
            mML[i][j] = (C_FLOAT32) 0.0;

    return 0;
}


// this function deletes the space used by the mLM matrix

void CModel::DestroyLM(void)
{
    C_INT32 i;

    // first delete each row
    for (i=0; i<IntMetab; i++)
        delete [] mLM[i];
    // then the vectors of pointers
    delete [] mLM;
    // make sure it becomes NULL
    mLM = NULL;
}


// this funtion switches two rows in the secondary matrices

void CModel::RedStoiRowSwitch(C_INT32 r1, C_INT32 r2)
{
    C_INT32 j;
    C_FLOAT32 dummy;

    // switch all elements it the two rows in RedStoi
    for (j=0; j<TotStep; j++)
    {
        dummy          = mRedStoi[r1][j];
        mRedStoi[r1][j] = mRedStoi[r2][j];
        mRedStoi[r2][j] = dummy;
    }
    // switch all elements it the two rows in Row
    j = mRow[r1];
    mRow[r1] = mRow[r2];
    mRow[r2] = j;
    // switch all elements in the two rows in mML
    for (j=0;j<IntMetab;j++)
    {
        dummy     = mML[r1][j];
        mML[r1][j] = mML[r2][j];
        mML[r2][j] = dummy;
    }
}


// this funtion switches two columns in the secondary matrices

void CModel::RedStoiColSwitch(C_INT32 c1, C_INT32 c2)
{
    C_INT32 i;
    C_FLOAT32 dummy;

    // switch all elements it the two cols in RedStoi
    for (i=0; i<IntMetab; i++)
    {
        dummy          = RedStoi[i][c1];                    /* switch cols in rstoi */
        RedStoi[i][c1] = RedStoi[i][c2];
        RedStoi[i][c2] = dummy;
    }
    // switch all elements in the two cols in Col
    i = mCol[c1];
    mCol[c1] = mCol[c2];
    mCol[c2] = i;
    // switch all elements in the two cols in mML
// for (i=0; i<IntMetab; i++)
// {
//  dummy     = mML[i][c1];
//  mML[i][c1] = mML[i][c2];
//  mML[i][c2] = dummy;
// }
}


// these two functions are for debugging purposes only

void CModel::InitDebug(void)
{
    HANDLE hDbgFile;
    ::GetTempFileName(".", "DBG", 0, DebugFile);
    hDbgFile = CreateFile(DebugFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    CloseHandle(hDbgFile);
}

void CModel::PrintSummary(void)
{
    CStdioFile DbgFile(DebugFile, CFile::modeWrite | CFile::typeText);
    string StrOut;
    C_INT32 i;
    // seek to the end of the file
    DbgFile.SeekToEnd();
    StrOut = "Summary:\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    StrOut.Format("TotSteps=%d TotMetab=%d IntMetab=%d IndMetab=%d DepMetab=%d ExtMetab=%d\n",
                  TotStep, TotMetab, IntMetab, IndMetab, DepMetab, ExtMetab);
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<TotStep; i++)
    {
        StrOut.Format("%s\n", LPCTSTR(Step[i].ChemEq));
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    StrOut = "\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
}

void CModel::PrintMatrices(void)
{
    CStdioFile DbgFile(DebugFile, CFile::modeWrite | CFile::typeText);
    string StrOut, StrEl;
    C_INT32 i, j;
    // seek to the end of the file
    DbgFile.SeekToEnd();
    // Stoichiometry
    StrOut = "Stoichiometry\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<TotMetab; i++)
    {
        StrOut.Empty();
        for (j=0; j< TotStep; j++)
        {
            StrEl.Format("%4.1f ", mStoichiometry[i][j]);
            StrOut += StrEl;
        }
        StrOut += "\n";
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    // Row & Col
    if (TotMetab > TotStep) j = TotMetab;
    else j = TotStep;
    StrOut = "Row, IRow, Col, ICol\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<j; i++)
    {
        StrOut.Format("%4.1f, %4.1f, %4.1f, %4.1f\n",
                      i<TotMetab ? mRow[i] : -1.0,
                      i<TotMetab ? mIRow[i] : -1.0,
                      i<TotStep  ? mCol[i] : -1.0,
                      i<TotStep  ? mICol[i] : -1.0);
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    // RedStoi
    StrOut = "RedStoi\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<IntMetab; i++)
    {
        StrOut.Empty();
        for (j=0; j< TotStep; j++)
        {
            StrEl.Format("%4.1f ", mRedStoi[i][j]);
            StrOut += StrEl;
        }
        StrOut += "\n";
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    // mML
    if (mML)
    {
        StrOut = "ml\n";
        DbgFile.WriteString(LPCTSTR(StrOut));
        for (i=0; i<IntMetab; i++)
        {
            StrOut.Empty();
            for (j=0; j< IntMetab; j++)
            {
                StrEl.Format("%4.1f ", mML[i][j]);
                StrOut += StrEl;
            }
            StrOut += "\n";
            DbgFile.WriteString(LPCTSTR(StrOut));
        }
        StrOut = "lm\n";
        DbgFile.WriteString(LPCTSTR(StrOut));
        for (i=0; i<IntMetab; i++)
        {
            StrOut.Empty();
            for (j=0; j< IntMetab; j++)
            {
                StrEl.Format("%4.1f ", mLM[i][j]);
                StrOut += StrEl;
            }
            StrOut += "\n";
            DbgFile.WriteString(LPCTSTR(StrOut));
        }
    }
    // ConsRel
    StrOut = "ConsRel\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<IntMetab; i++)
    {
        StrOut.Empty();
        for (j=0; j<IntMetab; j++)
        {
            StrEl.Format("%4.1f ", mConsRel[i][j]);
            StrOut += StrEl;
        }
        StrOut += "\n";
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    // Moieties
    StrOut = "Moiety\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    for (i=0; i<TotMoieties; i++)
    {
        StrOut.Format("%s = %lf\n", LPCTSTR(Moiety[i].Name), mMoiety[i].IConc);
        DbgFile.WriteString(LPCTSTR(StrOut));
    }
    StrOut = "\n\n";
    DbgFile.WriteString(LPCTSTR(StrOut));
    DbgFile.Close();
}


// this functions reduces RedStoi by doing a
// Gauss reduction with row and column pivoting
// NOTE: RedStoi must have been already loaded

C_INT32 CModel::Gauss(void)
{
    C_INT32 i, j, k, flag;
    C_FLOAT32 m;

    for (k=0; (k<TotStep) && (k<IntMetab); k++)
    {
        for (flag=0, i=k; i<IntMetab; i++)
            if (fabs(mRedStoi[i][k]) > ALMOST_ZERO)
            {
                // found a suitable divisor on this row
                flag = 1;
                break;
            }
        if (flag) // if a divisor was found
        {
            if (i != k)
                // switch row k with row i
                RedStoiRowSwitch(k, i);
        }
        else // if no divisor was found
        {
            do
            {
                // search for a divisor in the next columns
                for (j=k+1; j<TotStep; j++)
                    if (fabs(mRedStoi[k][j]) > ALMOST_ZERO)
                    {
                        // found a divisor on this column
                        flag = 1;
                        break;
                    }
                if (flag && (j != k))
                    // switch column j with column k
                    mRedStoiColSwitch(j, k);
                if (!flag) // we did not find a divisor
                {
                    // get rid of empty rows
                    for (i=0; i<IntMetab; i++)
                    {
                        if (! EmptyRow(i)) // all entries in row = 0
                        {
                            for (j=i+1; j<IntMetab; j++)
                                if (EmptyRow(j)) // j is the first non-empty row
                                {
                                    // switch row i with row j
                                    RedStoiRowSwitch(i, j);
                                    flag = 2; // DOES THIS SIGNAL CONSERVATION RELATIONS ???
                                    break;
                                }
                        }
                    }
                }
                if (!flag)
                {
                    // k is the number of independent metabolites
                    IndMetab = k;
                    DepMetab = IntMetab - IndMetab; // Dependent = Internal - Independent
                    return -1; // signal that we found conservation relations
                }
            }
            while(flag != 1); // until a divisor was not found
        }
        for (i=k+1; i<IntMetab; i++) // iterate over the next rows
        {
            if (fabs(mRedStoi[k][k]) > ALMOST_ZERO)
            {
                // m is the divisor (pivot)
                m =  mRedStoi[i][k] / mRedStoi[k][k];
                // keep its symmetric in the ML matrix
                mML[i][k] = m;
                if (m != (C_FLOAT32) 0.0) // paranoid check...
                {
                    // reduce another row
                    for (j=k; j<TotStep; j++)
                    {
                        mRedStoi[i][j] = mRedStoi[i][j] - m * mRedStoi[k][j];
                        if (fabs(mRedStoi[i][j]) <= ALMOST_ZERO) // make it a true zero
                            mRedStoi[i][j] = (C_FLOAT32) 0.0;
                    }
                }
            }
        }
    }
    IndMetab = k;
    DepMetab = IntMetab - IndMetab; // Dependent = Internal - Independent
    return 0; // job done, no linear dependencies ??????
}


// this function identifies the conserved moieties

void CModel::SpotDependent(void)
{
    C_INT32 i,j,k;
    C_FLOAT32 acum;

    // ml is lower triangular, so to invert it we simply have
    // do forward-substitution with the identity matrix

    // set the diagonal elements to 1
    for (i=0; i<IntMetab; i++) mML[i][i] = (C_FLOAT32) 1.0 ;

    // forward substitute
    for (j=0; j<IndMetab; j++)
        for (k=0; k<IndMetab; k++)
        {
            acum= (C_FLOAT32) 0.0;
            for (i=0; i<k; i++)
                acum += mML[k][i] * mLM[i][j];
            mLM[k][j] = ((k==j) ? (C_FLOAT32) 1.0 : - acum) / mML[k][k];
        }

    // dimension the ConsRel matrix
    // ResetConsRel();
    // ConsRel is the same as Reder's -L0
    for (i=IndMetab; i<IntMetab; i++)   // first calculate L0
        for (j=0; j<IndMetab; j++)    // which is
        {
            mConsRel[i][j] = (C_FLOAT32) 0.0;
            for (k=0; k<IndMetab; k++)
                mConsRel[i][j] += mML[i][k] * mLM[k][j]; // L0 = L21 * Inv(L11)
        }
    for (i=IndMetab; i<IntMetab; i++)   // Now map the lin. dep.
    {
        for (j=0; j<IndMetab; j++)    // which is
            mConsRel[i][j] = -mConsRel[i][j];   // -L0
        for (j=IndMetab; j<IntMetab; j++)  // merged with the
            mConsRel[i][j] = (i == j)
                ? (C_FLOAT32) 1.0 : (C_FLOAT32) 0.0;   // m0 -> m part of Id.
    }
}


// this function is the top-level call to do all
// structure invariant processing (matrix reduction, etc)
//
// it is called after: a) loading a model
//                     b) editing reactions
//                     b) editing metabolites

void CModel::Structural(void)
{
    //CStdioFile dbgf;
//CFileException fexcp;
    C_INT32 i;
//dbgf.Open("dbg.tmp", CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fexcp);

    if (TotStep > 0)
    {
//InitDebug();
        // set all dependent metabolites to variable since
        // Gauss depends on *not* having them marked. Later in
        // this procedure they get marked again
        for (i=0; i<TotMetab; i++)
            if (mMetabolite[i].Status == METAB_DEPENDENT) mMetabolite[i].Status = METAB_VARIABLE;
        // initialize the indices to RedStoi
        InitIndex();
        // identify implicit external metabs
        SpotExternal();
        // sort metabs
        SortMetabolites();
        // count the metabolite classes
        CountMetabolites();
        // initialize RedStoi
        InitRedStoi();
        // create the lm matrices
        CreateLM();
//Save(&dbgf);
//PrintSummary();
//PrintMatrices();
        // Reduce RedStoi by Gauss method
        Gauss();
//PrintSummary();
//PrintMatrices();
        // count the metabolite classes
        CountMetabolites();
        // identify the conserved moieties
        SpotDependent();
        // set the step and metabolite indexes
        MapSecondary();
        // mark the status of internal metabolites
        MarkStatus();
        // final count of the metabolite classes
        CountMetabolites();
        // setup all the Moiety objects (conc. total)
        SetupMoiety();
//  GetKernel();
//PrintSummary();
//PrintMatrices();
        // destroy the mML and lm matrices
        DestroyLM();
//dbgf.Close();
    }
}

// this routine calculates the null-space of the stoichiometry matrix
// following the algorithm of Schuster & Schuster J.Math.Chem. 6 17-40 (1991)
C_INT32 CModel::GetKernel(void)
{
    C_INT32 f,h,i,j,k,m,n,q,si,cp,rp;
    C_FLOAT32 **Echelon; // stoichiometry matrix in echelon format
    C_FLOAT32 **cb;  // auxiliary matrix
    BOOL exchange;
    C_FLOAT32 fTemp, z;
    C_INT32 iTemp, pi, pj;

    // initialise teh rank to 0
    Rank = 0;

    // check conditions
    if (TotStep < 1) return 1; // we need some steps!
    if (IntMetab < 1) return 2; // we need some metabolites!
// if (IntMetab >= TotStep) return 3;

    // reset the permutation matrix
    for (i=0; i<TotStep; i++) mKernelP[i] = i;

// FILE *fp;
// fp = fopen("ker.txt","wt");

    // create the echelon and auxiliary matrices
    Echelon = new C_FLOAT32 *[TotMetab];
    cb = new C_FLOAT32 *[TotMetab];
    for (i=0, j=0; i<TotMetab; i++)
        if (mMetabolite[i].Status != METAB_FIXED)
        {
            Echelon[j] = new C_FLOAT32[TotStep];
            cb[j] = new C_FLOAT32[TotStep];
            for (k=0; k<TotStep; k++)
            {
                Echelon[j][k] = mStoichiometry[i][k];
            }
            j++;
        }
    // transform it into echelon format
    for (i=0, k=IntMetab; i<k;)
    {
        if (Echelon[i][i]==0.0f)
        {
            for (j=i+1; (Echelon[i][j]==0.0f) && (j<TotStep); j++);
            if (j==TotStep)
            {
                if (i<k-1)
                {
                    // swap rows i and k-1
                    for (si=0; si<TotStep; si++)
                    {
                        fTemp = Echelon[i][si];
                        Echelon[i][si] = Echelon[k-1][si];
                        Echelon[k-1][si] = fTemp;
                    }
                }
                k--;
            }
            else
            {
                // swap columns i and j
                for (si=0; si<IntMetab; si++)
                {
                    fTemp = Echelon[si][i];
                    Echelon[si][i] = Echelon[si][j];
                    Echelon[si][j] = fTemp;
                }
                iTemp = mKernelP[i];
                mKernelP[i] = mKernelP[j];
                mKernelP[j] = iTemp;
            }
        }
        else
        {
            for (m=i+1; m<k; m++)
            {
                for (j=i; j<TotStep; j++)
                {
                    if (Echelon[m][i] != 0.0)
                        cb[m][j] = Echelon[m][j]*Echelon[i][i]/Echelon[m][i] - Echelon[i][j];
                    else cb[m][j] = Echelon[m][j];
                }
            }
            for (m=i+1; m<k; m++)
                for (j=i; j<TotStep; j++)
                    Echelon[m][j] = cb[m][j];
            i++;
        }
// PMMessageBox("CHECKPOINT 2", MB_OK | MB_ICONINFORMATION);
    }
    // k is the Rank of the stoichiometry matrix
    Rank = k>0?k:0;
    // print some stats
// fprintf(fp,"\n\n");
// for (i=0;i<IntMetab; i++)
// {
//  for (j=0;j<TotStep; j++)
//   fprintf(fp,"% .1f ", Echelon[i][j]);
//  fprintf(fp,"\n");
// }
    // delete the old kernel matrix
    if ((mKernelI>0) && (mKernelJ>0))
    {
        for (i=0;i<mKernelI; i++)
            delete [] mKernel[i];
        delete [] mKernel;
    }
    // calculate the dimensions of the kernel
    mKernelI = TotStep;
    mKernelJ = TotStep-Rank;
    // no point in continuing if mKernelJ<1 or mKernelI<1
    if (mKernelJ>0)
    {
        // allocate a new one
        mKernel = new C_FLOAT32 *[mKernelI];
        for (i=0; i<TotStep; i++)
            mKernel[i] = new C_FLOAT32[mKernelJ];
        // calculate the kernel
        for (m=Rank; m<mKernelI; m++)
            for (h=0; h<mKernelJ; h++)
            {
                if (m==h+Rank) mKernel[m][h] = 1.0f;
                else mKernel[m][h] = 0.0f;
            }
        for (j=0; j<mKernelJ; j++)
            for (i=Rank-1; i>=0; i--)
            {
                for (m=i+1, z=0.0f; m<Rank; m++)
                    z += Echelon[i][m]*mKernel[m][j];
                mKernel[i][j] = - (Echelon[i][Rank+j]+z)/Echelon[i][i];
            }
        // rearrange the kernel to canonical form
        // put all empty rows in the end
        for (i=0, DetBalance=0, k=TotStep-1; i<=k;)
        {
            for (h=0; (h<mKernelJ) && (Kernel[i][h]==0.0f); h++);
            if (h==mKernelJ)  // this row is full of zeroes
            {
                DetBalance++; // increase the counter of empty rows
                if (i<k)
                {
                    // exchange row i with k (put it at the end)
                    for (m=0; m<mKernelJ; m++)
                    {
                        fTemp = mKernel[i][m];
                        mKernel[i][m] = mKernel[k][m];
                        mKernel[k][m] = fTemp;
                    }
                    iTemp = mKernelP[i];
                    mKernelP[i] = mKernelP[k];
                    mKernelP[k] = iTemp;
                }
                k--;
            }
            else i++;
        }
//  fprintf(fp,"\n");
//  for (i=0;i<mKernelI; i++)
//  {
//   for (j=0;j<mKernelJ; j++)
//    fprintf(fp,"% .1f ", Kernel[i][j]);
//   fprintf(fp,"\n");
//  }
//  fprintf(fp,"\nKernelP\n");
//  for (j=0;j<mKernelI; j++)
//    fprintf(fp,"%d ", KernelP[j]);
//  fprintf(fp,"\nCol\n");
//  for (j=0;j<TotStep; j++)
//    fprintf(fp,"%d ", mCol[j]);
//  fprintf(fp,"\nICol\n");
//  for (j=0;j<TotStep; j++)
//    fprintf(fp,"%d ", mICol[j]);
//  fclose(fp);
    } // end if mKernelJ>0
    // destroy the echelon and auxiliary matrices
    for (i=0; i<IntMetab; i++)
    {
        delete [] Echelon[i];
        delete [] cb[i];
    }
    delete Echelon;
    delete cb;
    // signal all is well
    return 0;
}

// this routine calculates the elementary modes of the stoichiometry matrix
// according to the algortithm of Schuster
C_INT32 CModel::ElementaryModes(CStdioFile *fout)
{
    C_INT32 **sm;       /* pointer to stoichiometric matrix */
    C_INT32 **sub, **tab, **ntab, **phelp; /* pointer to current tableau, next tableau, help for test 1 */
    C_INT32 *revstate, *nrevstate;    /* reversibility of mode: 0 - revesible, 1 - irreversible */
    C_INT32 i,j,u,uu,x;     /* counter */
    C_INT32 pos1,pos, nreact, nmet;   /* number of current tableau, number of reactions and metabolites */
    C_INT32 colnr, rownr, nrownr, nnrownr;  /* number of columns and rows in the current and next tableau */
    C_INT32 f1,f2,f3;       /* factors for determination of linear combinations */
    C_INT32 nzero, nneg, npos, nrevneg, nrevpos, npairs;
    C_INT32 acrow=0;       /*number of calculated rows in the next tableau */
    C_INT32 test1;       /* bools for test conditions */
    string StrOut;

    nmet = IntMetab;
    nreact = TotStep;

    // allocate memory for matrices
    sm = (C_INT32**) malloc(nmet*sizeof(*sm));
    if (sm == NULL) return -1;
    revstate = (C_INT32*) malloc(nreact*sizeof(C_INT32));
    if (revstate == NULL)
    {
        free(sm);
        return -2;
    }
    // load stoichiometry matrix
    for (i=0; i<nmet; i++)
    {
        // allocate another row
        *(sm+i) = (C_INT32*) malloc(nreact*sizeof(C_INT32));
        if (*(sm+i) == NULL)
        {
            for (j=0; j<i; j++) free(*(sm+j));
            free(revstate);
            free(sm);
            return -3;
        }
        // fill it in
        for (j=0; j<nreact; j++)
            *(*(sm+i)+j) = (C_INT32) mStoichiometry[mRow[i]][mCol[j]];
    }
    // load reversibility matrix
    for (i=0; i<nreact; i++)
    {
        if (Step[mCol[i]].Reversible) revstate[i] = 0;
        else revstate[i] = 1;
    }

    colnr=nmet+nreact;
    rownr=nreact;

    // allocate sub-matrix
    sub = (C_INT32**) malloc(nreact*sizeof(*sub));
    if (sub == NULL)
    {
        for (i=0; i<nmet; i++) free(*(sm+i));
        free(revstate);
        free(sm);
        return -4;
    }

    for (i=0; i<nreact; i++)
    {
        // allocate row
        *(sub+i) = (C_INT32*) malloc(nreact*sizeof(C_INT32));
        if (*sub==NULL)
        {
            for (j=0; j<i; j++) free(*(sub+j));
            for (j=0; j<nmet; j++) free(*(sm+j));
            free(revstate);
            free(sm);
            return -5;
        }
        // initialize to identity matrix
        for (j=0; j<nreact; j++)
        {
            if (j==i) *(*(sub+i)+j)=1;
            else *(*(sub+i)+j)=0;
        }
    }

    // allocate tableau matrix
    tab = (C_INT32**) malloc(rownr*sizeof(*tab));
    if (tab==NULL)
    {
        for (j=0; j<nreact; j++) free(*(sub+j));
        free(sub);
        for (i=0; i<nmet; i++) free(*(sm+i));
        free(revstate);
        free(sm);
        return -6;
    }
    for (i=0; i<nreact; i++)
    {
        // allocate rows
        *(tab+i) = (C_INT32*) malloc(colnr*sizeof(C_INT32));
        if (*(tab+i) == NULL)
        {
            for (j=0; j<i; j++) free(*(tab+j));
            free(tab);
            for (j=0; j<nreact; j++) free(*(sub+j));
            free(sub);
            for (i=0; i<nmet; i++) free(*(sm+i));
            free(revstate);
            free(sm);
            return -7;
        }
        TRACE("M 1 tab[%d] %p %d\n", i, *(tab+i), colnr*sizeof(C_INT32));
        // initialize
        for (j=0; j<colnr; j++)
        {
            if (j<nmet) *(*(tab+i)+j) = *(*(sm+j)+i);
            else
                if (j==i+nmet) *(*(tab+i)+j) = 1;
                else *(*(tab+i)+j) = 0;
        }
    }
    // release unwanted memory
    for (i=0; i<nmet; i++) free(*(sm+i));
    free(sm);

    // carry out the main work
    for (pos1=0; pos1<nmet; pos1++)
    {
        // tick front-end
        nnrownr=10000000;
        for (pos=0; pos<nmet; pos++)
        {
            nzero=0; npos=0; nneg=0; acrow=0; nrevpos=0; nrevneg=0;              \
                                                                                     for (i=0; i<rownr; i++)
                                                                                     {
                                                                                         if (!(*(*(tab+i)+pos))) nzero++;
                                                                                         else if (*(*(tab+i)+pos)<0) nneg++;
                                                                                         else npos++;
                                                                                         if (!(*(revstate+i)))
                                                                                         {
                                                                                             if (*(*(tab+i)+pos)<0) nrevneg++;
                                                                                             if (*(*(tab+i)+pos)>0) nrevpos++;
                                                                                         }
                                                                                     }
            npairs = nneg*npos+(nrevneg*(nneg-1))+(nrevpos*(npos-1))+nrevneg*(nrevneg-1)+nrevpos*(nrevpos-1);
            nrownr = nzero+npairs;
            if ((nzero<rownr) && (nrownr<nnrownr)) x=pos;
        }
        pos=x;
        nzero=0; npos=0; nneg=0; acrow=0; nrevpos=0; nrevneg=0;              \
                                                                                 for (i=0; i<rownr; i++)
                                                                                 {
                                                                                     if (!(*(*(tab+i)+pos))) nzero++;
                                                                                     else if (*(*(tab+i)+pos)<0) nneg++;
                                                                                     else npos++;
                                                                                     if (!(*(revstate+i)))
                                                                                     {
                                                                                         if (*(*(tab+i)+pos)<0) nrevneg++;
                                                                                         if (*(*(tab+i)+pos)>0) nrevpos++;
                                                                                     }
                                                                                 }
        npairs = nneg*npos+(nrevneg*(nneg-1))+(nrevpos*(npos-1))+nrevneg*(nrevneg-1)+nrevpos*(nrevpos-1);
        nrownr = nzero+npairs;
        if (nrownr==10000000) break;
        // allocate more memory
        ntab = (C_INT32**) malloc((nrownr+1)*sizeof(*ntab));
        if (ntab==NULL)
        {
            for (j=0; j<nreact; j++) free(*(tab+j));
            free(tab);
            for (j=0; j<nreact; j++) free(*(sub+j));
            free(sub);
            free(revstate);
            return -8;
        }
        nrevstate = (C_INT32*) malloc((nrownr+1)*sizeof(C_INT32));
        if (nrevstate==NULL)
        {
            free(ntab);
            for (j=0; j<nreact; j++) free(*(tab+j));
            free(tab);
            for (j=0; j<nreact; j++) free(*(sub+j));
            free(sub);
            free(revstate);
            return -9;
        }
        phelp = ntab;
        for (i=0; i<rownr; i++)
            if (!(*(*(tab+i)+pos)))   /* 0 - zeilen */
            {
                *ntab++ = *(tab+i);
//   *(tab+i) = NULL;
                *nrevstate++ = *(revstate+i);
                acrow++;
            }
        for (i=0; i<rownr; i++)
            if (*(*(tab+i)+pos))      /* nicht 0 - zeilen */
            {
                for (j=i+1; j<rownr; j++)
                    if (*(*(tab+i)+pos))
                    {
                        if (*(*(tab+i)+pos) * *(*(tab+j)+pos) < 0)    /* vorzeichenpaare */
                        {
                            *ntab = (C_INT32*) malloc(colnr*sizeof(C_INT32));
                            if (*ntab==NULL)
                            {
                                for (j=0; j<nreact; j++) free(*(tab+j));
                                free(tab);
                                for (j=0; j<nreact; j++) free(*(sub+j));
                                free(sub);
                                free(revstate);
                                return -10;
                            }
                            TRACE("M 2 *ntab %p %d\n", *ntab, colnr*sizeof(C_INT32));
                            f3 = 0;
                            f1 = abs(*(*(tab+j)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                            f2 = abs(*(*(tab+i)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                            for (u=0; u<colnr; u++)
                            {
                                *(*ntab+u) = f1 * *(*(tab+i)+u) + f2 * *(*(tab+j)+u);
                                if (*(*ntab+u) != 0)
                                    f3 = gcd(f3, abs(*(*ntab+u)));
                            }
                            if (f3>1)
                                for (u=0; u<colnr; u++)
                                    (*(*ntab+u)) /= f3;
                            test1 = 1;
                            for (u=0; u<acrow; u++)
                            {
                                test1 = 0;
                                for (uu=nmet; uu<colnr; uu++)
                                {
                                    if (!((*(*(tab+i)+uu)) || (*(*(tab+j)+uu))))
                                        test1 |= (*(*(phelp+u)+uu));
                                    if (test1) break;
                                }
                                if (!test1) break;
                            }
                            if (!test1)
                            {
                                free(*ntab);
                                *ntab = NULL;
                                TRACE("F 3 *ntab %p\n", *ntab);
                            }
                            else
                            {
                                if (npairs==1)
                                    for (u=nmet; u<colnr; u++)
                                    {
                                        if (*(*ntab+u))
                                        {
                                            for (uu=0; uu<nreact; uu++)
                                                *(*(sub+u-nmet)+uu) = *(*ntab+uu+nmet);
                                        }
                                    }
                                ntab++;
                                acrow++;
                                *nrevstate++ = (*(revstate+i)) || (*(revstate+j));
                            }
                        }
                        else
                        {
                            if (!(*(revstate+i)))       /* v1 reversibel */
                            {
                                *ntab = (C_INT32*) malloc(colnr*sizeof(C_INT32));
                                if (*ntab==0)
                                {
                                    for (j=0; j<nreact; j++) free(*(tab+j));
                                    free(tab);
                                    for (j=0; j<nreact; j++) free(*(sub+j));
                                    free(sub);
                                    free(revstate);
                                    return -10;
                                }
                                f3 = 0;
                                f1 = abs(*(*(tab+j)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                                f2 = abs(*(*(tab+i)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                                for (u=0; u<colnr; u++)
                                {
                                    *(*ntab+u) = f2 * *(*(tab+j)+u) - f1 * *(*(tab+i)+u);
                                    if (*(*ntab+u) != 0)
                                        f3 = gcd(f3, abs(*(*ntab+u)));
                                }
                                if (f3>1)
                                    for (u=0; u<colnr; u++)
                                        (*(*ntab+u)) /= f3;
                                test1 = 1;
                                for (u=0; u<acrow; u++)
                                {
                                    test1 = 0;
                                    for (uu=nmet; uu<colnr; uu++)
                                    {
                                        if (!((*(*(tab+i)+uu)) || (*(*(tab+j)+uu))))
                                            test1 |= (*(*(phelp+u)+uu));
                                        if (test1) break;
                                    }
                                    if (!test1) break;
                                }
                                if (!test1)
                                {
                                    free(*ntab);
                                    *ntab = NULL;
                                }
                                else
                                {
                                    if (npairs==1)
                                        for (u=nmet; u<colnr; u++)
                                        {
                                            if (*(*ntab+u))
                                            {
                                                for (uu=0; uu<nreact; uu++)
                                                    *(*(sub+u-nmet)+uu) = *(*ntab+uu+nmet);
                                            }
                                        }
                                    ntab++;
                                    acrow++;
                                    *nrevstate++ = (*(revstate+i)) || (*(revstate+j));
                                }
                            }
                            if (!(*(revstate+j)))       /* v2 reversibel */
                            {
                                *ntab = (C_INT32*) malloc(colnr*sizeof(C_INT32));
                                if (*ntab==NULL)
                                {
                                    for (j=0; j<nreact; j++) free(*(tab+j));
                                    free(tab);
                                    for (j=0; j<nreact; j++) free(*(sub+j));
                                    free(sub);
                                    free(revstate);
                                    return -10;
                                }
                                f3 = 0;
                                f1 = abs(*(*(tab+j)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                                f2 = abs(*(*(tab+i)+pos)) / gcd(abs(*(*(tab+j)+pos)), abs(*(*(tab+i)+pos)));
                                for (u=0; u<colnr; u++)
                                {
                                    *(*ntab+u) = f1 * *(*(tab+i)+u)-f2**(*(tab+j)+u);
                                    if (*(*ntab+u) != 0)
                                        f3 = gcd(f3, abs(*(*ntab+u)));
                                }
                                if (f3>1)
                                    for (u=0; u<colnr; u++)
                                        (*(*ntab+u)) /= f3;
                                test1 = 1;
                                for (u=0; u<acrow; u++)
                                {
                                    test1 = 0;
                                    for (uu=nmet; uu<colnr; uu++)
                                    {
                                        if (!((*(*(tab+i)+uu)) || (*(*(tab+j)+uu))))
                                            test1 |= (*(*(phelp+u)+uu));
                                        if (test1) break;
                                    }
                                    if (!test1) break;
                                }
                                if (!test1)
                                {
                                    free(*ntab);
                                    *ntab = NULL;
                                }
                                else
                                {
                                    if (npairs==1)
                                        for (u=nmet; u<colnr; u++)
                                        {
                                            if (*(*ntab+u))
                                            {
                                                for (uu=0; uu<nreact; uu++)
                                                    *(*(sub+u-nmet)+uu) = *(*ntab+uu+nmet);
                                            }
                                        }
                                    ntab++;
                                    acrow++;
                                    *nrevstate++ = (*(revstate+i)) || (*(revstate+j));
                                }
                            }
                        }
                    }
                free(*(tab+i));
                *(tab+i) = NULL;
                TRACE("F 8 tab[%d] %p\n", i, *(tab+i));
            }
        ntab -= acrow;
        nrevstate -= acrow;
        free(tab);
        free(revstate);
        tab = phelp;
        revstate = nrevstate;
        rownr=acrow;
    }
    // write the elementary modes to the output file
    fout->WriteString("\nELEMENTARY MODES\n");
    for (i=0; i<rownr; i++)
    {
        StrOut.Format(" Mode %d (", i+1);
        if (*(revstate+i)) StrOut += "irreversible)\n";
        else StrOut += "reversible)\n";
        fout->WriteString(LPCTSTR(StrOut));
        for (j=nmet; j<colnr; j++)
            if (*(*(tab+i)+j) != 0)
            {
                StrOut.Format("  %+3d %s\n", *(*(tab+i)+j), LPCTSTR(Step[mCol[j-nmet]].Name));
                fout->WriteString(LPCTSTR(StrOut));
            }
    }
    fout->WriteString("\n");
    // release memory
    for (j=0; j<rownr; j++) if (*(tab+j)!=NULL) free(*(tab+j));
    free(tab);
    for (j=0; j<nreact; j++) free(*(sub+j));
    free(sub);
    free(revstate);
    // return
    return 0;
}

C_INT32 CModel::AddMetabolite(string &NewName)
{
    C_INT32 DimMetab, DimStep;
    C_INT32 i, j, *ivector, **imatrix;
    C_FLOAT32 **fmatrix;
    CMetab *OldMetabolite;

    // initialize the dimensions
    if (TotMetab == 0) DimMetab = 1;
    else DimMetab = TotMetab;
    if (TotStep == 0) DimStep = 1;
    else DimStep = TotStep;

    // return 1 if the string contains invalid characters
    if (NewName.IsEmpty()) return 1;
    if (NewName.FindOneOf(" \t.*=") != -1) return 1;
    if (NewName.Find("->") != -1) return 1;

    // return 2 if the name already exists
    for (i=0; i<TotMetab; i++)
        if (NewName == mMetabolite[i].Name)
            return 2;

    // create array for copy
    OldMetabolite  = new CMetab[DimMetab];
    // copy metabolite array
    for (i=0; i<TotMetab; i++)
        OldMetabolite[i] = mMetabolite[i];
    // destroy array
    delete [] mMetabolite;
    // create a new one
    mMetabolite  = new CMetab[TotMetab+1];
    // copy back the elements
    for (i=0; i<TotMetab; i++)
        mMetabolite[i] = OldMetabolite[i];
    // and add the new one
    mMetabolite[TotMetab].Name = NewName;
    mMetabolite[TotMetab].Status = METAB_FIXED;
    // delete temporary copy
    delete [] OldMetabolite;

    // deal with Row & IRow
    ivector = new C_INT32 [DimMetab];
    for (i=0; i<TotMetab; i++)
        ivector[i] = mRow[i];
    delete [] mRow;
    mRow = new C_INT32 [TotMetab+1];
    for (i=0; i<TotMetab; i++)
        mRow[i] = ivector[i];
    mRow[TotMetab] = TotMetab;
    for (i=0; i<TotMetab; i++)
        ivector[i] = mIRow[i];
    delete [] mIRow;
    mIRow = new C_INT32 [TotMetab+1];
    for (i=0; i<TotMetab; i++)
        mIRow[i] = ivector[i];
    mIRow[TotMetab] = TotMetab;
    delete [] ivector;

    fmatrix = new C_FLOAT32 *[DimMetab];
    for (i=0; i<DimMetab; i++)
    {
        fmatrix[i] = new C_FLOAT32[DimStep];
        for (j=0; j<DimStep; j++)
            fmatrix[i][j] = mStoichiometry[i][j];
    }
    for (i=0; i<DimMetab; i++)
        delete [] mStoichiometry[i];
    delete [] mStoichiometry;
    mStoichiometry = new C_FLOAT32 *[TotMetab+1];
    for (i=0; i<TotMetab+1; i++)
    {
        mStoichiometry[i] = new C_FLOAT32[DimStep];
        for (j=0; j<DimStep; j++)
            mStoichiometry[i][j] = i!=TotMetab ? fmatrix[i][j] : 0.0F;
    }

    for (i=0; i<DimMetab; i++)
        for (j=0; j<DimStep; j++)
            fmatrix[i][j] = mRedStoi[i][j];
    for (i=0; i<DimMetab; i++)
        delete [] mRedStoi[i];
    delete [] mRedStoi;
    mRedStoi = new C_FLOAT32 *[TotMetab+1];
    for (i=0; i<TotMetab+1; i++)
    {
        mRedStoi[i] = new C_FLOAT32[DimStep];
        for (j=0; j<DimStep; j++)
            mRedStoi[i][j] = i!=TotMetab ? fmatrix[i][j] : 0.0F;
    }

    for (i=0; i<DimMetab; i++)
        delete [] fmatrix[i];

    for (i=0; i<DimMetab; i++)
    {
        fmatrix[i] = new C_FLOAT32[DimMetab];
        for (j=0; j<DimMetab; j++)
            fmatrix[i][j] = mConsRel[i][j];
    }
    for (i=0; i<DimMetab; i++)
        delete [] mConsRel[i];
    delete [] mConsRel;
    mConsRel = new C_FLOAT32 *[TotMetab+1];
    for (i=0; i<TotMetab+1; i++)
    {
        mConsRel[i] = new C_FLOAT32[TotMetab+1];
        for (j=0; j<TotMetab; j++)
            mConsRel[i][j] = i!=TotMetab ? fmatrix[i][j] : 0.0F;
        mConsRel[i][TotMetab] = 0.0F;
    }

    for (i=0; i<DimMetab; i++)
        for (j=0; j<DimMetab; j++)
            fmatrix[i][j] = mML[i][j];
    for (i=0; i<DimMetab; i++)
        delete [] mML[i];
    delete [] mML;
    mML = new C_FLOAT32 *[TotMetab+1];
    for (i=0; i<TotMetab+1; i++)
    {
        mML[i] = new C_FLOAT32[TotMetab+1];
        for (j=0; j<TotMetab; j++)
            mML[i][j] = i!=TotMetab ? fmatrix[i][j] : 0.0F;
        mML[i][TotMetab] = 0.0F;
    }

    for (i=0; i<DimMetab; i++)
        delete [] fmatrix[i];
    delete [] fmatrix;

    imatrix = new C_INT32 *[DimStep];
    for (i=0; i<DimStep; i++)
    {
        imatrix[i] = new C_INT32[DimMetab];
        for (j=0; j<DimMetab; j++)
            imatrix[i][j] = mReactStruct[i][j];
    }
    for (i=0; i<DimStep; i++)
        delete [] mReactStruct[i];
    delete [] mReactStruct;
    mReactStruct = new C_INT32 *[DimStep];
    for (i=0; i<DimStep; i++)
    {
        mReactStruct[i] = new C_INT32[TotMetab+1];
        for (j=0; j<TotMetab; j++)
            mReactStruct[i][j] = imatrix[i][j];
        mReactStruct[i][TotMetab] = 0;
    }

    for (i=0; i<DimStep; i++)
        delete [] imatrix[i];
    delete [] imatrix;

    // increase the total
    TotMetab++;
    // return 0 - no error
    return 0;
}

// rebuilds the stoichiometry matrix from step data
void CModel::RebuildStoi(C_INT32 flag)
{
    C_INT32 i, j;

    // clean the matrix if needed
    if (flag==1)
        for (i=0; i<TotMetab; i++)
            for (j=0; j<TotStep; j++)
                mStoichiometry[i][j] = 0.0;

    for (i=0; i<TotStep; i++)
    {
        for (j=0; j<Step[i].SubstrateNo; j++)
            mStoichiometry[Step[i].Substrate[j]][i] -= 1.0;
        for (j=0; j<Step[i].ProductNo; j++)
            mStoichiometry[Step[i].Product[j]][i] += 1.0;
    }
}

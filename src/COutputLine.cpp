/*****************************************************************************
* PROGRAM NAME: COutputLine.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: COutputLine Class Implemention
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "copasi.h"			
#include "CDatum.h"
#include "COutputLine.h"

/**
 *  Default constructor. 
 */
COutputLine::COutputLine()
{
	mLine = NULL;
}

void COutputLine::Init()
{
	mLine = new CCDatum;
}

void COutputLine::Delete()
{
	if (mLine) delete mLine;
	mLine = NULL;
}

/**
 *  Destructor. 
 */
COutputLine::~COutputLine()
{
//	Delete();
}

/**
 *  Assignement operator. 
 *  Copies the contents from one COutputLine object to another.
 *  @param source reference to the recipient object.
 */
COutputLine& COutputLine::operator=(const COutputLine &source)
{
	mLine = source.mLine;
	
	return *this;
}

/**
 *  Return the pointer of the CDatum that can be output at the same line. 
 *  @return mLine
 *  @see mLine
 */
COutputLine::CCDatum * COutputLine::GetLine() const
{
	return mLine;
}

/**
 *  Sets the name of this line, (For example: Interactive time course)
 *  @param title constant reference to a string.
 */
void COutputLine::SetName(string LineName)
{
	mName = LineName;
}


/**
 *  Add new CDatum object to a line
 *  @param newDatum constant reference to CDatum.
 *  @see CDatum Class
     */
void COutputLine::AddDatum(CDatum & newDatum)
{
	mLine->add(newDatum);
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @param searchName refernece to a the time of seach section,
 *		   for example: Interactive time course		
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputLine::load(CReadConfig & configbuffer, string &searchName)
{
	C_INT32 Fail = 0;
	C_INT32 Size = 0;

	// Search string searchName from configure variable
	if (Fail = configbuffer.getVariable(searchName, "string",
                                        &mName,
                                        CReadConfig::SEARCH))
        return Fail;

	// now pout points the end of search string
	// Read the number of items in this section
	if (Fail = configbuffer.getVariable("Items", "C_INT32", 
										&Size, CReadConfig::NEXT))
        return Fail;

	Init();

	// Read objects and create the OutputLine
	for (int i = 0; i < Size; i++)
	{
		CDatum newItem;

		newItem.load(configbuffer);
		AddDatum(newItem);
	}

	return Fail;
}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputLine::save(CWriteConfig & configbuffer)
{
	C_INT32 Fail = 0;
	C_INT32 Size = 0;

	Size = mLine->size();

    if (Fail = configbuffer.setVariable(mName, "string", NULL))
		return Fail;

    if (Fail = configbuffer.setVariable("Items", "C_INT32", &Size))
		return Fail;

	// Output each datum in this line
	Fail = mLine->save(configbuffer);
	
	return Fail;
}

/**
 *	print the titles of the steady-state data file
 */
void COutputLine::SS_OutputTitles(ofstream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) 
{
	int i;
	CDatum item;
	string Title;

	// Set Left Justification
	fout.setf(ios::left);
	for (i = 0; i < mLine->size(); i++)
	{
		if (i) {
			switch (SSSeparator)
			{
			case 9: 
					fout << "\t";
					break;
			case 32:	
					fout << " ";
					break;
			case 44:
					fout << ",";
					break;
			}
		}
		item = (*mLine)[i];
		
		if (item.GetTitle().length() > SSColWidth)
			Title = item.GetTitle().substr(0, SSColWidth);
		else Title = item.GetTitle();
		
		if (SSQuotes) fout << "\"" << setw(SSColWidth) << Title << "\"";
		else fout << setw(SSColWidth) <<Title;
	}

	fout.unsetf(ios::left);
	fout << endl;
}

/**
 *	print the mpValue of each Object in the steady-state data file
 */
void COutputLine::SS_OutputData(ofstream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) 
{
	int i;
	C_INT32 Type;
	C_INT16 *Value1;
	C_INT32 *Value2;
	C_FLOAT32 *Value3;
	C_FLOAT64 *Value4;

	// Set Left Justification
	fout.setf(ios::left);
	// Set Float manipulators
	fout.setf(ios::scientific, ios::floatfield);
	fout.setf(ios::showpoint);

	for (i = 0; i < mLine->size(); i++)
	{
		if (i) {
			switch (SSSeparator)
			{
			case 9: 
					fout << "\t";
					break;
			case 32:	
					fout << " ";
					break;
			case 44:
					fout << ",";
					break;
			}
		}

		Type = (*mLine)[i].GetType();

		switch (Type)
		{
			case 1:	
					// Type is C_INT16
					Value1 = (C_INT16 *)(*mLine)[i].GetValue();
					if (!Value1)
						fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << 0;  //?? Sign setw(SSColWidth-1)
						else fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << *Value1; //?? Sign
					break;
			case 2:
					// Type is C_INT32
					Value2 = (C_INT32 *)(*mLine)[i].GetValue();
					if (!Value2)
						fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << 0;
						else fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << *Value2;
					break;
			case 3:
					// Type is C_FLOAT32
					Value3 = (C_FLOAT32 *)(*mLine)[i].GetValue();
					if (!Value3)
						fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << 0;
						else fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << *Value3;
					break;
			case 4:
					// Type is C_FLOAT64
					Value4 = (C_FLOAT64 *)(*mLine)[i].GetValue();
					if (!Value4)
						fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << 0;
						else fout << setprecision(SSColWidth - 8) << setw(SSColWidth) << *Value4;

					break;
		}

	}

	fout.unsetf(ios::left);
	fout << endl;
}

/**
 *	print the titles of the time course data file
 */
void COutputLine::Dyn_OutputTitles(ofstream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) 
{
	int i;
	CDatum item;
	string Title;

	// Set Left Justification
	fout.setf(ios::left);
	for (i = 0; i < mLine->size(); i++)
	{
		if (i) {
			switch (DynSeparator)
			{
			case 9: 
					fout << "\t";
					break;
			case 32:	
					fout << " ";
					break;
			case 44:
					fout << ",";
					break;
			}
		}
		item = (*mLine)[i];
		
		if (item.GetTitle().length() > DynColWidth)
			Title = item.GetTitle().substr(0, DynColWidth);
		else Title = item.GetTitle();
		
		if (DynQuotes) fout << "\"" << setw(DynColWidth) << Title << "\"";
		else fout << setw(DynColWidth) <<Title;
	}

	fout.unsetf(ios::left);
	fout << endl;
}

/**
 *	print the mpValue of each Object in the time course data file
 */
void COutputLine::Dyn_OutputData(ofstream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) 
{
	int i;
	C_INT32 Type;
	C_INT16 *Value1;
	C_INT32 *Value2;
	C_FLOAT32 *Value3;
	C_FLOAT64 *Value4;

	// Set Left Justification
	fout.setf(ios::left);
	// Set Float manipulators
	fout.setf(ios::scientific, ios::floatfield);
	fout.setf(ios::showpoint);

	for (i = 0; i < mLine->size(); i++)
	{
		if (i) {
			switch (DynSeparator)
			{
			case 9: 
					fout << "\t";
					break;
			case 32:	
					fout << " ";
					break;
			case 44:
					fout << ",";
					break;
			}
		}

		Type = (*mLine)[i].GetType();

		switch (Type)
		{
			case 1:	
					// Type is C_INT16
					Value1 = (C_INT16 *)(*mLine)[i].GetValue();
					if (!Value1)
						fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << 0;
						else fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << *Value1;
					break;
			case 2:
					// Type is C_INT32
					Value2 = (C_INT32 *)(*mLine)[i].GetValue();
					if (!Value2)
						fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << 0;
						else fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << *Value2;
					break;
			case 3:
					// Type is C_FLOAT32
					Value3 = (C_FLOAT32 *)(*mLine)[i].GetValue();
					if (!Value3)
						fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << 0;
						else fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << *Value3;
					break;
			case 4:
					// Type is C_FLOAT64
					Value4 = (C_FLOAT64 *)(*mLine)[i].GetValue();
					if (!Value4)
						fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << 0;
						else fout << setprecision(DynColWidth - 8) << setw(DynColWidth) << *Value4;

					break;
		}
	}

	fout.unsetf(ios::left);
	fout << endl;
}


/**
 *  Complie the mpValue in each output line
 */
void COutputLine::Compile(string &name, CModel &model)
{
	if (!mName.compare(name))
	{ // ???? Maybe it isnot necessary after finish whole module
		for (int i = 0; i < mLine->size(); i++)
		{
			(*mLine)[i].CompileDatum(model);
		}
	}
}

COutputLine::CCDatum::CCDatum() {}

COutputLine::CCDatum::~CCDatum() {}

C_INT16 COutputLine::CCDatum::isInsertAllowed(const CDatum & src)
{return TRUE;}

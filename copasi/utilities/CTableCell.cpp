/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CTableCell.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/15 18:47:00 $
   End CVS Header */

#include <limits>
#include <iostream>
#include <sstream>
#include <float.h>

#include "copasi.h"

#include "CTableCell.h"

CTableCell::CTableCell(const char & separator):
    mSeparator(separator),
    mName(""),
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mIsValue(false),
    mIsEmpty(true)
{}

CTableCell::CTableCell(const CTableCell & src):
    mSeparator(src.mSeparator),
    mName(src.mName),
    mValue(src.mValue),
    mIsValue(src.mIsValue),
    mIsEmpty(src.mIsEmpty)
{}

CTableCell::~CTableCell() {}

bool CTableCell::setSeparator(const char & separator)
{
  mSeparator = separator;
  return true;
}

const char & CTableCell::getSeparator() const {return mSeparator;}

const bool & CTableCell::isValue() const {return mIsValue;}

const bool & CTableCell::isEmpty() const {return mIsEmpty;}

const std::string & CTableCell::getName() const {return mName;}

const C_FLOAT64 & CTableCell::getValue() const {return mValue;}

#ifdef WIN32 
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
 #endif

std::istream & operator >> (std::istream &is, CTableCell & cell)
{
  static char buffer[256];

  cell.mName = "";

  do
    {
      is.getline(buffer, 256, cell.mSeparator);
      cell.mName += buffer;
    }
  while (strlen(buffer) == 255 && !is.fail());

  /* Trim leading and trailing whitespaces from the string */
  std::string::size_type begin = cell.mName.find_first_not_of("\x20\x09\x0d\x0a");

  if (begin == std::string::npos)
    {
      cell.mName = "";
      cell.mIsValue = false;
      cell.mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      cell.mIsEmpty = true;
      return is;
    }
  else
    {
      std::string::size_type end = cell.mName.find_last_not_of("\x20\x09\x0d\x0a");

      if (end == std::string::npos)
        cell.mName = cell.mName.substr(begin);
      else
        cell.mName = cell.mName.substr(begin, end - begin + 1);

      cell.mIsEmpty = false;
    }

  /* Try to convert the string into a number */
  char * Tail;
  cell.mValue = strtod(cell.mName.c_str(), & Tail);

  if (!*Tail)
    {
      cell.mIsValue = true;
    }
  else if (cell.mName.c_str() == "INF")
    {
      cell.mIsValue = true;
      cell.mValue = DBL_MAX * 2;
    }
  else if (cell.mName.c_str() == "-INF")
    {
      cell.mIsValue = true;
      cell.mValue = - DBL_MAX * 2;
    }
  else
    {
      cell.mIsValue = false;
      cell.mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  return is;
}

#ifdef WIN32
 # pragma warning (default: 4056 4756)
 #endif

CTableRow::CTableRow(const unsigned C_INT32 & size,
                     const char & separator):
    mCells(0),
    mSeparator(separator),
    mIsEmpty(true)
{resize(size);}

CTableRow::CTableRow(const CTableRow & src):
    mCells(src.mCells),
    mSeparator(src.mSeparator),
    mIsEmpty(src.mIsEmpty)
{}

CTableRow::~CTableRow() {}

const std::vector< CTableCell > & CTableRow::getCells() const
  {return mCells;}

bool CTableRow::resize(const unsigned C_INT32 & size)
{
  mCells.resize(size);

  std::vector< CTableCell >::iterator it = mCells.begin();
  std::vector< CTableCell >::iterator end = mCells.end();

  for (; it != end; ++it)
    it->setSeparator(mSeparator);

  return true;
}

const unsigned C_INT32 CTableRow::size() const
{return mCells.size();}

unsigned C_INT32 CTableRow::guessColumnNumber(std::istream &is,
    const bool & rewind)
{
  std::istream::pos_type pos;
  if (rewind) pos = is.tellg();

  std::stringstream line;
  is.get(*line.rdbuf(), '\x0a');

  // std::istream::get sets the failbit if it does not extract anything.
  // We expect empty lines and have to correct for it.
  if (is.fail() && !is.eof()) is.clear();

  is.ignore(1);

  if (rewind) is.seekg(pos);

  CTableCell Cell(mSeparator);
  unsigned C_INT32 count = 0;

  while (!line.eof())
    {
      line >> Cell;
      count++;
    }

  if (Cell.getName() == "") count--;

  return count;
}

const bool & CTableRow::isEmpty() const {return mIsEmpty;}

std::istream & operator >> (std::istream &is, CTableRow & row)
{
  std::stringstream line;

  is.get(*line.rdbuf(), '\x0a');

  // std::istream::get sets the failbit if it does not extract anything.
  // We expect empty lines and have to correct for it.
  if (is.fail() && !is.eof()) is.clear();

  is.ignore(1);

  row.mIsEmpty = true;
  std::vector< CTableCell >::iterator it = row.mCells.begin();
  std::vector< CTableCell >::iterator end = row.mCells.end();

  for (; it != end && !line.fail(); ++it)
    {
      line >> *it;
      if (!it->isEmpty()) row.mIsEmpty = false;
    }

  CTableCell Unread(row.mSeparator);
  while (!line.fail() && !line.eof())
    {
      row.mCells.push_back(Unread);
      line >> row.mCells.back();
      if (!row.mCells.back().isEmpty()) row.mIsEmpty = false;
    }

  if (it == end) return is;

  // Missing columns are filled with default
  for (; it != end; ++it)
    *it = Unread;

  return is;
}

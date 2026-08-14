// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CTableCell
#define COPASI_CTableCell

#include <iostream>
#include <vector>

class CTableCell
{
  // Operations
public:
  /**
   * Default constructor
   * @param const char & separator (default: '\t')
   */
  CTableCell(const char & separator = '\t');

  /**
   * Destructor
   */
  ~CTableCell();

  /**
   * Set the separator
   * @param const char & separator
   * @return bool success
   */
  bool setSeparator(const char & separator);

  /**
   * Retreive the separator
   * @return const char & separator
   */
  const char & getSeparator() const;

  /**
   * Check whether the cell contains a numeric value
   * @return bool isValue
   */
  const bool & isValue() const;

  /**
   * Retrieve the name.
   * @return const std::string & name
   */
  const std::string & getName() const;

  /**
   * Retrieve the value.
   * @return const C_FLOAT64 & value
   */
  const C_FLOAT64 & getValue() const;

  /**
   * Check whether a cell contains any data.
   * A cell is considered empty when it only contains
   * whitespace charaters.
   */
  const bool & isEmpty() const;

  /**
   * Formated stream input operator
   * @param CTableCell & cell
   * @return std::istream &
   */
  friend
  std::istream & operator >> (std::istream &is, CTableCell & cell);

  // Attributes
private:
  char mSeparator;

  std::string mName;

  C_FLOAT64 mValue;

  bool mIsValue;

  bool mIsEmpty;
};

class CTableRow
{
  // Operations
public:
  /**
   * Default constructor
   * @param const unisgned C_INT32 & size (default: 0)
   * @param const char & separator (default: '\t')
   */
  CTableRow(const size_t & size = 0,
            const char & separator = '\t');

  /**
   * Copy constructor
   * @param const CTableRow & src
   */
  CTableRow(const CTableRow & src);

  /**
   * Destructor
   */
  ~CTableRow();

  /**
   * Retrieve the cells.
   * @return const std::vector< CTableCell > & cells
   */
  const std::vector< CTableCell > & getCells() const;

  /**
   * Resize
   * @param const size_t & size
   * @return bool success
   */
  bool resize(const size_t & size);

  /**
   * Retrieve the size of the row
   * @return const size_t size
   */
  size_t size() const;

  /**
   * Retrieve the index of the last non empty cell
   * in the last read operation.
   * @const size_t & lastFilledCell
   */
  const size_t & getLastFilledCell() const;

  /**
   * Try to guess the number of columns
   * in the current line
   * @param std::istream &is
   * @param const bool & rewind
   * @return size_t numColumns
   */
  size_t guessColumnNumber(std::istream &is,
                           const bool & rewind);

  /**
   * Check whether row contains any cells with data
   * A row is considered empty when it all cells are empty.
   */
  const bool & isEmpty() const;

  /**
   * Formated stream input operator
   * @param CTableRow & cell
   * @return std::istream &
   */
  friend
  std::istream & operator >> (std::istream &is, CTableRow & cell);

private:
  /**
   * Fill the row with data from the inpute stream until End_Of_Line
   * is encountered and advance the stream accordingly.
   * @param std::istream & is
   * @return std::istream & is
   */
  std::istream & readLine(std::istream & is);

  // Attributes
private:
  std::vector< CTableCell > mCells;

  char mSeparator;

  bool mIsEmpty;

  size_t mLastFilledCell;
};

#endif // COPASI_CTableCell

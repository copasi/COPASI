/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CTableCell.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/23 18:59:12 $
   End CVS Header */

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
     * Copy constructor
     * @param const CTableCell & src
     */
    CTableCell(const CTableCell & src);

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
    CTableRow(const unsigned C_INT32 & size = 0,
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
     * @param const unsigned C_INT32 & size
     * @return bool success
     */
    bool resize(const unsigned C_INT32 & size);

    /**
     * Retrieve the size of the row
     * @return const unsigned C_INT32 size
     */
    const unsigned C_INT32 size() const;

    /**
     * Formated stream input operator
     * @param CTableRow & cell
     * @return std::istream &
     */
    friend
    std::istream & operator >> (std::istream &is, CTableRow & cell);

    // Attributes
  private:
    std::vector< CTableCell > mCells;

    char mSeparator;
  };

#endif // COPASI_CTableCell

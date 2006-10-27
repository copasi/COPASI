%{

#include "utilities/CMatrix.h"

%}


template <class CType>
class CMatrix
  {
  public:
    typedef CType elementType;

    /**
     * Default constructor
     * @param unsigned C_INT32 rows (default = 0)
     * @param unsigned C_INT32 cols (default = 0)
     */
    CMatrix(unsigned C_INT32 rows = 0, unsigned C_INT32 cols = 0);
    
    /**
     * Copy constructor
     * @param const CMatrix <CType> & src
     */
    CMatrix(const CMatrix <CType> & src);

    /**
     * Destructor.
     */
    virtual ~CMatrix();

    /**
     * The number of elements stored in the matrix.
     * @return unsigned C_INT32 size
     */
    virtual unsigned C_INT32 size();

    /**
     * The number of rows of the matrix.
     * @return unsigned C_INT32 rows
     */
    virtual unsigned C_INT32 numRows() const;

    /**
     * The number of columns of the matrix
     * @return unsigned C_INT32 cols
     */
    virtual unsigned C_INT32 numCols() const;

    /**
     * Resize the matrix. The previous content is lost
     * @param unsigned C_INT32 rows
     * @param unsigned C_INT32 cols
     */
    virtual void resize(unsigned C_INT32 rows, unsigned C_INT32 cols);
  };


%template(FloatMatrix) CMatrix<C_FLOAT64>;

typedef CMatrix<C_FLOAT64> FloatMatrix;

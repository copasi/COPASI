/**
 * CRandomSearch class
 */

#ifndef COPASI_CRandomSearch
#define COPASI_CRandomSearch

class CRandom;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */
class CRandomSearch : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(COptMethod::Type type);

    // Operations
  private:
    /**
     * Default Constructor
     */
    CRandomSearch();

  public:
    /**
     * Copy Constructor
     * @param const CRandomSearch & src
     */
    CRandomSearch(const CRandomSearch & src);

    /**
     * Destructor
     */
    virtual ~CRandomSearch();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual C_INT32 optimise();
  };

#endif  // COPASI_CRandomSearch

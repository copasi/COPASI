/**
 * CRandomSearchMaster class
 */

#ifndef COPASI_CRandomSearchMaster
#define COPASI_CRandomSearchMaster

class CRandomSearchMaster : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(COptMethod::Type type);

    // Operations
  private:
    /**
     * Default Constructor
     */
    CRandomSearchMaster();

  public:
    /**
     * Copy Constructor
     * @param const CRandomSearchMaster & src
     */
    CRandomSearchMaster(const CRandomSearchMaster & src);

    /**
     * Destructor
     */
    virtual ~CRandomSearchMaster();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual C_INT32 optimise();
  };

#endif  // COPASI_CRandomSearchMaster

/**
 *  CMoiety
 *  
 *  New class created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMoiety
#define COPASI_CMoiety

#include <string>
#include <vector>

#include "CMetab.h"
#include "CChemEqElement.h"

/** @dia:pos 52.1566,116.062 */
class CMoiety : public CCopasiContainer
  {
    // Attributes
  private:
    /**
     *
     */
    std::string & mName;

    /**
     *  Number of Particles of Moietiy.
     */
    C_FLOAT64 mNumber;

    /**
     *  Initial Number of Particles of Moietiy.
     */
    C_FLOAT64 mINumber;

    /**
     *  Vector of linear dependent CChemEqElement
     * @supplierCardinality 0..*
     */
    /** @dia:route 7,3; h,45.5713,110.781,50.1417,116.762,52.1566 */
    CCopasiVector < CChemEqElement > mEquation;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoiety(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CMoiety &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoiety(const CMoiety & src,
            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CMoiety();

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  This saves the data in Gepasi 3.21 file format
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 saveOld(CWriteConfig & configBuffer);

    /**
     *
     */
    void add
    (C_FLOAT64 value, CMetab & metabolite);

    /**
     *
     */
    void add
    (C_FLOAT64 value, CMetab * metabolite);

    /**
     *
     */
    void cleanup();

    /**
     *
     */
    void cleanup(const std::string & name);

    /**
     *
     */
    void cleanup(C_INT32 index);

    /**
     *
     */
    void change(C_INT32 index,
                C_FLOAT64 value);

    /**
     *
     */
    void change(const std::string & name,
                C_FLOAT64 value);

    /**
     *
     */
    void setName(const std::string name);

    /**
     *
     */
    void setInitialValue();

    /**
     *
     */
    const std::string & getName() const;

    /**
     *
     */
    std::string getDescription() const;

    /**
     *
     */
    C_FLOAT64 dependentNumber();

    /**
     *
     */
    C_FLOAT64 dependentRate();

    /**
     *
     */
    C_FLOAT64 getNumber() const;

    /**
     * Returns the address of mNumber
     */
    void * getNumberAddr();
  };

#endif // COPASI_CMoiety

/**
 *  CMathVariable class.
 *  The class CMathVariable associates a symbol with a CCopasiObject which
 *  functions as a variable in the system of ODEs.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathVariable
#define COPASI_CMathVariable

#include <string>

#include "CMathSymbol.h"

class CModel;
class CMetab;
class CCompartment;
class CMathEq;
class CMathConstantCompartment;

/** @dia:pos 47.1654,-4.20827 */
/** @dia:route CMathSymbol; v,-33.2334,-9.4956,-6.77401,67.1906,-4.20827 */
class CMathVariable: public CMathSymbol
  {
  public:
    /**
     * The types of the associated equation
     */
    enum Type {Eq = 0, StructuredDE, FreeFormDE};

    /**
     * A string representation of the equation/variable type
     */
    static const std::string TypeName[];

    // Attributes
  protected:
    /**
     ** The type of the associated equation
     */
    CMathVariable::Type mType;

    /**
     *
     */
    /** @dia:route 2,0; h,33.0379,-3.77715,38.2749,-4.20827,47.1654 */
    CMathEq * mpEq;

    // Operations
  protected:
    /**
     *
     */
    CMathVariable();

    /**
     *
     */
    CMathVariable(const CMathVariable & src);

  public:
    /**
     *
     */
    CMathVariable(const CCopasiObject * pObject);

    /**
     *
     */
    virtual ~CMathVariable();

    /**
     *
     */
    virtual bool setInitialValue(const C_FLOAT64 & value) = NULL;

    /**
     *
     */
    virtual const C_FLOAT64 & getInitialValue() const = NULL;

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const = NULL;

    /**
     *
     */
    bool setEq(CMathEq * eq,
               const CMathVariable::Type & type = CMathVariable::Eq);

    /**
     *
     */
    CMathEq * getEq();

    /**
     * 
     */
    CMathVariable::Type getType() const;
  };

/**
 * The class CMathVariableMetab associates a symbol with a metabolite
 * that is a variable in the system of ODEs
 */ 
/** @dia:pos 54.9742,19.8639 */
/** @dia:route CMathVariable; v,47.1654,7.19173,18.7388,72.0954,19.8639 */
class CMathVariableMetab : public CMathVariable
  {
    // Attributes
  private:
    /**
     *
     */
    /** @dia:route 9,0; h,36.0092,10.0564,42.3789,19.8639,54.9742 */
    CMathConstantCompartment * mpCompartment;

    // Operations
  protected:
    /**
     *
     */
    CMathVariableMetab();

    /**
     *
     */
    CMathVariableMetab(const CMathVariableMetab & src);

  public:
    /**
     *
     */
    CMathVariableMetab(const CMetab & metabolite);

    /**
     *
     */
    ~CMathVariableMetab();

    /**
     *
     */
    virtual bool setInitialValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getInitialValue() const;

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;

    /**
     *
     */
    bool setInitialConcentration(const C_FLOAT64 & concentration);

    /**
     *
     */
    const C_FLOAT64 & getInitialConcentration() const;

    /**
     *
     */
    const C_FLOAT64 & getConcentration() const;

    /**
     *
     */
    bool setInitialParticleNumber(const C_FLOAT64 & particleNumber);

    /**
     *
     */
    C_FLOAT64 getInitialParticleNumber() const;

    /**
     *
     */
    C_FLOAT64 getParticleNumber() const;

    /**
     *
     */
    CMathConstantCompartment & getCompartment() const;

    /**
     *
     */
    bool compile();
  };

/**
 * The class CMathVariableVolume associates a symbol with a compartment 
 * volume which is a variable in the system of ODEs
 */ 
/** @dia:pos 54.9742,10.1749 */
/** @dia:route CMathVariable; v,47.1654,7.19173,8.89254,69.5214,10.1749 */
class CMathVariableVolume : public CMathVariable
  {
    // Operations
  protected:
    /**
     *
     */
    CMathVariableVolume();

    /**
     *
     */
    CMathVariableVolume(const CMathVariableVolume & src);

  public:
    /**
     *
     */
    CMathVariableVolume(const CCompartment & compartment);

    /**
     *
     */
    ~CMathVariableVolume();

    /**
     *
     */
    virtual bool setInitialValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getInitialValue() const;

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;
  };

/**
 * The class CMathVariableTime associates a symbol with the model time
 * which is a variable in the system of ODEs
 */ 
/** @dia:pos 54.9742,35.5887 */
/** @dia:route CMathVariable; v,47.1654,7.19173,34.543,69.4554,35.5887 */
class CMathVariableTime : public CMathVariable
  {
    // Operations
  protected:
    /**
     *
     */
    CMathVariableTime();

    /**
     *
     */
    CMathVariableTime(const CMathVariableTime & src);

  public:
    /**
     *
     */
    CMathVariableTime(const CModel & model);

    /**
     *
     */
    ~CMathVariableTime();

    /**
     *
     */
    virtual bool setInitialValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getInitialValue() const;

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;
  };

#endif // COPASI_CMathVariable

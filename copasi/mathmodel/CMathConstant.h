/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathConstant.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/17 08:56:19 $
   End CVS Header */

/**
 *  CMathConstant class.
 *  The class CMathConstant associates a symbol with a CCopasiObject with
 *  that represents a fixed metabolite.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathConstant
#define COPASI_CMathConstant

#include <map>

#include "CMathSymbol.h"
#include "model/CReaction.h"

class CMetab;
class CMathVariableMetab;
class CMathConstantCompartment;
template < class CType > class CCopasiObjectReference;

/** @dia:pos -3.01499,-4.1693 */
/** @dia:route CMathSymbol; v,-33.2334,-9.4956,-6.77622,9.59181,-4.1693 */
class CMathConstant: public CMathSymbol
  {
    // Operations
  protected:
    /**
     *
     */
    CMathConstant();

    /**
     *
     */
    CMathConstant(const CMathConstant & src);

  public:
    /**
     *
     */
    CMathConstant(const CCopasiObject * pObject);

    /**
     *
     */
    virtual ~CMathConstant();

    /**
     *
     */
    virtual bool setValue(const C_FLOAT64 & value) = 0;

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const = 0;
  };

/** @dia:pos 2.18922,19.202 */
/** @dia:route CMathConstant; v,-3.01499,2.6307,18.3177,17.4624,19.202 */
class CMathConstantMetab : public CMathConstant
  {
    // Attributes
  private:
    /**
     *
     */
    /** @dia:route 13,4; h,36.0092,11.6564,41.4265,19.902,32.7356 */
    CMathConstantCompartment * mpCompartment;

    // Operations
  protected:
    /**
     *
     */
    CMathConstantMetab();

    /**
     *
     */
    CMathConstantMetab(const CMathConstantMetab & src);

  public:
    /**
     *
     */
    CMathConstantMetab(const CMetab & metabolite);

    /**
     *
     */
    ~CMathConstantMetab();

    /**
     *
     */
    virtual bool setValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;

    /**
     *
     */
    bool setConcentration(const C_FLOAT64 & concentration);

    /**
     *
     */
    const C_FLOAT64 & getConcentration() const;

    /**
     *
     */
    bool setParticleNumber(const C_FLOAT64 & particleNumber);

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

class CMathConstantReference : public CMathConstant
  {
    // Attributes
  private:
    /**
     *
     */
    static std::map< std::string, CCopasiObject * > mSelection;

    // Operations
  protected:
    /**
     *
     */
    CMathConstantReference();

    /**
     *
     */
    CMathConstantReference(const CMathConstantReference & src);

  public:
    /**
     *
     */
    CMathConstantReference(const CCopasiObjectReference< C_FLOAT64 > & reference);

    /**
     *
     */
    ~CMathConstantReference();

    /**
     *
     */
    virtual bool setValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;

    /**
     * Retreive the selection list
     * @return const std::map< std::string, CCopasiObject * > & selectionList
     */
    static const std::map< std::string, CCopasiObject * > & getSelection();

    /**
     * Build the selection list
     * @param const CModel * pModel
     * @return bool Success
     */
    static bool buildSelection(const CModel * pModel);
  };

/** @dia:pos 2.18922,32.6698 */
/** @dia:route CMathConstant; v,-3.01499,2.6307,31.9,19.1124,32.6698 */
class CMathConstantParameter : public CMathConstant
  {
    // Attributes
  private:
    std::string mReaction;

    // Operations
  private:
    /**
     *
     */
    static std::map< std::string, CCopasiObject * > mSelection;

  protected:
    /**
     *
     */
    CMathConstantParameter();

    /**
     *
     */
    CMathConstantParameter(const CMathConstantParameter & src);

  public:
    /**
     *
     */
    CMathConstantParameter(const CCopasiParameter & parameter,
                           const std::string & reaction);

    /**
     *
     */
    ~CMathConstantParameter();

    /**
     *
     */
    virtual bool setValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;

    /**
     *
     */
    const std::string & getReaction() const;

    /**
     * Retreive the selection list
     * @return const std::map< std::string, CCopasiObject * > & selectionList
     */
    static const std::map< std::string, CCopasiObject * > & getSelection();

    /**
     * Build the selection list
     * @param const CModel * pModel
     * @return bool Success
     */
    static bool buildSelection(const CModel * pModel);
  };

/** @dia:pos 2.18922,7.75635 */
/** @dia:route CMathConstant; v,-3.01499,2.6307,6.64374,19.0992,7.75635 */
class CMathConstantCompartment : public CMathConstant
  {
    // Attributes
  private:
    /**
     *
     */
    /** @dia:route 0,9; h,2.18922,7.75635,-6.00072,-23.7956,-12.6802 */
    std::vector< CMathSymbol * > mMetaboliteList;

    // Operations
  protected:
    /**
     *
     */
    CMathConstantCompartment();

    /**
     *
     */
    CMathConstantCompartment(const CMathConstantCompartment & src);

  public:
    /**
     *
     */
    CMathConstantCompartment(const CCompartment & compartment);

    /**
     *
     */
    ~CMathConstantCompartment();

    /**
     *
     */
    virtual bool setValue(const C_FLOAT64 & value);

    /**
     *
     */
    virtual const C_FLOAT64 & getValue() const;

    /**
     *
     */
    const C_FLOAT64 & getTransientValue() const;

    /**
     *
     */
    const std::vector< CMathSymbol * > & getMetaboliteList() const;

    /**
     *
     */
    bool compile();
  };
#endif // COPASI_CMathConstant

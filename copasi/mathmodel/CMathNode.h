/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathNode.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:57 $
   End CVS Header */

/**
 * CMathNode class.
 * The class CMathNode is describes a node of the equation tree.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathNode
#define COPASI_CMathNode

#include <string>
#include "utilities/CCopasiNode.h"

class CMathSymbol;

/** @dia:pos -23.1584,-36.8607 */
class CMathNode: public CCopasiNode< std::string >
  {
    // Attributes
  protected:
    std::string mData;

    // Operations
  public:
    CMathNode(CMathNode * pParent = NULL);

    CMathNode(const CMathNode &src);

    CMathNode(const std::string & data, CMathNode * pParent = NULL);

    virtual ~CMathNode();

    virtual std::string getData() const;

    virtual bool setData(const std::string & data);
  };

class CMathNodeOperation: public CMathNode
  {
    // Attributes
  protected:
    static const std::string Operations;

    // Operations
  protected:
    CMathNodeOperation(CMathNode * pParent = NULL);

  public:
    CMathNodeOperation(const std::string & operation, CMathNode * pParent = NULL);

    CMathNodeOperation(const CMathNodeOperation &src);

    virtual ~CMathNodeOperation();

    virtual std::string getData() const;
  };

class CMathNodeDerivative: public CMathNodeOperation
  {
    // Operations
  public:
    CMathNodeDerivative(const std::string & operation = "d/d", CMathNode * pParent = NULL);

    CMathNodeDerivative(const CMathNodeDerivative &src);

    virtual ~CMathNodeDerivative();

    virtual std::string getData() const;
  };

class CMathNodeNumber: public CMathNode
  {
    // Operations

  public:
    CMathNodeNumber(const C_FLOAT64 & number = 0.0, CMathNode * pParent = NULL);

    CMathNodeNumber(const CMathNodeNumber &src);

    virtual ~CMathNodeNumber();

    virtual std::string getData() const;

    virtual bool setData(const C_FLOAT64 & number);
  };

class CMathNodeSymbol: public CMathNode
  {
    // Attributes
  protected:
    const CMathSymbol * mpSymbol;

    // Operations
  public:
    CMathNodeSymbol(const CMathSymbol * pSymbol = NULL, CMathNode * pParent = NULL);

    CMathNodeSymbol(const CMathNodeSymbol & src);

    virtual ~CMathNodeSymbol();

    virtual std::string getData() const;

    virtual bool setData(const CMathSymbol * pSymbol);
  };

class CMathNodeFunction: public CMathNodeSymbol
  {
    // Operations
  public:
    CMathNodeFunction(const CMathSymbol * pSymbol = NULL, CMathNode * pParent = NULL);

    CMathNodeFunction(const CMathNodeFunction & src);

    virtual ~CMathNodeFunction();

    virtual std::string getData() const;
  };

class CMathNodeList: public CMathNode
  {
    // Operations
  public:
    CMathNodeList(CMathNode * pParent = NULL);

    CMathNodeList(const CMathNodeList & src);

    virtual ~CMathNodeList();

    virtual std::string getData() const;
  };

#endif // COPASI_CMathNode

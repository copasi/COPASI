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
class CMathNode: public CCopasiNode< CMathSymbol * >
  {
    // Operations:
  public:
    CMathNode();

    CMathNode(const CMathNode &src);

    virtual ~CMathNode();

    virtual std::string getText() const;
  };

class CMathNodeOperation: public CMathNode
  {
    // Attributes
  protected:
    static const std::string Operations;

    std::string mOperation;

    // Operations
  protected:
    CMathNodeOperation();

  public:
    CMathNodeOperation(const std::string & operation);

    CMathNodeOperation(const CMathNodeOperation &src);

    virtual ~CMathNodeOperation();

    virtual std::string getText() const;
  };

class CMathNodeDerivative: public CMathNodeOperation
  {
    // Operations
  public:
    CMathNodeDerivative(const std::string & operation = "d/d");

    CMathNodeDerivative(const CMathNodeDerivative &src);

    virtual ~CMathNodeDerivative();

    virtual std::string getText() const;
  };

class CMathNodeNumber: public CMathNode
  {
    // Attributes
  private:
    C_FLOAT64 mNumber;

    // Operations

  public:
    CMathNodeNumber(const C_FLOAT64 & number = 0.0);

    CMathNodeNumber(const CMathNodeNumber &src);

    virtual ~CMathNodeNumber();

    virtual std::string getText() const;
  };

class CMathNodeSymbol: public CMathNode
  {
    // Attributes
  protected:
    const CMathSymbol * mpSymbol;

    // Operations
  public:
    CMathNodeSymbol(const CMathSymbol * pSymbol = NULL);

    CMathNodeSymbol(const CMathNodeSymbol & src);

    virtual ~CMathNodeSymbol();

    virtual std::string getText() const;
  };

class CMathNodeFunction: public CMathNodeSymbol
  {
    // Operations
  public:
    CMathNodeFunction(const CMathSymbol * pSymbol = NULL);

    CMathNodeFunction(const CMathNodeFunction & src);

    virtual ~CMathNodeFunction();

    virtual std::string getText() const;
  };

#endif // COPASI_CMathNode

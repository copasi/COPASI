// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CBrent
#define COPASI_CBrent

class CBrent
{
public:
  class Eval
  {
  public:
    virtual ~Eval();

    virtual double operator()(const double & /* value */);
  };

  template <class CType> class EvalTemplate : public Eval
  {
  private:
    double(CType::*mMethod)(const double & value);  // pointer to member function
    CType * mpType;                                         // pointer to object

  public:

    // constructor - takes pointer to an object and pointer to a member and stores
    // them in two private variables
    EvalTemplate(CType * pType,
                 double(CType::*method)(const double & value))
    {
      mpType = pType;
      mMethod = method;
    };

    virtual ~EvalTemplate() {};

    virtual double operator()(const double & value)
    {
      return (*mpType.*mMethod)(value);
    }
  };

  /**
   * Brent root finding method.
   * @param double left
   * @param double right
   * @param evalF function
   * @param double * pRoot
   * @param double * pRootValue
   * @param double tolerance
   * @return bool success
   */
  static bool findRoot(double left,
                       double right,
                       Eval * pFunction,
                       double * pRoot,
                       double * pRootValue,
                       double tolerance);
};

#endif // COPASI_CBrent

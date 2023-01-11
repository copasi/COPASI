// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include <limits>

class CRandom;

class FPraxis
{
public:
  virtual ~FPraxis() {};

  virtual const double & operator()(double * /* value */, int & /* n */)
  {
    static double NaN = std::numeric_limits< double >::quiet_NaN();
    return NaN;
  }
};

template < class CType >
class FPraxisTemplate : public FPraxis
{
private:
  const double & (CType::*mMethod)(double *, int &); // pointer to member function
  CType * mpType;                                    // pointer to object

public:
  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  FPraxisTemplate(CType * pType,
                  const double & (CType::*method)(double *, int &))
  {
    mpType = pType;
    mMethod = method;
  };

  virtual ~FPraxisTemplate() {};

  // override operator "()"
  virtual const double & operator()(double * value, int & n)
  {
    return (*mpType.*mMethod)(value, n);
  }; // execute member function
};

class CPraxis
{
public:
  CPraxis();

  ~CPraxis();

  double operator()(double t0,
                    double h0,
                    int n,
                    int prin,
                    double x[],
                    FPraxis * f);

private:
  double flin(int n,
              int j,
              double l,
              FPraxis * f,
              double x[],
              int & nf,
              double v[],
              double q0[],
              double q1[],
              double & qd0,
              double & qd1,
              double & qa,
              double & qb,
              double & qc);

  void minfit(int n,
              double tol,
              double a[],
              double q[]);

  void minny(int n,
             int j,
             int nits,
             double & d2,
             double & x1,
             double & f1,
             bool fk,
             FPraxis * f,
             double x[],
             double t,
             double h,
             double v[],
             double q0[],
             double q1[],
             int & nl,
             int & nf,
             double dmin,
             double ldt,
             double & fx,
             double & qa,
             double & qb,
             double & qc,
             double & qd0,
             double & qd1);

  void print2(int n,
              double x[],
              int prin,
              double fx,
              int nf,
              int nl);

  void quad(int n,
            FPraxis * f,
            double x[],
            double t,
            double h,
            double v[],
            double q0[],
            double q1[],
            int & nl,
            int & nf,
            double dmin,
            double ldt,
            double & fx,
            double & qf1,
            double & qa,
            double & qb,
            double & qc,
            double & qd0,
            double & qd1);

  double r8_hypot(double x, double y);

  double r8_uniform_01(int & seed);

  void r8mat_print(int m, int n, double a[], std::string title);

  void r8mat_print_some(int m, int n, double a[], int ilo, int jlo, int ihi, int jhi, std::string title);

  void r8mat_transpose_in_place(int n, double a[]);

  void r8vec_copy(int n, double a1[], double a2[]);

  double r8vec_max(int n, double r8vec[]);

  double r8vec_min(int n, double r8vec[]);

  double r8vec_norm(int n, double a[]);

  void r8vec_print(int n, double a[], std::string title);

  void svsort(int n, double d[], double v[]);

  void timestamp();

private:
  CRandom * mpRandom;
};

#endif // COPASI_CPraxis

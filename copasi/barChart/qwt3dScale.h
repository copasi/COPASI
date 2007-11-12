// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dScale.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/12 17:01:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SCALE_H
#define SCALE_H

#include "qwt3d_scale.h"

#include <qstring.h>
#include "qwt3d_types.h"
#include "qwt3d_autoptr.h"

//! Automatic beautifying of linear scales
class LinearAutoScaler2 : public Qwt3D::LinearAutoScaler
  {
  public:
    int execute2(double& a, double& b, double start, double stop, int ivals);
  };

//! The standard (1:1) mapping class for axis numbering
class ValueScale : public Qwt3D::Scale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Qwt3D::Scale>;
  protected:
    int autoscale(double& a, double& b, double start, double stop, int ivals);
    //! Returns a new heap based object utilized from qwt3d_ptr
    Qwt3D::Scale* clone() const {return new ValueScale(*this);}
    void calculate();
    LinearAutoScaler2 autoscaler_p2;
  public:
    QString ticLabel(unsigned int idx) const;
  };

class ColumnScale : public ValueScale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Scale>;
  protected:
    Qwt3D::Scale* clone() const {return new ColumnScale(*this);}
  public:
    ColumnScale(const std::vector<std::string> * vos, int showColumn = -1);
    virtual QString ticLabel(unsigned int idx) const;
    const std::vector<std::string> *mpColumnsDes;
    int showColumn;
  };

class RowScale : public ValueScale
  {
    friend class Qwt3D::Axis;
    friend class Qwt3D::qwt3d_ptr<Scale>;
  protected:
    Qwt3D::Scale* clone() const {return new RowScale(*this);}
  public:
    RowScale(const std::vector<std::string> * vos, int showRow = -1);
    QString ticLabel(unsigned int idx) const;
    const std::vector<std::string> *mpRowsDes;
    int showRow;
  };
#endif // SCALE_H

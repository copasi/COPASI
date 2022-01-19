// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
//  dc_decsol.h
//  Radau5
//
//  Created by Abhishekh Gupta on 1/9/19.
//  Copyright © 2019 Abhishekh Gupta. All rights reserved.
//

#ifndef dc_decsol_h
#define dc_decsol_h

#include "CRadau5.h"
#include "decsol.h"

int decomr_(integer *n, doublereal *fjac, integer *ldjac,
            doublereal *fmas, integer *ldmas, integer *mlmas, integer *mumas,
            integer *m1, integer *m2, integer *nm1, doublereal *fac1, doublereal *
            e1, integer *lde1, integer *ip1, integer *ier, integer *ijob, logical
            *calhes, integer *iphes);

int decomc_(integer *n, doublereal *fjac, integer *ldjac,
            doublereal *fmas, integer *ldmas, integer *mlmas, integer *mumas,
            integer *m1, integer *m2, integer *nm1, doublereal *alphn, doublereal
            *betan, doublereal *e2r, doublereal *e2i, integer *lde1, integer *ip2,
            integer *ier, integer *ijob);

int slvrar_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
            nm1, doublereal *fac1, doublereal *e1, integer *lde1, doublereal *z1,
            doublereal *f1, integer *ip1, integer *iphes, integer *ier, integer *
            ijob);

int slvrai_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
            nm1, doublereal *alphn, doublereal *betan, doublereal *e2r,
            doublereal *e2i, integer *lde1, doublereal *z2, doublereal *z3,
            doublereal *f2, doublereal *f3, doublereal *cont, integer *ip2,
            integer *iphes, integer *ier, integer *ijob);

int slvrad_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
            nm1, doublereal *fac1, doublereal *alphn, doublereal *betan,
            doublereal *e1, doublereal *e2r, doublereal *e2i, integer *lde1,
            doublereal *z1, doublereal *z2, doublereal *z3, doublereal *f1,
            doublereal *f2, doublereal *f3, doublereal *cont, integer *ip1,
            integer *ip2, integer *iphes, integer *ier, integer *ijob);

int estrad_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, doublereal *h__, doublereal *dd1,
            doublereal *dd2, doublereal *dd3, CRadau5::evalF fcn, integer *nfcn, doublereal
            *y0, doublereal *y, integer *ijob, doublereal *x, integer *m1,
            integer *m2, integer *nm1, doublereal *e1, integer *lde1, doublereal *
            z1, doublereal *z2, doublereal *z3, doublereal *cont, doublereal *f1,
            doublereal *f2, integer *ip1, integer *iphes, doublereal *scal,
            doublereal *err, logical *first, logical *reject, doublereal *fac1,
            doublereal *rpar, integer *ipar);

int estrav_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, doublereal *h__, doublereal *dd, S_fp
            fcn, integer *nfcn, doublereal *y0, doublereal *y, integer *ijob,
            doublereal *x, integer *m1, integer *m2, integer *nm1, integer *ns,
            integer *nns, doublereal *e1, integer *lde1, doublereal *zz,
            doublereal *cont, doublereal *ff, integer *ip1, integer *iphes,
            doublereal *scal, doublereal *err, logical *first, logical *reject,
            doublereal *fac1, doublereal *rpar, integer *ipar);

int slvrod_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
            nm1, doublereal *fac1, doublereal *e, integer *lde, integer *ip,
            doublereal *dy, doublereal *ak, doublereal *fx, doublereal *ynew,
            doublereal *hd, integer *ijob, logical *stage1);

int slvseu_(integer *n, doublereal *fjac, integer *ldjac,
            integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
            integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
            nm1, doublereal *fac1, doublereal *e, integer *lde, integer *ip,
            integer *iphes, doublereal *del, integer *ijob);

#endif /* dc_decsol_h */

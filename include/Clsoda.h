#ifndef COPASI_Clsoda
#define COPASI_Clsoda

#include "copasi.h"
#include "CModel.h"

class Clsoda 
{
// Attributes
public:
    // This are standard lsoda parameters
    C_FLOAT64 hu;
    C_FLOAT64 h;
    C_FLOAT64 tn;
    C_FLOAT64 tolsf;
    C_FLOAT64 tsw;
    C_INT32 nst;
    C_INT32 nfe;
    C_INT32 nje;
    C_INT32 nqu;
    C_INT32 nq;
    C_INT32 imxer;
    C_INT32 mused;
    C_INT32 meth;

private:
    CModel * mModel;

    // This are standard lsoda parameters
    C_INT32 prfl;
    C_INT32 _ml;
    C_INT32 mu;
    C_FLOAT64 sqrteta;
    C_FLOAT64 * yp1;
    C_FLOAT64 * yp2;
    C_FLOAT64 ccmax;
    C_FLOAT64 el0;
    C_FLOAT64 hmin;
    C_FLOAT64 hmxi;
    C_FLOAT64 rc;
    C_INT32 illin;
    C_INT32 init;
    C_INT32 mxstep;
    C_INT32 mxhnil;
    C_INT32 nhnil;
    C_INT32 ntrep;
    C_INT32 nslast;
    C_INT32 nyh;
    C_INT32 ierpj;
    C_INT32 iersl;
    C_INT32 jcur;
    C_INT32 jstart;
    C_INT32 kflag;
    C_INT32 l;
    C_INT32 miter;
    C_INT32 maxord;
    C_INT32 maxcor;
    C_INT32 msbp;
    C_INT32 mxncf;
    C_INT32 n;
    C_FLOAT64 pdnorm;
    C_INT32 ixpr;
    C_INT32 jtyp;
    C_INT32 mxordn;
    C_INT32 mxords;
    C_FLOAT64 conit;
    C_FLOAT64 crate;
    C_FLOAT64 el[14];
    C_FLOAT64 elco[13][14];
    C_FLOAT64 hold;
    C_FLOAT64 rmax;
    C_FLOAT64 tesco[13][4];
    C_INT32 ialth;
    C_INT32 ipup;
    C_INT32 lmax;
    C_INT32 meo;
    C_INT32 nslp;
    C_FLOAT64  pdest;
    C_FLOAT64  pdlast;
    C_FLOAT64  ratio;
    C_FLOAT64  cm1[13];
    C_FLOAT64  cm2[6];
    C_INT32 icount;
    C_INT32 irflag;
    C_INT32 mesflg;
    C_FLOAT64 ** yh;
    C_FLOAT64 ** wm;
    C_FLOAT64 * ewt;
    C_FLOAT64 * savf;
    C_FLOAT64 * acor;
    C_INT32 * ipvt;

// Operations
public:
    Clsoda();

    ~Clsoda();

    // This are standard lsoda fuctions
    void xsetf(C_INT32 mflag);

    void lsoda_freevectors();

    void lsoda(CModel *model,
               C_INT32 neq,
               C_FLOAT64 *y,
               C_FLOAT64 *t,
               C_FLOAT64 tout,
               C_INT32 itol,
               C_FLOAT64 *rtol,
               C_FLOAT64 *atol,
               C_INT32 itask,
               C_INT32 *istate,
               C_INT32 iopt,
               C_INT32 jt,
               C_INT32 iwork1,
               C_INT32 iwork2,
               C_INT32 iwork5,
               C_INT32 iwork6,
               C_INT32 iwork7,
               C_INT32 iwork8,
               C_INT32 iwork9,
               C_FLOAT64 rwork1,
               C_FLOAT64 rwork5,
               C_FLOAT64 rwork6,
               C_FLOAT64 rwork7
        );

    void intdy(C_FLOAT64 t,
               C_INT32 k,
               C_FLOAT64 * dky,
               C_INT32 * iflag);

private:
    /**
     *  This in connection with mModel replaces the callback function!!!
     */
    void Eval(C_INT32 n, 
              C_FLOAT64 t, 
              C_FLOAT64 * y, 
              C_FLOAT64 * ydot);


    // This are standard lsoda parameters
    void terminate(C_INT32 * istate);

    void terminate2(C_FLOAT64 * y,
                    C_FLOAT64 * t);

    void freevectors();

    void successreturn(C_FLOAT64 *y,
                       C_FLOAT64 *t,
                       C_INT32 itask,
                       C_INT32 ihit, 
                       C_FLOAT64 tcrit, 
                       C_INT32 *istate);

    void stoda(C_INT32 neq, 
               C_FLOAT64 *y);

    void endstoda();

    void prja(C_INT32 neq,
              C_FLOAT64 *y);

    void correction(C_INT32 neq,
                    C_FLOAT64 *y,
                    C_INT32 *corflag,
                    C_FLOAT64 pnorm,
                    C_FLOAT64 *del,
                    C_FLOAT64 *delp,
                    C_FLOAT64 *told,
                    C_INT32 *ncf,
                    C_FLOAT64 *rh,
                    C_INT32 *m);

    void resetcoeff();

    void methodswitch(C_FLOAT64 dsm,
                      C_FLOAT64 pnorm, 
                      C_FLOAT64 *pdh,
                      C_FLOAT64 *rh);

    void ewset(C_INT32 itol,
               C_FLOAT64 * rtol, 
               C_FLOAT64 * atol,
               C_FLOAT64  * ycur);

    C_FLOAT64 vmnorm(C_INT32 n,
                     C_FLOAT64 * v,
                     C_FLOAT64 * w);

    void cfode(C_INT32 meth);

    void scaleh(C_FLOAT64 * rh,
                C_FLOAT64 * pdh);

    void orderswitch(C_FLOAT64 * rhup,
                     C_FLOAT64 dsm, 
                     C_FLOAT64 * pdh,
                     C_FLOAT64 * rh,
                     C_INT32 * orderflag);

    C_FLOAT64 fnorm(C_INT32 n,
                    C_FLOAT64 ** a,
                    C_FLOAT64 * w);

    void corfailure(C_FLOAT64 * told,
                    C_FLOAT64 * rh,
                    C_INT32 * ncf,
                    C_INT32 * corflag);

    void solsy(C_FLOAT64 * y);

    void lsoda_dgefa(C_FLOAT64 ** a, 
                     C_INT32 n, 
                     C_INT32 * ipvt, 
                     C_INT32 * info);

    C_INT32 lsoda_idamax(C_INT32 n,
                         C_FLOAT64 * dx,
                         C_INT32 incx);
    
    void lsoda_dgesl(C_FLOAT64 ** a,
                     C_INT32 n,
                     C_INT32 * ipvt, 
                     C_FLOAT64 * b, 
                     C_INT32 job);

    void lsoda_daxpy(C_INT32 n,
                     C_FLOAT64 da, 
                     C_FLOAT64 * dx,
                     C_INT32 incx, 
                     C_FLOAT64 * dy,
                     C_INT32 incy);

    void lsoda_dscal(C_INT32 n,
                     C_FLOAT64 da,
                     C_FLOAT64 * dx,
                     C_INT32 incx);

    C_FLOAT64 lsoda_ddot(C_INT32 n, 
                         C_FLOAT64 * dx,
                         C_INT32 incx, 
                         C_FLOAT64 * dy,
                         C_INT32 incy);

};

#endif // COPASI_Clsoda

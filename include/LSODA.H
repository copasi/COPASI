/**************************************************/
/* lsoda.h - header file for blocks calling lsoda */
/* lybrary with ANSI C style function prototypes  */
/**************************************************/

void lsoda (void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *),
            C_INT32 neq,
            C_FLOAT64 *y,
            C_FLOAT64 *t,
            C_FLOAT64 tout,
            C_INT32 itol,
            C_FLOAT64 *rtol,
            C_FLOAT64 *atol,
            C_INT32 itask,
            *istate,
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

void xsetf (C_INT32 mflag);
void freevectors (void);

/***************************/
/* useful global variables */
/***************************/

extern C_FLOAT64 hu;    /* the step size in t last used (successfully)       */
extern C_FLOAT64 h;     /* ???? */
extern C_FLOAT64 tn;    /* ???? */
extern C_FLOAT64 tolsf; /* tolerance scale factor, greater than 1.0          */
extern C_FLOAT64 tsw;   /* the value of t at the time of the last method sw. */
extern C_INT32 nst;     /* the number of steps taken for the problem so far  */
extern C_INT32 nfe;     /* the number of f evaluations for the probl. so far */
extern C_INT32 nje;     /* the number of jacobian evaluations (and of matrix */
                        /* LU decompositions) for the problem so far         */
extern C_INT32 nqu;     /* the method order last used                        */
extern C_INT32 nq;      /* ???? */
extern C_INT32 imxer;   /* the index of the component of largest magnitude   */
                        /* in the weighted local error vector e(i)/ewt(i),   */
                        /* on an error return with istate = -4 or -5         */
extern C_INT32 mused;   /* the method indicator for the last successful step */
                        /* 1 means Adams (nonstiff), 2 means bdf (stiff)     */
extern C_INT32 meth;    /* ???? */

/**************************************************/
/* lsoda.h - header file for blocks calling lsoda */
/* lybrary with ANSI C style function prototypes  */
/**************************************************/

void lsoda (void (*f)(int, double, double *, double *),
            int neq,
            double *y,
            double *t,
            double tout,
            int itol,
            double *rtol,
            double *atol,
            int itask,
            *istate,
            int iopt,
            int jt,
            int iwork1,
            int iwork2,
            int iwork5,
            int iwork6,
            int iwork7,
            int iwork8,
            int iwork9,
            double rwork1,
            double rwork5,
            double rwork6,
            double rwork7
           );

void xsetf (int mflag);
void freevectors (void);

/***************************/
/* useful global variables */
/***************************/

extern double hu;      /* the step size in t last used (successfully)       */
extern double h;       /* ???? */
extern double tn;      /* ???? */
extern double tolsf;   /* tolerance scale factor, greater than 1.0          */
extern double tsw;     /* the value of t at the time of the last method sw. */
extern int nst;        /* the number of steps taken for the problem so far  */
extern int nfe;        /* the number of f evaluations for the probl. so far */
extern int nje;        /* the number of jacobian evaluations (and of matrix */
                       /* LU decompositions) for the problem so far         */
extern int nqu;        /* the method order last used                        */
extern int nq;         /* ???? */
extern int imxer;      /* the index of the component of largest magnitude   */
                       /* in the weighted local error vector e(i)/ewt(i),   */
                       /* on an error return with istate = -4 or -5         */
extern int mused;      /* the method indicator for the last successful step */
                       /* 1 means Adams (nonstiff), 2 means bdf (stiff)     */
extern int meth;       /* ???? */

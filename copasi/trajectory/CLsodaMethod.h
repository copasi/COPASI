#ifndef COPASI_CLsodaMethod
#define COPASI_CLsodaMethod

class CLsodaMethod : private CTrajectoryMethod
  {
    friend CTrajectoryMethod *
    CTrajectoryMethod::createTrajectoryMethod(CTrajectoryMethod::Type type);

    // Attributes
  private:

    // public:
  private:

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
    C_FLOAT64 pdest;
    C_FLOAT64 pdlast;
    C_FLOAT64 ratio;
    C_FLOAT64 cm1[13];
    C_FLOAT64 cm2[6];
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
  private:
    /**
     *  Default constructor.
     */
    CLsodaMethod();

  public:
    /**
     *  Copy constructor.
     *  @param "const CLsodaMethod &" src
     */
    CLsodaMethod(const CLsodaMethod & src);

    /**
     *  Destructor.
     */
    ~CLsodaMethod();

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     *  @return "const double" actualDeltaT
     */
    const double step(const double & deltaT);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the initialState given.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "double &" deltaT
     *  @param "const CState *" initialState
     *  @return "const double" actualDeltaT
     */
    const double step(const double & deltaT, const CState * initialState);
  };
#endif // COPASI_CLsodaMethod

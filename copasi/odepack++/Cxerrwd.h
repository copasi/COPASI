/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/Cxerrwd.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/17 15:18:55 $
   End CVS Header */

#ifndef ODEPACK_xerrwd
 #define ODEPACK_xerrwd

#include <iostream>
 #include <string>

class Cxerrwd
  {
  public:
    Cxerrwd(const bool & print = true,
            std::ostream & os = std::cout);

    ~Cxerrwd();

    void operator() (const std::string & msg, C_INT *nmes, C_INT *nerr, C_INT
                     *level, C_INT *ni, C_INT *i1, C_INT *i2, C_INT *nr,
                     double *r1, double *r2, C_INT msg_len);

    void setOstream(std::ostream & os);
    void enablePrint(const bool & print = true);

  private:
    bool mPrint;
    std::ostream * mpOstream;
  };

#endif // ODEPACK_xerrwd

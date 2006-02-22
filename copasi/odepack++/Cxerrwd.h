/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/Cxerrwd.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/22 15:08:44 $
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

    void operator() (const std::string & msg, const C_INT *nmes, const C_INT *nerr, const C_INT
                     *level, const C_INT *ni, const C_INT *i1, const C_INT *i2, const C_INT *nr,
                     const double *r1, const double *r2, C_INT msg_len);

    void setOstream(std::ostream & os);
    void enablePrint(const bool & print = true);

  private:
    bool mPrint;
    std::ostream * mpOstream;
  };

#endif // ODEPACK_xerrwd

/**
 * CFunctionParameter
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionParameter
#define COPASI_CFunctionParameter

#include <string>
#include <iostream>

#include "utilities/utilities.h"

using std::string;
using std::ostream;
using std::endl;

class CFunctionParameter
  {
  public:
    static const string DataTypeName[];

    //Attributes

  public:
    /**
     *  Valid data type for a function parameter
     */
    enum DataType {INT16 = 0, INT32, UINT16, UINT32, FLOAT32, FLOAT64,
                   VINT16, VINT32, VUINT16, VUINT32, VFLOAT32, VFLOAT64};

  private:
    /**
     *  The name of the parameter. 
     */
    string mName;

    /**
     *  The data type of the parameter this may be one of INT16, INT32, 
     *  UINT16, UINT32, FLOAT32, FLOAT64, VINT16, VINT32, VUINT16, VUINT32,
     *  VFLOAT32, VFLOAT64
     */
    CFunctionParameter::DataType mType;

    /**
     *  The usage or meaning of the parameter. This has no functional 
     *  implication for CFunction but it might be used in derived classes.
     *  Possible usage is SUBSTRATE, PRODUCT, MODIFIER, or PARAMETER
     */
    string mUsage;

  public:
    /**
     *  Default constructor 
     */
    CFunctionParameter();

    /**
     *  Copy constructor
     *  @param "const CFunctionParameter" & src
     */
    CFunctionParameter(const CFunctionParameter & src);

    /**
     *  Specified constuctor, sets all member values at once
     *  @param "const string &" name
     *  @param "const CFunctionParameter::DataType &" type
     *  @param "const string &" usage
     */
    CFunctionParameter(const string & name, const DataType & type, const string & usage);

    /**
     *  Destructor
     */
    virtual ~CFunctionParameter();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object. 
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    virtual void load(CReadConfig & configbuffer,
                      CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    virtual void save(CWriteConfig & configbuffer);

    /**
     *  Retrieves the name of the parameter
     *  @return  "const string" & name
     */
    const string & getName() const;

    /**
     *  Sets the name of the parameter
     *  @param "const string" & name
     */
    void setName(const string & name);

    /**
     *  Retrieves the data type of the parameter
     *  @return "const CFunctionParameter::DataType" & type
     */
    const CFunctionParameter::DataType & getType() const;

    /**
     *  Sets the data type of the parameter
     *  @param "const CFunctionParameter::DataType" & type
     */
    void setType(const CFunctionParameter::DataType & type);

    /**
     *  Retrieves the usage of the parameter
     *  @return "const string" & usage
     */
    const string & getUsage() const;

    /**
     *  Sets the usage of the parameter
     *  @param "const string" & usage
     */
    void setUsage(const string & usage);

    /**
     * insert operator
     */
    friend ostream & operator<<(ostream &os, const CFunctionParameter & d)
    {
      os << "CFunctionParameter: "
      << d.mName
      << " mType " << d.mType
      << " mUsage " << d.mUsage << endl;

      return os;
    }
  };

#endif // COPASI_CFunctionParameter

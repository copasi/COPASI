/**
 * CCopasiXMLInterface class.
 * The class CCopasiXMLInterface is the interface to various XML document 
 * containing Copasi relevant informtion.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiXMLInterface
#define COPASI_CCopasiXMLInterface

#include <vector>
#include <string>

class CModel;
template <class CType> class CCopasiVectorN;
class CFunction;
class CCopasiTask;
class CCopasiReport;

/**
 * A list of XML attributes used by saveElement and startSaveElement.
 */
class CXMLAttributeList
  {
    // Attributes
  private:
    /**
     * The attribute list
     */
    std::vector< std::string > mAttributeList;

    // Operations
  public:
    /**
     * Constructor.
     */
    CXMLAttributeList();

    /**
     * Copy constructor.
     * @param const CXMLAttributeList & src
     */
    CXMLAttributeList(const CXMLAttributeList & src);

    /**
     * Destructor.
     */
    ~CXMLAttributeList();

    /**
     * Erase the content of the attribute list.
     * @return bool success
     */
    bool erase();

    /**
     * Add an attribute to the end of the list.
     * Note: the value will be XML encoded
     * @param const std::string & name
     * @param const std::string & value
     * @return bool success
     */
    bool addAttribute(const std::string & name,
                      const std::string & value);

    /**
     * Retreive the size of the list.
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 size();

    /**
     * Set the name of the indexed attribute
     * @param const unsigned C_INT32 & index
     * @param const std::string & name
     * @return bool success
     */
    bool setName(const unsigned C_INT32 & index,
                 const std::string & name);

    /**
     * Retreive the name of the indexed attribute.
     * @param const unsigned C_INT32 & index
     * @return const std::string & name
     */
    const std::string & getName(const unsigned C_INT32 & index) const;

    /**
     * Set the value of the indexed attribute
     * Note: the value will be XML encoded
     * @param const unsigned C_INT32 & index
     * @param const std::string & value
     * @return bool success
     */
    bool setValue(const unsigned C_INT32 & index,
                  const std::string & value);

    /**
     * Retreive the value of the indexed attribute.
     * @param const unsigned C_INT32 & index
     * @return const std::string & value
     */
    const std::string & getValue(const unsigned C_INT32 & index) const;

    /**
     * Retreive the indexed attribute.
     * @param const unsigned C_INT32 & index
     * @return std::string attribute
     */
    std::string getAttribute(const unsigned C_INT32 & index) const;
  };

/**
 * The class CCopasiXMLInterface specifies an interface to various XML formats
 * related to COPASI relevant information.
 * Derived classes have to implement the following two methods:
 * @see bool load(std::istream & is)
 * @see bool save(std::ostream & os)
 *
 * Note: the responsibilty to free allocated memory during load is handed to the
 *       user.
 */
class CCopasiXMLInterface
  {
    // Attributes
  protected:
    /**
     * Pointer to a model which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CModel * mpModel;

    /**
     * Pointer to a vector of functions which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CFunction > * mpFunctionList;

    /**
     * Pointer to a vector of tasks which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CCopasiTask > * mpTaskList;

    /**
     * Pointer to a vector of reports which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CCopasiReport > * mpReportList;

    /**
     * A pointer to the input stream
     */
    std::istream *mpIstream;

    /**
     * A pointer to the output stream
     */
    std::ostream *mpOstream;

    /**
     * Indent
     */
    std::string mIndent;

    // Operations
  public:
    /**
     * Constructor.
     */
    CCopasiXMLInterface();

    /**
     * Destructor.
     */
    virtual ~CCopasiXMLInterface();

    /**
     * Load information from a given istream.
     * @param std::istream & is
     * @return bool success
     */
    virtual bool load(std::istream & is) = NULL;

    /**
     * Load information from a file.
     * @param const std::string & fileName
     * @return bool success
     */
    bool load(const std::string & fileName);

    /**
     * Save information to a given ostream.
     * @param std::ostream & os
     * @return bool success
     */
    virtual bool save(std::ostream & os) = NULL;

    /**
     * Save information to a file.
     * @param const std::string & fileName
     * @return bool success
     */
    bool save(const std::string & fileName);

    /**
     * Set the model.
     * @param const CModel & model
     * @return bool success
     */
    bool setModel(const CModel & model);

    /**
     * Retreive the model.
     * @return CModel * pModel
     */
    CModel * getModel() const;

    /**
     * Retreive whether the XML contains a model.
     * @return bool have Model
     */
    bool haveModel() const;

    /**
     * Free the model.
     * @return bool success
     */
    bool freeModel();

    /**
     * Set the function list.
     * @param const CCopasiVectorN< CFunction > & functionList
     * @return bool success
     */
    bool setFunctionList(const CCopasiVectorN< CFunction > & functionList);

    /**
     * Retreive the function list.
     * @return CCopasiVectorN< CFunction > * functionList
     */
    CCopasiVectorN< CFunction > * getFunctionList() const;

    /**
     * Retreive whether the XML contains a function list.
     * @return bool haveFunctionList
     */
    bool haveFunctionList() const;

    /**
     * Free the function list.
     * @return bool success
     */
    bool freeFunctionList();

    /**
     * Set the task list.
     * @param const CCopasiVectorN< CCopasiTask > & taskList
     * @return bool success
     */
    bool setTaskList(const CCopasiVectorN< CCopasiTask > & taskList);

    /**
     * Retreive the task list.
     * @return CCopasiVectorN< CCopasiTask > * taskList
     */
    CCopasiVectorN< CCopasiTask > * getTaskList() const;

    /**
     * Retreive whether the XML contains a task list.
     * @return bool haveTaskList
     */
    bool haveTaskList() const;

    /**
     * Free the task list.
     * @return bool success
     */
    bool freeTaskList();

    /**
     * Set the report list.
     * @param const CCopasiVectorN< CCopasiReport > & reportList
     * @return bool success
     */
    bool setReportList(const CCopasiVectorN< CCopasiReport > & reportList);

    /**
     * Retreive the report list.
     * @return CCopasiVectorN< CCopasiReport > * reportList
     */
    CCopasiVectorN< CCopasiReport > * getReportList() const;

    /**
     * Retreive whether the XML contains a report list.
     * @return bool haveReportList
     */
    bool haveReportList() const;

    /**
     * Free the report list.
     * @return bool success
     */
    bool freeReportList();

    /**
     * Encode a given string to a valid XML string
     * @param const std::string & str
     * @return std::string encoded
     */
    static std::string encode(const std::string & str);

    /**
     * Encode a given string to a utf-8 string
     * @param const std::string & str
     * @return std::string encoded
     */
    static std::string utf8(const std::string & str);

  protected:
    /**
     * Save an XML element to the ostream
     * @param const std::string & name
     * @param CXMLAttributeList & attributeList
     * @return bool success
     */
    bool saveElement(const std::string & name,
                     CXMLAttributeList & attributeList);

    /**
     *
     * @param const std::string & name
     * @param CXMLAttributeList & attributeList
     * @return bool success
     */
    bool startSaveElement(const std::string & name,
                          CXMLAttributeList & attributeList);

    /**
     *
     * @param const std::string & name
     * @return bool success
     */
    bool endSaveElement(const std::string & name);
  };

#endif // COPASI_CCopasiXMLInterface

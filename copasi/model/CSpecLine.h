#ifndef Copasi_SpecLine
#define Copasi_SpecLine

#include <string>
#include <vector>
#include "copasi.h"

#include "model/CMetab.h"

class CModel;
class CDeTerm;

/**
 * CSpecLine
 * 
 * This class represents a line of input from the spec file. It contains
 * a type identifier and a string, representing the actual input.
 */ 
/** @dia:pos 55.814,11.5496 */
class CSpecLine
  {
  public:
    /**
     * This enumerated type specifies the type of line contained in the spec.
     */
    enum SpecLineType
    {
      CMNT,       // Comments
      DE,        // Differential equations
      EQN,       // Moiety specification equations
      INIT,       // Initializations
      CNST,       // Constant assignments
      VOL,       // Volume assignment
      CPT,       // Compartment volume assignments
      RATE,       // Rate constant assignments
      FUN      // Kinetic function specifications
    };

    /**
     * Default constructor
     */
    CSpecLine();

    /**
     * The named constructor
     */
    CSpecLine(C_INT32 type, std::string contents);

    /**
     * Destructor
     */
    ~CSpecLine();

    /**
     * Retrieve the type.
     * @return The type
     */
    C_INT32 getType() {return mType;}

    static std::string convertedType(int type);

    /**
     * Retrieve the content string
     */
    std::string &getString() {return mContents;}

    /**
     * Extract and return the left hand side of the contents string. 
     * If the left hand side is preceded by a compartment specifier, 
     * this is stripped from the returned string.
     * @return The (stripped) left hand side string
    */
    std::string extractLeft();

    /**
     * Extract and return the right hand side of the contents string. 
     * @return The right hand side string
    */
    std::string extractRight();

    /**
     * Extract and return the compartment name/number on the right hand side
     * @return The compartment specifier
     */
    std::string extractCpt();

  private:
    /**
     * The type
     */
    C_INT32 mType;
    /**
     * The contents
     */
    std::string mContents;

    // private operations
    std::string stripBlanks(std::string instr);
  };

/**
 * The CBaseEqn class holds basic information about an equation, 
 * and is used as an intermediate in processing the spec input.
 * It stores the LHS metabolite, the compartment this is in, and the RHS string.
 */

/** @dia:pos 44.726,-0.362133 */
class CBaseEqn
  {
  public:
    /**
     * Named constructor
     */
    CBaseEqn(std::string comp, std::string metab, std::string contents)
        : mCompartment(comp), mMetabolite(metab), mContents(contents) {}

    /**
     * Destructor
     */
    ~CBaseEqn() {}

    /**
     * Retrieve the string containing the name of the compartment.
     * @return The compartment name.
     */
    std::string getCompartment() const {return mCompartment;}

    /**
     * Retrieve the string containing the name of the metabolite
     * @return The metabolite name
     */
    std::string getMetabolite() const {return mMetabolite;}

    /**
     * Retrieve the string containing the contents of the right hand side.
     * @return The RHS contents.
     */
    std::string getContents() const{return mContents;}

    /**
     * Overloads the == operator. Equality is true if the strings
     * mCompartment and mMetabolite match.
     */
    bool operator==(const CBaseEqn &rhs) const;

  private:
    std::string mCompartment;
    std::string mMetabolite;
    std::string mContents;
  };

/**
 * The CNameVal class holds a name-value pair.
 * CNameVal is used as an intermediate in processing the spec input.
 */

/** @dia:pos 57.926,25.0669 */
class CNameVal
  {
  public:
    /**
     * Named constructor
     */
    CNameVal(std::string name, C_FLOAT64 val): mName(name), mVal(val) {};

    /*
     * Destructor
     */
    ~CNameVal() {};

    /**
     * Return the name
     * @return The name
     */
    std::string getName() const {return mName;}

    /**
     * Return the value
     * @return The value field
     */
    C_FLOAT64 getVal() const {return mVal;}

  private:
    /**
     * The name
     */
    std::string mName;
    /**
     * The value
     */
    C_FLOAT64 mVal;
  };

/**
 * Class CTempReactionSet contains a vector of CTempReaction, as well as
 * methods to add or find elements to the vector. CTempReaction holds
 * temporary information about a reaction - the rate constant, a
 * string describing the rate and the set of metabolites, for now
 * described by CTempMetab. It is used while the various parameters of
 * a reaction are still being determined. When complete, it may easily
 * be used to construct a CReaction.
 */

/** @dia:pos 23.1588,35.123 */
class CTempMetab
  {
  public:
    enum Type{UNDEF = 0, SUBSTRATE, PRODUCT, DUAL};
    CTempMetab(const CMetab *metab) : mMetab(metab), mMultiplicity(0), mNumChange(0) {}

    CTempMetab(const CTempMetab &rhs);
    const CMetab *getMetab() const {return mMetab;}
    C_INT32 getMultiplicity() const {return mMultiplicity;}
    void setMultiplicity(const C_INT32 mult) {mMultiplicity = mult;}
    C_INT32 getNumChange() const {return mNumChange;}
    void setNumChange(const C_INT32 num) {mNumChange = num;}

  private:
    /** @dia:route 2,2; h,117.263,51.5961,123.99,35.123,42.6964 */
    const CMetab *mMetab;
    C_INT32 mMultiplicity;
    C_INT32 mNumChange;

    friend std::ostream & operator<<(std::ostream &os, const CTempMetab & m)
    {
      os << "Name = '" << m.mMetab->getName();
      os << "', Multiplicty = '" << m.mMultiplicity;
      os << "', Change = '" << m.mNumChange << "'";
      return os;
    }
  };

/** @dia:pos 51.4155,37.5278 */
class CTempReaction
  {
  public:
    CTempReaction(std::string name) : mName(name) {}
    CTempReaction(const CDeTerm *deTerm);
    std::string getName() const {return mName;}
    void setDescription(std::string desc) {mRateDescription = desc;}
    std::string getDescription() const {return mRateDescription;}

    CTempMetab *addMetabolite(const CMetab *metab);
    //std::vector<CTempMetab> &getMetabs() {return mMetabs;}

    void compile(CModel *model,
                 const std::vector< CNameVal> & rates,
                 const std::vector< CNameVal> & constants);

    void create_substrates_and_products_lists();
    std::string getChemEquation() const;
    void setIdentifiers(const CDeTerm *deTerm);

  private:
    bool isIn(std::vector< CTempMetab> & metabs, const std::string & target);
    C_FLOAT64 getParameterValue(const std::string & name,
                                const std::vector< CNameVal> & rates,
                                const std::vector< CNameVal> & constants);

  private:
    std::string mName;
    std::string mRateDescription;
    /** @dia:route 17,3; h,42.6964,40.423,48.4754,38.2278,51.4155 */
    std::vector< CTempMetab> mMetabs;
    /** @dia:route 13,3; h,42.6964,38.823,48.4754,38.2278,51.4155 */
    std::vector< CTempMetab> mSubstrates;
    /** @dia:route 9,3; h,42.6964,37.023,48.4754,38.2278,51.4155 */
    std::vector< CTempMetab> mProducts;
    std::vector< std::string> mIdentifiers;

    friend std::ostream & operator<<(std::ostream & os, const CTempReaction & r)
    {
      os << "TempReaction = '" << r.mName << "'" << std::endl;
      os << "  Rate       = '" << r.mRateDescription << "'" << std::endl;
      unsigned int i;
      os << "  Metabolites:" << std::endl;

      for (i = 0; i < r.mMetabs.size(); i++)
        os << "    " << i << ": " << r.mMetabs[i] << std::endl;

      os << "  Substrates: " << std::endl;

      for (i = 0; i < r.mSubstrates.size(); i++)
        os << "    " << i << ": " << r.mSubstrates[i] << std::endl;

      os << "  Products:   " << std::endl;

      for (i = 0; i < r.mProducts.size(); i++)
        os << "    " << i << ": " << r.mProducts[i] << std::endl;

      return os;
    }
  };

/** @dia:pos 96.4407,39.6026 */
class CTempReactionSet
  {
  public:
    CTempReactionSet();
    void addReaction(CTempReaction *temp_react);
    CTempReaction *findReaction(std::string name);
    std::vector< CTempReaction> getReactions() {return mReactions;}
    C_INT32 size() {return mReactions.size();}
    CTempReaction &operator[](C_INT32 i) {return mReactions[i];}

  private:
    /** @dia:route 2,0; h,88.8259,37.5278,93.7594,39.6026,96.4407 */
    std::vector< CTempReaction> mReactions;
  };

#endif // Copasi_SpecLine

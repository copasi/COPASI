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

class CSpecLine
  {
  public:
    /**
     * This enumerated type specifies the type of line contained in the spec.
     */
    enum SpecLineType
    {
      CMNT,  // Comments
      DE,   // Differential equations
      EQN,  // Moiety specification equations
      INIT,  // Initializations
      CNST,  // Constant assignments
      VOL,  // Volume assignment
      CPT,  // Compartment volume assignments
      RATE,  // Rate constant assignments
      FUN      // Kinetic function specifications
    };

    /**
     * Default constructor
     */
    CSpecLine();

    /**
     * The named constructor
     */
    CSpecLine(C_INT32 type, string contents);

    /**
     * Destructor
     */
    ~CSpecLine();

    /**
     * Retrieve the type.
     * @return The type
     */
    C_INT32 getType() { return mType; }

    static string convertedType(int type);

    /**
     * Retrieve the content string
     */
    string &getString() { return mContents; }

    /**
     * Extract and return the left hand side of the contents string. 
     * If the left hand side is preceded by a compartment specifier, 
     * this is stripped from the returned string.
     * @return The (stripped) left hand side string
    */
    string extractLeft();

    /**
     * Extract and return the right hand side of the contents string. 
     * @return The right hand side string
    */
    string extractRight();

    /**
     * Extract and return the compartment name/number on the right hand side
     * @return The compartment specifier
     */
    string extractCpt();

  private:
    /**
     * The type
     */
    C_INT32 mType;
    /**
     * The contents
     */
    string mContents;

    // private operations
    string stripBlanks(string instr);
  };

/**
 * The CBaseEqn class holds basic information about an equation, 
 * and is used as an intermediate in processing the spec input.
 * It stores the LHS metabolite, the compartment this is in, and the RHS string.
 */

class CBaseEqn
  {
  public:
    /**
     * Named constructor
     */
    CBaseEqn(string comp, string metab, string contents)
        : mCompartment(comp), mMetabolite(metab), mContents(contents) {}

    /**
     * Destructor
     */
    ~CBaseEqn() {}

    /**
     * Retrieve the string containing the name of the compartment.
     * @return The compartment name.
     */
    string getCompartment() const { return mCompartment; }

    /**
     * Retrieve the string containing the name of the metabolite
     * @return The metabolite name
     */
    string getMetabolite() const { return mMetabolite; }

    /**
     * Retrieve the string containing the contents of the right hand side.
     * @return The RHS contents.
     */
    string getContents() const{ return mContents; }

    /**
     * Overloads the == operator. Equality is true if the strings
     * mCompartment and mMetabolite match.
     */
    bool operator==(const CBaseEqn &rhs) const;

  private:
    string mCompartment;
    string mMetabolite;
    string mContents;
  };

/**
 * The CNameVal class holds a name-value pair.
 * CNameVal is used as an intermediate in processing the spec input.
 */

class CNameVal
  {
  public:
    /**
     * Named constructor
     */
    CNameVal(string name, C_FLOAT64 val): mName(name), mVal(val) {};

    /*
     * Destructor
     */
    ~CNameVal() {};

    /**
     * Return the name
     * @return The name
     */
    string getName() const { return mName; }

    /**
     * Return the value
     * @return The value field
     */
    C_FLOAT64 getVal() const { return mVal; }

  private:
    /**
     * The name
     */
    string mName;
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

class CTempMetab
  {
  public:
    enum Type{UNDEF = 0, SUBSTRATE, PRODUCT, DUAL};
    CTempMetab(CMetab *metab) : mMetab(metab), mMultiplicity(0), mNumChange(0) {}

    CTempMetab(const CTempMetab &rhs);
    CMetab *getMetab() { return mMetab; }
    C_INT32 getMultiplicity() { return mMultiplicity; }
    void setMultiplicity(C_INT32 mult) { mMultiplicity = mult; }
    C_INT32 getNumChange() { return mNumChange; }
    void setNumChange(C_INT32 num) { mNumChange = num; }

  private:
    CMetab *mMetab;
    C_INT32 mMultiplicity;
    C_INT32 mNumChange;

    friend ostream & operator<<(ostream &os, const CTempMetab & m)
    {
      os << "Name = '" << m.mMetab->getName();
      os << "', Multiplicty = '" << m.mMultiplicity;
      os << "', Change = '" << m.mNumChange << "'";
      return os;
    }
  };

class CTempReaction
  {
  public:
    CTempReaction(string name) : mName(name) {}
    string getName() { return mName; }
    void setDescription(string desc) { mRateDescription = desc; }
    string getDescription() { return mRateDescription; }

    CTempMetab *addMetabolite(CMetab *metab);
    vector <CTempMetab> &getMetabs() { return mMetabs; }

    void compile(CModel *model,
                 const vector<CNameVal> & rates,
                 const vector<CNameVal> & constants);
    void setIdentifiers(const CDeTerm *deTerm);

  private:
    bool isIn(vector<CTempMetab> & metabs, const string & target);
    C_FLOAT64 getParameterValue(const string & name,
                                const vector<CNameVal> & rates,
                                const vector<CNameVal> & constants);

  private:
    string mName;
    string mRateDescription;
    vector<CTempMetab> mMetabs;
    vector<CTempMetab> mSubstrates;
    vector<CTempMetab> mProducts;
    vector<string> mIdentifiers;

    friend ostream & operator<<(ostream & os, const CTempReaction & r)
    {
      os << "TempReaction = '" << r.mName << "'" << endl;
      os << "  Rate       = '" << r.mRateDescription << "'" << endl;
      unsigned int i;
      os << "  Metabolites:" << endl;

      for (i = 0; i < r.mMetabs.size(); i++)
        os << "    " << i << ": " << r.mMetabs[i] << endl;

      os << "  Substrates: " << endl;

      for (i = 0; i < r.mSubstrates.size(); i++)
        os << "    " << i << ": " << r.mSubstrates[i] << endl;

      os << "  Products:   " << endl;

      for (i = 0; i < r.mProducts.size(); i++)
        os << "    " << i << ": " << r.mProducts[i] << endl;

      return os;
    }
  };

class CTempReactionSet
  {
  public:
    CTempReactionSet();
    void addReaction(CTempReaction *temp_react);
    CTempReaction *findReaction(string name);
    vector<CTempReaction> getReactions() { return mReactions; }
    C_INT32 size() { return mReactions.size(); }
    CTempReaction &operator[](C_INT32 i) { return mReactions[i]; }

  private:
    vector<CTempReaction> mReactions;
  };

#endif // Copasi_SpecLine

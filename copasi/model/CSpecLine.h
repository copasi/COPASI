#ifndef Copasi_SpecLine
#define Copasi_SpecLine

#include <string>
#include "copasi.h"

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
            CMNT,	// Comments
            DE,		// Differential equations
            EQN,	// Moiety specification equations
            INIT,	// Initializations
            CNST,	// Constant assignments
            VOL,	// Volume assignment
            CPT,	// Compartment volume assignments
            RATE,	// Rate constant assignments
            FUN     	// Kinetic function specifications
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
    C_INT32 getType() {return mType;}

    static string convertedType(int type);

    /**
     * Retrieve the content string
     */
    string &getString() {return mContents;}
    
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
        :mCompartment(comp), mMetabolite(metab), mContents(contents) {}
    /**
     * Destructor
     */
    ~CBaseEqn() {}
    /**
     * Retrieve the string containing the name of the compartment.
     * @return The compartment name.
     */
    string getCompartment() const {return mCompartment;}
    /**
     * Retrieve the string containing the name of the metabolite
     * @return The metabolite name
     */
    string getMetabolite() const {return mMetabolite;}
    /**
     * Retrieve the string containing the contents of the right hand side.
     * @return The RHS contents.
     */
    string getContents() const{return mContents;}
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
    CNameVal(string name, C_FLOAT64 val): mName(name), mVal(val) {}
    /*
     * Destructor
     */
    ~CNameVal();
    /**
     * Return the name
     * @return The name
     */
    string getName() { return mName; }
    /**
     * Return the value
     * @return The value field
     */
    C_FLOAT64 getVal() { return mVal; }
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

#endif // Copasi_SpecLine

/**
 *  CGene class.
 *  Written by Pedro Mendes September 2002.
 *  
 *  For representing a gene and all the elements needed for COPASI 
 *  to represent it in a model
 */

#ifndef COPASI_CGene
#define COPASI_CGene

#include <string>
#include <iostream>

class CGene;

class CGeneModifier
  {
    // Attributes

  private:
    /**
     *  Modifier gene
     */
    CGene * mModifier;

    /**
     *  Type (0=Inhibition, 1=Activation)
     */
    C_INT32 mType;

    /**
     *  Inhibition/activation constant
     */
    C_FLOAT64 mK;

    /**
     *  Hill coefficient
     */
    C_FLOAT64 mn;

  public:

    /**
     *  Default constructor
     */
    CGeneModifier(void);

    /**
     *  Constructor
     *  @param modf pointer to CGene modifier.
     *  @param type (0=Inhibition, 1=Activation).
     *  @param K positive value for effect strength.
     */
    CGeneModifier(CGene * modf, C_INT32 type, C_FLOAT64 K, C_FLOAT64 n);

    /**
     *  Retrieves the pointer to the modifier
     */
    CGene * getModifier(void);

    /**
     *  Retrieves the type of modification
     */
    C_INT32 getType(void);

    /**
     *  Retrieves the inhibition/activation constant
     */
    C_FLOAT64 getK(void);

    /**
     *  Retrieves the Hill coefficient
     */
    C_FLOAT64 getn(void);

    /**
     *  Destructor
     */
    ~CGeneModifier();

    /**
     *  cleanup()
     */
    void cleanup();
  };

class CGene
  {
    // Attributes

  private:
    /**
     *  Name of the gene
     */
    string mName;

    /**
     *  Basal or maximal rate for the transcription
     */
    C_FLOAT64 mRate;

    /**
     *  Basal or maximal rate for the transcription
     */
    C_FLOAT64 mDegradationRate;

    /**
     *  number of incoming links to this gene
     */
    C_INT32 mInDegree;

    /**
     *  number of outgoing links from this gene
     */
    C_INT32 mOutDegree;

    /**
     *  List of other genes that modify transcription of this one
     *  @supplierCardinality 0..*
     *  @associates <{CGene*}>
     */
    CCopasiVector < CGeneModifier > mModifier;

  public:

    /**
     *  Default constructor
     */
    CGene();

    /**
     *  Destructor
     */
    ~CGene();

    /**
     *  Sets the name of the gene.
     */
    void setName(const string & name);

    /**
     *  Retrieve the name of the gene.
     */
    const string & getName() const;

    /**
     *  Retrieve the number of modifiers.
     */
    C_INT32 getModifierNumber();

    /**
     *  Retrieve a Modifier.
     */
    CGene * getModifier(C_INT32 n);

    /**
     *  Sets the name of the gene.
     */
    void setRate(C_FLOAT64 rate);

    /**
     *  Retrieves the constant
     */
    C_FLOAT64 getDegradationRate(void);

    /**
     *  Sets the name of the gene.
     */
    void setDegradationRate(C_FLOAT64 rate);

    /**
     *  Retrieves the constant
     */
    C_FLOAT64 getRate(void);

    /**
     *  Add a new Modifier to this gene.
     */
    void addModifier(CGene *modf, C_INT32 type, C_FLOAT64 K, C_FLOAT64 n);

    /**
     *  Removes a Modifier from this gene.
    *
    *  @param "CGene *" modf pointer to the modifier gene to remove
     */
    void removeModifier(CGene *modf);

    /**
     *  Retrieve the type of Modifier n.
     */
    C_INT32 getModifierType(C_INT32 n);

    /**
     *  Retrieve the inhibition/activation constant of Modifier i.
     */
    C_FLOAT64 getK(C_INT32 i);

    /**
     *  Retrieve the Hill coefficient of Modifier i.
     */
    C_FLOAT64 getn(C_INT32 i);

    /**
     *  Retrieve the number of negative modifiers
    *  @return C_INT32 the number of negative modifiers
     */
    C_INT32 getNegativeModifiers(void);

    /**
     *  Retrieve the number of positive modifiers
     *  @return C_INT32 the number of negative modifiers
     */
    C_INT32 getPositiveModifiers(void);

    /**
     *  Retrieve the number incoming links to this gene
     *  @return C_INT32 the in-degree
     */
    C_INT32 getInDegree();

    /**
     *  Increment the in-degree of this gene
     */
    void addInDegree();

    /**
     *  Retrieve the number outgoing links from this gene
     *  @return C_INT32 the out-degree
     */
    C_INT32 getOutDegree();

    /**
     *  Increment the out-degree of this gene
     */
    void addOutDegree();

    /**
     *  Decrement the in-degree of this gene
     */
    void decreaseInDegree();

    /**
     *  Decrement the out-degree of this gene
     */
    void decreaseOutDegree();

    /**
     *  Retrieve the total number of links (incoming and outgoing) of this gene
     *  @return C_INT32 the total degree
     */
    C_INT32 getTotalDegree();

    /**
     *  cleanup()
     */
    void cleanup();
  };

#endif // COPASI_CGene

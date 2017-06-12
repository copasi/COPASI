// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CChemEqParser
#define COPASI_CChemEqParser

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-register"
#endif

#include <vector>
#include <string>

#undef yyFlexLexer
#include "copasi/FlexLexer.h"

#define yyFlexLexer CChemEqParser

#undef yyYaccParser
#define yyYaccParser CChemEqParserBase

#undef YYDEBUG
#ifdef COPASI_DEBUG
# define YYDEBUG 0  // Set this different from zero to trace the parser
#else
# define YYDEBUG 0
#endif // COPASI_DEBUG

/**
 * This is a base class for the CChemEqParser adding member
 * attributes to enhance the internal functionality.
 */
class yyYaccParser
{
public:
  /**
   * Default constructor
   */
  yyYaccParser();

  /**
   * Destructor
   */
  virtual ~yyYaccParser();

  virtual int yylex() = 0;

  virtual int yyparse();

  const bool & isReversible() const;

  const std::vector< std::string > & getSubstrateNames() const;
  const std::vector< C_FLOAT64 > & getSubstrateMulitplicities() const;
  const std::vector< std::string > & getSubstrateCompartments() const;

  const std::vector< std::string > & getProductNames() const;
  const std::vector< C_FLOAT64 > & getProductMulitplicities() const;
  const std::vector< std::string > & getProductCompartments() const;

  const std::vector< std::string > & getModifierNames() const;
  const std::vector< C_FLOAT64 > & getModifierMulitplicities() const;
  const std::vector< std::string > & getModifierCompartments() const;

protected:
  void correctErrorPosition();

  // Attributes
public:
  struct Data
  {
    std::string name;
    C_FLOAT64 multiplicity;
    std::string compartment;
  };

protected:
  Data * mpData;

  unsigned C_INT32 mPosition;
  bool mReversibility;

  std::vector< std::string > mSubstrateNames;
  std::vector< C_FLOAT64 > mSubstrateMult;
  std::vector< std::string > mSubstrateCompartments;

  std::vector< std::string > mProductNames;
  std::vector< C_FLOAT64 > mProductMult;
  std::vector< std::string > mProductCompartments;

  std::vector< std::string > mModifierNames;
  std::vector< C_FLOAT64 > mModifierMult;
  std::vector< std::string > mModifierCompartments;
};

class CChemEqParser: public FlexLexer, public yyYaccParser
{
public:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer(std::istream& arg_yyin, std::ostream& arg_yyout);
  yyFlexLexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);
private:
  void ctor_common();

public:

  virtual ~yyFlexLexer();

  void yy_switch_to_buffer(yy_buffer_state* new_buffer);
  yy_buffer_state* yy_create_buffer(std::istream* s, int size);
  yy_buffer_state* yy_create_buffer(std::istream& s, int size);
  void yy_delete_buffer(yy_buffer_state* b);
  void yyrestart(std::istream* s);
  void yyrestart(std::istream& s);

  void yypush_buffer_state(yy_buffer_state* new_buffer);
  void yypop_buffer_state();

  virtual int yylex();
  virtual void switch_streams(std::istream& new_in, std::ostream& new_out);
  virtual void switch_streams(std::istream* new_in = 0, std::ostream* new_out = 0);
  virtual int yywrap();

protected:
  virtual int LexerInput(char* buf, int max_size);
  virtual void LexerOutput(const char* buf, int size);
  virtual void LexerError(const char* msg);

  void yyunput(int c, char* buf_ptr);
  int yyinput();

  void yy_load_buffer_state();
  void yy_init_buffer(yy_buffer_state* b, std::istream& s);
  void yy_flush_buffer(yy_buffer_state* b);

  int yy_start_stack_ptr;
  int yy_start_stack_depth;
  int* yy_start_stack;

  void yy_push_state(int new_state);
  void yy_pop_state();
  int yy_top_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans(yy_state_type current_state);
  int yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  char yy_hold_char;

  // Number of characters read into yy_ch_buf.
  int yy_n_chars;

  // Points to current character in buffer.
  char* yy_c_buf_p;

  int yy_init;                // whether we need to initialize
  int yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  int yy_did_buffer_switch_on_eof;

  size_t yy_buffer_stack_top; /**< index of top of stack. */
  size_t yy_buffer_stack_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_stack; /**< Stack as an array. */
  void yyensure_buffer_stack(void);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  char* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;

  char* yy_full_match;
  int* yy_full_state;
  int yy_full_lp;

  int yy_lp;
  int yy_looking_for_trail_begin;

  int yy_more_flag;
  int yy_more_len;
  int yy_more_offset;
  int yy_prev_more_offset;
};

#endif // COPASI_CChemEqParser

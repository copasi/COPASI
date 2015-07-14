// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CUnitParser
#define COPASI_CUnitParser

#include "copasi/utilities/CUnit.h"
//#include <vector>
//#include <string>

#undef yyFlexLexer
#include "FlexLexer.h"

#define yyFlexLexer CUnitParser

#undef yyYaccParser
#define yyYaccParser CUnitParserBase

#undef YYDEBUG
#ifdef COPASI_DEBUG
# define YYDEBUG 0  // Set this different from zero to trace the parser
#else
# define YYDEBUG 0
#endif // COPASI_DEBUG

/**
 * This is a base class for the CUnitParser adding member
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

  const std::set< CUnitComponent > & getComponents() const;

  const std::set< std::string > & getSymbols() const;

  void setAvogadro(const C_FLOAT64 & avogadro);

protected:
  void correctErrorPosition();

  // Attributes
public:
//struct {CUnit unit, CUnitComponent component, char * pText}
  struct Data
  {
    CUnit *pUnit;
    std::string text;
  };
protected:

  CUnit *mpUnit;
  unsigned C_INT32 mPosition;
  C_FLOAT64 mAvogadro;
  std::set< std::string > mSymbols;
};

class CUnitParser: public FlexLexer, public yyYaccParser
{
public:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  CUnitParser(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

  virtual ~CUnitParser();

  void yy_switch_to_buffer(struct yy_buffer_state* new_buffer);

  struct yy_buffer_state* yy_create_buffer(std::istream* s, int size);

  void yy_delete_buffer(struct yy_buffer_state* b);
  void yyrestart(std::istream* s);

  void yypush_buffer_state(struct yy_buffer_state* new_buffer);
  void yypop_buffer_state(void);

  virtual int yylex();
  virtual void switch_streams(std::istream* new_in, std::ostream* new_out);
  virtual int yywrap();

protected:
  virtual int LexerInput(char* buf, int max_size);
  virtual void LexerOutput(const char* buf, int size);
  virtual void LexerError(const char* msg);

  void yyunput(int c, char* buf_ptr);
  int yyinput();

  void yy_load_buffer_state();

  void yy_init_buffer(struct yy_buffer_state* b, std::istream* s);

  void yy_flush_buffer(struct yy_buffer_state* b);

  int yy_start_stack_ptr;
  int yy_start_stack_depth;
  int* yy_start_stack;

  void yy_push_state(int new_state);
  void yy_pop_state();
  int yy_top_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans(yy_state_type current_state);
  int yy_get_next_buffer();

  std::istream* yyin; // input source for default LexerInput
  std::ostream* yyout; // output sink for default LexerOutput

  struct yy_buffer_state* yy_current_buffer;

  // yy_hold_char holds the character lost when yytext is formed.
  char yy_hold_char;

  // Number of characters read into yy_ch_buf.
  int yy_n_chars;

  // Points to current character in buffer.
  char* yy_c_buf_p;

  int yy_init;  // whether we need to initialize
  int yy_start;  // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  int yy_did_buffer_switch_on_eof;

  size_t yy_buffer_stack_top; /**< index of top of stack. */
  size_t yy_buffer_stack_max; /**< capacity of stack. */
  struct yy_buffer_state ** yy_buffer_stack; /**< Stack as an array. */
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

typedef yyYaccParser::Data CChemEqParserlval;

#endif // COPASI_CUnitParser

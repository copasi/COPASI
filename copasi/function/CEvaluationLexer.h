// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationLexer.h,v $
//   $Revision: 1.11.20.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/05 17:04:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationLexer
#define COPASI_CEvaluationLexer

#include <vector>

#undef yyFlexLexer
#include "FlexLexer.h"

#define yyFlexLexer CEvaluationLexer

#undef yyYaccParser
#define yyYaccParser CEvaluationParserBase

#undef YYDEBUG
#ifdef COPASI_DEBUG
# define YYDEBUG 0  // Set his different from zero to trace the parser
#else
# define YYDEBUG 0
#endif // COPASI_DEBUG

/**
 * This is a base class for the CEvaluationLexer adding member
 * attributes to enhance the internal functionality.
 */
class yyYaccParser
  {
  public:
    /**
     * Default constructor
     */
    yyYaccParser():
        mpNode(NULL),
        mpRootNode(NULL),
        mpNodeList(NULL),
        mPosition(0)
    {}

    /**
     * Destructor
     */
    virtual ~yyYaccParser() {}

    /**
     * Retrieve the generated list of nodes.
     * The user owns the list and is repsonsible for the destruction.
     * To delete the list please use freeNodeList.
     * Please note that each call to yylex() creates a new list which
     * must be destoyed.
     * @return std::vector< CEvaluationNode * > * pNodeList
     */
    std::vector< CEvaluationNode * > *getNodeList()
    {return mpNodeList;}

    /**
     * Convenient function to free the list of generated nodes.
     * @param std::vector< CEvaluationNode * > * pNodeList
     */
    static void freeNodeList(std::vector< CEvaluationNode * > * pNodeList)
    {
      if (pNodeList == NULL) return;

      std::vector< CEvaluationNode * >::iterator it;
      std::vector< CEvaluationNode * >::iterator end = pNodeList->end();

      for (it = pNodeList->begin(); it != end; ++it)
        if (*it && (*it)->getParent())
          (*it)->getParent()->removeChild(*it);

      for (it = pNodeList->begin(); it != end; ++it)
        pdelete(*it);

      pdelete(pNodeList);
    }

    virtual int yylex() = 0;

    virtual int yyparse();

  CEvaluationNode * getRootNode() {return mpRootNode;}

    unsigned C_INT32 getErrorPosition() {return mPosition;}

  protected:
    CEvaluationNode * mpNode;
    CEvaluationNode * mpRootNode;
    std::vector< CEvaluationNode * > * mpNodeList;
    unsigned C_INT32 mPosition;

  private:
    void correctErrorPosition()
    {
      std::vector< CEvaluationNode * >::iterator it
      = mpNodeList->begin();
      std::vector< CEvaluationNode * >::iterator end
      = mpNodeList->end();
      unsigned C_INT32 oldPosition = mPosition;
      mPosition = 0;

      for (; it != end && mPosition < oldPosition; ++it)
        mPosition += (*it)->getData().length();

      if (mPosition > 0)
        mPosition -= (*--it)->getData().length();
    }
  };

class CEvaluationLexer : public FlexLexer, public yyYaccParser
  {
  public:
    // arg_yyin and arg_yyout default to the cin and cout, but we
    // only make that assignment when initializing in yylex().
    yyFlexLexer(FLEX_STD istream* arg_yyin = 0, FLEX_STD ostream* arg_yyout = 0);

    virtual ~yyFlexLexer();

    void yy_switch_to_buffer(struct yy_buffer_state* new_buffer);
    struct yy_buffer_state* yy_create_buffer(FLEX_STD istream* s, int size);
    void yy_delete_buffer(struct yy_buffer_state* b);
    void yyrestart(FLEX_STD istream* s);

    void yypush_buffer_state(struct yy_buffer_state* new_buffer);
    void yypop_buffer_state(void);

    virtual int yylex();
    virtual void switch_streams(FLEX_STD istream* new_in, FLEX_STD ostream* new_out);

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

#endif // COPASI_CEvaluationLexer

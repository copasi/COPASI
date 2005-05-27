/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/Attic/CEvaluationFlexLexer.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/27 18:10:50 $
   End CVS Header */

#ifndef COPASI_CEvaluationFlexLexer
#define COPASI_CEvaluationFlexLexer

class CEvaluationFlexLexerBase
  {
  public:
    CEvaluationFlexLexerBase():
        mpNode(NULL),
        mpNodeList(NULL),
        mPosition(0)
    {}

    std::vector< CEvaluationNode * > *getNodeList()
    {return mpNodeList;}

  protected:
    CEvaluationNode * mpNode;
    std::vector< CEvaluationNode * > * mpNodeList;
    unsigned C_INT32 mPosition;
  };

class CEvaluationFlexLexer : public FlexLexer, public CEvaluationFlexLexerBase
  {
  public:
    // arg_yyin and arg_yyout default to the cin and cout, but we
    // only make that assignment when initializing in yylex().
    CEvaluationFlexLexer(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

    virtual ~CEvaluationFlexLexer();

    void yy_switch_to_buffer(struct yy_buffer_state* new_buffer);

    struct yy_buffer_state* yy_create_buffer(std::istream* s, int size);

    void yy_delete_buffer(struct yy_buffer_state* b);
    void yyrestart(std::istream* s);

    virtual int yylex();
    virtual void switch_streams(std::istream* new_in, std::ostream* new_out);

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

#endif // COPASI_CEvaluationFlexLexer

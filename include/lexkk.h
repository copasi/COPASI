// definitions of routines in lexkk.cpp
typedef unsigned int yy_size_t;
struct yy_buffer_state
{
//    FILE *yy_input_file;
    char *yy_ch_buf;
    char *yy_buf_pos;
    yy_size_t yy_buf_size;
    int yy_n_chars;
    int yy_is_our_buffer;
    int yy_is_interactive;
    int yy_at_bol;
    int yy_fill_buffer;
    int yy_buffer_status;
};
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern char *kktext;
int kklex(void);
YY_BUFFER_STATE kk_scan_string(const char *str);
void kk_delete_buffer(YY_BUFFER_STATE b);

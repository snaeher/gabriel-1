
#ifndef B0
#define B0    ;
#define B1(T) ;
#endif

// basic graphics operations used in the LEDA window & panel classes

// display


bool x_open_display(void)        B1(bool)
void x_close_display(void)	 B0
void x_flush_display(void)	 B0

const char* x_display_info(int& width, int& height, int& dpi) B1(const char*)

void x_do_not_open_display(bool) B0

char* x_root_pixrect(int,int,int,int) B1(char*)


// windows

int x_create_window(void* inf, int width, int height, int bg_col, 
                    const char* label, const char* icon_label, int parent, 
                    void (*redraw)(void*,int,int,int,int,int)) B1(int)

void x_open_window(int win, int x, int y, int w, int h, int p_win=0, 
                                                       bool hidden = false) B0
void x_set_topmost(int win)   B0
void x_resize_window(int win, int x, int y, int width, int height, int p)   B0
void x_clear_window(int win, int x0, int y0, int x1, int y1, int xorig=0,
                                                             int yorig=0)   B0
void x_close_window(int win)				B0
void x_minimize_window(int win)				B0
void x_destroy_window(int win)				B0

void* x_window_handle(int win)                          B1(void*)

int   x_window_opened(int win)				B1(int)
int   x_window_bits_saved(int win )			B1(int)

void* x_window_inf(int win)				B1(void*)
int   x_window_height(int win)				B1(int)
int   x_window_width(int win)				B1(int)
void  x_window_frame(int win, int&, int&, int&, int&)   B0

int   x_window_minimized(int win)                       B1(int)

int  x_set_cursor(int win, int cursor_id)		B1(int)
void x_set_label(int win, const char* label)		B0
void x_set_icon_label(int win, const char* label)	B0
void x_set_border_width(int win, int w)			B0
void x_set_border_color(int win, int c)			B0

int  x_get_border_color(int win)               B1(int)
int  x_get_border_width(int win)               B1(int)
int  x_get_cursor(int win)                     B1(int)

int  x_get_resizing(int win)                   B1(int)

void x_set_special_event_handler(int win,
             void (*fun)(void*,const char*,const char*,int,int),
             unsigned long data)                        B0 

void x_set_icon_pixmap(int win,char*)			B0


// buffering

int  x_create_buffer(int)				B1(int)
int  x_create_buffer(int,int,int)			B1(int)
void x_delete_buffer(int)				B0
void x_flush_buffer(int,int,int,int,int)		B0
void x_flush_buffer(int,int,int,int,int,int,int)	B0
int  x_start_buffering(int)				B1(int)
int  x_start_buffering(int,int,int)			B1(int)
void x_set_buffer(int,char*)				B0
void x_stop_buffering(int)				B0
void x_stop_buffering(int, char**)			B0
int  x_test_buffer(int)					B1(int)


// timer

void x_start_timer(int win, int msec)			B0
void x_stop_timer(int win)				B0


// clipping

void x_set_clip_rectangle(int win,int,int,int,int)			B0
void x_clip_mask_rectangle(int w, int x0, int y0, int x1, int y1,int m) B0
void x_clip_mask_polygon(int w, int n, int *xcoord, int *ycoord, int m) B0
void x_clip_mask_ellipse(int w, int x, int y, int r1, int r2, int m)    B0
void x_clip_mask_chord(int w, int x0, int y0, int x1, int y1, int cx, int cy, int r, int mode) B0


// drawing

void x_pixel(int win, int x, int y)					B0
void x_pixels(int win, int n, int* x, int* y)				B0

int  x_get_pixel(int win, int x, int y)					B1(int)

void x_line0(int win, int x1, int y1, int x2, int y2)			B0
void x_line(int win, int x1, int y1, int x2, int y2)			B0
void x_lines(int win, int n, int* x1, int* y1, int* x2, int* y2)	B0

void x_rect(int win, int x1, int y1, int x2, int y2)			B0
void x_box(int win, int x1, int y1, int x2, int y2)			B0
void x_polyline(int win, int n, int* xcoord, int* ycoord, int adjust=0)	B0 
void x_polyline(int win, int n, int* xcoord, int* ycoord, int* clrs)	B0 
void x_arc(int win,int x0,int y0,int r1,int r2,double start,double angle)B0
void x_ellipse(int win, int x0, int y0, int r1, int r2)			B0

void x_fill_polygon(int win, int n, int* xcoord, int* ycoord)		B0
void x_fill_arc(int win,int x0,int y0,int r1,int r2,double start,double angle)B0
void x_fill_ellipse(int win, int x0, int y0, int r1, int r2)		B0

void x_text(int win, int x, int y, const char* s)			B0
void x_text(int win, int x, int y, const char* s, int l)		B0
void x_ctext(int win, int x, int y, const char* s)			B0

void x_text_underline(int win,int x,int y,const char* s,int l,int r)	B0
void x_ctext_underline(int win,int x,int y,const char* s,int l,int r)	B0


// bitmaps

char* x_create_bitmap(int win, int width, int height, unsigned char* data,int f)
                                                                  B1(char*)
void  x_insert_bitmap(int win, int x, int y, char* bmap)	  B0
void  x_delete_bitmap(char* bmap)				  B0


// pixrects

char* x_create_pixrect_from_bits(int win,int w,int h,unsigned char* data,
                                                     int fg, int bg) 
                                                                     B1(char*)

char* x_create_pixrect_from_bgra(int win,int w,int h,unsigned char* data, 
                                                     float scale_f=1) 
                                                                     B1(char*)

char* x_create_pixrect_from_xpm(int win, const char** xpm)	     B1(char*)

char* x_create_pixrect(int win, int x1, int y1, int x2, int y2)	     B1(char*)

void  x_insert_pixrect(int win, char* prect)				    B0
void  x_insert_pixrect(int win, int x, int y, char* prect)		    B0
void  x_insert_pixrect(int win, int x, int y, char*,int,int,int,int)	    B0
void  x_insert_pixrect(int win, int x, int y, int w, int h, char*)	    B0

unsigned char* x_pixrect_to_bgra(int win, char* prect)  B1(unsigned char*) 

void  x_delete_pixrect(char* prect)                     B0

void  x_set_pixrect_alpha(char* prect, int a)		B0
void  x_set_pixrect_phi(char* prect, float phi)		B0
void  x_set_pixrect_anchor(char* prect, int x, int y)	B0

void  x_get_pixrect_size(char*,int&,int&)               B0
void  x_get_pixrect_anchor(char*,int&,int&)             B0


// fonts and text

int  x_set_font(int win, const char* fname)	B1(int)

void x_set_text_font(int win)			B0
void x_set_italic_font(int win)			B0
void x_set_bold_font(int win)			B0
void x_set_fixed_font(int win)			B0
void x_set_button_font(int win)			B0

void x_reset_font(int win)	                B0

int x_text_width(int win, const char* s)	B1(int)
int x_text_width(int win, const char* s, int l)	B1(int)
int x_text_height(int win, const char* s)	B1(int)


// drawing parameters

int           x_set_color(int win, int col)		B1(int)
int           x_set_bg_color(int win, int col)		B1(int)
char*         x_set_bg_pixmap(int win, char* p)		B1(char*)
void          x_set_bg_origin(int win, int x, int y)	B0
int           x_set_line_width(int win, int w)		B1(int)
int           x_set_join_style(int win, int s)		B1(int)
drawing_mode  x_set_mode(int win, drawing_mode m)	B1(drawing_mode)
text_mode     x_set_text_mode(int win, text_mode tm)	B1(text_mode)
line_style    x_set_line_style(int win, line_style ls)	B1(line_style)
void          x_set_stipple(int win, char* bits, int s)	B0

int           x_get_color(int win)			B1(int)
int           x_get_line_width(int win)			B1(int)
drawing_mode  x_get_mode(int win)			B1(drawing_mode)
text_mode     x_get_text_mode(int win)			B1(text_mode)
line_style    x_get_line_style(int win)			B1(line_style)

void x_set_read_gc(int win)				B0
void x_reset_gc(int win)				B0


// events

int x_get_next_event(int& w,int& x,int& y,int& val1,int& val2,
                                                    unsigned long& t,
                                                    int msec=0) B1(int)
void x_put_back_event(void) B0


// mouse

void x_grab_pointer(int w)			B0
void x_move_pointer(int w, int x, int y)        B0
void x_set_focus(int w)				B0


// tooltips

void  x_set_tooltip(int w, int id, int x0,int y0,int x1,int y1, const char*) B0
void  x_del_tooltip(int w, int id) B0

//misc

void x_window_to_screen(int w, int& x, int& y)	B0
void x_screen_to_window(int w, int& x, int& y)	B0

void  x_text_to_clipboard(int w, const char* txt)  B0
char* x_text_from_clipboard(int w)                  B1(char*)


//------------------------------------------------------------------------------
// mswin
//------------------------------------------------------------------------------

void x_set_alpha(int win, int a)		B0

// dialogs
int x_choose_file(int w,int mode,const char* title, const char* filt,
                                                    const char* def_ext,
                                                    char* dname, 
                                                    char* fname) B1(int)
int x_choose_color(int w, int col) B1(int)

// clipboard
void  x_pixrect_to_clipboard(int w, char* prect)  B0
char* x_pixrect_from_clipboard(int w)		  B1(char*)

// metafile
void  x_open_metafile(int w, const char* fname)   B0
void  x_close_metafile(int w)                     B0
void  x_load_metafile(int w,int,int,int,int,const char* fname)   B0
void  x_metafile_to_clipboard(int w)  B0


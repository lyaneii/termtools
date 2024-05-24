/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:02:01 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:58:06
 */

#ifndef TERMTOOLS_H
# define TERMTOOLS_H

typedef struct
{
	int	x;
	int	y;
	int	button_state;
}	t_mouse;

enum e_mouse_button_state
{
	MOUSE_LCLICK = 32,
	MOUSE_MCLICK = 33,
	MOUSE_RCLICK = 34,
	MOUSE_RELEASE = 35,
	MOUSE_MOVE_LCLICK = 32 + MOUSE_LCLICK,
	MOUSE_MOVE_MCLICK = 32 + MOUSE_MCLICK,
	MOUSE_MOVE_RCLICK = 32 + MOUSE_RCLICK,
	MOUSE_MOVE = 32 + MOUSE_RELEASE
};

/* Enables the automatic sending of mouse events to the terminal. */
void	enable_mouse_tracking(void);
/* Disables the automatic sending of mouse events to the terminal. */
void	disable_mouse_tracking(void);

/*
Parses the sequence of bytes representing a mouse event into a struct.
The struct contains the x,y coordinates and the button state of the mouse.
*/
t_mouse	get_mouse_info(const unsigned char *b_sequence);
/* Checks if the starting sequence of bytes is a mouse event. */
int		is_mouse_event(const unsigned char *b_sequence);
/* Checks if the mouse is in the bounding box of p(x0, y0) to p(x1, y1).*/
int		mouse_is_in_bounds(t_mouse mouse, int x0, int y0, int x1, int y1);

int		state_is_released(int state);
int		state_is_right_click(int state);
int		state_is_middle_click(int state);
int		state_is_left_click(int state);

/* Hides the terminal cursor. */
void	hide_cursor(void);
/* Unhides the terminal cursor. */
void	unhide_cursor(void);
/* Toggles between hiding and unhiding of the terminal cursor. */
void	toggle_cursor_visibility(void);
/* Saves position of the terminal cursor. */
void	save_cursor_position(void);
/* Loads the last saved position of the terminal cursor. */
void	load_cursor_position(void);
/* Moves the terminal cursor to p(x,y). */
void	move_cursor_to_position(int x, int y);
/* Moves the terminal cursor to the start of the last line. */
void	move_cursor_to_last_line(void);
/* Shows info about the location and button state of the mouse at the point starting from p(x,y). */
void	show_mouse_info(t_mouse mouse, int x, int y);

struct	termios; /* Forward declaration of termios struct. */

/*
Sets the current terminal to rawmode, which disables the echoing of characters and reads the input per byte.
Stores the previous attributes of the terminal in termios_p.
*/
void	set_terminal_rawmode(struct termios *termios_p);
/* Sets the current terminal attributes to the attributes stored in termios_p. */
void	set_terminal_attributes(struct termios *termios_p);
/* Clears all the characters from the terminal. */
void	clear_terminal_screen(void);
/* Saves a snapshot of what is currently on the terminal. */
void	save_snapshot_terminal(void);
/* Loads the last saved snapshot of the terminal. */
void	load_saved_snapshot_terminal(void);

/* Puts char 'c' at p(x, y). */
void	ttools_draw_char(int x, int y, char c);
/* Draws a line from p(x0, y0) to p(x1, y1) using char 'c'. */
void	ttools_draw_line(int x0, int y0, int x1, int y1, char c);
/* Draws a hollow rectangle from p(x0, y0) to p(x1, y1) using char 'c'. */
void	ttools_draw_box(int x0, int y0, int x1, int y1, char c);
/* Puts text at the point starting from p(x, y). */
void	ttools_draw_text(int x, int y, const char *text);

#endif
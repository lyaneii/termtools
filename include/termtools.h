/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termtools.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 19:12:28 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/23 21:46:55 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	enable_mouse_tracking(void);
void	disable_mouse_tracking(void);
int		is_mouse_event(const unsigned char *code);
t_mouse	get_mouse_info(const unsigned char *info);
int		mouse_is_in_bounds(t_mouse cursor, int x0, int y0, int x1, int y1);

void	hide_cursor(void);
void	unhide_cursor(void);
void	toggle_cursor_visibility(void);
void	save_cursor_position(void);
void	load_cursor_position(void);
void	move_cursor_to_position(int x, int y);
void	move_cursor_to_last_line(void);
void	show_cursor_info(t_mouse cursor, int x, int y);

int		state_is_released(int state);
int		state_is_right_click(int state);
int		state_is_middle_click(int state);
int		state_is_left_click(int state);

struct	termios;
void	set_terminal_rawmode(struct termios *original);
void	set_terminal_mode(struct termios *original);
void	clear_terminal_screen(void);

void	ttools_draw_char(int x, int y, char c);
void	ttools_draw_line(int x0, int y0, int x1, int y1, char c);
void	ttools_draw_box(int x0, int y0, int x1, int y1, char c);
void	ttools_draw_text(int x, int y, const char *text);

#endif
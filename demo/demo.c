/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   demo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/22 14:05:41 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/24 13:26:35 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "termtools.h"
#define BUF_SIZE 7
#define MARGIN 2
#define BOUNDS_TOP MARGIN
#define BOUNDS_LEFT MARGIN
#define BOUNDS_RIGHT (255 - 32 - MARGIN)
#define BOUNDS_BOTTOM (255 - 32 - MARGIN)

struct termios origin;
static void	toggle_bounds(void);
static void	display_instructions(void);
static void	display_current_drawing_char(char c);
static void	restore_original_state(void);
static void	erase(int x, int y, int size);
static void	initialise_terminal_state(void);
static void	draw_box(t_mouse r2, char c);

int	main(void)
{
	unsigned char	buf[BUF_SIZE];
	char			draw_char = '@';
	int				bytes;
	t_mouse			prev;
	t_mouse			current;

	initialise_terminal_state();
	toggle_bounds();
	display_instructions();
	display_current_drawing_char(draw_char);
	current.x = -1;
	prev.x = -1;
	while ((bytes = read(STDIN_FILENO, buf, BUF_SIZE - 1)) > 0)
	{
		buf[bytes] = '\0';
		if(isprint(buf[0]) && !strchr("hcriqb", buf[0]))
		{
			draw_char = buf[0];
			display_current_drawing_char(draw_char);
		}
		if (buf[0] == 'q')
			break ;
		if (buf[0] == 'b')
		{
			toggle_bounds();
			display_current_drawing_char(draw_char);
		}
		if (buf[0] == 'i')
			display_instructions();
		if (buf[0] == 'h')
			toggle_cursor_visibility();
		if (buf[0] == 'c')
		{
			clear_terminal_screen();
			toggle_bounds();
			toggle_bounds();
			display_current_drawing_char(draw_char);
		}
		if (buf[0] == 'r' && \
			mouse_is_in_bounds(current, BOUNDS_LEFT, BOUNDS_TOP, BOUNDS_RIGHT, BOUNDS_BOTTOM))
			draw_box(current, draw_char);
		if (is_mouse_event(buf))
		{
			current = get_mouse_info(buf);
			if (mouse_is_in_bounds(current, BOUNDS_LEFT, BOUNDS_TOP, BOUNDS_RIGHT, BOUNDS_BOTTOM))
				move_cursor_to_position(current.x, current.y);
			if (state_is_left_click((int)buf[3]) && \
				mouse_is_in_bounds(current, BOUNDS_LEFT, BOUNDS_TOP, BOUNDS_RIGHT, BOUNDS_BOTTOM))
			{
				if (prev.x == -1)
					prev = get_mouse_info(buf);
				ttools_draw_line(prev.x, prev.y, current.x, current.y , draw_char);
				fflush(stdout);
			}
			else if (state_is_middle_click((int)buf[3]) && \
				mouse_is_in_bounds(current, BOUNDS_LEFT, BOUNDS_TOP, BOUNDS_RIGHT, BOUNDS_BOTTOM))
			{
				erase(current.x, current.y, 5);
				fflush(stdout);
			}
			if (mouse_is_in_bounds(current, BOUNDS_LEFT, BOUNDS_TOP, BOUNDS_RIGHT, BOUNDS_BOTTOM))
				prev = get_mouse_info(buf);
			// show_cursor_info(current, 1, 1);
			tcflush(STDIN_FILENO, TCIFLUSH);
		}
	}
	restore_original_state();
	return (0);
}

static void	toggle_bounds(void)
{
	t_mouse bounds;
	static int show = 1;
	char	c = 'x';

	if (!show)
		c = ' ';
	bounds.button_state = 0;
	bounds.x = BOUNDS_LEFT - 1;
	bounds.y = BOUNDS_TOP - 1;
	draw_box(bounds, c);
	bounds.x = BOUNDS_RIGHT + 1;
	bounds.y = BOUNDS_BOTTOM + 1;
	draw_box(bounds, c);
	show = !show;
}

static void	display_current_drawing_char(char c)
{
	move_cursor_to_position(15, 1);
	printf("| [%c] - current drawing char |", c);
	fflush(stdout);
}

static void	display_instructions(void)
{
	const char *info[] = {
		"===========================================",
		"| left click - draw                       |",
		"| middle click - erase in a 5x5 square    |",
		"| [b] - toggle drawing bounds visibility  |",
		"| [i] - show this info panel              |",
		"| [h] - toggle cursor visiblity           |",
		"| [c] - clear terminal screen             |",
		"| [r] - set 1st corner of rectangle       |",
		"| [r] again - set 2nd corner of rectangle |",
		"|             and finishes the rectangle  |",
		"| [q] - quit the program                  |",
		"| press any other printable character to  |",
		"| change the drawing character e.g. 'L'   |",
		"===========================================",
	};
	int	info_count = sizeof(info) / sizeof(info[0]);

	for (int i = 0; i < info_count; i++)
		ttools_draw_text(4, 3 + i, info[i]);
}

static void	draw_box(t_mouse r2, char c)
{
	static int stage = 0;
	static t_mouse	r1;

	if (r2.x == -1)
		return ;
	if (stage == 0)
		r1 = r2;
	if (stage != 0)
	{
		ttools_draw_box(r1.x, r1.y, r2.x, r2.y, c);
		stage = 0;
	}
	else
		stage++;
}

static void	restore_original_state(void)
{
	load_terminal_screen();
	set_terminal_mode(&origin);
	disable_mouse_tracking();
	tcflush(STDIN_FILENO, TCIFLUSH);
	unhide_cursor();
}

static void	erase(int x, int y, int size)
{
	x -= size / 2;
	y -= size / 2;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			ttools_draw_char(x + j, y + i, ' ');
	}
	fflush(stdout);
}

static void	initialise_terminal_state(void)
{
	save_terminal_screen();
	set_terminal_rawmode(&origin);
	enable_mouse_tracking();
	hide_cursor();
	clear_terminal_screen();
}

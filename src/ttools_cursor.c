/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:46 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:04:29
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdbool.h>
#include "termtools.h"

void	hide_cursor(void)
{
	printf("\033[?25l");
	fflush(stdout);
}

void	unhide_cursor(void)
{
	printf("\033[?25h");
	fflush(stdout);
}

void	toggle_cursor_visibility(void)
{
	static bool hide = true;

	hide = !hide;
	if (hide)
		hide_cursor();
	else
		unhide_cursor();
}

void	save_cursor_position(void)
{
	printf("\033[s");
	fflush(stdout);
}

void	load_cursor_position(void)
{
	printf("\033[u");
	fflush(stdout);
}

void	move_cursor_to_position(int x, int y)
{
	printf("\033[%d;%dH", y, x);
	fflush(stdout);
}

void	move_cursor_to_last_line(void)
{
	struct winsize w;
	ioctl(1, TIOCGWINSZ, &w);

	printf("\033[%d;1H", w.ws_row);
	fflush(stdout);
}

void	show_mouse_info(t_mouse cursor, int x, int y)
{
	save_cursor_position();
	move_cursor_to_position(x, y);
	printf("(%-3d, %-3d) %d", cursor.x, cursor.y, cursor.button_state);
	load_cursor_position();
	fflush(stdout);
}

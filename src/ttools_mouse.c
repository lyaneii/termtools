/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:57 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:56:07
 */

#include <stdio.h>
#include <string.h>
#include "termtools.h"

void	enable_mouse_tracking(void)
{
	printf("\033[?1003h");
	fflush(stdout);
}

void	disable_mouse_tracking(void)
{
	printf("\033[?1003l");
	fflush(stdout);
}

int	is_mouse_event(const unsigned char *b_sequence)
{
	if (b_sequence && !strncmp("\033[M", (char *)b_sequence, 3))
		return (1);
	return (0);
}

t_mouse	get_mouse_info(const unsigned char *b_sequence)
{
	t_mouse	mouse;

	mouse.x = b_sequence[4] - 32;
	mouse.y = b_sequence[5] - 32;
	mouse.button_state = b_sequence[3];
	return (mouse);
}

int	mouse_is_in_bounds(t_mouse mouse, int x0, int y0, int x1, int y1)
{
	if (mouse.x == -1)
		return (1);
	if (mouse.x < x0 || mouse.x > x1)
		return (0);
	if (mouse.y < y0 || mouse.y > y1)
		return (0);
	return (1);
}

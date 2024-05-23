/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ttools_mouse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/22 20:46:01 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/23 23:53:23 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

int	is_mouse_event(const unsigned char *code)
{
	if (code && !strncmp("\033[M", (char *)code, 3))
		return (1);
	return (0);
}

t_mouse	get_mouse_info(const unsigned char *info)
{
	t_mouse	mouse;

	mouse.x = info[4] - 32;
	mouse.y = info[5] - 32;
	mouse.button_state = info[3];
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

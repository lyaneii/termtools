/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:50 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:05:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termtools.h"

void	ttools_draw_char(int x, int y, char c)
{
	move_cursor_to_position(x, y);
	putchar(c);
}

void	ttools_draw_line(int x0, int y0, int x1, int y1, char c)
{
	int dx, dy, sx, sy, err, e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1; 
	err = dx + dy;
	while (1)
	{
		ttools_draw_char(x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
	fflush(stdout);
}

void	ttools_draw_box(int x0, int y0, int x1, int y1, char c)
{
	ttools_draw_line(x0, y0, x1, y0, c);
	ttools_draw_line(x0, y1, x1, y1, c);
	ttools_draw_line(x0, y0, x0, y1, c);
	ttools_draw_line(x1, y0, x1, y1, c);
}

void	ttools_draw_text(int x, int y, const char *text)
{
	move_cursor_to_position(x, y);
	printf("%s", text);
	fflush(stdout);
}

/*
 * @Author: lyaneii 
 * @Date: 2024-05-25 12:01:31 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-25 13:43:09
 */

#include "termtools.h"
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 7
#define BOUND_X 120
#define BOUND_Y 160
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct termios origin;

void	clean_program(void)
{
	unhide_cursor();
	disable_mouse_tracking();
	set_terminal_attributes(&origin);
	load_saved_snapshot_terminal();
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		clean_program();
		exit(130);
	}
}

void	init_program(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	save_snapshot_terminal();
	set_terminal_rawmode(&origin);
	enable_mouse_tracking();
	hide_cursor();
}

typedef struct
{
	int x;
	int y;
}	t_vec2;

typedef struct
{
	t_vec2	loc;
	t_vec2	target;
}	t_cam2;

void	show_cam_info(t_cam2 cam, int x, int y)
{
	save_cursor_position();
	move_cursor_to_position(x, y);
	printf("s(%-3d, %-3d) t(%-3d, %-3d)", cam.loc.x, cam.loc.y, cam.target.x, cam.target.y);
	load_cursor_position();
	fflush(stdout);
}

void	draw_scene(t_cam2 player)
{
	show_cam_info(player, 60, 0);
	save_cursor_position();
	ttools_draw_char(player.loc.x, player.loc.y, 'p');
	load_cursor_position();
}

t_cam2	init_cam(void)
{
	t_cam2 cam;

	cam.loc.x = 60;
	cam.loc.y = 55;
	cam.target.x = 60;
	cam.target.y = 4;
	return (cam);
}

void	update_cam_loc(t_cam2 *cam, int x, int y)
{
	ttools_draw_char(cam->loc.x, cam->loc.y, ' ');
	cam->loc.x = x < 2 ? max(x, 2) : min(x, BOUND_X - 1);
	cam->loc.y = y < 2 ? max(y, 2) : min(y, BOUND_Y - 1);
	draw_scene(*cam);
}

int	main(void)
{
	int				bytes;
	unsigned char	buf[BUF_SIZE];
	t_cam2			player = init_cam();
	t_mouse			mouse;

	init_program();
	ttools_draw_box(1, 1, BOUND_X, BOUND_Y, 'x');
	draw_scene(player);
	mouse.x = -1;
	while ((bytes = read(STDIN_FILENO, buf, BUF_SIZE - 1)) != -1)
	{
		if (buf[0] == 'w')
			update_cam_loc(&player, player.loc.x, player.loc.y - 1);
		else if (buf[0] == 'a')
			update_cam_loc(&player, player.loc.x - 1, player.loc.y);
		else if (buf[0] == 's')
			update_cam_loc(&player, player.loc.x, player.loc.y + 1);
		else if (buf[0] == 'd')
			update_cam_loc(&player, player.loc.x + 1, player.loc.y);
		else if (is_mouse_event(buf))
		{
			mouse = get_mouse_info(buf);
			if (state_is_left_click(buf[3]))
			{
				player.target.x = mouse.x;
				player.target.y = mouse.y;
				draw_scene(player);
			}
		}
	}
	clean_program();
	return (0);
}

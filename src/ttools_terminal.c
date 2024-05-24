/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:01:01 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:02:50
 */

#include <stdio.h>

void	clear_terminal_screen(void)
{
	printf("\033[2J");
	fflush(stdout);
}

void	save_terminal_screen(void)
{
	printf("\033[?1049h");
	fflush(stdout);
}

void	load_terminal_screen(void)
{
	printf("\033[?1049l");
	fflush(stdout);
}

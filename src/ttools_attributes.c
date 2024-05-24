/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:23 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:55:54
 */

#include <termios.h>

void	set_terminal_rawmode(struct termios *termios_p)
{
	struct termios term;

	tcgetattr(1, termios_p);
	term = *termios_p;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(1, TCSAFLUSH, &term);
}

void	set_terminal_attributes(struct termios *termios_p)
{
	tcsetattr(1, TCSAFLUSH, termios_p);
}

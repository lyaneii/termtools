/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:23 
 * @Last Modified by: lyaneii
 * @Last Modified time: 2024-05-24 20:04:33
 */

#include <termios.h>

void	set_terminal_rawmode(struct termios *original)
{
	struct termios term;

	tcgetattr(1, original);
	term = *original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(1, TCSAFLUSH, &term);
}

void	set_terminal_mode(struct termios *original)
{
	tcsetattr(1, TCSAFLUSH, original);
}

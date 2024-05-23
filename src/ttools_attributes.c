/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ttools_terminalmode.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 15:54:15 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/23 19:18:10 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ttools_terminal.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 19:22:21 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/24 13:20:28 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

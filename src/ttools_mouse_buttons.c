/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ttools_mouse_buttons.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kwchu <kwchu@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 15:51:00 by kwchu         #+#    #+#                 */
/*   Updated: 2024/05/23 19:17:25 by kwchu         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "termtools.h"

int	state_is_released(int state)
{
	if (state == MOUSE_RELEASE || state == MOUSE_MOVE)
		return (1);
	return (0);
}

int	state_is_right_click(int state)
{
	if (state == MOUSE_RCLICK || state == MOUSE_MOVE_RCLICK)
		return (1);
	return (0);
}

int	state_is_middle_click(int state)
{
	if (state == MOUSE_MCLICK || state == MOUSE_MOVE_MCLICK)
		return (1);
	return (0);
}

int	state_is_left_click(int state)
{
	if (state == MOUSE_LCLICK || state == MOUSE_MOVE_LCLICK)
		return (1);
	return (0);
}

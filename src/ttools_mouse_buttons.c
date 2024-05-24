/*
 * @Author: lyaneii 
 * @Date: 2024-05-24 20:00:54 
 * @Last Modified by:   lyaneii 
 * @Last Modified time: 2024-05-24 20:00:54 
 */

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

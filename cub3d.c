/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:02:31 by praders           #+#    #+#             */
/*   Updated: 2025/11/14 13:40:25 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

int	main(int argc, char **argv)
{
	pc()->argc = argc;
	pc()->argv = argv;
	pc()->mode = MENU;
	init_game();
	hook_and_loop();
	destroy_everything(1);
	return (0);
}

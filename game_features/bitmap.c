/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:21 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 17:21:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int find_index(char c)
{
    
}

void draw_char(char c)
{
    static char *bmap = "0123456789";
}

void draw_str(char *str)
{
    while (*str)
        draw_char(*str++);
}

/*
draw_hud - lvl no centro ou eval numero de mortes na esquerda
carregar imagem da barra com texto fixo
carregar imagem de cada digito 
juntar as partes a cada frame

organizar funcoes minimapa - simplificar calculos de pixel position
*/
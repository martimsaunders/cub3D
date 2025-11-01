#include "../cub3d.h"

static void draw_player()
{
    int player_radius = BLOCK / 4;
    int x;
    int y;

    y = -player_radius - 1;
    while (++y <= player_radius)
    {
        x = -player_radius - 1;
        while (++x <= player_radius)
        {
            if (y == -player_radius || y == player_radius || x == -player_radius || x == player_radius)
				put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000);
			else
				put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0xff0000);
        }
    }
}

static void put_floor_wall_pixel(int x, int y, t_mmap *m)
{
    int mapy;
    int mapx;

    mapy = m->mapy;
    mapx = m->mapx;
    if(pc()->map[mapy][mapx] == '1')
    {
        m->frac_x = m->world_x - floor(m->world_x); //pixel x position on the block
        m->frac_y = m->world_y - floor(m->world_y); //pixel y position on the block
        m->relx = (int)(m->frac_x * BLOCK); //pixel x relative position on the grid
        m->rely = (int)(m->frac_y * BLOCK); //pixel y relative position on the grid
        if (m->relx == 0 && (mapx == 0 || pc()->map[mapy][mapx - 1] != '1')) //left edge
            return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000));
        if (m->relx == BLOCK - 1 && (pc()->map[mapy][mapx + 1] == '\0' || pc()->map[mapy][mapx + 1] != '1')) //right edge
            return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000));
        if (m->rely == 0 && (mapy == 0 || pc()->map[mapy - 1][mapx] != '1')) //up edge
            return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000));
        if (m->rely == BLOCK - 1 && (pc()->map[mapy + 1] == NULL || pc()->map[mapy + 1][mapx] != '1')) //down edge
            return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000));
        return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x7B68EE));
    }
    if ((mapx + mapy) % 2 == 0)
        return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0xFFFFFF));
    return (put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0xE6E6FA));
}

static void map_element_draw(int x, int y, t_mmap *m)
{
    m->angle = pc()->player.angle + PI / 2;
    // posição pixel relativo a player e rotação da camera
    m->world_x = pc()->player.x + 0.25 + (x * cos(m->angle) - y * sin(m->angle)) / BLOCK;
    m->world_y = pc()->player.y + 0.25 + (x * sin(m->angle) + y * cos(m->angle)) / BLOCK;
    //coordenadas na grid do pixel
    m->mapx = (int)floor(m->world_x);
    m->mapy = (int)floor(m->world_y);
    if (m->mapy >= 0 && m->mapy < ps()->map_h && m->mapx >= 0 && m->mapx < (int)ft_strlen(pc()->map[m->mapy]))
    {
        put_floor_wall_pixel(x, y, m);
    }
    else
        put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000);
}

void draw_mini_map()
{
    int x;
    int y;
    t_mmap m;

    y = -MAP_RADIUS;
    while (y <= MAP_RADIUS)
    {
        x = -MAP_RADIUS;
        while (x <= MAP_RADIUS)
        {
            if (x * x + y * y <= MAP_RADIUS * MAP_RADIUS)
            {
                if (x * x + y * y > (MAP_RADIUS - 2) * (MAP_RADIUS - 2))
                    put_pixel(MAP_RADIUS + x, MAP_RADIUS + y, 0x000000);
                else
                    map_element_draw(x, y, &m);
            }
            x++;
        }
        y++;
    }
    draw_player();
}

#include "../cub3d.h"

static void map_pixel_put(int x, int y, int color)
{
    float angle;
    float rotx;
    float roty;

    angle = pc()->player.angle;
    rotx = x * cos(-angle) - y * sin(-angle);
    roty = x * sin(-angle) + y * cos(-angle);
    put_pixel(MAP_RADIUS + rotx, MAP_RADIUS + roty, color);
    put_pixel(MAP_RADIUS + rotx, MAP_RADIUS + roty + 1, color);
}

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

static void put_floor_wall_pixel(int mapx, int mapy, int x, int y)
{
    if(pc()->map[mapy][mapx] == '1') //wall
    {
        if (fmod(pc()->player.x + x, BLOCK) == 0.0f) //grid block edge x
        {
            if (mapx == 0 || mapx == (int)ft_strlen(pc()->map[mapy]) - 1 || pc()->map[mapy][mapx - 1] != '1' || pc()->map[mapy][mapx + 1] != '1')
                return (map_pixel_put(x, y, 0x000000));
        }
        if (fmod(pc()->player.y + y, BLOCK) == 0.0f) //grid block edge y
        {
            if (mapy == 0 || mapy == ps()->map_h || pc()->map[mapy + 1][mapx] != '1' || pc()->map[mapy - 1][mapx] != '1')
                return (map_pixel_put(x, y, 0x000000));
        }
        return (map_pixel_put(x, y, 0x7B68EE));
    }
    else
    {
        //floor
        if ((mapx + mapy) % 2 == 0)
            return (map_pixel_put(x, y, 0xFFFFFF));
        return (map_pixel_put(x, y, 0xE6E6FA));
    }
}

static void map_element_draw(int x, int y)
{
    int mapx;
    int mapy;

    mapx = ((int)(pc()->player.x * BLOCK) + x) / BLOCK;
    mapy = ((int)(pc()->player.y * BLOCK) + y) / BLOCK;
    if (mapy >= 0 && mapy < ps()->map_h)
    {
        if(mapx >= 0 && mapx < (int)ft_strlen(pc()->map[mapy]))
        {
            put_floor_wall_pixel(mapx, mapy, x, y);
            return ;
        }
    }
    map_pixel_put(x, y, 0x000000);
}

void draw_mini_map()
{
    int x;
    int y;

    y = -MAP_RADIUS;
    while (y <= MAP_RADIUS)
    {
        x = -MAP_RADIUS;
        while (x <= MAP_RADIUS)
        {
            if(x*x + y*y <= MAP_RADIUS*MAP_RADIUS)
                map_element_draw(x, y);
            x++;
        }
        y++;
    }
    draw_player();
}
//comparar com minha versao profundamente e entender porque valor esta ao contrario e nao atualiza
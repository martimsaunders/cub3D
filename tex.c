#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"

int main()
{
    int fd = open("tex.txt",O_RDONLY);
    int c = 0;
    char *line;
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        c++;
        free(line);
    }
    close(fd);
    char **arr = ft_calloc(c + 1, sizeof(char *));
    fd = open("tex.txt",O_RDONLY);
    c = 0;
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        arr[c++] = ft_strdup(line);
        free(line);
    }
    arr[c] = NULL;
    close(fd);
    int y = -1;
    while(arr[++y])
    {
        int x = -1;
        while (arr[y][++x])
        {
            if (arr[y][x] != ',' && arr[y][x] != '\"' && arr[y][x] != 'F' && arr[y][x] != ' ' && arr[y][x] != '\n')
                arr[y][x] = 'F';
        }
    }
    fd = open("tex2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    y = -1;
    while(arr[++y])
    {
        int x = -1;
        while (arr[y][++x])
        {
            write(fd, &arr[y][x], 1);
        }
    }
    close(fd);
    parse_free_array(arr);
}
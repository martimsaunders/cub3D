#include "../cub3d.h"

typedef struct s_file_data
{
    char **file;
    int line_count;
    int map_idx;
    int n_tex;
    int s_tex;
    int e_tex;
    int w_tex;
    int c_col;
    int f_col;
    char *n_path;
    char *s_path;
    char *e_path;
    char *w_path;
    int *c_hex;
    int *f_hex;
} t_file_data;

void parse_init_f(t_file_data *f)
{
    f->line_count = 0;
    f->c_col = 0;
    f->f_col = 0;
    f->e_tex = 0;
    f->n_tex = 0;
    f->s_tex = 0;
    f->w_tex = 0;
    f->file = NULL;
    f->n_path = pc()->image.wall_n.path;
    f->s_path = pc()->image.wall_s.path;
    f->e_path = pc()->image.wall_e.path;
    f->w_path = pc()->image.wall_o.path;
    f->c_hex = pc()->image.ceiling;
    f->f_hex = pc()->image.floor;
}

void	err_msg(char *msg, char var)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (var)
		ft_putchar_fd(var, 2);
	write(2, "\n", 1);
}

bool file_fill(t_file_data *f, const char *filepath)
{
    int fd;
    char *line;
    int i;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (perror("Error\n"), false);
    i = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        f->file[i] = ft_strdup(line);
        if (!f->file[i++])
            return (perror("Error\n"), false);
    }
    f->file[i] = NULL;
    close(fd);
    return (true);
}

bool file_load(t_file_data *f, const char *filepath)
{
    int fd;
    char *line;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (perror("Error\n"), false);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        f->line_count++;
    }
    f->file = ft_calloc(f->line_count + 1, sizeof(char *));
    if (!f->file)
        return (perror("Error\n"), false);
    close(fd);
    return (file_fill(f, filepath));
}

bool parse_is_empty_line(const char *line)
{
    while(line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n')
            return (false);
        line++;
    }
    return (true);
}

bool parse_is_space(char c)
{
    if (c == ' ' || c == '\t')
        return (true);
    return (false);
}

bool parse_is_map_line(const char *line)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else if (*line == '1')
            return (true);
        else
            return (false);
    }
    return (false);
}

bool parse_is_texture(const char *line)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
            return (true);
        else
            return (false);
    }
    return (false);
}

char parse_get_char(char *line)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else
            return (*line);
    }
    return (0);
}

bool parse_check_texture(char *line, int *id, char **dst)
{
    if (*id != 0)
        return (err_msg("Duplicated texture: ", *line), false);
    line++;
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else
            break ;
    }
    *dst = ft_strdup(line);
    if (!*dst)
        return (perror("Error\n"), false);
    if (open(*dst, O_RDONLY) == -1)
        return (perror("Error\n"), false);
    *id = 1;
    return (true);
}

bool parse_get_texture(char *line, t_file_data *f)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else if (*line == 'N')
            return (parse_check_texture(line, &f->n_tex, &f->n_path));
        else if (*line == 'E')
            return (parse_check_texture(line, &f->e_tex, &f->e_path));
        else if (*line == 'S')
            return (parse_check_texture(line, &f->s_tex, &f->s_path));
        else if (*line == 'W')
            return (parse_check_texture(line, &f->w_tex, &f->w_path));
    }
    return (false);
}

bool parse_is_color(const char *line)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else if (*line == 'C' || *line == 'F')
            return (true);
        else
            return (false);
    }
    return (false);
}

bool parse_check_color(char *line, int *id, int *dst)
{
    //traduzir cor
}

bool parse_get_color(char *line, t_file_data *f)
{
    while(line)
    {
        if (parse_is_space(*line))
            line++;
        else if (*line == 'C')
            return (parse_check_color(line, &f->c_col, &f->c_hex));
        else if (*line == 'F')
            return (parse_check_color(line, &f->f_col, &f->f_hex));
    }
    return (false);
}

bool parse_header(t_file_data *f)
{
    int i;
    bool ret;

    i = -1;
    while (f->file[++i])
    {
        if (parse_is_empty_line(f->file[i]))
            continue;
        else if (parse_is_map_line(f->file[i]))
            break ;
        else if (parse_is_texture(f->file[i]))
            ret = parse_get_texture(f->file[i], f);
        else if (parse_is_color(f->file[i]))
            ret = parse_get_color(f->file[i], f);
        else
            return (err_msg("Wrong identifier: ", parse_get_char(f->file[i])), false);
        if (!ret)
            return (false);
    }
    f->map_idx = i;
    return (true);
}

void parse_map_file(const char *filepath)
{
    t_file_data f;

    parse_init_f(&f);
    // 1. Ler arquivo completo em memória (todas as linhas)
    if (!file_load(&f, filepath))
        file_destroy(&f, 1);

    // 3. Interpretar e validar cada config da seção de header
    parse_header(&f);

    // 4. Transformar a seção de mapa em matriz (char**)
    parse_map_matrix(&g->map, &f.map_section);

    // 5. Validar mapa (contornos, caracteres, player, elementos)
    validate_map(&g->map);

    // 6. Processar informações derivadas (spawn, altura/largura, sprites)
    build_map_metadata(g);

    // 7. Liberar buffers temporários do parser
    file_destroy(&f);
}

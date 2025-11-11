#include "../cub3d.h"

bool	parse_is_empty_line(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
	}
	return (true);
}

bool	parse_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	parse_is_map_line(const char *line)
{
	while (line)
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

bool	parse_is_texture(const char *line)
{
	while (line)
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

bool	parse_is_color(const char *line)
{
	while (line)
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

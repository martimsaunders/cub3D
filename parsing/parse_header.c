#include "../cub3d.h"

bool	parse_check_all_infos(t_parse *f)
{
	if (!f->c_col || !f->f_col)
		return (err_msg("Color info missing", 0), false);
	if (!f->n_path || !f->e_path || !f->s_path || !f->w_path)
		return (err_msg("Texture info missing", 0), false);
	return (true);
}

bool	parse_header(t_parse *f)
{
	int		i;
	bool	ret;

	i = -1;
	while (f->file[++i])
	{
		if (!parse_is_empty_line(f->file[i]))
		{
			if (parse_is_map_line(f->file[i]))
				break ;
			else if (parse_is_texture(f->file[i]))
				ret = parse_get_texture(f->file[i], f);
			else if (parse_is_color(f->file[i]))
				ret = parse_get_color(f->file[i], f);
			else
				return (err_msg("Wrong identifier: ",
						parse_get_char(f->file[i])), false);
			if (!ret)
				return (false);
		}
	}
	f->map_idx = i;
	return (parse_check_all_infos(f));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <bboisset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:37:38 by bboisset          #+#    #+#             */
/*   Updated: 2020/08/03 20:16:33 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	inspect_line(char *str, int line_n, t_map_config *config,
	int map_start)
{
	int		i;
	char	*set;

	i = 0;
	set = (line_n == 1) ? "1" : "012NSEW";
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '2')
			i = char_is_sprite(str, i, line_n - map_start, config);
		else
		{
			if (is_in_set(str[i], "NSEW"))
			{
				char_is_player(config, str, i, line_n - map_start);
				str[i] = '0';
			}
			if (!is_in_set(str[i++], set) || config->player_count > 1)
				return (-4);
		}
		if (i < 0)
			return (i);
	}
	return (inspect_line_end(str, config));
}

static int	element_hub_two(char *str, int line_n, int res,
	t_map_config *config)
{
	if (str[0] == 'E' && str[1] == 'A' && !config->textures->east_texture_path)
		config->textures->east_texture_path = get_path(2, str, config);
	else if (str[0] == 'S' && str[1] != 'O' &&
		!config->textures->sprite_texture_path)
		config->textures->sprite_texture_path = get_path(1, str, config);
	else if (str[0] == 'W' && str[1] == 'E' &&
		!config->textures->west_texture_path)
		config->textures->west_texture_path = get_path(2, str, config);
	else if (str[0] == 'F' && !config->sky_color.red)
		res = assign_sky(str, config);
	else if (str[0] == 'C' && !config->ground_color.red)
		res = assign_ground(str, config);
	if (res < 0)
		config->config_error = res;
	if (config->config_error < 0)
		return (-1);
	return (res);
}

static int	element_hub(char *str, int line_n, t_map_config *config)
{
	static int	map_start = 0;
	int			res;

	res = 0;
	while (str[0] == ' ')
		str++;
	if (str[0] == '1' && !map_start)
		map_start = line_n;
	if (map_start)
		res = inspect_line(str, line_n, config, map_start);
	else if (str[0] == '\0')
		return (0);
	else if (str[0] == 'R' && !config->res.x)
		res = assign_resolutions(str, config);
	else if (str[0] == 'N' && str[1] == 'O' &&
		!config->textures->north_texture_path)
		config->textures->north_texture_path = get_path(2, str, config);
	else if (str[0] == 'S' && str[1] == 'O' &&
		!config->textures->south_texture_path)
		config->textures->south_texture_path = get_path(2, str, config);
	if (res < 0)
		config->config_error = res;
	return (element_hub_two(str, line_n, res, config));
}

int			read_file(int fd, t_map_config *config)
{
	int		fd_status;
	int		line_n;
	int		res;
	char	*new_line;

	line_n = 0;
	fd_status = 1;
	while (fd_status == 1)
	{
		if ((fd_status = get_next_line(fd, &new_line)) == -1)
			return (-1);
		if (ft_strlen(new_line) > 0)
			res = element_hub(new_line, line_n++, config);
		free(new_line);
		if (res == -1)
			return (-1);
	}
	if (fd_status == -1 || config->player_count == 0)
		return (-1);
	return (0);
}

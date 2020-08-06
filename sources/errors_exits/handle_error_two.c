/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <bboisset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:36:01 by bboisset          #+#    #+#             */
/*   Updated: 2020/08/04 17:42:26 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	map_error(t_map_config *config, int code)
{
	if (code == 1)
		code = config->config_error != 0 ? config->config_error : 1;
	free_config(config, NULL);
	code_error(code);
	return (-1);
}

int	temp_map_switcher_error(char **map, int i, char **ptr_temp_map)
{
	int j;

	j = 0;
	while (j < i - 1)
		free(map[j++]);
	free(map);
	free(ptr_temp_map);
	return (-1);
}

int	cam_mall_err(t_map_config *config, t_data *data, int code)
{
	free_config(config, data);
	free_data(data);
	code_error(code);
	return (-1);
}

int	full_error_d(t_full_conf *full_conf, int type, int code)
{
	if (type > 0 && full_conf->config->small_res == 0)
		free_gun(full_conf->data, full_conf->gun);
	if (type > 2 && full_conf->config->small_res == 0)
		free_minimap(full_conf->data, full_conf->minimap, 1);
	code = full_conf->config->config_error <
		0 ? full_conf->config->config_error : code;
	full_error(full_conf->config, full_conf->data, full_conf->camera, code);
	free(full_conf);
	return (-1);
}

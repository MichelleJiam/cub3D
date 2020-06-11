/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:22:54 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/11 17:48:09 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pos_setter(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

int		inset(char *line, int i)
{
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
		|| line[i] == 'F' || line[i] == 'C')
		return (1);
	return (0);
}

int		isnumber(char *line, int i)
{
	if (line[i] && line[i] >= '0' && line[i] <= '9')
		return (1);
	return (0);
}

int		value_finder(char *line, int *i, char exc)
{
	while (line[*i] && !isnumber(line, *i) && line[*i] != '-')
	{
		if (line[*i] != exc && line[*i] != 32 &&
			(line[*i] < 9 || line[*i] > 13))
			return (-1);
		(*i)++;
	}
	return (0);
}

int		whitespaceskip(char *line, int *i)
{
	if (line[*i] != 32 && (line[*i] < 9 || line[*i] > 13))
		return (0);
	while (line[*i] == 32 || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
	return (1);
}

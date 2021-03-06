/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:35:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/18 17:56:28 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int ac, char **av)
{
	t_tetri	*list;
	char	*map;
	int		tetri_nbr;
	int		display;

	list = NULL;
	map = NULL;
	tetri_nbr = 0;
	display = 0;
	if (ac == 2 || (ac == 3 && !ft_strcmp(av[1], "-d")))
	{
		if (ac == 3)
		{
			av++;
			display++;
		}
		if ((tetri_nbr = set_list(av[1], &list)))
		{
			if (!(solve_tetri(list, map, tetri_nbr, display)))
				ft_putstr("error\n");
		}
		else
			ft_putstr("error\n");
		tetri_del(&list);
	}
	else
		ft_putstr("usage: ./fillit [-d] FILE\n");
	return (0);
}

/*
** Find minimal map size for given tetri list
*/

int		solve_tetri(t_tetri *list, char *map, int tetri_nbr, int display)
{
	int map_len;

	map_len = 2;
	while (map_len * map_len < tetri_nbr * 4)
		map_len++;
	if ((map = create_map(map, map_len)))
	{
		while (!backtrack(list, map, map_len++, 0, display))
		{
			if (!(map = create_map(map, map_len)))
				break ;
		}
	}
	if (!map)
		return (0);
	if (!display)
		ft_putstr(map);
	else
		print_solution(map);
	ft_strdel(&map);
	return (1);
}

/*
** Recursively try every possible combinations of tetris
** Returns 1 if a solution has been found for the current map size
** Returns 0 otherwise
*/

int		backtrack(t_tetri *ptr, char *map, int map_len, int i, int display)
{
	if (display)
		ft_putstr(KCLR);
	if (ptr != NULL)
	{
		while (((i + ptr->coord[7]) + 1 < (map_len + 1) * map_len))
		{
			if (map[i + ptr->coord[1]] == '.')
			{
				if (!conflict(ptr, map, map_len, i))
				{
					if (display)
						print_tetri_color(map, ptr, map_len, i, KGRN);
					break ;
				}
				if (display)
					print_tetri_color(map, ptr, map_len, i, KRED);
			}
			else if (display)
				print_tetri_color(map, ptr, map_len, i, KRED);
			i++;
		}
		if ((ptr->coord[7] + i) + 1 >= ((map_len + 1) * map_len))
		{
			if (display)
				print_tetri_color(map, ptr, map_len, i, KRED);
			i = 0;
			return (0);
		}
		while (backtrack(ptr->next, map, map_len, 0, display) == 0)
		{
			if (display)
				print_tetri_color(map, ptr, map_len, i, KRED);
			put_tetri(ptr, map, map_len, i);
			return (backtrack(ptr, map, map_len, i + 1, display));
		}
	}
	return (1);
}

/*
** Determine wether the given position is valid for the current tetri
** Returns 1 in case of conflict, 0 otherwise
*/

int		conflict(t_tetri *tetri, char *map, int map_len, int pos)
{
	int i;
	int *coord;

	i = 0;
	coord = tetri->coord;
	while (i < 8)
	{
		if (map[pos + coord[i] * (map_len + 1) + coord[i + 1]] != '.')
			return (1);
		i += 2;
	}
	put_tetri(tetri, map, map_len, pos);
	return (0);
}

/*
** Write tetri at given position in map if it's not already set
** Erase it otherwise
*/

void	put_tetri(t_tetri *tetri, char *map, int map_len, int pos)
{
	int		i;
	int		*coord;
	char	c;

	i = 0;
	coord = tetri->coord;
	if (map[pos + coord[1] + (coord[0] * (map_len + 1))] == '.')
	{
		c = tetri->name;
		tetri->pos = pos;
	}
	else
	{
		c = '.';
		pos = tetri->pos;
		tetri->pos = 0;
	}
	map[pos + coord[1] + (coord[0] * (map_len + 1))] = c;
	map[pos + coord[3] + (coord[2] * (map_len + 1))] = c;
	map[pos + coord[5] + (coord[4] * (map_len + 1))] = c;
	map[pos + coord[7] + (coord[6] * (map_len + 1))] = c;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:20:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/02 19:50:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"

#define BUFF_SIZE 22

typedef struct	s_tetri
{
	int *coord;
	char name;
	struct	s_tetri *next;
}				t_tetri;

t_tetri	*parse_input(char *file);
int		get_input(int fd, char buff[BUFF_SIZE]);
t_tetri	*get_tetri(char buff[BUFF_SIZE], int tetri_count);
/*
** TOOLS
*/
void	tetri_push(t_tetri **alist, t_tetri *list);
t_tetri	*new_tetri(int *coord, char name);
void	tetri_del(t_tetri **alst);
int		*set_coord(int coord[8], int blocks, int pos);
#endif
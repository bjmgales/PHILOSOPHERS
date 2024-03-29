/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:15:11 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:48:50 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	parsing(int argc, char **argv)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error.\nMissing or extra argument.\n");
		return (1);
	}
	while (++c < argc)
	{
		while (argv[c][++i])
		{
			if (argv[c][i] < '0' || argv[c][i] > '9')
			{
				printf("Error.\nArgument format is wrong.\n");
				return (1);
			}
		}
		i = -1;
	}
	return (0);
}

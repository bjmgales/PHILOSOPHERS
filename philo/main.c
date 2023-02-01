/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:20:57 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:47:11 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	main(int argc, char **argv)
{
	t_info	data;

	if (parsing(argc, argv))
		return (1);
	data = args_init(argv);
	if (data.must_eat == 0 || data.fork_nbr == 0 || data.t_to_die == 0
		||data.t_to_eat == 0 || data.t_to_sleep == 0)
	{
		printf(BOLD"\n\t\tCan't put a \"0\" in args.\n\n");
		return (1);
	}
	malloc_data(&data);
	mutex_init(&data);
	start_routine(data);
	return (0);
}

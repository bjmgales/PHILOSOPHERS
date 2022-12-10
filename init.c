/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:14 by bgales            #+#    #+#             */
/*   Updated: 2022/12/10 11:45:44 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	args_init(t_info *args, char **argv)
{
	int	i;

	i = -1;
	args->fork = ft_atoi(argv[1]);
	args->philo = malloc(sizeof(t_philo) * args->fork - 1);
	while (++i < args->fork)
	{
		if (i == args->fork - 1)
		{
			args->philo[i].fork_r = &args->philo[0].fork_l;
			args->philo[i].nbr = i + 1;
			pthread_mutex_init(args->philo[i].fork_r, NULL);
		}
		else
		{
			args->philo[i].fork_r = &args->philo[i + 1].fork_l;
			args->philo[i].nbr = i + 1;
			pthread_mutex_init(args->philo[i].fork_r, NULL);
		}
	}
	args->t_to_die = ft_atoi(argv[2]);
	args->t_to_eat = ft_atoi(argv[3]);
	args->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->nb_of_eat = ft_atoi(argv[5]);
}

void	*thread_init(t_info args)
{
	int			i;

	i = -1;
	while (++i < args.fork)
	{
		if (pthread_create(&args.philo[i].th, NULL, philo(args, i), NULL) != 0)
		{
			printf("Error in Thread#%d creation. \n", i);
			return ((void *)(1));
		}
	}
	printf("lol\n");
	i = args.fork ;
	 while (--i > -1)
	{
		printf("%d\n", i);
		if (pthread_join(args.philo[i].th, NULL) != 0)
		{
			printf("Error in Thread#%D join. \n", i);
			return ((void *)(1));
		}
	 }
	return ((void *)(0));
}

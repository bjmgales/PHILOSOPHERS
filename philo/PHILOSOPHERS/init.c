/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:14 by bgales            #+#    #+#             */
/*   Updated: 2022/12/22 13:33:35 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void args_alloc(t_info *args, char **argv)
{
	args->meal_count = malloc(sizeof(int));
	args->t_to_die = malloc(sizeof(unsigned int));
	args->t_to_eat = malloc(sizeof(unsigned int));
	args->t_to_sleep = malloc(sizeof(unsigned int));
	args->dead = malloc(sizeof(int));
	args->nb_of_eat = malloc(sizeof(int));
	args->start = malloc(sizeof(long) * 1);
	args->fork_nbr = malloc(sizeof(int));
	*args->fork_nbr = ft_atoi(argv[1]);
	*args->t_to_die = ft_atoi(argv[2]);
	*args->t_to_eat = ft_atoi(argv[3]);
	*args->t_to_sleep = ft_atoi(argv[4]);
	*args->dead = 0;
	if (argv[5])
		*args->nb_of_eat = ft_atoi(argv[5]) * *args->fork_nbr;
	else
		*args->nb_of_eat = -1;
	return ;
}
void	args_init(t_info *args, char **argv)
{
	int	i;

	i = -1;
	args_alloc(args, argv);
	args->philo = malloc(sizeof(t_philo) * *args->fork_nbr);
	args->fork_r = malloc(sizeof(pthread_mutex_t));
	args->fork_l = malloc(sizeof(pthread_mutex_t) * *args->fork_nbr);
	*args->fork_r = malloc(sizeof(pthread_mutex_t) * *args->fork_nbr);
	args->print= malloc(sizeof(pthread_mutex_t) * *args->fork_nbr);
	*args->meal_count = 0;
	while (++i < *args->fork_nbr)
	{
		args->philo[i].args = args;
		if (i == *args->fork_nbr - 1)
		{
			args->philo[i].nbr = i + 1;
			args->fork_r[i] = &args->fork_l[0];
			pthread_mutex_init(&args->fork_l[0], NULL);
		}
		else
		{
			args->philo[i].nbr = i + 1;
			args->fork_r[i] = &args->fork_l[i + 1];
			pthread_mutex_init(&args->fork_l[i + 1], NULL);
		}
	}
	return;
}

void	*thread_init(t_info args)
{
	int			i;
	pthread_t 	check;

	i = -1;
	pthread_mutex_init(args.print, NULL);
	*args.start = ft_start_time();
	while (++i < *args.fork_nbr)
	{
		if (pthread_create(&args.philo[i].th, NULL, philo, (void *)&args.philo[i]) != 0)
		{
			printf("Error in Thread#%d creation. \n", i);
			return ((void *)(1));
		}
		if (pthread_create(&check, NULL, is_dead, (void *)&args) != 0)
		{
			printf("Error in Thread#%d creation. \n", i);
			return ((void *)(1));
		}
	}
	return ((void *)(0));
}

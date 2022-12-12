/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:14 by bgales            #+#    #+#             */
/*   Updated: 2022/12/12 16:17:20 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void args_alloc(t_info *args, char **argv)
{
	args->t_to_die = malloc(sizeof(unsigned int));
	args->t_to_eat = malloc(sizeof(unsigned int));
	args->t_to_sleep = malloc(sizeof(unsigned int));
	args->nb_of_eat = malloc(sizeof(unsigned int));
	args->start = malloc(sizeof(long) * 1);
	args->fork_nbr = malloc(sizeof(int));
	*args->start = ft_start_time();
	*args->fork_nbr = ft_atoi(argv[1]);
	*args->t_to_die = ft_atoi(argv[2]);
	*args->t_to_eat = ft_atoi(argv[3]);
	*args->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		*args->nb_of_eat = ft_atoi(argv[5]);
	return ;
}
void	args_init(t_info *args, char **argv)
{
	int	i;

	i = -1;
	args_alloc(args, argv);
	args->philo = malloc(sizeof(t_philo) * *args->fork_nbr);
	args->fork_l = malloc(sizeof(pthread_mutex_t) * *args->fork_nbr);
	args->fork_r = malloc(sizeof(pthread_mutex_t) * *args->fork_nbr);
	while (++i < *args->fork_nbr)
	{
		args->philo[i].args = args;
		if (i == *args->fork_nbr - 1)
		{
			args->fork_r[i] = args->fork_l[0];
			args->philo[i].nbr = i + 1;
			pthread_mutex_init(&args->fork_r[i], NULL);
		}
		else
		{
			args->fork_r[i] = args->fork_l[i + 1];
			args->philo[i].nbr = i + 1;
			pthread_mutex_init(&args->fork_r[i], NULL);
		}
	}
	return;
}

void	*thread_init(t_info args)
{
	int			i;

	i = -1;
	pthread_mutex_init(&args.print, NULL);
	while (++i < *args.fork_nbr)
	{
		if (pthread_create(&args.philo[i].th, NULL, philo, (void *)&args.philo[i]) != 0)
		{
			printf("Error in Thread#%d creation. \n", i);
			return ((void *)(1));
		}
	}
	i = *args.fork_nbr ;
	 while (--i > -1)
	{
		if (pthread_detach(args.philo[i].th) != 0)
		{
			printf("Error in Thread#%D join. \n", i);
			return ((void *)(1));
		}
	 }
	return ((void *)(0));
}

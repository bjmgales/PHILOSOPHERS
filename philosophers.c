/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:29:02 by bgales            #+#    #+#             */
/*   Updated: 2022/12/10 11:17:08 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

int	parsing(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 5 && argc != 6)
	{
		printf("Error : Arguments are unvalid.\n");
		return (1);
	}
	argc--;
	while (argc > 1)
	{
		while (argv[argc][++i])
		{
			if (argv[argc][i] < 48 || argv[argc][i] > 57)
			{
				printf("Error : Arguments format is wrong.\n");
				return (1);
			}
		}
		i = -1;
		argc--;
	}
	return (0);
}

void	*philo(t_info args, int i)
{
	args.start = ft_start_time();
	pthread_mutex_lock(&args.philo[i].fork_l);
	printf("%ld %d has taken a fork\n", ft_time(args.start), args.philo[i].nbr);
	pthread_mutex_lock(args.philo[i].fork_r);
	printf("%ld %d has taken a fork\n", ft_time(args.start), args.philo->nbr);
	pthread_mutex_unlock(&args.philo[i].fork_l);
	pthread_mutex_unlock(args.philo[i].fork_r);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	args;
	//struct timeval time;
	if (parsing(argc, argv) == 1)
		return (1);
	args_init(&args, argv);
	thread_init(args);
	// gettimeofday(&time, NULL);
	// printf("lol\n");
	// printf("%d\n", time.tv_usec);
	// printf("%ld\n", time.tv_sec);
}

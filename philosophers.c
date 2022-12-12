/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:29:02 by bgales            #+#    #+#             */
/*   Updated: 2022/12/12 16:38:58 by bgales           ###   ########.fr       */
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

void	meal_time(t_philo *philo)
{
	ft_print(philo, 'E');
	usleep(*philo->args->t_to_eat);
	ft_print(philo, 'S');
	usleep(*philo->args->t_to_sleep);
	ft_print(philo, 'T');
}
void	take_fork(t_philo *philo, int i)
{

	pthread_mutex_lock(&philo->args->fork_r[i]);
	ft_print(philo, 'F');
	pthread_mutex_lock(&philo->args->fork_l[i + 1]);
	ft_print(philo, 'F');
	meal_time(philo);
	pthread_mutex_unlock(&philo->args->fork_r[i]);
	pthread_mutex_unlock(&philo->args->fork_l[i + 1]);
}


void	*philo(void *philo)
{
	t_philo *a;
	a = philo;
	take_fork(a, a->nbr - 1);
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

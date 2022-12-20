/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:29:02 by bgales            #+#    #+#             */
/*   Updated: 2022/12/17 13:01:09 by bgales           ###   ########.fr       */
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

void	meal_time(t_philo *philo, int i)
{
	ft_print(philo, 'E');
	usleep(*philo->args->t_to_eat);
	philo->last_eat = ft_start_time();
	*philo->args->meal_count += 1;
	pthread_mutex_unlock(philo->args->fork_r[i]);
	pthread_mutex_unlock(&philo->args->fork_l[i]);
	ft_print(philo, 'S');
	usleep(*philo->args->t_to_sleep);
	ft_print(philo, 'T');
}

int	take_fork(t_philo *philo, int i)
{
	if (i % 2 == 0)
	{
		if (pthread_mutex_lock(philo->args->fork_r[i]) != 0)
		{
			printf("Mutex for~k r#%d error\n", i);
			return 1;
		}
		else
			ft_print(philo, 'F');
		if (pthread_mutex_lock(&philo->args->fork_l[i]) != 0)
	 	{
			printf("Mutex for~k r#%d error\n", i);
			return 1;
		}
		else
			ft_print(philo, 'F');
	}
	 else
	 {
	 	if(pthread_mutex_lock(&philo->args->fork_l[i]) != 0)
	 	{
	  		printf("Mutex fork l#%d error\n", i);
	 		ft_print(philo, 'F');
	 	}
		else
			ft_print(philo, 'F');

		if (pthread_mutex_lock(philo->args->fork_r[i]) != 0)
		{
			printf("Mutex for~k r#%d error\n", i);
			return 1;
		}
		else
			ft_print(philo, 'F');
	 }

		meal_time(philo, i);
		return 0;

}


void	*philo(void *philo)
{
	t_philo *a;
	a = philo;
	a->last_eat = ft_start_time();
	if(*a->args->nb_of_eat)
	{
		while(!*a->args->dead && *a->args->meal_count != *a->args->nb_of_eat)
		{
			take_fork(a, a->nbr - 1);
		}
	}
	else
	{
		while(!*a->args->dead)
			take_fork(a, a->nbr - 1);
	}
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

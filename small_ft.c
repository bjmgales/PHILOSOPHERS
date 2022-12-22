/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:27:40 by bgales            #+#    #+#             */
/*   Updated: 2022/12/22 13:46:49 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_start_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000000 + start.tv_usec);

}
long ft_time(long start_time)
{
	struct timeval end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000000 + end.tv_usec) - start_time);
}

void ft_print_info(t_info *args)
{
	int i;

	i = -1;

	while (++i < *args->fork_nbr)
	{
		printf("%dst philo has : %d fork number\n%ld time\n%d time to die\n%d time to eat\n%d time to sleep\n", args->philo[i].nbr,
		*args->philo[i].args->fork_nbr, ft_time(*args->philo[i].args->start),
		*args->philo[i].args->t_to_die, *args->philo[i].args->t_to_eat,
		*args->philo[i].args->t_to_sleep);
		printf("\n");
	}
}

void ft_print(t_philo *philo, int status)
{
	// if(!*philo->args->dead)
	// {
	// 	check_state(philo);
	// 	if(pthread_mutex_lock(philo->args->print) != 0)
	// 	{
	// 		printf("Mutex lock error\n");
	// 		return;
	// 	}
	// }
	pthread_mutex_lock(philo->args->print);
	if (!*philo->args->dead)
	{
		if (status == 'S')
			printf("%ld %d is sleeping\n", ft_time(*philo->args->start), philo->nbr);
		if (status == 'F')
			printf("%ld %d has taken a fork\n", ft_time(*philo->args->start), philo->nbr);
		if (status == 'T')
			printf("%ld %d is thinking\n", ft_time(*philo->args->start), philo->nbr);
		if (status == 'E')
			printf("%ld %d is eating\n", ft_time(*philo->args->start), philo->nbr);
	}
	pthread_mutex_unlock(philo->args->print);
	return;
}

void *is_dead(void *args)
{
	t_info	*a;
	int		i;

	a = args;
	i = -1;
	while (++i < *a->fork_nbr)
	{
		if (ft_time(a->philo[i].last_eat) > *a->t_to_die)
		{
			pthread_mutex_lock(a->print);
			printf("%d philo last eat :%ld\n", a->philo[i].nbr, ft_time(a->philo[i].last_eat));
			printf("t_to_die :%u\n", *a->t_to_die);
			printf("lol\n");
			printf("%ld %d died\n", ft_time(*a->start), a->philo[i].nbr);
			i = -1;
			while (++i < *a->fork_nbr)
				pthread_detach(a->philo[i].th);
			return (0);
		}
	}
	return 0;
}

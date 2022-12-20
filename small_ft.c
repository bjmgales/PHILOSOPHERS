/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:27:40 by bgales            #+#    #+#             */
/*   Updated: 2022/12/17 12:59:56 by bgales           ###   ########.fr       */
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

	if(pthread_mutex_lock(philo->args->print) != 0)
	{
		printf("Mutex lock error\n");
		return;
	}
	if (!check_state(philo))
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
	if (status == 'D')
		printf("%ld %d died\n", ft_time(*philo->args->start), philo->nbr);

	pthread_mutex_unlock(philo->args->print);
	return;
}

int check_state(void *philo)
{
	t_philo *a;
	int i;

	i = -1;
	a = philo;

	while (++i < *a->args->fork_nbr)
	{
		if (ft_time(a->last_eat) > *a->args->t_to_die || *a->args->meal_count > *a->args->nb_of_eat)
		{
		printf("%ld %d died\n", ft_time(*a->args->start), a->nbr);
			pthread_mutex_unlock(a->args->print);
			*a->args->dead = 1;
			return 1;
		}
	}
	return 0;
}

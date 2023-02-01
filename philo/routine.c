/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:16:56 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:39:36 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	meal_time(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data_lock);
	philo->last_eat = timestamp(philo->data->start);
	philo->has_eaten = 1;
	pthread_mutex_unlock(&philo->data_lock);
	ft_print(philo, 'E');
	time = ft_time();
	while (time_diff(time) < philo->data->t_to_eat)
		usleep(100);
	pthread_mutex_lock(&philo->hyper_lock);
	unlock_fork(philo);
	pthread_mutex_unlock(&philo->hyper_lock);
	ft_print(philo, 'S');
	time = ft_time();
	while (time_diff(time) < philo->data->t_to_sleep)
		usleep(100);
	ft_print(philo, 'T');
	return ;
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->nbr - 1]);
	ft_print(philo, 'F');
	pthread_mutex_lock(&philo->hyper_lock);
	if (philo->nbr == philo->data->fork_nbr)
	{
		pthread_mutex_lock(&philo->data->fork[0]);
		ft_print(philo, 'F');
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->nbr]);
		ft_print(philo, 'F');
	}
	pthread_mutex_unlock(&philo->hyper_lock);
	meal_time(philo);
	return ;
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = philo;
	if (ph->nbr % 2 != 0)
		usleep(20000);
	while (1)
		take_fork(ph);
	return (0);
}

void	*thread_launch(t_info data)
{
	int	i;

	i = -1;
	while (++i < data.fork_nbr)
	{
		data.philo[i].last_eat = timestamp(data.start);
		if (pthread_create(&data.philo[i].th, NULL,
				routine, (void *)&data.philo[i]) != 0)
		{
			printf("Error in thread#%d creation\n", i);
			return ((void *)(1));
		}
		usleep(10);
	}
	return (0);
}

void	*start_routine(t_info data)
{
	int			i;
	pthread_t	death_th;
	pthread_t	meal_th;

	i = -1;
	data.start = ft_time();
	philo_init(&data);
	thread_launch(data);
	if (pthread_create(&death_th, NULL, is_dead_two, (void *)&data) != 0)
		return ((void *)(1));
	if (data.must_eat != -1)
		if (pthread_create(&meal_th, NULL, meal_number, (void *)&data) != 0)
			printf("Error in death_check thread creation\n");
	pthread_mutex_lock(&data.dead);
	pthread_mutex_lock(&data.dead);
	while (++i < data.fork_nbr)
		pthread_detach(data.philo[i].th);
	pthread_mutex_lock(&data.bool_lock);
	if (data.eat_bool)
		pthread_join(meal_th, NULL);
	if (data.death_bool)
		pthread_join(death_th, NULL);
	pthread_mutex_unlock(&data.bool_lock);
	return (0);
}

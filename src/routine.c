/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:16:56 by bgales            #+#    #+#             */
/*   Updated: 2023/02/13 16:40:16 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_lock);
	philo->last_eat = timestamp(philo->data->start);
	philo->has_eaten = 1;
	philo->eat_nbr++;
	pthread_mutex_unlock(&philo->data_lock);
	print_eat(philo);
	custom_sleeper(philo->data->t_to_eat);
	pthread_mutex_lock(&philo->hyper_lock);
	unlock_fork(philo);
	pthread_mutex_unlock(&philo->hyper_lock);
	print_sleep(philo);
	custom_sleeper(philo->data->t_to_sleep);
	print_think(philo);
	return ;
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->hyper_lock);
	take_fork_r(philo);
	take_fork_l(philo);
	pthread_mutex_unlock(&philo->hyper_lock);
	meal_time(philo);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = philo;
	pthread_mutex_lock(&ph->data_lock);
	ph->last_eat = timestamp(ph->data->start);
	pthread_mutex_unlock(&ph->data_lock);
	if (ph->nbr % 2 == 0)
		custom_sleeper(8);
	while (1)
		take_fork(ph);
	return (0);
}

void	*thread_launch(t_info d)
{
	int	i;

	i = -1;
	while (++i < d.fork_nbr)
	{
		pthread_create(&d.philo[i].th, NULL, routine, (void *)&d.philo[i]);
		usleep(10);
	}
	return (0);
}

void	*start_routine(t_info data)
{
	int			i;
	pthread_t	death_th;

	i = -1;
	data.start = ft_time();
	philo_init(&data);
	thread_launch(data);
	pthread_create(&death_th, NULL, is_dead_two, (void *)&data);
	pthread_mutex_lock(&data.dead);
	pthread_mutex_lock(&data.dead);
	while (++i < data.fork_nbr)
		pthread_detach(data.philo[i++].th);
	pthread_join(death_th, NULL);
	return (0);
}

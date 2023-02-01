/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:36:40 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:46:47 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*stop_signal_d(t_info *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->bool_lock);
	data->death_bool = 1;
	pthread_mutex_unlock(&data->bool_lock);
	printf(BOLD"%ld %d died\n", timestamp(data->start), data->philo->nbr);
	while (++i < data->fork_nbr)
	{
		pthread_mutex_unlock(&data->philo[i].hyper_lock);
		pthread_mutex_lock(&data->philo[i].hyper_lock);
	}
	return (0);
}

void	stop_signal_e(t_info *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->bool_lock);
	data->eat_bool = 1;
	pthread_mutex_unlock(&data->bool_lock);
	while (++i < data->fork_nbr)
	{
		pthread_mutex_unlock(&data->philo[i].hyper_lock);
		pthread_mutex_lock(&data->philo[i].hyper_lock);
	}
	printf(BOLD"\n\t  PHILOSOPHERS HAVE EATEN ENOUGH !\n");
	i = -1;
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->nbr - 1]);
	if (philo->nbr == philo->data->fork_nbr)
	{
		pthread_mutex_unlock(&philo->data->fork[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->nbr]);
	}
}
// void	*meal_death_threads(t_info *data)
// {
// 	pthread_t	*d_th;
// 	pthread_t	*m_th;

// 	if (pthread_create(d_th, NULL, is_dead_two, (void *)data) != 0)
// 	{
// 		printf("Error in death_check thread creation\n");
// 		return ((void *)(1));
// 	}
// 	if (data->must_eat > 0)
// 	{
// 		printf("lol\n");
// 		if (pthread_create(m_th, NULL, meal_number, (void *)data) != 0)
// 		{
// 			printf("Error in death_check thread creation\n");
// 			return ((void *)(1));
// 		}
// 	}
// 	pthread_mutex_lock(&data->dead);
// 	pthread_mutex_lock(&data->dead);
// 	end_thread(data, d_th, m_th);
// 	return (0);
// }

// void	end_thread(t_info *data, pthread_t death_th, pthread_t meal_th)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->fork_nbr)
// 		pthread_detach(data->philo[i].th);
// 	pthread_mutex_lock(&data->bool_lock);
// 	if (data->eat_bool)
// 		pthread_join(meal_th, NULL);
// 	if (data->death_bool)
// 		pthread_join(death_th, NULL);
// 	pthread_mutex_unlock(&data->bool_lock);
// }

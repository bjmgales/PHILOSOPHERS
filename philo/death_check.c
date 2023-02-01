/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:36:29 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:32:57 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*meal_number(void *args)
{
	t_info	*data;
	int		i;
	int		sum;

	sum = 0;
	i = 0;
	data = args;
	while (1)
	{
		if (i == data->fork_nbr)
			i = 0;
		pthread_mutex_lock(&data->philo[i].data_lock);
		if (data->philo[i].has_eaten)
			sum++;
		data->philo[i].has_eaten = 0;
		if (sum == data->must_eat)
		{
			stop_signal_e(data);
			pthread_mutex_unlock(&data->dead);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].data_lock);
		i++;
	}
}

void	*is_dead_two(void *args)
{
	t_info	*data;
	int		i;

	i = 0;
	data = args;
	while (1)
	{
		if (i == data->fork_nbr)
			i = 0;
		pthread_mutex_lock(&data->philo[i].data_lock);
		if ((timestamp(data->start) - data->philo[i].last_eat) > data->t_to_die)
		{
			stop_signal_d(data);
			pthread_mutex_unlock(&data->dead);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].data_lock);
		i++;
	}
	return (0);
}

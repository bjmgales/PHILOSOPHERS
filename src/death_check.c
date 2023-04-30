/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:36:29 by bgales            #+#    #+#             */
/*   Updated: 2023/02/13 17:12:13 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_check(t_info *data, int i, int sum)
{
	data->philo[i].has_eaten = 0;
	if (sum >= data->must_eat && data->must_eat != -1)
	{
		if (!stop_signal_e(data))
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
	}
	return (0);
}

int	death_check(t_info *data, int i)
{
	if ((timestamp(data->start) - data->philo[i].last_eat) > data->t_to_die)
	{
		stop_signal_d(data, i);
		return (1);
	}
	return (0);
}

void	*is_dead_two(void *args)
{
	t_info	*data;
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	data = args;
	while (1)
	{
		if (i >= data->fork_nbr)
			i = 0;
		pthread_mutex_lock(&data->philo[i].data_lock);
		if (data->philo[i].has_eaten)
			sum++;
		if (eat_check(data, i, sum) || death_check(data, i))
			return (0);
		pthread_mutex_unlock(&data->philo[i].data_lock);
		i++;
	}
	return (0);
}

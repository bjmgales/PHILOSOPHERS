/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:36:40 by bgales            #+#    #+#             */
/*   Updated: 2023/02/13 17:13:03 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_lock(t_info *data, char c)
{
	int	i;

	i = -1;
	if (c == 'L')
	{
		while (++i < data->fork_nbr)
		{
			pthread_mutex_unlock(&data->philo[i].data_lock);
			pthread_mutex_lock(&data->philo[i].data_lock);
		}
	}
	if (c == 'U')
		while (++i < data->fork_nbr)
			pthread_mutex_unlock(&data->philo[i].data_lock);
	return ;
}

void	hyper_bool_lock(t_info *data)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&data->death_lock);
	pthread_mutex_lock(&data->death_lock);
	pthread_mutex_unlock(&data->print_lock);
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_unlock(&data->bool_lock);
	pthread_mutex_lock(&data->bool_lock);
	data->eat_bool = 1;
	data->death_bool = 1;
	pthread_mutex_unlock(&data->bool_lock);
	data->fkn_stop = 1;
	return ;
}

void	*stop_signal_d(t_info *data, int c)
{
	int	i;

	i = -1;
	hyper_bool_lock(data);
	data_lock(data, 'L');
	usleep(1000);
	printf("%ld %d died\n", timestamp(data->start), data->philo[c].nbr);
	pthread_mutex_unlock(&data->dead);
	return (0);
}

int	stop_signal_e(t_info *d)
{
	int	i;

	i = 0;
	data_lock(d, 'L');
	while (d->philo[i].eat_nbr >= d->must_eat / d->fork_nbr)
	{
		i++;
		if (i == d->fork_nbr)
			break ;
	}
	if (i < d->fork_nbr)
	{
		data_lock(d, 'U');
		return (1);
	}
	i = -1;
	hyper_bool_lock(d);
	usleep(1000);
	printf("\n\t  PHILOSOPHERS HAVE EATEN ENOUGH !\n");
	pthread_mutex_unlock(&d->dead);
	return (0);
}

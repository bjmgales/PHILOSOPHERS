/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:36:29 by bgales            #+#    #+#             */
/*   Updated: 2023/01/28 16:41:04 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*meal_number(void *args)
{
	t_info *data;
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
		if(sum == data->must_eat)
		{
			pthread_mutex_lock(&data->bool_lock);
			data->eat_bool = 1;
			pthread_mutex_unlock(&data->bool_lock);
			pthread_mutex_lock(&data->print_lock);
			printf(BOLD"\n\t  PHILOSOPHERS HAVE EATEN ENOUGH !\n");
			i = -1;
			while (++i < data->fork_nbr)
			{
			 	pthread_mutex_unlock(&data->philo[i].hyper_lock);
				pthread_mutex_lock(&data->philo[i].hyper_lock);
			}
			pthread_mutex_unlock(&data->dead);
			return 0;
		}
		pthread_mutex_unlock(&data->philo[i].data_lock);
		i++;
	}
}


void	*is_dead_two(void *args)
{
	t_info *data;
	int		i;

	i = 0;
	data = args;
	while (1)
	{
		if (i == data->fork_nbr)
			i = 0;
		pthread_mutex_lock(&data->philo[i].data_lock);
		if((timestamp(data->start) - data->philo[i].last_eat) > data->t_to_die)
		{
			pthread_mutex_lock(&data->bool_lock);
			data->death_bool = 1;
			pthread_mutex_unlock(&data->bool_lock);
			pthread_mutex_lock(&data->print_lock);
			printf(RED"%ld %d died\t \t  LAST EAT : %ld ms\n",
			timestamp(data->start), data->philo[i].nbr, (timestamp(data->start) - data->philo[i].last_eat));
			 i = -1;
			 while (++i < data->fork_nbr)
			 {
			 	pthread_mutex_unlock(&data->philo[i].hyper_lock);
			 	pthread_mutex_lock(&data->philo[i].hyper_lock);
			 }
			pthread_mutex_unlock(&data->dead);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].data_lock);
		i++;
	}

	return 0;
}

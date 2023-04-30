/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:11:08 by bgales            #+#    #+#             */
/*   Updated: 2023/02/13 14:47:01 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork_r(t_philo *ph)
{
	if (ph->nbr == ph->data->fork_nbr)
	{
		pthread_mutex_lock(&ph->data->fork[0]);
		print_fork(ph);
	}
	else
	{
		pthread_mutex_lock(&ph->data->fork[ph->nbr]);
		print_fork(ph);
	}
	return (0);
}

int	take_fork_l(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->fork[ph->nbr - 1]);
	print_fork(ph);
	return (0);
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

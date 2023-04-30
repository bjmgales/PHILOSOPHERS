/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:48:19 by bgales            #+#    #+#             */
/*   Updated: 2023/02/13 16:30:25 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_lock);
	pthread_mutex_unlock(&philo->data_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d is eating\n", timestamp(philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_lock);
	pthread_mutex_unlock(&philo->data_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d is sleeping \n", timestamp(philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_lock);
	pthread_mutex_unlock(&philo->data_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d is thinking\n", timestamp(philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_lock);
	pthread_mutex_unlock(&philo->data_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d has taken a fork\n",
		timestamp(philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->print_lock);
}

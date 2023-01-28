/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:20:57 by bgales            #+#    #+#             */
/*   Updated: 2023/01/28 15:37:27 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void unlock_fork(t_philo *philo)
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

void mutex_destroy(t_info *data)
{
	int i = -1;

	while (++i < data->fork_nbr)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_detach(data->philo[i].th);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_unlock(&data->print_lock);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print_lock);
}
int main(int argc, char **argv)
{
	t_info	data;
	if (parsing(argc, argv))
		return (1);
	data = args_init(argv);
	if (data.must_eat == 0 || data.fork_nbr == 0 || data.t_to_die == 0
		||data.t_to_eat == 0 || data.t_to_sleep == 0 )
	{
		printf(BOLD"\n\t\tCan't put a \"0\" in args.\n\n");
		return (1);
	}
	malloc_data(&data);
	mutex_init(&data);
	start_routine(data);
	return (0);
}
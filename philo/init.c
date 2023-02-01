/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:36:40 by bgales            #+#    #+#             */
/*   Updated: 2023/01/29 16:45:40 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	malloc_data(t_info *data)
{
	data->philo = malloc(sizeof(t_philo) * data->fork_nbr);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->fork_nbr);
}

void	mutex_init(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->fork_nbr)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->philo[i].data_lock, NULL);
		pthread_mutex_init(&data->philo[i].hyper_lock, NULL);
	}
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->bool_lock, NULL);
	return ;
}

void	philo_init(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->fork_nbr)
	{
		data->philo[i].nbr = i + 1;
		data->philo[i].data = data;
	}
	return ;
}

t_info	args_init(char **argv)
{
	t_info	ret;

	ret.fork_nbr = ft_atoi(argv[1]);
	ret.t_to_die = ft_atoi(argv[2]);
	ret.t_to_eat = ft_atoi(argv[3]);
	ret.t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ret.must_eat = ft_atoi(argv[5]) * ret.fork_nbr;
	else
		ret.must_eat = -1;
	ret.eat_bool = 0;
	ret.death_bool = 0;
	return (ret);
}

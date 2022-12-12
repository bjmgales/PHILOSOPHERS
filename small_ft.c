/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:27:40 by bgales            #+#    #+#             */
/*   Updated: 2022/12/12 16:18:05 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
long ft_start_time()
{
	struct timeval start;

	gettimeofday(&start, NULL);
	return(start.tv_sec * 1000000 + start.tv_usec);

}
long ft_time(long start_time)
{
	struct timeval end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000000 + end.tv_usec) - start_time);
}

void ft_print_info(t_info *args)
{
	int i;

	i = -1;

	while (++i < *args->fork_nbr)
	{
		printf("%dst philo has : %d fork number\n%ld time\n%d time to die\n%d time to eat\n%d time to sleep\n", args->philo[i].nbr,
		*args->philo[i].args->fork_nbr, ft_time(*args->philo[i].args->start),
		*args->philo[i].args->t_to_die, *args->philo[i].args->t_to_eat,
		*args->philo[i].args->t_to_sleep);
		printf("\n");
	}
}

void ft_print(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->args->print);
	if (status == 'S')
		printf("%ld %d is sleeping\n", ft_time(*philo->args->start), philo->nbr);

	if (status == 'F')
		printf("%ld %d has taken a fork\n", ft_time(*philo->args->start), philo->nbr);
	if (status == 'T')
		printf("%ld %d is thinking\n", ft_time(*philo->args->start), philo->nbr);
	if (status == 'E')
		printf("%ld %d is eating\n", ft_time(*philo->args->start), philo->nbr);
	pthread_mutex_unlock(&philo->args->print);


}
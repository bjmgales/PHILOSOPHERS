/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:27:38 by bgales            #+#    #+#             */
/*   Updated: 2023/02/01 13:36:08 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long	time_diff(long start)
{
	long	current_time;

	current_time = ft_time();
	return (current_time - start);
}

long	ft_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

long	timestamp(long start_time)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - start_time);
}

void	ft_print(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (status == 'E')
		printf(GREEN"%ld %d is eating\n",
			timestamp(philo->data->start), philo->nbr);
	if (status == 'F')
		printf(BLUE"%ld %d has taken a fork\n",
			timestamp(philo->data->start), philo->nbr);
	if (status == 'S')
		printf(YELLOW"%ld %d is sleeping\n",
			timestamp(philo->data->start), philo->nbr);
	if (status == 'T')
		printf(MAGENTA"%ld %d is thinking\n",
			timestamp(philo->data->start), philo->nbr);
	pthread_mutex_unlock(&philo->data->print_lock);
	return ;
}

int	ft_atoi(const char *str)
{
	long	sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= 48 && str[i] <= 57))
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (result * sign > __INT32_MAX__ || result * sign < INT32_MIN)
		return (0);
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:27:38 by bgales            #+#    #+#             */
/*   Updated: 2023/02/10 15:06:14 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	custom_sleeper(int time_ms)
{
	struct timeval	temp;
	long int		start_time;

	gettimeofday(&temp, NULL);
	start_time = ((long int)temp.tv_usec / 1000)
		+ ((long int)temp.tv_sec * 1000);
	usleep((float)time_ms * 950);
	while (((long int)temp.tv_usec / 1000)
		+ ((long int)temp.tv_sec * 1000) - start_time < (time_ms))
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	return (0);
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

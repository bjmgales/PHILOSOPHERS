/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:27:40 by bgales            #+#    #+#             */
/*   Updated: 2022/12/09 14:22:02 by bgales           ###   ########.fr       */
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
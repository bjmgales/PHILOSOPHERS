/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:46:07 by bgales            #+#    #+#             */
/*   Updated: 2022/12/10 11:57:25 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/syscall.h>
# include <sys/types.h>

typedef struct s_philo
{
	pthread_t		th;
	int				nbr;
	int				*fork_r;
	int				fork_l;
}		t_philo;

typedef struct s_lst
{
	long			start;
	int				*fork;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	nb_of_eat;
	t_philo			*philo;
}		t_info;

int		ft_atoi(const char *str);
void	args_init(t_info *args, char **argv);
void	*thread_init(t_info args);
void	*philo(t_info args, int i);
long	ft_time(long start);
long	ft_start_time();


#endif

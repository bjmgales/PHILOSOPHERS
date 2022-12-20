/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:46:07 by bgales            #+#    #+#             */
/*   Updated: 2022/12/17 12:34:06 by bgales           ###   ########.fr       */
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

struct s_lst;

typedef struct s_philo
{
	pthread_t		th;
	struct s_lst	*args;
	int				nbr;
	long			last_eat;
}		t_philo;

typedef struct s_lst
{
	long			*start;
	int				*fork_nbr;
	unsigned int	*t_to_die;
	unsigned int	*t_to_eat;
	unsigned int	*t_to_sleep;
	unsigned int	*nb_of_eat;
	unsigned int	*meal_count;
	int				*dead;
	pthread_mutex_t	**fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t *print;
	t_philo			*philo;
}		t_info;

int		ft_atoi(const char *str);
void 	ft_print_info(t_info *args);
void 	*test(void *args);
void	args_init(t_info *args, char **argv);
void	*thread_init(t_info args);
void	*philo(void *args);
long	ft_time(long start);
long	ft_start_time();
void 	ft_print(t_philo *philo, int status);
int 	check_state(void *philo);


#endif

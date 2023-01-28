/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:46:07 by bgales            #+#    #+#             */
/*   Updated: 2023/01/28 11:10:00 by bgales           ###   ########.fr       */
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

#define RESET   "\033[0m"
#define BLACK   "\033[1m\033[30m"      /* Bold Black */
#define RED     "\033[1m\033[31m"      /* Bold Red */
#define GREEN   "\033[1m\033[32m"      /* Bold Green */
#define YELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BLUE    "\033[1m\033[34m"      /* Bold Blue */
#define MAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define CYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLD    "\033[1m\033[37m"      /* Bold White */

struct	s_lst;
typedef struct s_philo
{
	struct s_lst	*data;
	pthread_t		th;
	int				nbr;
	long			last_eat;
	int				has_eaten;
	int				nb_of_eat;
	pthread_mutex_t data_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t hyper_lock;

}		t_philo;

typedef struct s_lst
{
	long			start;
	int				death_bool;
	int				eat_bool;
	int				fork_nbr;
	int				must_eat;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	pthread_mutex_t	*fork;
	pthread_mutex_t bool_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t dead;
	t_philo			*philo;
}		t_info;

int		parsing(int argc, char **argv);
int		ft_atoi(const char *str);
t_info	args_init(char **argv);
void	philo_init(t_info *data);
void	malloc_data(t_info *data);
void	mutex_init(t_info *data);
void	*start_routine(t_info data);
long	timestamp(long start_time);
void	ft_print(t_philo *philo, int status);
long	ft_time(void);
void	*meal_number(void *args);
void	*is_dead_two(void *args);
void 	mutex_destroy(t_info *data);
long 	time_diff(long start);
void 	unlock_fork(t_philo *philo);
#endif

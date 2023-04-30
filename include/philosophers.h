/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:46:07 by bgales            #+#    #+#             */
/*   Updated: 2023/04/30 13:34:19 by bgales           ###   ########.fr       */
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

struct	s_lst;
typedef struct s_philo
{
	struct s_lst	*data;
	pthread_t		th;
	int				nbr;
	int				eat_nbr;
	long			last_eat;
	int				has_eaten;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	hyper_lock;

}		t_philo;

typedef struct s_lst
{
	long			start;
	int				death_bool;
	int				eat_bool;
	int				fork_nbr;
	int				must_eat;
	int				fkn_stop;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	pthread_mutex_t	*fork;
	pthread_mutex_t	bool_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead;
	pthread_mutex_t	death_lock;
	t_philo			*philo;
}		t_info;

/**
@brief Check if a philosopher has eaten enough and should stop eating
 *
@param data A pointer to the struct containing the data of the simulation
@param i The index of the philosopher to check
@param sum The number of philosophers that have eaten so far
 *
@return 0 if the philosopher can keep eating, 1 if they should stop
 */
int	eat_check(t_info *data, int i, int sum);

/**
@brief Check if a philosopher has died
 *
@param data A pointer to the struct containing the data of the simulation
@param i The index of the philosopher to check
 *
@return 0 if the philosopher is still alive, 1 if they have died
 */
int	death_check(t_info *data, int i);

/**
@brief Check if any philosophers have died or if they have all eaten enough
 *
@param args A pointer to the struct containing the data of the simulation
 *
@return NULL
 */
void	*is_dead_two(void *args);

/**
@brief Lock the right fork of the philosopher
 *
@param ph A pointer to the struct representing the philosopher
 *
@return 0
 */
int	take_fork_r(t_philo *ph);

/**
@brief Lock the left fork of the philosopher
 *
@param ph A pointer to the struct representing the philosopher
 *
@return 0
 */
int	take_fork_l(t_philo *ph);

/**
@brief Unlock the forks of the philosopher
 *
@param philo A pointer to the struct representing the philosopher
 *
@return NULL
 */
void	unlock_fork(t_philo *philo);

/**
@brief Allocate memory for the data of the simulation
 *
@param data A pointer to the struct containing the data of the simulation
 *
@return NULL
 */
void	malloc_data(t_info *data);

/**
@brief Initialize the mutexes used by the simulation
 *
@param data A pointer to the struct containing the data of the simulation
 *
@return NULL
 */
void	mutex_init(t_info *data);

/**
@brief Initialize the philosophers of the simulation
 *
@param data A pointer to the struct containing the data of the simulation
 *
@return NULL
 */
void	philo_init(t_info *data);

/**
@brief Initialize the data of the simulation based on the command-line arguments
 *
@param argv An array of strings containing the command-line arguments
 *
@return A struct containing the initialized data
 */
t_info	args_init(char **argv);

/**
@brief Locks and unlocks various mutexes for the provided t_info struct.
       Sets the eat_bool and death_bool values to 1 and fkn_stop to 1.
 *
@param data a pointer to a t_info struct to be updated
 *
@return void
 */
void	hyper_bool_lock(t_info *data);

/**
@brief Prints the message "<timestamp> <philosopher_number> died" to stdout
       and unlocks the dead mutex. Returns NULL.
 *
@param data a pointer to a t_info struct to be used for the print
@param c an integer specifying the index of the philosopher in the philosopher array that has died
 *
@return NULL
 */
void	*stop_signal_d(t_info *data, int c);

/**
@brief Checks if all philosophers have eaten the required number of times.
       If they have, prints the message "PHILOSOPHERS HAVE EATEN ENOUGH!"
       to stdout and unlocks the dead mutex. Returns 0 if all philosophers have eaten
       the required number of times, else returns 1.
 *
@param d a pointer to a t_info struct to be used for the check
 *
@return int 0 if all philosophers have eaten the required number of times, else 1.
 */
int	stop_signal_e(t_info *d);

/**
@brief Parses the command line arguments passed to the program.
       Returns 0 if the parsing was successful, else 1.
 *
@param argc an integer containing the number of command line arguments
@param argv an array of strings containing the command line arguments
 *
@return int 0 if the parsing was successful, else 1.
 */
int	parsing(int argc, char **argv);

/**
@brief Locks and unlocks the data and print_lock mutexes of the t_philo struct provided,
       then prints the message "<timestamp> <philosopher_number> is eating" to stdout.
 *
@param philo a pointer to a t_philo struct to be used for the print
 *
@return void
 */
void	print_eat(t_philo *philo);

/**
@brief Locks and unlocks the data and print_lock mutexes of the t_philo struct provided,
       then prints the message "<timestamp> <philosopher_number> is sleeping" to stdout.
 *
@param philo a pointer to a t_philo struct to be used for the print
 *
@return void
 */
void	print_sleep(t_philo *philo);

/**
@brief Locks and unlocks the data and print_lock mutexes of the t_philo struct provided,
       then prints the message "<timestamp> <philosopher_number> is thinking" to stdout.
 *
@param philo a pointer to a t_philo struct to be used for the print
 *
@return void
 */
void	print_think(t_philo *philo);

/**
@brief Prints a message indicating that the philosopher has taken a fork.
 *
@param philo a pointer to a `t_philo` structure representing the philosopher
 *
@return void
 */
void print_fork(t_philo *philo);

/**
@brief Simulates the philosopher's meal time, by locking and unlocking mutexes,
updating the last_eat, has_eaten, and eat_nbr fields of the `t_philo` structure,
calling the `print_eat` function, sleeping for a certain amount of time using the `custom_sleeper` function,
unlocking the forks using the `unlock_fork` function, and calling the `print_sleep` and `print_think` functions.
 *
@param philo a pointer to a `t_philo` structure representing the philosopher
 *
@return void
 */
void meal_time(t_philo *philo);

/**
@brief Takes the forks in the right and left of the philosopher,
using the `take_fork_r` and `take_fork_l` functions, respectively,
and then calls the `meal_time` function.
 *
@param philo a pointer to a `t_philo` structure representing the philosopher
 *
@return void
 */
void take_fork(t_philo *philo);

/**
@brief The main function of the philosopher thread,
which initializes the last_eat field of the `t_philo` structure,
sleeps for 8 milliseconds if the philosopher number is even,
and then repeatedly calls the `take_fork` function.
 *
@param philo a pointer to a `t_philo` structure representing the philosopher
 *
@return void*
 */
void *routine(void *philo);

/**
@brief Launches the threads representing the philosophers,
by creating them using the `pthread_create` function with the `routine` function as argument,
and then sleeps for a short amount of time using the `usleep` function.
 *
@param d a `t_info` structure representing the data needed for the simulation
 *
@return void*
 */
void *thread_launch(t_info d);

/**
@brief The main function of the program,
which initializes the data, launches the threads using the `thread_launch` function,
and waits for the death of a philosopher thread using the `pthread_join` function.
 *
@param data a `t_info` structure representing the data needed for the simulation
 *
@return void*
 */
void *start_routine(t_info data);

/**
@brief A custom sleeper function,
which sleeps for a certain amount of time in milliseconds,
by using the `usleep` and `gettimeofday` functions.
 *
@param time_ms the amount of time to sleep in milliseconds
 *
@return int 0 if successful
 */
int custom_sleeper(int time_ms);

/**
@brief Returns the current time in milliseconds,
by using the `gettimeofday` function.
 *
@return long the current time in milliseconds
 */
long ft_time(void);

/**
@brief Returns the current time in milliseconds since the start of the simulation,
by subtracting the start time from the current time using the `gettimeofday` function.
 *
@param start_time the start time of the simulation in milliseconds
 *
@return long the current time in milliseconds since the start of the simulation
 */
long timestamp(long start_time);

/**
@brief Converts the initial portion of the string pointed to by str to int representation.
@param str The string to convert.
@return The converted integer value, or 0 if the conversion fails.
 */
int ft_atoi(const char *str);

#endif

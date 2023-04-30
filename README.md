# PHILOSOPHERS

In this project, you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.

| Program name | `philo` |
|:--- |:--- |
| **Turn in files** | `Makefile, *.h, *.c, in directory philo/` |
| **Arguments** | `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]` |
| **Makefile** | `NAME, all, clean, fclean, re` |
| **External functions** | `memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock` |
| **Libft authorized** | `No` |
| **Description** | `Philosophers with threads and mutexes` |

## Common instructions 
<details>
<summary>see more</summary>
  
* Your project must be written in accordance with the Norm. If you have bonus
files/functions, they are included in the norm check and you will receive a 0 if there
is a norm error inside.
* Your functions should not quit unexpectedly (segmentation fault, bus error, double
free, etc) apart from undefined behaviors. If this happens, your project will be
considered non functional and will receive a 0 during the evaluation.
* All heap allocated memory space must be properly freed when necessary. No leaks
will be tolerated.
* If the subject requires it, you must submit a Makefile which will compile your
source files to the required output with the flags -Wall, -Wextra and -Werror, and
your Makefile must not relink.
* Your Makefile must at least contain the rules $(NAME), all, clean, fclean and
re.
* To turn in bonuses to your project, you must include a rule bonus to your Makefile,
which will add all the various headers, librairies or functions that are forbidden on
the main part of the project. Bonuses must be in a different file _bonus.{c/h}.
Mandatory and bonus part evaluation is done separately.
* If your project allows you to use your libft, you must copy its sources and its
associated Makefile in a libft folder with its associated Makefile. Your project’s
Makefile must compile the library by using its Makefile, then compile the project.
* We encourage you to create test programs for your project even though this work
won’t have to be submitted and won’t be graded. It will give you a chance
to easily test your work and your peers’ work. You will find those tests especially
useful during your defence. Indeed, during defence, you are free to use your tests
and/or the tests of the peer you are evaluating.
* Submit your work to your assigned git repository. Only the work in the git repository will be graded. If Deepthought is assigned to grade your work, it will be done
after your peer-evaluations. If an error happens in any section of your work during
Deepthought’s grading, the evaluation will stop.
</details>

## Global rules
<details>
<summary>see more</summary>
You have to write a program for the mandatory part and another one for the bonus part
(if you decide to do the bonus part). They both have to comply with the following rules:
* Global variables are forbidden!  
Your(s) program(s) should take the following arguments: 
* number_of_philosophers 
* me_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
* number_of_philosophers: The number of philosophers and also the number
of forks.
* time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
* time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
* number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
* Each philosopher has a number ranging from 1 to number_of_philosophers.
* Philosopher number 1 sits next to philosopher number number_of_philosophers.  
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
About the logs of your program:
* Any state change of a philosopher must be formatted as follows:
* timestamp_in_ms X has taken a fork
* timestamp_in_ms X is eating
* timestamp_in_ms X is sleeping
* timestamp_in_ms X is thinking
* timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
* Again, philosophers should avoid dying!
</details>

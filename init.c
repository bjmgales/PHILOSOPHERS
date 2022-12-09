/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:14 by bgales            #+#    #+#             */
/*   Updated: 2022/12/08 18:29:29 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	args_init(t_info *args, char **argv)
{
	int	i;

	i = -1;
	args->fork = ft_atoi(argv[1]);
	args->philo = malloc
	args->t_to_die = ft_atoi(argv[2]);
	args->t_to_eat = ft_atoi(argv[3]);
	args->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->nb_of_eat = ft_atoi(argv[5]);

}
void *thread_init(t_info args)
{
	pthread_t 	th[args.fork - 1];
	int			i;

	i = args.fork;
	while (--i > -1)
	{
		if(pthread_create(&th[i],NULL, philo(args), NULL) != 0)
		{
			printf("Error in Thread#%D creation. \n", i);
			return (void *)(1);
		}
		printf("%d, %p\n",i,  th[i]);
	}
	printf("lol\n");
	i = args.fork;
	while (--i > -1)
	{
	printf("%d\n", i);
		if(pthread_join(th[i], NULL) != 0)
		{
			printf("Error in Thread#%D join. \n", i);
			return (void *)(1);
		}
	}

	return (void *)(0);
}


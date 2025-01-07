/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:15:24 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/07 03:23:42 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(s_philo *philo, int argc, char **argv)
{
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->meals = 0;
	if (argc == 6)
		philo->meals = ft_atoi(argv[5]);
}

void	creat_philosophers(s_philo *philo)
{
	int i;

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);


	i = philo->philo_num;
	while (i--)
	{
		// if (pthread_create(philo[i]->philo_id, NULL, &routine, &philo[i]) != 0)
		// {
		// 	printf("Error\n : pthread_create failed\n");
		// 	return ;
		// }
	}
	
}


int	main(int argc, char **argv)
{
	s_philo		philo;
	int			i;
	
	if (argc < 5 || argc > 6)
	{
		printf("Error\n : invalid number of argument\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (check_num(argv[i]))
			return (1);
		i++;
	}
	memset(&philo, 0, sizeof(philo));
	init_philo(&philo, argc, argv);
	
	return (0);
}

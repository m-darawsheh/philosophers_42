/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:15:24 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/29 19:29:46 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atoi(argv[1]);
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
	if(!table->philosophers)
	{
		printf("Error\n : malloc failed\n");
		return ;
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if(!table->forks)
	{
		printf("Error\n : malloc failed\n");
		return ;
	}
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->times_start = get_time();
	table->meals = 0;
	table->there_is_meal = 0;
	table->is_dead = 1;
	if (argc == 6)
	{
		table->meals = (ft_atoi(argv[5]) * table->num_philosophers);
		table->there_is_meal = 1;
	}
}

int	main(int argc, char **argv)
{
	t_table		table;
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
	if (ft_atoi(argv[1]) == 1)
	{
		// usleep (ft_atoi(argv[2]) * 1000);
		printf( "[%s] \t philo id 1 is dead\n", argv[2]);
		return (0);
	}
	else
	{
		init_args(&table, argc, argv);
		creat_philo(&table);
	}
	printf("[-----this is procece not thread-----]");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:15:24 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/11 16:42:19 by mdarawsh         ###   ########.fr       */
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
	table->meals = 0;
	if (argc == 6)
		table->meals = ft_atoi(argv[5]);
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
	init_args(&table, argc, argv);
	
	return (0);
}

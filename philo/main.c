/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:15:24 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/17 18:45:12 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_table *table, int argc, char **argv)
{
	table->numbers = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philosopher) * table->numbers);
	if (!table->philo)
	{
		printf("Error\n : malloc failed\n");
		return ;
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->numbers);
	if (!table->forks)
	{
		printf("Error\n : malloc failed\n");
		return ;
	}
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->times_start = get_time();
	table->number_of_meals = 0;
	table->there_is_meal = 0;
	table->is_dead = 1;
	table->all_philo_eatn = 1;
	if (argc == 6)
	{
		table->number_of_meals = ft_atoi(argv[5]);
		table->there_is_meal = 1;
	}
}

void	init_and_create(t_table *t_table, int argc, char **argv)
{
	init_args(t_table, argc, argv);
	creat_philo(t_table);
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
		usleep(ft_atoi(argv[3]) * 1000);
		printf("[%s] \t philo id 1 is dead\n", argv[2]);
		return (0);
	}
	else
		init_and_create(&table, argc, argv);
	return (0);
}

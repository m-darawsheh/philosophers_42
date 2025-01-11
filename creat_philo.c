/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/11 17:12:45 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creat_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].philosopher, NULL, "routine", &table->philosophers[i]);
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_philosophers];
		table->philosophers[i].last_meal = 0;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].philosopher, NULL);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:06:58 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/10 16:28:37 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_routine(t_table *table, int l)
{
	pthread_mutex_lock(&table->write_mutex);
	int	current_time;
	current_time = get_time();
	if ((current_time - table->philo[l].when_ate) > table->time_to_die)
	{
		pthread_mutex_lock(&table->spare);
		table->is_dead = 0;
		pthread_mutex_unlock(&table->spare);
		printf("[%d] philo number %d is dead\n",
			current_time - table->times_start,
			table->philo[l].id);
		pthread_mutex_unlock(&table->write_mutex);
		return (0);
	}
	if (table->meals == 0 && table->there_is_meal)
	{
		table->is_dead = 0;
		table->there_is_meal = 0;
		pthread_mutex_unlock(&table->write_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->write_mutex);
	return (1);
}

void	*r_routine(void *args)
{
	int		l;
	t_table	*table;

	table = (t_table *)args;
	while (table->there_is_meal || table->is_dead)
	{
		// pthread_mutex_lock(&table->spare);
		l = 0;
		while (l < table->numbers)
		{
			if (!exit_routine(table, l))
				return (NULL);
			l++;
		}
		usleep(100);
	}
	return (NULL);
}

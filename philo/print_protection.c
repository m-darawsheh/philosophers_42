/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_protection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:55 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/17 18:54:57 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protected_print(t_table *table, int philo_id, char *msg, char *color)
{
	pthread_mutex_lock(&table->is_dead_mutex);
	if (!table->is_dead)
	{
		pthread_mutex_unlock(&table->is_dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&table->is_dead_mutex);
	pthread_mutex_lock(&table->write_mutex);
	if (table->is_dead)
		printf("%s%d \t philo id %d %s%s\n",
			color,
			get_time() - table->times_start,
			philo_id,
			msg,
			COLOR_RESET);
	pthread_mutex_unlock(&table->write_mutex);
}

void	printf_sleep(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is sleeping", COLOR_BLUE);
}

void	printf_eat(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is eating", COLOR_MAGENTA);
}

void	printf_fork(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "has taken the fork", COLOR_RED);
}

void	printf_think(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is thinking", COLOR_CYAN);
}

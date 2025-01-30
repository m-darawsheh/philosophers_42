/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_protection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:55 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/30 13:33:24 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protected_print(t_table *table, int philo_id, char *msg)
{
	if (!table->is_dead)
		return ;
	pthread_mutex_lock(&table->write_mutex);
	if (table->is_dead)
		printf("%d \t philo id %d %s\n",
			get_time() - table->times_start,
			philo_id,
			msg);
	pthread_mutex_unlock(&table->write_mutex);
}

void	printf_sleep(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is sleeping");
}

void	printf_eat(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is eating");
}

void	printf_fork(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "has taken the fork");
}

void	printf_think(t_philosopher *philo)
{
	protected_print(philo->table, philo->id, "is thinking");
}

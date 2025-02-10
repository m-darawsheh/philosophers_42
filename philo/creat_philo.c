/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/10 15:34:16 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
	printf_think(philo);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->table->there_is_meal || philo->table->is_dead)
	{
		pthread_mutex_lock(&philo->table->write_mutex);
		if (!philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->write_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->write_mutex);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->spare, NULL);
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].right_fork = &table->forks[(i + 1) % table->numbers];
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].when_ate = 0;
		i++;
	}
}

void	creat_philo(t_table *table)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	init_forks(table);
	init_data(table);
	while (i < table->numbers)
	{
		pthread_create(&table->philo[i].philosopher, NULL,
			routine, &table->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, r_routine, table);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->numbers)
	{
		pthread_join(table->philo[i].philosopher, NULL);
		i++;
	}
	free_fun(table);
	return ;
}

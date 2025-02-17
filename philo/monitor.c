/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:06:58 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/17 10:42:56 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	exit_routine(t_table *table, int l)
// {
// 	int	current_time;

// 	current_time = get_time();
// 	if ((current_time - table->philo[l].when_ate) > table->time_to_die)
// 	{
// 		table->is_dead = 0;
// 		printf("[%d] philo number %d is dead\n",
// 			current_time - table->times_start,
// 			table->philo[l].id);
// 		pthread_mutex_unlock(&table->write_mutex);
// 		return (0);
// 	}
// 	if (table->meals == 0 && table->there_is_meal)
// 	{
// 		table->is_dead = 0;
// 		table->there_is_meal = 0;
// 		pthread_mutex_unlock(&table->write_mutex);
// 		return (0);
// 	}
// 	return (1);
// }

// void	*r_routine(void *args)
// {
// 	int		l;
// 	t_table	*table;

// 	table = (t_table *)args;
// 	while (table->there_is_meal || table->is_dead)
// 	{
// 		l = 0;
// 		while (l < table->numbers)
// 		{
// 			pthread_mutex_lock(&table->write_mutex);
// 			if (!exit_routine(table, l))
// 				return (NULL);
// 			pthread_mutex_unlock(&table->write_mutex);
// 			l++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }


int	exit_routine(t_table *table, int l)
{
    int	current_time;

    current_time = get_time();
    pthread_mutex_lock(&table->is_dead_mutex);
    if ((current_time - table->philo[l].when_ate) > table->time_to_die)
    {
        table->is_dead = 0;
        pthread_mutex_unlock(&table->is_dead_mutex);
        printf("[%d] philo number %d is dead\n",
            current_time - table->times_start,
            table->philo[l].id);
        pthread_mutex_unlock(&table->write_mutex);
        return (0);
    }
    if (table->meals == 0 && table->there_is_meal)
    {
        table->is_dead = 0;
        pthread_mutex_unlock(&table->is_dead_mutex);
        table->there_is_meal = 0;
        pthread_mutex_unlock(&table->write_mutex);
        return (0);
    }
    pthread_mutex_unlock(&table->is_dead_mutex);
    return (1);
}

void	*r_routine(void *args)
{
    int		l;
    t_table	*table;

    table = (t_table *)args;
    while (1)
    {
        pthread_mutex_lock(&table->is_dead_mutex);
        if (!table->there_is_meal && !table->is_dead)
        {
            pthread_mutex_unlock(&table->is_dead_mutex);
            break;
        }
        pthread_mutex_unlock(&table->is_dead_mutex);

        l = 0;
        while (l < table->numbers)
        {
            pthread_mutex_lock(&table->write_mutex);
            if (!exit_routine(table, l))
            {
                // pthread_mutex_unlock(&table->write_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&table->write_mutex);
            l++;
        }
        usleep(100);
    }
    return (NULL);
}
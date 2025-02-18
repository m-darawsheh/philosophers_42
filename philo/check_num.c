/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:20:47 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/18 15:29:00 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long start_time, long long duration_ms, t_table *table)
{
	long long	end_time;

	end_time = start_time + duration_ms;
	while (get_time() < end_time)
	{
		pthread_mutex_lock(&table->is_dead_mutex);
		if (!table->is_dead)
		{
			pthread_mutex_unlock(&table->is_dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->is_dead_mutex);
		usleep(1);
	}
}

int	check_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			printf("Error\n : invalid argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_thread(t_table *table)
{
	int	l;

	l = 0;
	while (l < table->numbers)
	{
		if (pthread_create(&table->philo[l].philosopher, NULL,
				routine, &table->philo[l]) != 0)
		{
			printf("Error\n : pthread_create failed\n");
			return (1);
		}
		usleep (100);
		l++;
	}
	return (0);
}

int	join_thread(t_table *table)
{
	int	l;

	l = 0;
	while (l < table->numbers)
	{
		if (pthread_join(table->philo[l].philosopher, NULL) != 0)
		{
			printf("Error\n : pthread_join failed\n");
			return (1);
		}
		l++;
	}
	return (0);
}

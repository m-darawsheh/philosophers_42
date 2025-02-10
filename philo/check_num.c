/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:20:47 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/10 16:40:24 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long start_time, long long duration_ms, t_table *table)
{
	long long	end_time;

	end_time = start_time + duration_ms;
	while (get_time() < end_time)
	{
		pthread_mutex_lock(&table->write_mutex);
		if (!table->is_dead)
		{
			pthread_mutex_unlock(&table->write_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->write_mutex);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:23:11 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/01 14:33:39 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	free_fun(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	free(table->forks);
	free(table->philo);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
	printf_sleep(philo);
	usleep((philo->table->time_to_sleep) * 1000);
}

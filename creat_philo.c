/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:39 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
	free(table->philosophers);
}




void *r_routine(void *args)
{
	t_table *table = (t_table *)args;
	int l;
	int current_time;

	while (table->there_is_meal || table->is_dead)
	{
		l = 0;
		while (l < table->numbers)
		{
			pthread_mutex_lock(&table->write_mutex);
			current_time = get_time();
			if ((current_time - table->philosophers[l].when_ate) > table->time_to_die)
			{
				table->is_dead = 0;
				printf("[%d] philo number %d is dead\n",
					current_time - table->times_start,
					table->philosophers[l].id);
				pthread_mutex_unlock(&table->write_mutex);
				return NULL;
			}
			if (table->meals == 0 && table->there_is_meal)
			{
				table->is_dead = 0;
				table->there_is_meal = 0;
				pthread_mutex_unlock(&table->write_mutex);
				printf("All philosophers have eaten\n");
				return NULL;
			}
			pthread_mutex_unlock(&table->write_mutex);
			l++;
		}
		usleep(500);
	}
	return NULL;
} 

void	ft_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->table->write_mutex);

	printf_sleep(philo);

	usleep((philo->table->time_to_sleep) * 1000);
	
}

void ft_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->table->write_mutex);

	printf_think(philo);
}



void *routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;

	while (philo->table->there_is_meal || philo->table->is_dead)
	{
		pthread_mutex_lock(&philo->table->write_mutex);
		if (!philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->write_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->write_mutex);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return NULL;
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
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->numbers)
	{
		
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->numbers];
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].when_ate = 0;
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
		pthread_create(&table->philosophers[i].philosopher, NULL, routine, &table->philosophers[i]);
		usleep (10);
		i++;
	}
	pthread_create(&monitor, NULL, r_routine, table);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->numbers)
	{
		pthread_join(table->philosophers[i].philosopher, NULL);
		i++;
	}
	free_fun(table);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/20 17:15:17 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*r_routine(void *arg)
{
	t_table			*table = (t_table *)arg;
	int				l;
	usleep(50);
	while (1)
	{
		l = 0;
		while (l < table->num_philosophers)
		{
			if (get_time() - table->philosophers[l].when_ate >= table->time_to_die)
			{
				printf("[%d] philo number is %d is dead\n", get_time() - table->times_start, table->philosophers->id);
				table->is_dead = 0;
				return (NULL);
			}
			l++;
		}
	}
}



int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// here we take the two forks
void	ft_eat(t_philosopher *philo)
{
	
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("%d \t the philo id %d has taken the fork\n", get_time() - philo->table->times_start, philo->id);
	printf("%d \t the philo id %d has taken the fork\n", get_time() - philo->table->times_start, philo->id);
	printf("%d \t philo number %d is eating\n", get_time() - philo->table->times_start, philo->id);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->when_ate = get_time();
	// philo->final =  get_time();
	// philo->when_ate = philo->final - philo->init; 
	// after usleep forks will be unlock
} 

void	ft_sleep(t_philosopher *philo)
{
	printf("%d \t philo id %d is sleeping\n" , get_time() - philo->table->times_start, philo->id);
	usleep(philo->table->time_to_sleep * 1000);
	
}

void	ft_think(t_philosopher *philo)
{
	printf("%d \t philo id %d is thinking\n", get_time() - philo->table->times_start, philo->id);
}

// void pointer because when fucnition return null it mean success
void	*routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;
	while (philo->table->is_dead)
	{
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
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);	
		i++;
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->num_philosophers)
	{
		
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_philosophers];
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
	pthread_create(&monitor, NULL, r_routine, table);
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].philosopher, NULL, routine, &table->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].philosopher, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}


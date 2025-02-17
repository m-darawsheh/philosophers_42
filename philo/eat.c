/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:11:39 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/17 10:53:38 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philosopher *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	unlock_forks(t_philosopher *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}	
}

void	print_forks_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->is_dead_mutex);
	if (philo->table->meals != 0 && philo->table->there_is_meal)
	{
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		pthread_mutex_lock(&philo->table->write_mutex);
		philo->table->meals--;
		pthread_mutex_unlock(&philo->table->write_mutex);
		printf_fork(philo);
		printf_eat(philo);
	}
	else if (!philo->table->there_is_meal && philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		printf_fork(philo);
		printf_eat(philo);
	}
	else
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
}

void	finish_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	philo->when_ate = get_time();
	pthread_mutex_unlock(&philo->table->write_mutex);
	ft_usleep(get_time(), philo->table->time_to_eat, philo->table);
	unlock_forks(philo);
}

void	ft_eat(t_philosopher *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->table->is_dead_mutex);
	if (!philo->table->is_dead)
	{
		unlock_forks(philo);
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->is_dead_mutex);
	print_forks_eat(philo);
	finish_eat(philo);
}

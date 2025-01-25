/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/25 18:28:22 by mdarawsh         ###   ########.fr       */
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
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_sl);
	free(table->forks);
	free(table->philosophers);
}

void *r_routine(void *args)
{
    t_table *table = (t_table *)args;
    int l;

    while (1)
    {
        l = 0;
        while (l < table->num_philosophers)
        {
            pthread_mutex_lock(&table->write_mutex);
            if (get_time() - table->philosophers[l].when_ate >= table->time_to_die)
            {
                printf("[%d] philo number is %d is dead\n", 
                    get_time() - table->times_start, 
                    table->philosophers[l].id);
                table->is_dead = 0;
                pthread_mutex_unlock(&table->write_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->write_mutex);
            l++;
        }
        usleep(100); // Small delay to prevent busy waiting
    }
    return NULL;
}

// Replace all printf functions with this single protected version
void protected_print(t_table *table, int philo_id, char *msg)
{
    pthread_mutex_lock(&table->write_mutex);
    if (table->is_dead)
        printf("%d \t philo id %d %s\n", 
            get_time() - table->times_start, 
            philo_id, 
            msg);
    pthread_mutex_unlock(&table->write_mutex);
}

void printf_sleep(t_philosopher *philo)
{
    protected_print(philo->table, philo->id, "is sleeping");
}

void printf_eat(t_philosopher *philo)
{
    protected_print(philo->table, philo->id, "is eating");
}

void printf_fork(t_philosopher *philo)
{
    protected_print(philo->table, philo->id, "has taken the fork");
}




void	printf_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->print_th);
	printf("%d \t philo id %d is thinking\n" , get_time() - philo->table->times_start, philo->id);
	pthread_mutex_unlock(&philo->table->print_th);
}


void ft_eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->write_mutex);
    if (!philo->table->is_dead)
    {
        pthread_mutex_unlock(&philo->table->write_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->table->write_mutex);

    // Lock forks in order to prevent deadlocks
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else 
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    pthread_mutex_lock(&philo->table->write_mutex);
    if (!philo->table->is_dead)
    {
        pthread_mutex_unlock(&philo->table->write_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->table->write_mutex);
	printf_fork(philo);
    printf_eat(philo);
    usleep(philo->table->time_to_eat * 1000);
    philo->when_ate = get_time();

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
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

// void pointer because when fucnition return null it mean success
// void	*routine(void *arg)
// {
// 	t_philosopher *philo = (t_philosopher *)arg;
// 	while (philo->table->is_dead)
// 	{
// 		ft_eat(philo);
// 		ft_sleep(philo);
// 		ft_think(philo);
// 	}
// 	return (NULL);
// }


void *routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (1)
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
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);	
		i++;
	}
	pthread_mutex_init(&table->print_sl, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->print_th, NULL);
	pthread_mutex_init(&table->print_ea, NULL);
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
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].philosopher, NULL, routine, &table->philosophers[i]);
		usleep (20);
		i++;
	}
	pthread_create(&monitor, NULL, r_routine, table);
	i = 0;
	pthread_join(monitor, NULL);
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].philosopher, NULL);
		i++;
	}
	free_fun(table);
	return;
}

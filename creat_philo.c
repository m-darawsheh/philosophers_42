/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:44:19 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/29 20:03:47 by mdarawsh         ###   ########.fr       */
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
	pthread_mutex_destroy(&table->write_mutex);
	free(table->forks);
	free(table->philosophers);
}



void protected_print(t_table *table, int philo_id, char *msg)
{
    if(!table->is_dead)
        return;
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

void printf_think(t_philosopher *philo)
{
    protected_print(philo->table, philo->id, "is thinking");
}


void ft_eat(t_philosopher *philo)
{

    if (philo->left_fork < philo->right_fork)
    {
        usleep(philo->table->num_philosophers * 100);
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
        pthread_mutex_unlock(&philo->table->write_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->table->write_mutex);
    
    printf_fork(philo);
    printf_eat(philo);
    
        if (philo->table->meals > 0 && philo->table->there_is_meal)
        {
            pthread_mutex_lock(&philo->table->write_mutex);
            philo->table->meals--;
            pthread_mutex_unlock(&philo->table->write_mutex);
        }
        else if (philo->table->meals == 0 && philo->table->there_is_meal)
        {
            pthread_mutex_lock(&philo->table->write_mutex);
            philo->table->there_is_meal = 0;
            philo->table->is_dead = 0;
            return ;
            pthread_mutex_unlock(&philo->table->write_mutex);
        }
    pthread_mutex_lock(&philo->table->write_mutex);
    philo->when_ate = get_time();
    pthread_mutex_unlock(&philo->table->write_mutex);
    
    usleep(philo->table->time_to_eat * 1000);

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






void *r_routine(void *args)
{
    t_table *table = (t_table *)args;
    int l;
    int current_time;

    while (table->there_is_meal || table->is_dead)
    {
        l = 0;
        while (l < table->num_philosophers)
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


// void *routine(void *arg)
// {
//     t_philosopher *philo = (t_philosopher *)arg;
//     // int            i;

//     // i = philo->table->meals;
//     while ( philo->table->there_is_meal || philo->table->is_dead )
//     {
//         pthread_mutex_lock(&philo->table->write_mutex);
//         if (!philo->table->is_dead)
//         {
//             pthread_mutex_unlock(&philo->table->write_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&philo->table->write_mutex);
//         ft_eat(philo);
        
//         ft_sleep(philo);  
//         ft_think(philo);
//         if(philo->table->meals>= -1)
//         {
//             pthread_mutex_lock(&philo->table->write_mutex);
//             philo->table->meals--;
//             pthread_mutex_unlock(&philo->table->write_mutex);
//         }
//         else
//         {
//             pthread_mutex_lock(&philo->table->write_mutex);
//             philo->table->there_is_meal = 0;
//             philo->table->is_dead = 0;
//             pthread_mutex_unlock(&philo->table->write_mutex);
//         }
//     }
//     return NULL;
// }



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
	while (i < table->num_philosophers)
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
    	usleep (10);
    	i++;
    }
    // usleep(table->num_philosophers * 100);
    pthread_create(&monitor, NULL, r_routine, table);
    pthread_join(monitor, NULL);
    i = 0;
    while (i < table->num_philosophers)
    {
    	pthread_join(table->philosophers[i].philosopher, NULL);
    	i++;
    }
    
	free_fun(table);
	return;
}

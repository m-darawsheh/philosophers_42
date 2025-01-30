/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:20:14 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/30 14:13:24 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	pthread_t		philosopher;
	int				id;
	int				when_ate;
	int				final;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philosopher;

typedef struct s_table
{
	int				numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				times_start;
	int				is_dead;
	int				there_is_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philosopher	*philosophers;
}	t_table;

int		check_num(char *argv);
int		ft_atoi(char *str);
void	creat_philo(t_table *table);
int		get_time(void);
void	protected_print(t_table *table, int philo_id, char *msg);
void	printf_sleep(t_philosopher *philo);
void	printf_eat(t_philosopher *philo);
void	printf_fork(t_philosopher *philo);
void	printf_think(t_philosopher *philo);
void	lock_forks(t_philosopher *philo);
void	unlock_forks(t_philosopher *philo);
void	print_forks_eat(t_philosopher *philo);
void	finish_eat(t_philosopher *philo);
void	ft_eat(t_philosopher *philo);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:20:14 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/02/03 15:52:35 by mdarawsh         ###   ########.fr       */
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

# define COLOR_RESET   "\x1b[0m"
# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"

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
	t_philosopher	*philo;
}	t_table;

int		check_num(char *argv);
int		ft_atoi(char *str);
void	creat_philo(t_table *table);
int		get_time(void);
void	protected_print(t_table *table, int philo_id, char *msg, char *color);
void	printf_sleep(t_philosopher *philo);
void	printf_eat(t_philosopher *philo);
void	printf_fork(t_philosopher *philo);
void	printf_think(t_philosopher *philo);
void	lock_forks(t_philosopher *philo);
void	unlock_forks(t_philosopher *philo);
void	print_forks_eat(t_philosopher *philo);
void	finish_eat(t_philosopher *philo);
void	ft_eat(t_philosopher *philo);
void	free_fun(t_table *table);
void	ft_sleep(t_philosopher *philo);
void	*r_routine(void *args);
int		exit_routine(t_table *table, int l);
void	ft_usleep(long long start_time, long long duration_ms, t_table *table);

#endif
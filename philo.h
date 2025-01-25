/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:20:14 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/25 17:23:46 by mdarawsh         ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct s_philosopher {
	pthread_t		philosopher;
	int				id;
	int				when_ate;
	int				final;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_table			*table;
} t_philosopher;

typedef struct s_table {
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				times_start;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_sl;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	print_th;
	pthread_mutex_t	print_ea;
	t_philosopher	*philosophers;
} t_table;

int		check_num(char *argv);
int		ft_atoi(char *str);
void	creat_philo(t_table *table);
int		get_time(void);
# endif
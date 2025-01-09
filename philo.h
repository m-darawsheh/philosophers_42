/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 06:20:14 by mdarawsh          #+#    #+#             */
/*   Updated: 2025/01/09 07:42:29 by mdarawsh         ###   ########.fr       */
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

typedef struct s_philosopher {
	int 			id;
	long 			last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philosopher;

typedef struct s_table {
	int				num_philosophers;
	int				meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
} t_table;

int	check_num(char *argv);
int	ft_atoi(char *str);

# endif
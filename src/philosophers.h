/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:00:25 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:32:37 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					num_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					total_meals;
	int					t0;
	pthread_mutex_t		write_mtx;
	int					meals_eaten;
	pthread_mutex_t		eaten_mtx;
	int					philo_death;
	pthread_mutex_t		death_mtx;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		fork_mtx;
	int					last_meal;
	int					num_meals;
	t_data				*data;
	t_philo				*next;
}						t_philo;

long					ft_atoi_long(char *str);
int						check_arg(int argc, char **argv);
int						init_data(int argc, char **argv, t_data *data);
int						philo_died(t_data *data);
void					*cycle(void *philo_data);
int						meals_eaten(t_data *data);
int						check_death(t_philo *philo);
void					print_status(t_philo *philo, char *str);
void					ft_sleep(int ms);
int						get_actual_time(void);
void					free_all(t_data *data);
void					free_threads(t_data *data);
void					free_all_mutex(t_data *data);
void					free_philo_mutex(t_data *data);
void					free_mutex(t_data *data, char type);
void					ft_lstadd_back(t_philo **lst, t_philo *new);
void					ft_lstclear_philos(t_philo **philo);

#endif
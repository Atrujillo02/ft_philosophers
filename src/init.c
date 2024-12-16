/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:02:52 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:38:31 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_threads(t_data *data)
{
	t_philo	*aux;
	int		i;

	i = 0;
	aux = data->philos;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&aux->fork_mtx, NULL))
			return (free_threads(data), free_philo_mutex(data), 0);
		if (pthread_create(&aux->thread, NULL, &cycle, aux))
			return (free_threads(data), free_philo_mutex(data), 0);
		aux = aux->next;
		i++;
	}
	return (1);
}

static int	init_philo_data(t_data *data)
{
	t_philo	*aux;
	int		i;

	i = 0;
	while (i < data->num_philos)
	{
		aux = malloc(sizeof(t_philo));
		if (!aux)
			return (0);
		memset(aux, 0, sizeof(t_philo));
		aux->id = i + 1;
		aux->data = data;
		aux->next = NULL;
		aux->last_meal = get_actual_time();
		ft_lstadd_back(&data->philos, aux);
		i++;
	}
	return (1);
}

static int	data_to_mtx(t_data *data)
{
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (0);
	if (pthread_mutex_init(&data->eaten_mtx, NULL))
		return (pthread_mutex_destroy(&data->write_mtx), 0);
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (free_mutex(data, 'e'), 0);
	return (1);
}

static void	go_data(t_data *data, long num, int len_argv)
{
	if (len_argv == 1)
		data->num_philos = (int)num;
	else if (len_argv == 2)
		data->time_die = (int)num;
	else if (len_argv == 3)
		data->time_eat = (int)num;
	else if (len_argv == 4)
		data->time_sleep = (int)num;
	else if (len_argv == 5)
		data->total_meals = (int)num;
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	data->total_meals = -1;
	while (i < argc)
	{
		go_data(data, ft_atoi_long(argv[i]), i);
		i++;
	}
	if (!data_to_mtx(data))
		return (free(data), 0);
	if (!init_philo_data(data))
	{
		ft_lstclear_philos(&data->philos);
		free(data->philos);
		free_mutex(data, 'd');
		free(data);
		return (0);
	}
	data->t0 = get_actual_time();
	if (!init_threads(data))
		return (free_all(data), 0);
	return (1);
}

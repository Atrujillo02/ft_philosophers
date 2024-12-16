/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:08:44 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:39:12 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *data)
{
	free_all_mutex(data);
	ft_lstclear_philos(&data->philos);
	free(data->philos);
	free(data);
}

void	free_threads(t_data *data)
{
	t_philo	*aux;

	aux = data->philos;
	while (aux)
	{
		if (aux->thread)
			pthread_detach(aux->thread);
		aux = aux->next;
	}
}

void	free_all_mutex(t_data *data)
{
	free_mutex(data, 'd');
	free_philo_mutex(data);
}

void	free_philo_mutex(t_data *data)
{
	t_philo	*aux;

	aux = data->philos;
	while (aux)
	{
		pthread_mutex_destroy(&aux->fork_mtx);
		aux = aux->next;
	}
}

void	free_mutex(t_data *data, char type)
{
	pthread_mutex_destroy(&data->write_mtx);
	if (type == 'd')
		pthread_mutex_destroy(&data->death_mtx);
	if (type == 'd' || type == 'e')
		pthread_mutex_destroy(&data->eaten_mtx);
}

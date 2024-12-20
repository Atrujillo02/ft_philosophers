/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:07:12 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:32:53 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(int ms)
{
	int	initial;

	initial = get_actual_time();
	while (get_actual_time() - initial < ms)
		usleep(50);
}

void	print_status(t_philo *philo, char *str)
{
	if (meals_eaten(philo->data) || philo_died(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_mtx);
	printf("%d	%d %s\n", get_actual_time() - philo->data->t0, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_mtx);
}

int	meals_eaten(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data->eaten_mtx);
	if (data->total_meals == 0 || data->meals_eaten == data->num_philos)
		result = 1;
	return (pthread_mutex_unlock(&data->eaten_mtx), result);
}

int	check_death(t_philo *philo)
{
	if (philo->last_meal + philo->data->time_die < get_actual_time())
	{
		print_status(philo, "died");
		pthread_mutex_lock(&philo->data->death_mtx);
		philo->data->philo_death = 1;
		pthread_mutex_unlock(&philo->data->death_mtx);
		return (1);
	}
	return (0);
}

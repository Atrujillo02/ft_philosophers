/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:05:55 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:38:02 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philos_states(t_data *data)
{
	t_philo	*aux;

	aux = data->philos;
	while (!check_death(aux) && !meals_eaten(data))
	{
		if (aux->next)
			aux = aux->next;
		else
			aux = data->philos;
	}
}

long	ft_atoi_long(char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (num * sign);
}

static int	is_positive_int_in_range(char *str, int argv_len)
{
	long	num;
	int		num_condition;

	num = ft_atoi_long(str);
	num_condition = num >= 0;
	if (argv_len == 1)
		num_condition = num > 0;
	return (num_condition && num <= INT_MAX);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_positive_int_in_range(argv[i], i))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!check_arg(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	memset(data, 0, sizeof(t_data));
	if (!init_data(argc, argv, data))
		return (-1);
	check_philos_states(data);
	while (data->philos)
	{
		pthread_join(data->philos->thread, NULL);
		pthread_mutex_destroy(&data->philos->fork_mtx);
		data->philos = data->philos->next;
	}
	if (data->total_meals == 0 || (!data->philo_death
			&& data->meals_eaten == data->num_philos))
		printf("All philos have eaten %d times\n", data->total_meals);
	return (free_all(data), 0);
}

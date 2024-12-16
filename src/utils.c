/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:31:31 by atrujill          #+#    #+#             */
/*   Updated: 2023/05/22 10:26:50 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*aux;

	if (!*lst)
		*lst = new;
	else
	{
		aux = *lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_lstclear_philos(t_philo **philo)
{
	t_philo	*next;

	while (*philo)
	{
		next = (*philo)->next;
		free(philo);
		*philo = next;
	}
}

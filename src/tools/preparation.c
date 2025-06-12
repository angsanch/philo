/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:50:14 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 07:26:52 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	prepare_mutexes(t_philo *philo)
{
	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->args.philos);
	if (philo->mutex == NULL)
	{
		return (0);
	}
	while (philo->mutex_count < philo->args.philos)
	{
		if (pthread_mutex_init(&philo->mutex[philo->mutex_count], NULL) != 0)
		{
			return (0);
		}
		philo->mutex_count ++;
	}
	return (1);
}

static int	prepare_threads(t_philo *philo)
{
	(void)philo;
	return (1);
}

int	prepare_philo(t_philo *philo)
{
	if (!prepare_mutexes(philo))
	{
		philo_delete(philo);
		return (0);
	}
	if (!prepare_threads(philo))
	{
		philo_delete(philo);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:50:14 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 17:15:18 by angsanch         ###   ########.fr       */
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
	t_philo_data	*pd;

	philo->thread = malloc(sizeof(pthread_t) * philo->args.philos);
	if (philo->thread == NULL)
	{
		return (0);
	}
	while (philo->thread_count < philo->args.philos)
	{
		pd = malloc(sizeof(t_philo_data) * 1);
		if (pd == NULL)
		{
			return (0);
		}
		pd->philo = philo;
		pd->id = philo->thread_count;
		if (pthread_create(&philo->thread[philo->thread_count], NULL,
				&philosopher, pd) != 0)
		{
			free(pd);
			return (0);
		}
		philo->thread_count ++;
	}
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

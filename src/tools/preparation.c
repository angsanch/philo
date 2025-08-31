/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:50:14 by angsanch          #+#    #+#             */
/*   Updated: 2025/08/31 10:46:34 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	prepare_mutexes(t_philo *philo)
{
	while (philo->mutex_count < philo->args.philos)
	{
		if (pthread_mutex_init(&philo->thinker[philo->mutex_count].mutex,
				NULL) != 0)
		{
			return (0);
		}
		philo->mutex_count ++;
	}
	if (pthread_mutex_init(&philo->printing, NULL) != 0)
	{
		return (0);
	}
	return (1);
}

static int	prepare_threads(t_philo *philo)
{
	t_philo_data	*pd;

	while (philo->thread_count < philo->args.philos)
	{
		pd = malloc(sizeof(t_philo_data) * 1);
		if (pd == NULL)
		{
			return (0);
		}
		pd->philo = philo;
		pd->id = philo->thread_count;
		if (pthread_create(&philo->thinker[philo->thread_count].thread, NULL,
				&philosopher, pd) != 0)
		{
			free(pd);
			return (0);
		}
		philo->thread_count ++;
	}
	return (1);
}

static int	prepare_status(t_philo *philo)
{
	unsigned long	status_count;

	status_count = 0;
	while (status_count < philo->args.philos)
	{
		philo->thinker[status_count].status = NON;
		status_count ++;
	}
	return (1);
}

int	prepare_philo(t_philo *philo)
{
	philo->thinker = malloc(sizeof(t_philosoper) * philo->args.philos);
	if (philo->thinker == NULL)
	{
		philo_delete(philo);
		return (0);
	}
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
	if (!prepare_status(philo))
	{
		philo_delete(philo);
		return (0);
	}
	return (1);
}

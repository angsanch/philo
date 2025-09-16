/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 07:06:33 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/16 14:26:23 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_event(t_philo_data *pd, const char *event)
{
	pthread_mutex_lock(&pd->philo->printing);
	printf("%lu %u %s\n", millis(), pd->id + 1, event);
	pthread_mutex_unlock(&pd->philo->printing);
}

void	take_fork(t_philo_data *pd, unsigned int id)
{
	pthread_mutex_lock(&pd->philo->thinker[id % pd->philo->args.philos].mutex);
	philo_event(pd, "has taken a fork");
	pthread_mutex_lock(&pd->philo->thinker[pd->id].status_lock);
	pd->philo->thinker[pd->id].status = FORK;
	pthread_mutex_unlock(&pd->philo->thinker[pd->id].status_lock);
}

void	release_fork(t_philo_data *pd, unsigned int id)
{
	pthread_mutex_unlock(&pd->philo->thinker[id % pd->philo->args.philos]
		.mutex);
}

unsigned int	get_wait(t_philosoper *thinker)
{
	unsigned int	result;
	unsigned int	time;

	pthread_mutex_lock(&thinker->status_lock);
	time = millis();
	if (thinker->status == SLEEP)
		result = 0;
	else
	{
		if (thinker->last_eat < time)
			result = 0;
		else
			result = thinker->last_eat - time;
	}
	pthread_mutex_unlock(&thinker->status_lock);
	return (result);
}

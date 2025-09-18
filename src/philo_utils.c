/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 07:06:33 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/16 17:23:38 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

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
	if (thinker->status == SLEEP || thinker->status == THINK)
		result = 0;
	else
	{
		if (thinker->eat_end < time)
			result = 0;
		else
			result = thinker->eat_end - time;
	}
	pthread_mutex_unlock(&thinker->status_lock);
	return (result);
}

int	wait(t_philo_data *pd, unsigned int ms)
{
	unsigned int	time;
	unsigned int	end;
	t_philosoper	*thinker;

	time = millis();
	end = time + ms;
	thinker = &pd->philo->thinker[pd->id];
	while (time < end)
	{
		usleep(1000);
		pthread_mutex_lock(&thinker->status_lock);
		if (pd->philo->end || \
			thinker->eat_start + pd->philo->args.die < millis())
		{
			return (0);
		}
		pthread_mutex_unlock(&thinker->status_lock);
		time = millis();
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 07:06:33 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/30 07:25:38 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

void	philo_event(t_philo_data *pd, const char *event)
{
	pthread_mutex_lock(&pd->philo->printing);
	if (!pd->philo->end)
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

int	wait(t_philo_data *pd, unsigned int ms, bool (*condition)(t_philo_data *))
{
	size_t			time;
	unsigned int	end;
	t_philosoper	*think;

	time = millis();
	end = time + ms;
	think = &pd->philo->thinker[pd->id];
	while (time < end || ms == 0)
	{
		usleep(250);
		pthread_mutex_lock(&think->status_lock);
		if (pd->philo->end || think->eat_start + pd->philo->args.die < millis())
		{
			think->status = DEAD;
			pthread_mutex_unlock(&think->status_lock);
			return (0);
		}
		pthread_mutex_unlock(&think->status_lock);
		if (condition)
			if (condition(pd))
				return (1);
		time = millis();
	}
	return (1);
}

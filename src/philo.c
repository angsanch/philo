/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:09:55 by angsanch          #+#    #+#             */
/*   Updated: 2025/08/29 18:57:03 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

static void	philo_event(t_philo_data *pd, const char *event)
{
	pthread_mutex_lock(&pd->philo->printing);
	printf("%lu %u %s\n", millis(), pd->id + 1, event);
	pthread_mutex_unlock(&pd->philo->printing);
}

static void	take_fork(t_philo_data *pd, unsigned int id)
{
	pthread_mutex_lock(&pd->philo->mutex[id % pd->philo->args.philos]);
	philo_event(pd, "has taken a fork");
}

static void	release_fork(t_philo_data *pd, unsigned int id)
{
	pthread_mutex_unlock(&pd->philo->mutex[id % pd->philo->args.philos]);
}

void	*philosopher(void *pd_void)
{
	t_philo_data	*pd;
	unsigned int	eaten;

	pd = pd_void;
	eaten = 0;
	while (eaten < pd->philo->args.eat_times || !pd->philo->args.eat_times_set)
	{
		take_fork(pd, pd->id + (pd->id % 2 == 0));
		take_fork(pd, pd->id + (pd->id % 2 == 1));
		philo_event(pd, "is eating");
		usleep(pd->philo->args.eat * 1000);
		release_fork(pd, pd->id + (pd->id % 2 == 0));
		release_fork(pd, pd->id + (pd->id % 2 == 1));
		philo_event(pd, "is sleeping");
		usleep(pd->philo->args.sleep * 1000);
		eaten ++;
	}
	free(pd);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:09:55 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/16 14:49:46 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

static int	eat(t_philo_data *pd)
{
	t_philosoper	*thinker;

	thinker = &pd->philo->thinker[pd->id];
	pthread_mutex_lock(&thinker->status_lock);
	thinker->status = EAT;
	thinker->last_eat = millis() + pd->philo->args.eat;
	pthread_mutex_unlock(&thinker->status_lock);
	take_fork(pd, pd->id + (pd->id % 2 == 0));
	take_fork(pd, pd->id + (pd->id % 2 == 1));
	philo_event(pd, "is eating");
	usleep(pd->philo->args.eat * 1000);
	release_fork(pd, pd->id + (pd->id % 2 == 0));
	release_fork(pd, pd->id + (pd->id % 2 == 1));
	return (1);
}

static int	psleep(t_philo_data *pd)
{
	philo_event(pd, "is sleeping");
	pthread_mutex_lock(&pd->philo->thinker[pd->id].status_lock);
	pd->philo->thinker[pd->id].status = SLEEP;
	pthread_mutex_unlock(&pd->philo->thinker[pd->id].status_lock);
	if (pd->philo->args.sleep > pd->philo->args.die)
	{
		usleep(pd->philo->args.eat * 1000);
		return (0);
	}
	usleep(pd->philo->args.sleep * 1000);
	return (1);
}

static int	think(t_philo_data *pd)
{
	t_philosoper	*thinker[2];
	unsigned int	lwait;
	unsigned int	rwait;

	thinker[1] = &pd->philo->thinker[pd->id % pd->philo->args.philos];
	if (pd->id == 0)
		thinker[0] = &pd->philo->thinker[pd->philo->args.philos - 1];
	else
		thinker[0] = &pd->philo->thinker[pd->id - 1];
	lwait = get_wait(thinker[0]);
	rwait = get_wait(thinker[1]);
	if (rwait > lwait)
		lwait = rwait;
	if (lwait == 0)
		return (1);
	philo_event(pd, "is thinking");
	rwait = millis();
	if (rwait + lwait <= pd->philo->thinker[pd->id].last_eat
		+ pd->philo->args.die)
	{
		usleep(lwait * 1000);
		return (1);
	}
	usleep((pd->philo->thinker[pd->id].last_eat + pd->philo->args.die - rwait) * 1000);
	return (0);
}

void	*philosopher(void *pd_void)
{
	t_philo_data	*pd;
	unsigned int	eaten;

	pd = pd_void;
	eaten = 0;
	while (eaten < pd->philo->args.eat_times || !pd->philo->args.eat_times_set)
	{
		if (!eat(pd))
			break ;
		if (!psleep(pd))
			break ;
		if (!think(pd))
			break ;
		eaten ++;
	}
	if (eaten < pd->philo->args.eat_times || !pd->philo->args.eat_times_set)
	{
		philo_event(pd, "died");
	}
	free(pd);
	return (NULL);
}

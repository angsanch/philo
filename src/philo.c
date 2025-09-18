/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:09:55 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/16 17:25:08 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo_data *pd)
{
	t_philosoper	*thinker;
	int				status;

	thinker = &pd->philo->thinker[pd->id];
	take_fork(pd, pd->id + (pd->id % 2 == 0));
	take_fork(pd, pd->id + (pd->id % 2 == 1));
	pthread_mutex_lock(&thinker->status_lock);
	thinker->status = EAT;
	thinker->eat_start = millis();
	thinker->eat_end = thinker->eat_start + pd->philo->args.eat;
	pthread_mutex_unlock(&thinker->status_lock);
	philo_event(pd, "is eating");
	status = wait(pd, pd->philo->args.eat);
	release_fork(pd, pd->id + (pd->id % 2 == 0));
	release_fork(pd, pd->id + (pd->id % 2 == 1));
	return (status);
}

static int	psleep(t_philo_data *pd)
{
	int	status;

	pthread_mutex_lock(&pd->philo->thinker[pd->id].status_lock);
	pd->philo->thinker[pd->id].status = SLEEP;
	pthread_mutex_unlock(&pd->philo->thinker[pd->id].status_lock);
	philo_event(pd, "is sleeping");
	status = wait(pd, pd->philo->args.sleep);
	return (status);
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
	if (rwait + lwait <= pd->philo->thinker[pd->id].eat_start
		+ pd->philo->args.die)
	{
		return (wait(pd, lwait));
	}
	return (wait(pd, pd->philo->thinker[pd->id].eat_start
			+ pd->philo->args.die - rwait));
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
		eaten ++;
		if (!(eaten < pd->philo->args.eat_times
			|| !pd->philo->args.eat_times_set))
			continue ;
		if (!psleep(pd))
			break ;
		if (!think(pd))
			break ;
	}
	if (eaten < pd->philo->args.eat_times || !pd->philo->args.eat_times_set)
	{
		if (!pd->philo->end)
		{
			philo_event(pd, "died");
			pd->philo->end = true;
		}
	}
	free(pd);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:09:55 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/23 01:27:52 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	forks_available(t_philo_data *pd)
{
	t_philosoper	*thinker;
	enum e_status	status;
	size_t	id;

	id = pd->id - (pd->id % 2) + (1 - (pd->id % 2));
	thinker = &pd->philo->thinker[id % pd->philo->args.philos];
	pthread_mutex_lock(&thinker->status_lock);
	status = thinker->status;
	pthread_mutex_unlock(&thinker->status_lock);
	return (status != EAT);
}

static int	think(t_philo_data *pd)
{
	t_philosoper	*thinker;

	thinker = &pd->philo->thinker[pd->id];
	if (forks_available(pd))
		return (1);
	philo_event(pd, "is thinking");
	pthread_mutex_lock(&thinker->status_lock);
	thinker->status = THINK;
	pthread_mutex_unlock(&thinker->status_lock);
	return (wait(pd, 0, &forks_available));
}

static int	eat(t_philo_data *pd)
{
	t_philosoper	*thinker;
	size_t			fork_id;
	int				status;

	thinker = &pd->philo->thinker[pd->id];
	fork_id = pd->id - (pd->id % 2);
	if (!think(pd))
		return (0);
	take_fork(pd, fork_id);
	take_fork(pd, fork_id + 1);
	pthread_mutex_lock(&thinker->status_lock);
	thinker->eat_start = millis();
	thinker->status = EAT;
	pthread_mutex_unlock(&thinker->status_lock);
	philo_event(pd, "is eating");
	status = wait(pd, pd->philo->args.eat, NULL);
	release_fork(pd, fork_id + 1);
	release_fork(pd, fork_id);
	return (status);
}

static int	psleep(t_philo_data *pd)
{
	int	status;

	pthread_mutex_lock(&pd->philo->thinker[pd->id].status_lock);
	pd->philo->thinker[pd->id].status = SLEEP;
	pthread_mutex_unlock(&pd->philo->thinker[pd->id].status_lock);
	philo_event(pd, "is sleeping");
	status = wait(pd, pd->philo->args.sleep, NULL);
	return (status);
}

static int	loop(t_philo_data *pd)
{
	unsigned int	eaten;

	eaten = 0;
	if (pd->philo->args.eat_times == 0 && pd->philo->args.eat_times_set)
		return (1);
	while (true)
	{
		if (!eat(pd))
			return (0);
		eaten ++;
		if (!(eaten < pd->philo->args.eat_times
				|| !pd->philo->args.eat_times_set))
			return (1);
		if (!psleep(pd))
			return (0);
	}
}

void	*philosopher(void *pd_void)
{
	t_philo_data	*pd;
	t_philosoper	*thinker;

	pd = pd_void;
	thinker = &pd->philo->thinker[pd->id];
	if (!loop(pd))
	{
		if (!pd->philo->end)
		{
			philo_event(pd, "died");
			pd->philo->end = true;
		}
	}
	pthread_mutex_lock(&thinker->status_lock);
	thinker->status = DEAD;
	pthread_mutex_unlock(&thinker->status_lock);
	free(pd);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:09:55 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/30 07:14:34 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	forks_available(t_philo_data *pd)
{
	t_philosoper	*thinker;
	t_philosoper	*fork[2];
	enum e_status	status[2];

	thinker = &pd->philo->thinker[pd->id];
	fork[0] = &pd->philo->thinker[thinker->fork[1]];
	fork[1] = &pd->philo->thinker[thinker->fork[0]];
	pthread_mutex_lock(&fork[0]->status_lock);
	status[0] = fork[0]->status;
	pthread_mutex_unlock(&fork[0]->status_lock);
	pthread_mutex_lock(&fork[1]->status_lock);
	status[1] = fork[1]->status;
	pthread_mutex_unlock(&fork[1]->status_lock);
	return (status[0] != EAT && status[1] != EAT);
}

static int	think(t_philo_data *pd)
{
	t_philosoper	*thinker;

	thinker = &pd->philo->thinker[pd->id];
	philo_event(pd, "is thinking");
	pthread_mutex_lock(&thinker->status_lock);
	thinker->status = THINK;
	pthread_mutex_unlock(&thinker->status_lock);
	return (wait(pd, 0, &forks_available));
}

int	eat(t_philo_data *pd)
{
	t_philosoper	*thinker;
	int				status;

	thinker = &pd->philo->thinker[pd->id];
	if (!think(pd))
		return (0);
	take_fork(pd, thinker->fork[1]);
	take_fork(pd, thinker->fork[0]);
	pthread_mutex_lock(&thinker->status_lock);
	thinker->eat_start = millis();
	thinker->status = EAT;
	pthread_mutex_unlock(&thinker->status_lock);
	philo_event(pd, "is eating");
	status = wait(pd, pd->philo->args.eat, NULL);
	release_fork(pd, thinker->fork[1]);
	release_fork(pd, thinker->fork[0]);
	return (status);
}

int	psleep(t_philo_data *pd)
{
	int	status;

	pthread_mutex_lock(&pd->philo->thinker[pd->id].status_lock);
	pd->philo->thinker[pd->id].status = SLEEP;
	pthread_mutex_unlock(&pd->philo->thinker[pd->id].status_lock);
	philo_event(pd, "is sleeping");
	status = wait(pd, pd->philo->args.sleep, NULL);
	return (status);
}

void	*philosopher(void *pd_void)
{
	t_philo_data	*pd;
	t_philosoper	*thinker;

	pd = pd_void;
	thinker = &pd->philo->thinker[pd->id];
	if (pd->philo->args.philos == 1)
	{
		loner(pd);
		return (NULL);
	}
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

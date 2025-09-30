/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 06:55:38 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/30 07:22:50 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop(t_philo_data *pd)
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

int	loner(t_philo_data *pd)
{
	take_fork(pd, pd->philo->thinker[pd->id].fork[0]);
	wait(pd, pd->philo->args.die, NULL);
	philo_event(pd, "died");
	release_fork(pd, pd->philo->thinker[pd->id].fork[0]);
	return (0);
}

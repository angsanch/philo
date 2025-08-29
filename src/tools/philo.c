/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:18:10 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/24 01:32:52 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_delete(t_philo *philo)
{
	void	*rets;

	if (philo == NULL)
	{
		return ;
	}
	if (philo->thread)
	{
		while (philo->thread_count > 0)
		{
			philo->thread_count --;
			pthread_join(philo->thread[philo->thread_count], &rets);
		}
		free(philo->thread);
	}
	if (philo->mutex)
	{
		while (philo->mutex_count > 0)
		{
			philo->mutex_count --;
			pthread_mutex_destroy(&philo->mutex[philo->mutex_count]);
		}
		free(philo->mutex);
		pthread_mutex_destroy(&philo->printing);
	}
}

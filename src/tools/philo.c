/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:18:10 by angsanch          #+#    #+#             */
/*   Updated: 2025/08/31 10:44:45 by angsanch         ###   ########.fr       */
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
	if (philo->thinker)
	{
		while (philo->thread_count > 0)
		{
			philo->thread_count --;
			pthread_join(philo->thinker[philo->thread_count].thread, &rets);
		}
		while (philo->mutex_count > 0)
		{
			philo->mutex_count --;
			pthread_mutex_destroy(&philo->thinker[philo->mutex_count].mutex);
		}
		pthread_mutex_destroy(&philo->printing);
		free(philo->thinker);
	}
}

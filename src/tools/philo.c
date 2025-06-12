/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:18:10 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 07:33:28 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_delete(t_philo *philo)
{
	if (philo == NULL)
	{
		return ;
	}
	if (philo->mutex)
	{
		while (philo->mutex_count > 0)
		{
			philo->mutex_count --;
			pthread_mutex_destroy(&philo->mutex[philo->mutex_count]);
		}
		free(philo->mutex);
	}
}

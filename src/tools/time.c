/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 05:20:50 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/13 05:43:22 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

size_t	millis(void)
{
	struct timeval	tv;
	struct timezone	tz;
	static size_t	start_sec = 0;
	static size_t	start_usec = 0;

	if (start_sec == 0)
	{
		gettimeofday(&tv, &tz);
		start_sec = tv.tv_sec;
		start_usec = tv.tv_usec;
		return (0);
	}
	gettimeofday(&tv, &tz);
	return (((tv.tv_sec - start_sec) * 1000) + \
		((tv.tv_usec - start_usec) * 0.001));
}

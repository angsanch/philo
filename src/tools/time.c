/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 05:20:50 by angsanch          #+#    #+#             */
/*   Updated: 2025/08/29 19:06:59 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

size_t	millis(void)
{
	struct timeval				tv;
	struct timezone				tz;
	static struct s_time_data	data = {0, 0, false};
	long						sec_diff;
	long						usec_diff;

	if (!data.initialized)
	{
		gettimeofday(&tv, &tz);
		data.start_sec = tv.tv_sec;
		data.start_usec = tv.tv_usec;
		data.initialized = true;
		return (0);
	}
	gettimeofday(&tv, &tz);
	sec_diff = tv.tv_sec - data.start_sec;
	usec_diff = tv.tv_usec - data.start_usec;
	if (usec_diff < 0)
	{
		sec_diff --;
		usec_diff += 1000000;
	}
	return ((sec_diff * 1000) + (usec_diff / 1000));
}

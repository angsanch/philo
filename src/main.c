/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:34:06 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 07:32:30 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	if (!arg_parse(&philo.args, argc - 1, &argv[1]))
	{
		return (84);
	}
	if (!prepare_philo(&philo))
	{
		return (84);
	}
	philo_delete(&philo);
	return (0);
}

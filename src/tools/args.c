/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:02:57 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 07:02:02 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_parse(t_args *args, int argc, char **argv)
{
	int	i;

	if (argc <= 0 || argc > 5)
	{
		return (0);
	}
	i = 0;
	args->eat_times_set = argc == 5;
	while (i < argc)
	{
		args->nums[i] = my_getnbr_base(argv[i], "0123456789");
		if (my_intlen_base(args->nums[i], 10) != my_strlen(argv[i]))
		{
			return (0);
		}
		i ++;
	}
	return (1);
}

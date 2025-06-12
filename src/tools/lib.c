/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:46:21 by angsanch          #+#    #+#             */
/*   Updated: 2025/06/12 06:24:25 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static ssize_t	my_strchr_index(char const *str, char c)
{
	ssize_t	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (i);
		i ++;
	}
	return (-1);
}

size_t	my_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i ++;
	return (i);
}

size_t	my_intlen_base(long long nb, int base_len)
{
	unsigned long long	n;
	size_t				len;

	n = nb;
	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len ++;
		n = -nb;
	}
	while (n)
	{
		n /= base_len;
		len ++;
	}
	return (len);
}

int	my_getnbr_base(char const *str, char const *base)
{
	int		result;
	int		multiplicator;
	size_t	base_len;
	int		power;
	size_t	i;

	result = 0;
	multiplicator = 1;
	base_len = my_strlen(base);
	power = 1;
	if (str[0] == '-')
	{
		multiplicator = -1;
		str ++;
	}
	i = my_strlen(str) - 1;
	while (i + 1 > 0)
	{
		result += power * my_strchr_index(base, str[i]);
		power *= base_len;
		i --;
	}
	return (result * multiplicator);
}

int	my_strcmp(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == 0)
			break ;
		i ++;
	}
	return (s1[i] - s2[i]);
}

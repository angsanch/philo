/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angsanch <angsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:42:18 by angsanch          #+#    #+#             */
/*   Updated: 2025/09/30 07:23:43 by angsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>

enum e_status
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
};

typedef union args_wrapper
{
	struct
	{
		unsigned int	philos;
		unsigned int	die;
		unsigned int	eat;
		unsigned int	sleep;
		unsigned int	eat_times;
		bool			eat_times_set;
	};
	unsigned int	nums[5];
}	t_args;

typedef struct s_philosopher
{
	pthread_mutex_t	status_lock;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	unsigned int	fork[2];
	enum e_status	status;
	bool			status_init;
	size_t			eat_start;
}	t_philosoper;

typedef struct philo_wrapper
{
	t_args			args;
	t_philosoper	*thinker;
	unsigned long	mutex_count;
	unsigned long	thread_count;
	pthread_mutex_t	printing;
	bool			end;
}	t_philo;

typedef struct philo_data
{
	t_philo			*philo;
	unsigned int	id;
}	t_philo_data;

struct	s_time_data
{
	size_t	start_sec;
	size_t	start_usec;
	bool	initialized;
};

int		arg_parse(t_args *args, int argc, char **argv);
int		prepare_philo(t_philo *philo);
void	philo_delete(t_philo *philo);

void	*philosopher(void *pd);

size_t	millis(void);

size_t	my_strlen(char const *str);
size_t	my_intlen_base(long long nb, int base_len);
int		my_getnbr_base(char const *str, char const *base);
int		my_strcmp(char const *s1, char const *s2);

void	philo_event(t_philo_data *pd, const char *event);
void	take_fork(t_philo_data *pd, unsigned int id);
void	release_fork(t_philo_data *pd, unsigned int id);
int		wait(t_philo_data *pd, unsigned int ms,
			bool (*condition)(t_philo_data *));

int		eat(t_philo_data *pd);
int		psleep(t_philo_data *pd);
int		loop(t_philo_data *pd);
int		loner(t_philo_data *pd);

#endif

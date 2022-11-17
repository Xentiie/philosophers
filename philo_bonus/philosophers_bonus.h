/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:48:21 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/06 19:48:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>


typedef struct s_data t_data;

typedef struct s_philo
{
	int			i;
	int			eat_count;
	long long	last_eat_timestamp;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;

	int				philo_died;
	
	int				loop;
	
	long long		start_time;
	
	t_philo			**philos;
	
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*stop;
}	t_data;

long long	timestamp(void);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

void		philo_eats(t_philo *philo);
void		philo_print(t_data *dat, int id, char *string);
void		*philo_thread(void *arg);

void		free_all(t_data *dat);

#endif
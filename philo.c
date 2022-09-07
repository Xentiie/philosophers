/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:46:28 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/07 00:46:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		philo_wait(long long time, t_data *dat)
{
	long long i;

	i = timestamp();
	while (!(dat->philo_died))
	{
		if (timestamp() - i >= time)
			break ;
		usleep(50);
	}
}

void		philo_print(t_data *dat, int id, char *string)
{
	pthread_mutex_lock(&(dat->print));
	if (!(dat->philo_died))
	{
		printf("%lli ", timestamp() - dat->start_time);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(dat->print));
	return ;
}

void	philo_eats(t_philo *philo)
{
	t_data *dat;

	dat = philo->data;
	pthread_mutex_lock(&(dat->forks[philo->l_id]));
	philo_print(dat, philo->i, "has taken a fork");
	pthread_mutex_lock(&(dat->forks[philo->r_id]));
	philo_print(dat, philo->i, "has taken a fork");
	pthread_mutex_lock(&(dat->is_eating));
	philo_print(dat, philo->i, "is eating");
	philo->last_eat_timestamp = timestamp();
	philo_wait(dat->eat_time, dat);
	pthread_mutex_unlock(&(dat->is_eating));
	pthread_mutex_unlock(&(dat->forks[philo->l_id]));
	pthread_mutex_unlock(&(dat->forks[philo->r_id]));
	philo->eat_count++;
}

void	*philo_thread(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*dat;

	i = 0;
	philo = (t_philo *)arg;
	dat = philo->data;
	pthread_mutex_lock(&dat->is_eating);
	printf("%d '%p'\n", philo->i, philo->data);
	pthread_mutex_unlock(&dat->is_eating);
	if (philo->i % 2)
		usleep(15000);
	while (!(dat->philo_died))
	{
		philo_eats(philo);
		if (dat->all_eat)
			break ;
		philo_print(dat, philo->i, "is sleeping");
		philo_wait(dat->sleep_time, dat);
		philo_print(dat, philo->i, "is thinking");
		i++;
	}
	return (NULL);
}

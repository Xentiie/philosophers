/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:46:28 by reclaire          #+#    #+#             */
/*   Updated: 2022/11/17 16:58:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void philo_print(t_data *dat, int id, char *string)
{
	sem_wait(dat->message);
	printf("%lli ", timestamp() - dat->start_time);
	printf("%i ", id + 1);
	printf("%s\n", string);
	sem_post(dat->message);
	return;
}

void philo_eats(t_philo *philo)
{
	t_data *dat;

	dat = philo->data;
	sem_wait(philo->data->forks);
	philo_print(dat, philo->i, "has taken a fork");
	sem_wait(philo->data->forks);
	philo_print(dat, philo->i, "has taken a fork");

	philo->last_eat_timestamp = timestamp();
	philo_print(dat, philo->i, "is eating");
	usleep(dat->eat_time * 1000);
	philo->eat_count++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void *philo_death_check(void *d)
{
	t_data *dat;
	t_philo *philo;

	philo = (t_philo *)d;
	dat = philo->data;
	while (1)
	{
		sem_wait(philo->data->death);
		if (timestamp() - philo->last_eat_timestamp > philo->data->death_time)
		{
			//philo_print(dat, philo->i, "died");
			sem_wait(dat->message);
			printf("%lli ", timestamp() - dat->start_time);
			printf("%i died\n", philo->i + 1);
			sem_post(dat->stop);
			break;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if (dat->eat_count != -1 && philo->eat_count >= dat->eat_count)
		{
			sem_wait(dat->message);
			printf("%lli ", timestamp() - dat->start_time);
			printf("%i Done !\n", philo->i + 1);
			sem_post(dat->stop);
			break;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

void *philo_thread(void *arg)
{
	int i;
	t_philo *philo;
	t_data *dat;
	pthread_t death_check;

	i = 0;
	philo = (t_philo *)arg;
	dat = philo->data;
	pthread_create(&death_check, NULL, philo_death_check, philo);
	pthread_detach(death_check);
	while (1)
	{
		philo_eats(philo);
		philo_print(dat, philo->i, "is sleeping");
		usleep(dat->sleep_time * 1000);
		philo_print(dat, philo->i, "is thinking");
		i++;
	}
	return (NULL);
}

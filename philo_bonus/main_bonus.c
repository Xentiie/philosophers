/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:47:47 by reclaire          #+#    #+#             */
/*   Updated: 2022/09/06 19:47:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <fcntl.h>
#include <sys/wait.h>

void	create_semaphores(t_data *dat)
{
	sem_unlink("death");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("forks");
	dat->death = sem_open("death", O_CREAT, S_IRWXU, 1);
	dat->message = sem_open("message", O_CREAT, S_IRWXU, 1);
	dat->stop = sem_open("stop", O_CREAT, S_IRWXU, 1);
	dat->forks = sem_open("forks", O_CREAT, S_IRWXU,
			dat->philo_count);
}

void	do_forks(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->philo_count)
	{
		dat->philos[i]->pid = fork();
		if (dat->philos[i]->pid == 0)
		{
			philo_thread(dat->philos[i]);
			exit(0);
		}
		i++;
		usleep(100);
	}
}

void	launch(t_data *dat)
{
	int	i;

	i = 0;
	dat->philos = malloc(sizeof(t_philo *) * dat->philo_count);
	while (i < dat->philo_count)
	{
		dat->philos[i] = malloc(sizeof(t_philo));
		dat->philos[i]->data = dat;
		dat->philos[i]->i = i;
		dat->philos[i]->last_eat_timestamp = timestamp();
		i++;
	}
	do_forks(dat);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid args\n");
		exit (1);
	}
	data = malloc(sizeof(t_data));
	data->philo_died = 0;
	data->start_time = timestamp();
	data->philo_count = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (data->philo_count < 1 || data->death_time < 0 || data->eat_time < 0
		|| data->sleep_time < 0 || data->philo_count > 250)
		return (1);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
	create_semaphores(data);
	sem_wait(data->stop);
	launch(data);
	sem_wait(data->stop);
	cleanup(data);

	return (0);
}

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

#include "philosophers.h"

void	mainloop(t_data *r, t_philo **philos)
{
	int	i;

	r->loop = 0;
	while (!(r->loop))
	{
		i = -1;
		while (++i < r->philo_count && !(r->philo_died))
		{
			if (timestamp() - philos[i]->last_eat_timestamp > r->death_time)
			{
				philo_print(r, i, "died");
				r->philo_died = 1;
			}
			usleep(100);
		}
		if (r->philo_died)
			break ;
		i = 0;
		while (r->eat_count != -1 && i < r->philo_count
			&& philos[i]->eat_count >= r->eat_count)
			i++;
		if (i == r->philo_count)
			r->loop = 1;
	}
}

void	launch(t_data *dat)
{
	int	i;

	i = 0;
	dat->philos = malloc(sizeof(t_philo *) * dat->philo_count);
	pthread_mutex_init(&(dat->is_eating), NULL);
	pthread_mutex_init(&(dat->print), NULL);
	while (i < dat->philo_count)
	{
		pthread_mutex_init(&(dat->forks[i]), NULL);
		dat->philos[i] = malloc(sizeof(t_philo));
		dat->philos[i]->data = dat;
		dat->philos[i]->i = i;
		dat->philos[i]->l_id = (i - 1);
		dat->philos[i]->r_id = i;
		dat->philos[i]->last_eat_timestamp = timestamp();
		pthread_create(&(dat->philos[i]->thread),
			NULL, philo_thread, dat->philos[i]);
		i++;
	}
	dat->philos[0]->l_id = dat->philo_count - 1;
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->philo_count < 1 || data->death_time < 0 || data->eat_time < 0
		|| data->sleep_time < 0 || data->philo_count > 250)
		return (1);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
	launch(data);
	mainloop(data, data->philos);
	free_all(data);
	return (0);
}

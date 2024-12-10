/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:54:01 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/10 15:38:03 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils/utils.h"

int init_struct(t_prog *prog, char **av, pthread_mutex_t *forks)
{
	int 			i;

	if(pthread_mutex_init(&prog->dead_lock, NULL) != 0)
		return 0;
	prog->is_dead = 0;
	prog->nb_of_philo = ft_atoi(av[1]);
	prog->philo = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
	if (!prog->philo)
		return (0);
	if (!forks)
		return (0);
	i = -1;
	while (++i < (ft_atoi(av[1])))
	{
		if(pthread_mutex_init(&forks[i], NULL) != 0)
			return 0;
	}
	return (init_philo(av, &prog->philo, forks));
}

int init_philo(char **av, t_philo **philo, pthread_mutex_t *forks)
{
	int i;

	i = -1;
	while (++i < (ft_atoi(av[1])))
	{
		if (pthread_mutex_init(&(*philo)[i].eat_lock, NULL) != 0)
			return (0);
		(*philo)[i].id = i + 1;
		(*philo)[i].nb_of_philo = ft_atoi(av[1]);
		(*philo)[i].eat_bool = 0;
		(*philo)[i].think_bool = 0;
		(*philo)[i].is_dead = 0;
		(*philo)[i].sleep_bool = 0;
		(*philo)[i].eaten = 0;
		if (av[5])
			(*philo)[i].eat_nrb_time = ft_atoi(av[5]);
		else
			(*philo)[i].eat_nrb_time = -1;
		(*philo)[i].time_to_die = ft_atoi(av[2]) * 1000;
		(*philo)[i].time_to_eat = ft_atoi(av[3]) * 1000;
		(*philo)[i].time_to_sleep = ft_atoi(av[4]) * 1000;
		(*philo)[i].time = 0;
		(*philo)[i].last_meal = 0;
		(*philo)[i].forks = forks;
		// imp
		// time_die - time_eat - time_sleep
		// test time_sleep > time_to_eat
		// test time_sleep < time_to_eat
		(*philo)[i].l_fork = &forks[i];
		(*philo)[i].r_fork = &forks[(i + 1) % ft_atoi(av[1])];
	}
	return (1);
}

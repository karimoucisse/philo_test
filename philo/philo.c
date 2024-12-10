/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:59:20 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/10 17:39:05 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils/utils.h"

void monitoring(t_prog *prog)
{
	int i;
	int is_full;
	int j;

	i = -1;
	is_full = 0;
	while (++i < prog->nb_of_philo)
	{
		usleep(15);
		j = -1;
		is_full = 0;
		while (++j < prog->nb_of_philo)
		{
			pthread_mutex_lock(&prog->philo[j].eat_lock);
			if (prog->philo[j].eaten == prog->philo[j].eat_nrb_time)
				is_full += 1;
			pthread_mutex_unlock(&prog->philo[j].eat_lock);
		}
		if (is_full == prog->nb_of_philo)
			break;
		if (ft_is_dead(&prog->philo[i]))
		{
			i = -1;
			while (++i < prog->nb_of_philo)
			{
				pthread_mutex_lock(prog->philo[i].dead_lock);
				prog->philo[i].is_dead = 1;
				pthread_mutex_unlock(prog->philo[i].dead_lock);
			}
			break;
		}
		if (i == (prog->nb_of_philo - 1))
			i = -1;
	}
}

int start_prog(t_prog prog, char **av)
{
	int i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_create(&prog.philo[i].p_thread, NULL, &routine, &(prog.philo[i])) != 0)
			prog_destroyer(&prog, 1);
	}
	return (1);
}

int end_prog(t_prog prog, char **av)
{
	int i;
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_join(prog.philo[i].p_thread, NULL) != 0)
			prog_destroyer(&prog, 1);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_prog prog;
	int i;
	int long start;
	pthread_mutex_t forks[200];

	check_args(ac, av);
	if (!init_struct(&prog, av, forks))
		prog_destroyer(&prog, 1);
	i = -1;
	start = current_time();
	while (++i < ft_atoi(av[1]))
	{
		prog.philo[i].dead_lock = &prog.dead_lock;
		prog.philo[i].print_lock = &prog.print_lock;
		prog.philo[i].start = start;
	}
	start_prog(prog, av);
	monitoring(&prog);
	end_prog(prog, av);
	prog_destroyer(&prog, 0);
}

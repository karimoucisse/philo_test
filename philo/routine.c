/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:29:23 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/13 15:32:00 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils/utils.h"

int	is_dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->eaten == philo->eat_nrb_time)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	if (philo->nb_of_philo % 2 && philo->time_to_eat > philo->time_to_sleep)
		usleep((philo->time_to_die - (philo->time_to_eat
					+ philo->time_to_sleep)) / 2);
	else if (philo->time_to_eat == philo->time_to_sleep)
		usleep(500);
	pthread_mutex_lock(philo->dead_lock);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if ((philo->nb_of_philo % 2) && philo->id == 1)
		usleep(10);
	else if (!(philo->id % 2))
		usleep((philo->time_to_eat / 2));
	while (1)
	{
		take_forks(philo);
		if (philo->nb_of_philo == 1)
			break ;
		ft_is_eating(philo);
		pthread_mutex_lock(&philo->eat_lock);
		print_msg(philo, "is sleeping");
		pthread_mutex_unlock(&philo->eat_lock);
		usleep(philo->time_to_sleep);
		pthread_mutex_lock(&philo->eat_lock);
		print_msg(philo, "is thinking");
		pthread_mutex_unlock(&philo->eat_lock);
		if (is_dead_or_full(philo))
			break ;
	}
	return (0);
}

void	ft_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	philo->time = current_time();
	print_msg(philo, "is eating");
	philo->last_meal = current_time();
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->eat_lock);
	usleep(philo->time_to_eat);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	handle_death(t_philo *philo)
{
	print_msg(philo, "died");
	pthread_mutex_lock(philo->dead_lock);
	philo->is_dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(&philo->eat_lock);
}

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->eaten == philo->eat_nrb_time)
		return (pthread_mutex_unlock(&philo->eat_lock), 0);
	if (philo->last_meal == 0
		&& ((current_time() - philo->start) >= (philo->time_to_die / 1000)))
	{
		handle_death(philo);
		return (1);
	}
	else if (((current_time() - philo->last_meal)
			>= (philo->time_to_die / 1000)) && philo->last_meal != 0)
	{
		handle_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

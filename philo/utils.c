/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:14:45 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/13 15:34:43 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	long int	time;

	pthread_mutex_lock(philo->dead_lock);
	if (!philo->is_dead)
	{
		time = current_time() - philo->start;
		pthread_mutex_lock(philo->print_lock);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
}

long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

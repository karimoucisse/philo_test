#include "philo.h"
#include "utils/utils.h"

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (((philo->id + 1) % 2) != 0)
		usleep(1500);
	// if((philo->nb_of_philo % 2 != 0) && (philo->id + 1) == philo->nb_of_philo)
	// 	usleep(philo->time_to_eat / 2);
	while (1)
	{
		take_forks(philo);
		if(philo->nb_of_philo == 1)
			break;
		ft_is_eating(philo);
		pthread_mutex_lock(&philo->eat_lock);
		if (philo->eaten == philo->eat_nrb_time)
		{
			pthread_mutex_unlock(&philo->eat_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->eat_lock);
		print_msg(philo, "is sleeping");
		usleep(philo->time_to_sleep);
		print_msg(philo, "is thinking");
		// usleep(1500);
		pthread_mutex_lock(philo->dead_lock);
		if (philo->is_dead)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(philo->dead_lock);
	}
	return (0);
}

void ft_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	philo->time = current_time();
	print_msg(philo, "is eating");
	philo->last_meal = current_time();
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->eat_lock);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->eaten == philo->eat_nrb_time)
		return (pthread_mutex_unlock(&philo->eat_lock), 0);
	if (philo->last_meal == 0 && ((current_time() - philo->start) >= (philo->time_to_die / 1000)))
	{
		pthread_mutex_unlock(&philo->eat_lock);
		print_msg(philo, "died");
		pthread_mutex_lock(philo->dead_lock);
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	else if (((current_time() - philo->last_meal) >= (philo->time_to_die / 1000)) && philo->last_meal != 0)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		print_msg(philo, "died");
		pthread_mutex_lock(philo->dead_lock);
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	else
		return (pthread_mutex_unlock(&philo->eat_lock), 0);
}

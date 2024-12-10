#include "philo.h"

void print_msg(t_philo *philo, char *msg)
{
	long int time;

	pthread_mutex_lock(philo->dead_lock);
	if (!philo->is_dead)
	{
		time = current_time() - philo->start;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(philo->dead_lock);
}

long	current_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

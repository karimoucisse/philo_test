#include "philo.h"
#include "utils/utils.h"

void take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
	if (philo->nb_of_philo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
		usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return;
	}
    if (philo->id % 2) {
        first_fork = philo->l_fork;
        second_fork = philo->r_fork;
    } else {
        first_fork = philo->r_fork;
        second_fork = philo->l_fork;
    }
    pthread_mutex_lock(first_fork);
    print_msg(philo, "has taken a fork");
    pthread_mutex_lock(second_fork);
    print_msg(philo, "has taken a fork");
}


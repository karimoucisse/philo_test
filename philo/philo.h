/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:59:31 by kcisse            #+#    #+#             */
/*   Updated: 2024/12/13 15:29:09 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				nb_of_philo;
	int				eat_bool;
	int				think_bool;
	int				is_dead;
	int				sleep_bool;
	int				eaten;
	int				eat_nrb_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		time;
	long int		last_meal;
	long int		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*print_lock;
	pthread_t		p_thread;
}	t_philo;

typedef struct s_prog
{
	int				nb_of_philo;
	int				current_id;
	int				is_dead;
	long int		start;
	long int		time_to_die;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_t		p_thread_m;
	t_philo			*philo;
}	t_prog;

// ERRORS
void		error_printer(char *msg);
void		prog_destroyer(t_prog *prog, int status);

// CHECKER
int			check_args(int ac, char **av);

// HANDLE STRUCT
int			init_struct(t_prog *prog, char **av, pthread_mutex_t *forks);
int			init_philo(char **av, t_philo **philo, pthread_mutex_t *forks);

// ROUTINE
void		*routine(void *data);
void		ft_is_eating(t_philo *philo);
int			ft_is_dead(t_philo *philo);

// MUTEX
void		take_forks(t_philo *philo);

// UTILS
void		print_msg(t_philo *philo, char *msg);
long int	current_time(void);

#endif

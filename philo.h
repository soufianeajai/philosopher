#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"
# define MIL_SEC_COEF 1000
# define GRANULARITY_US 60

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				id;
	int				nbr_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nbr_meals;
	int				meals_to_eat;
	int				dead;
	size_t			start_time;
	size_t			last_meal;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_mutex_t	*printing_lock;
}					t_philo;

void				ft_clear(t_philo *philos);
void				ft_sleep(size_t exact_time);
void				*simulate_dinner(void *arg);
int					everyone_alive(t_philo *philo);
int					philos_still_hungry(t_philo *philo);
size_t				time_now(void);
void				ft_initialize(t_philo *philos, t_philo input,
						pthread_mutex_t *printing_lock);
void				forks_init(t_philo *philos);
void				create_threads(t_philo *philos, void *simulate_dinner);
void				join_threads(t_philo *philos);
void				print_state(t_philo philo, char *state, size_t time,
						pthread_mutex_t *printing_lock);
int					ft_isdigit(char *str);
size_t				ft_atoi(const char *str);
void				ft_assign(t_philo *input, size_t nbr, int flag);
void				parse_input(t_philo *input, char **av);

#endif

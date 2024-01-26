#include "philo.h"

void	*simulate_dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->dead && philo->nbr_meals)
	{
		print_state(*philo, THINK, time_now(), philo->printing_lock);
		pthread_mutex_lock(philo->fork_1);
		print_state(*philo, TAKE_FORK, time_now(), philo->printing_lock);
		pthread_mutex_lock(philo->fork_2);
		print_state(*philo, TAKE_FORK, time_now(), philo->printing_lock);
		print_state(*philo, EAT, time_now(), philo->printing_lock);
		philo->last_meal = time_now();
		philo->nbr_meals--;
		ft_sleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->fork_2);
		pthread_mutex_unlock(philo->fork_1);
		print_state(*philo, SLEEP, time_now(), philo->printing_lock);
		ft_sleep(philo->time_to_sleep);
	}
	return (0);
}

int	everyone_alive(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_philos)
	{
		if (time_now() - philo[i].last_meal >= (size_t)philo[i].time_to_die)
		{
			print_state(philo[i], DEAD, time_now(), philo[i].printing_lock);
			i = 0;
			while (i < philo[0].nbr_philos)
			{
				philo[i].dead = 1;
				pthread_mutex_destroy(philo[i].fork_1);
				i++;
			}
			pthread_mutex_destroy(philo->printing_lock);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philos_still_hungry(t_philo *philo)
{
	int	i;
	int	need_to_eat;

	i = 0;
	need_to_eat = 0;
	while ((i < philo[0].nbr_philos) && (philo[0].nbr_meals > 0))
	{
		need_to_eat += philo[i].meals_to_eat;
		i++;
	}
	if ((need_to_eat == 0) && (philo[0].nbr_meals >= 0))
		return (0);
	return (1);
}

void	print_state(t_philo philo, char *state, size_t time,
		pthread_mutex_t *lock)
{
	if (philo.dead == 1)
		return ;
	pthread_mutex_lock(lock);
	printf("%lu %d %s\n", (time - philo.start_time), philo.id, state);
	if (strncmp(state, DEAD, strlen(DEAD)) != 0)
		pthread_mutex_unlock(lock);
}
// do not change anything in this function !!!!!~!

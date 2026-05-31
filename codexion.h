/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 18:59:21 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>

typedef struct s_simulation	t_simulation;
typedef struct s_coder		t_coder;

typedef struct s_dongle
{
	pthread_mutex_t	lock_dongle;
	int				is_taken;
	long			last_release_time;
}	t_dongle;

typedef struct s_request
{
	t_coder	*coder;
	int		arrival_order;
}	t_request;

typedef struct s_heap
{
	t_request	*requests;
	int			size;
}	t_heap;

struct s_coder
{
	int				ID;
	int				number_of_compiles_done;
	pthread_mutex_t	safe_number_of_compiles_done;
	long			start_of_last_compile;
	pthread_mutex_t	safe_start_of_last_compile;
	pthread_t		coder_thread;
	pthread_cond_t	wait;
	pthread_mutex_t	mut_wait;
	int				can_compile;
	t_simulation	*sim;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
};

struct s_simulation
{
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	int				coders_finished;
	int				count_mutex;
	char			*scheduler;
	long			time_start_simulation;
	int				arrival_counter;
	pthread_mutex_t	writing;
	int				is_mut_writing;
	int				stop_sim;
	pthread_mutex_t	stop_sim_mutex;
	int				is_mut_stop_sim;
	pthread_t		monitor_thread;
	pthread_t		scheduler_thread;
	pthread_mutex_t	finished_mutex;
	int				is_mut_finished;
	pthread_mutex_t	heap_mutex;
	int				is_mut_heap;
	t_coder			*coders;
	t_dongle		*dongles;
	t_heap			*request_heap;
};

int			parse_digit(int argc, char **argv);
int			fill_simulation(t_simulation *sim, char **argv);
int			check_scheduler(char *argv);
int			init_simulation(t_simulation *sim);
long		get_current_time_ms(void);
long		get_simulation_time(t_simulation *sim);
int			create_threads(t_simulation *sim);
int			join_threads(t_simulation *sim);
void		*coder_routine(void *arg);
void		log_status(t_simulation *sim, t_coder *coder, char *message);
void		*monitor(void *arg);
int			get_stop(t_simulation *sim);
void		set_stop(t_simulation *sim);
long		get_start(t_coder *coder);
void		set_start(t_coder *coder);
void		smart_sleep(t_simulation *sim, long time_to_wait);
int			take_dongle(t_coder *coder);
void		release_dongle(t_coder *coder);
int			get_compile_nbr(t_coder *coder);
void		increment_compile_nbr(t_coder *coder);
void		heapify_up(t_heap *heap, t_simulation *sim);
void		heapify_down(t_heap *heap, t_simulation *sim);
void		heap_push(t_heap *heap, t_request request, t_simulation *sim);
t_request	heap_pop(t_heap *heap, t_simulation *sim);
void		*scheduler_routine(void *arg);
void		wait_simulation_start(t_simulation *sim);
void		notify_compile_finished(t_coder *coder);
long		safe_atol(char *str);
int			coder_cycle(t_coder *coder);

#endif

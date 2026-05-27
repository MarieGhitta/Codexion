/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:29 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
#include <pthread.h>

typedef struct s_simulation t_simulation;

typedef struct s_dongle {
    pthread_mutex_t lock_dongle;
} t_dongle;

typedef struct s_coder {
    int ID;
    int number_of_compiles_done;
    long    start_of_last_compile;
    pthread_mutex_t safe_start_of_last_compile;
    pthread_mutex_t safe_number_of_compiles_done;
    t_simulation *sim;
    pthread_t    coder_thread;
    t_dongle    *left_dongle;
    t_dongle    *right_dongle;
} t_coder;

struct s_simulation {
    int number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    int count_mutex;
    char *scheduler;
    long    time_start_simulation;
    pthread_mutex_t writing;
    pthread_mutex_t stop_sim_mutex;
    pthread_t   monitor_thread;
    int is_mut_writing;
    int stop_sim;
    int is_mut_stop_sim;
    t_coder    *coders;
    t_dongle    *dongles;
    
};


int parse_digit(int argc, char **argv);
int fill_simulation(t_simulation *sim, char **argv);
int check_scheduler(char *argv);
int init_simulation(t_simulation *sim);
long get_current_time_ms();
long get_simulation_time(t_simulation *sim);
int create_threads(t_simulation *sim);
int join_threads(t_simulation *sim);
void *coder_routine(void *arg);
void log_status(t_simulation *sim, t_coder *coder, char *message);
void *monitor(void *arg);
int get_stop(t_simulation *sim);
void set_stop(t_simulation *sim);
long get_start(t_coder *coder);
void set_start(t_coder *coder);
void smart_sleep(t_simulation *sim, long time_to_wait);
int take_dongle(t_coder *coder);
void release_dongle(t_coder *coder);
int get_compile_nbr(t_coder *coder);
void increment_compile_nbr(t_coder *coder);

#endif

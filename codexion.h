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

typedef struct s_simulation {
    int number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
    t_coder    *coders;
    t_dongle    *dongles;
    
} t_simulation;

typedef struct s_dongle {
    pthread_mutex_t lock_dongle;
} t_dongle;

typedef struct s_coder {
    int ID;
    int number_of_compiles_done;
    long    start_of_last_compile;
    t_simulation *sim;
    pthread_t    coder;
    t_dongle    *left_dongle;
    t_dongle    *right_dongle;
} t_coder;

int parse_digit(int argc, char **argv);
int fill_simulation(t_simulation *sim, char **argv);
int check_scheduler(char *argv);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:02:31 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

static int fill_coders_and_dongles(t_simulation *sim)
{
    sim->coders = malloc(sim->number_of_coders * sizeof(t_coder));
    if (!sim->coders)
        return 1;
    sim->dongles = malloc(sim->number_of_coders * sizeof(t_dongle));
    if (!sim->dongles)
    {
        free(sim->coders);
        return 1;
    }
    return 0;
}

static int init_dongles(t_simulation *sim)
{
    int i;
    int lock_dongle_init;

    i = 0;
    while (i < sim->number_of_coders)
    {
        lock_dongle_init = pthread_mutex_init(&sim->dongles[i].lock_dongle, NULL);
        if (lock_dongle_init != 0)
            return 1;
        sim->count_mutex += 1;
        i++;
    }
    return 0;
}

static int init_coders(t_simulation *sim)
{
    int i;
    int start_compile_init;       

    i = 0;
    while(i < sim->number_of_coders)
    {
        sim->coders[i].ID = i + 1;
        sim->coders[i].number_of_compiles_done = 0;
        sim->coders[i].start_of_last_compile = 0;
        sim->coders[i].left_dongle = &sim->dongles[i % sim->number_of_coders];
        sim->coders[i].right_dongle = &sim->dongles[(i + 1) % sim->number_of_coders];
        sim->coders[i].sim = sim;
        start_compile_init = pthread_mutex_init(&sim->coders[i].safe_start_of_last_compile, NULL);
        if (start_compile_init != 0)
            return 1;
        i++;
    }
    return 0;
}

int init_simulation(t_simulation *sim)
{
    int mutex_writing;
    int mutex_stop_sim;

    if (fill_coders_and_dongles(sim) == 1)
        return 1;
    if (init_dongles(sim) == 1)
        return 1;
    if (init_coders(sim) == 1)
        return 1;
    mutex_writing = pthread_mutex_init(&sim->writing, NULL);
    if (mutex_writing != 0)
        return 1;
    sim->is_mut_writing = 1;
    mutex_stop_sim = pthread_mutex_init(&sim->stop_sim_mutex, NULL);
    if (mutex_stop_sim  != 0)
        return 1;
    sim->is_mut_stop_sim = 1;
    sim->request_heap->size = 0;
    return 0;
}
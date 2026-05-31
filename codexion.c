/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:37 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void destroy_mutex_coders(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->count_mutex)
    {
        pthread_mutex_destroy(&sim->dongles[i].lock_dongle);
        pthread_mutex_destroy(&sim->coders[i].safe_start_of_last_compile);
        pthread_mutex_destroy(
            &sim->coders[i].safe_number_of_compiles_done);
        pthread_mutex_destroy(&sim->coders[i].mut_wait);
        pthread_cond_destroy(&sim->coders[i].wait);
        i++;
    }
}

void destroy_simulation(t_simulation *sim)
{
    if (sim)
    {
        if (sim->is_mut_writing)
            pthread_mutex_destroy(&sim->writing);
        if (sim->is_mut_stop_sim)
            pthread_mutex_destroy(&sim->stop_sim_mutex);
        pthread_mutex_destroy(&sim->heap_mutex);
        pthread_mutex_destroy(&sim->finished_mutex);
        destroy_mutex_coders(sim);
        if (sim->dongles)
            free(sim->dongles);
        if (sim->coders)
            free(sim->coders);
        if (sim->request_heap)
        {
            if (sim->request_heap->requests)
                free(sim->request_heap->requests);
            free(sim->request_heap);
        }
    }
    free(sim);
}

static int init_heap(t_simulation *sim)
{
    sim->request_heap = malloc(sizeof(t_heap));
    if (!sim->request_heap)
        return (1);
    sim->request_heap->requests = 
        malloc(sim->number_of_coders * sizeof(t_request));
    if (!sim->request_heap->requests)
    {
        free(sim->request_heap);
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_simulation *sim;

    if (argc != 9)
        return (printf("ERROR: must be 8 arguments\n"), 1);
    if (parse_digit(argc, argv))
        return (1);
    if (check_scheduler(argv[8]))
        return (1);
    sim = malloc(sizeof(t_simulation));
    if (!sim)
        return (1);
    memset(sim, 0, sizeof(t_simulation));
    if (fill_simulation(sim, argv))
        return (free(sim), printf("Error\n"), 1);
    if (init_heap(sim))
        return (free(sim), 1);
    init_simulation(sim);
    sim->time_start_simulation = get_current_time_ms();
    create_threads(sim);
    join_threads(sim);
    destroy_simulation(sim);
    return (0);
}

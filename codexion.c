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

void destroy_simulation(t_simulation *sim)
{
    int i;

    i = 0;
    if (sim)
    {
        if (sim->is_mut_writing)
            pthread_mutex_destroy(&sim->writing);
        while (i < sim->count_mutex)
        {
            pthread_mutex_destroy(&sim->dongles[i].lock_dongle);
            i++;
        }
        if (sim->dongles)
            free(sim->dongles);
        if (sim->coders)
            free(sim->coders);
    }
    free(sim);
}

int main(int argc, char **argv){
    if (argc != 9) {
        printf("ERROR: must be 8 arguments\n");
        return 1;
    }
    if (parse_digit(argc, argv) == 1)
        return 1;
    if (check_scheduler(argv[8]))
        return 1;
    t_simulation *sim;
    sim = malloc(sizeof(t_simulation));
    if (!sim)
        return 1;
    memset(sim, 0, sizeof(t_simulation));
    fill_simulation(sim, argv);
    init_simulation(sim);
    sim->time_start_simulation = get_simulation_time(sim);
    create_threads(sim);
    join_threads(sim);
    destroy_simulation(sim);
    return 0;
}

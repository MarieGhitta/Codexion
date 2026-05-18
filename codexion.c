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

void destroy_simulation(t_simulation *sim)
{
    int i;

    i = 0;
    if (sim)
    {
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
    //test fill-in
    int i;

    i = 0;
    while (i < sim->number_of_coders)
    {
        printf("coders ID: %d\n", sim->coders[i].ID);
        printf("Left dongle: %p\n", sim->coders[i].left_dongle);
        printf("Right dongle: %p\n", sim->coders[i].right_dongle);
        printf("Compile: %d fois\n", sim->coders[i].number_of_compiles_done);
        printf("Last compile time: %ld\n", sim->coders[i].start_of_last_compile);
        i++;
    }
    destroy_simulation(sim);
    return 0;
}

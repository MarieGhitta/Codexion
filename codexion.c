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
        return NULL;
    fill_simulation(sim, argv);
    printf("Nb codeurs: %d\n", sim->number_of_coders);
    printf("Time burnout: %ld\n", sim->time_to_burnout);
    printf("Time compile: %ld\n", sim->time_to_compile);
    printf("Time debug: %ld\n", sim->time_to_debug);
    printf("Time refactor: %ld\n", sim->time_to_refactor);
    printf("Nb compiles: %d\n", sim->number_of_compiles_required);
    printf("Dongle cooldown: %d\n", sim->dongle_cooldown);
    printf("Scheduler: %s\n", sim->scheduler);
    free(sim);
    return 0;
}

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
        return 1;
    fill_simulation(sim, argv);
    init_simulation(sim);
    //test fill-in
    int i;

    i = 0;
    while (i < sim->number_of_coders)
    {
        printf("coders ID: %d\n", sim->coders[i].ID);
        
        i++;
    }
    free(sim);
    return 0;
}

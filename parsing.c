/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:02:31 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "codexion.h"

static int is_digit(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    return 0;
}

int parse_digit(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc - 1)
    {
        j = 0;
        if (!argv[i][j])
            return (printf("ERROR: empty string.\n"), 1);
        if (argv[i][0] == '+')
            j++;
        if (!argv[i][j])
            return (printf("ERROR: invalid format, must be a positif digit.\n"),1);
        while (argv[i][j])
        {
            if (!is_digit(argv[i][j]))
                return (printf("ERROR: must be a positif digit.\n"), 1);
            j++;   
        }
        i++;
    }
    return 0;
}

int check_scheduler(char *argv)
{
    if (strcmp(argv, "fifo") != 0 && strcmp(argv, "edf") != 0)
    {
        printf("ERROR: invalid scheduler format.\n");
        return 1;
    }
    return 0;
}

int fill_simulation(t_simulation *sim, char **argv)
{
    sim->number_of_coders = atoi(argv[1]);
    sim->time_to_burnout = atoi(argv[2]);
    sim->time_to_compile = atoi(argv[3]);
    sim->time_to_debug = atoi(argv[4]);
    sim->time_to_refactor = atoi(argv[5]);
    sim->number_of_compiles_required = atoi(argv[6]);
    sim->dongle_cooldown = atoi(argv[7]);
    sim->scheduler = argv[8];
    return 0;
}
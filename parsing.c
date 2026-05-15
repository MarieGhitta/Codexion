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

void parse_int_str(number_of_coders, number_of_compiles_required, scheduler)
{
    if atoi(number_of_coders) < 0
    {
        printf("ERROR: number of coders must be a positive number.\n");
        return 1;
    }
    if atoi(number_of_compiles_required) < 0
    {
        printf("ERROR: number_of_compiles_required must be a positive number.\n");
        return 1;
    }
    if strcmp(scheduler, "fifo") != 0 or strcmp(scheduler, "edf") != 0 {
        printf("ERROR: incorrect format for scheduler.\n")
    }
}
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

int is_digit(char c){
    if (c >= 48 && c <= 57)
        return 1;
    return 0;
}

int parse_digit(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc - 1){
        j = 0;
        if (!argv[i][j]){
            printf("ERROR: empty string.\n");
            return 1;
        }
        if (argv[i][0] == '+' && argv[i][1])
            j++;
        while (argv[i][j]){
            if (!is_digit(argv[i][j]))
            {
                printf("ERROR: must be a digit.\n");
                return 1;
            }
            j++;   
        }
        i++;
    }
    return 0;
    /*if (atoi(number_of_coders) < 0)
    {
        printf("ERROR: number of coders must be a positive number.\n");
        return 1;
    }
    if (atoi(number_of_compiles_required) < 0)
    {
        printf("ERROR: number_of_compiles_required must be a positive number.\n");
        return 1;
    }
    if (strcmp(scheduler, "fifo") != 0 && strcmp(scheduler, "edf") != 0) {
        printf("ERROR: incorrect format for scheduler.\n");
    }*/
}
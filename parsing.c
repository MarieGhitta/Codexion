/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:02:29 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 18:26:21 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "codexion.h"
#include <limits.h>

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	parse_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc - 1)
	{
		j = 0;
		if (!argv[i][j])
			return (printf("ERROR: empty string.\n"), 1);
		if (argv[i][0] == '+')
			j++;
		if (!argv[i][j])
			return (printf("ERROR: must be a positif digit.\n"), 1);
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (printf("ERROR: must be a positif digit.\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_scheduler(char *argv)
{
	if (strcmp(argv, "fifo") != 0 && strcmp(argv, "edf") != 0)
	{
		printf("ERROR: invalid scheduler format.\n");
		return (1);
	}
	return (0);
}

static int	parse_int(t_simulation *sim, char **argv)
{
	long	value;

	value = safe_atol(argv[1]);
	if (value == -1 || value == 0 || value > INT_MAX)
		return (1);
	sim->number_of_coders = (int)value;
	value = safe_atol(argv[6]);
	if (value == -1 || value == 0 || value > INT_MAX)
		return (1);
	sim->number_of_compiles_required = (int)value;
	value = safe_atol(argv[7]);
	if (value == -1 || value > INT_MAX)
		return (1);
	sim->dongle_cooldown = (int)value;
	return (0);
}

static int	parse_long(t_simulation *sim, char **argv)
{
	long	value;

	value = safe_atol(argv[2]);
	if (value == -1 || value == 0)
		return (1);
	sim->time_to_burnout = value;
	value = safe_atol(argv[3]);
	if (value == -1 || value == 0)
		return (1);
	sim->time_to_compile = value;
	value = safe_atol(argv[4]);
	if (value == -1 || value == 0)
		return (1);
	sim->time_to_debug = value;
	value = safe_atol(argv[5]);
	if (value == -1 || value == 0)
		return (1);
	sim->time_to_refactor = value;
	sim->scheduler = argv[8];
	return (0);
}

int	fill_simulation(t_simulation *sim, char **argv)
{
	if (parse_int(sim, argv))
		return (1);
	if (parse_long(sim, argv))
		return (1);
	return (0);
}

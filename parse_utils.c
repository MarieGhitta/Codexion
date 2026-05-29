/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:35 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/15 15:00:37 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>

long safe_atol(char *str)
{
    long    nbr;
    int     i;

    nbr = 0;
    i = 0;

    if (!str || !str[0])
        return (1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        if (nbr > (LONG_MAX - (str[i] - '0')) / 10)
            return (-1);
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr);
}
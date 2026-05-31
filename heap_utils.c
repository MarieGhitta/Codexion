/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 17:14:42 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>
#include <string.h>

static int	compare_request(t_request request_a,
	t_request request_b, t_simulation *sim)
{
	long	deadline_a;
	long	deadline_b;

	deadline_a = get_start(request_a.coder) + sim->time_to_burnout;
	deadline_b = get_start(request_b.coder) + sim->time_to_burnout;
	if (strcmp(sim->scheduler, "fifo") == 0)
	{
		if (request_a.arrival_order > request_b.arrival_order)
			return (1);
	}
	if (strcmp(sim->scheduler, "edf") == 0)
	{
		if (deadline_a > deadline_b)
			return (1);
		if (deadline_a == deadline_b)
			return (request_a.arrival_order > request_b.arrival_order);
	}
	return (0);
}

void	heapify_up(t_heap *heap, t_simulation *sim)
{
	int			i;
	int			parent;
	t_request	temp_request;

	i = heap->size - 1;
	while ((i != 0))
	{
		parent = (i - 1) / 2;
		if (compare_request(heap->requests[parent],
				heap->requests[i], sim) == 1)
		{
			temp_request = heap->requests[i];
			heap->requests[i] = heap->requests[parent];
			heap->requests[parent] = temp_request;
			i = parent;
		}
		else
			break ;
	}
}

static int	find_priority_child(t_heap *heap, t_simulation *sim, int i)
{
	int	left_child;
	int	right_child;
	int	priority_child;

	left_child = 2 * i + 1;
	right_child = 2 * i + 2;
	if (left_child >= heap->size)
		return (-1);
	else if (right_child >= heap->size)
		priority_child = left_child;
	else
	{
		if (compare_request(heap->requests[left_child],
				heap->requests[right_child], sim) == 1)
			priority_child = left_child;
		else
			priority_child = right_child;
	}
	return (priority_child);
}

void	heapify_down(t_heap *heap, t_simulation *sim)
{
	int			i;
	int			priority_child;
	t_request	temp_request;

	i = 0;
	while ((1))
	{
		priority_child = find_priority_child(heap, sim, i);
		if (priority_child == -1)
			break ;
		if ((compare_request(heap->requests[i],
					heap->requests[priority_child], sim) == 1))
		{
			temp_request = heap->requests[priority_child];
			heap->requests[priority_child] = heap->requests[i];
			heap->requests[i] = temp_request;
			i = priority_child;
		}
		else
			break ;
	}
}

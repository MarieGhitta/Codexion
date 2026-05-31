/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghitta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:00:27 by mghitta           #+#    #+#             */
/*   Updated: 2026/05/31 18:03:12 by mghitta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>
#include <string.h>

void	heap_push(t_heap *heap, t_request request, t_simulation *sim)
{
	heap->requests[heap->size] = request;
	heap->size += 1;
	heapify_up(heap, sim);
}

t_request	heap_pop(t_heap *heap, t_simulation *sim)
{
	t_request	pop_request;

	pop_request = heap->requests[0];
	heap->requests[0] = heap->requests[heap->size - 1];
	heap->size -= 1;
	heapify_down(heap, sim);
	return (pop_request);
}

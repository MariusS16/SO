// SPDX-License-Identifier: BSD-3-Clause

#include "log/log.h"
#include "os_graph.h"
#include "os_threadpool.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 4

static int sum;
static os_graph_t *graph;
static os_threadpool_t *tp;
/* TODO: Define graph synchronization mechanisms. */
pthread_mutex_t main_mutex;
pthread_mutex_t helper_mutex;

/* TODO: Define graph task argument. */
typedef struct {
	unsigned int node_index;
} graph_task_arg_t;

static void process_node(void *idx);

graph_task_arg_t *create_graph_task_arg(unsigned int node_index)
{
	graph_task_arg_t *arg = malloc(sizeof(*arg));

	DIE(arg == NULL, "malloc");
	arg->node_index = node_index;
	return arg;
}

static void graph_task_function(void *arg)
{
	graph_task_arg_t *task_arg = (graph_task_arg_t *)arg;
	unsigned int idx = task_arg->node_index;

	unsigned int num_neighbours = graph->nodes[idx]->num_neighbours;

	while (num_neighbours > 0) {
		unsigned int neighbour = graph->nodes[idx]->neighbours[--num_neighbours];

		pthread_mutex_lock(&helper_mutex);
		if (graph->visited[neighbour] != NOT_VISITED) {
			pthread_mutex_unlock(&helper_mutex);
			continue;
		}

		graph->visited[neighbour] = PROCESSING;
		enqueue_task(tp, create_task(process_node, create_graph_task_arg(neighbour), NULL));
		pthread_mutex_unlock(&helper_mutex);
	}
}

static void process_node(void *idx)
{
	if (graph->visited[*(unsigned int *)idx] == DONE)
		return;

	pthread_mutex_lock(&main_mutex);

	sum += graph->nodes[*(unsigned int *)idx]->info;
	graph->visited[*(unsigned int *)idx] = DONE;

	enqueue_task(tp, create_task(graph_task_function, create_graph_task_arg(*(unsigned int *)idx), free));
	pthread_mutex_unlock(&main_mutex);
}

int main(int argc, char *argv[])
{
	FILE *input_file;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input_file = fopen(argv[1], "r");
	DIE(input_file == NULL, "fopen");

	graph = create_graph_from_file(input_file);

	/* TODO: Initialize graph synchronization mechanisms. */
	pthread_mutex_init(&main_mutex, NULL);
	pthread_mutex_init(&helper_mutex, NULL);

	graph_task_arg_t *argument = malloc(sizeof(*argument));

	DIE(argument == NULL, "malloc");
	argument->node_index = 0;

	tp = create_threadpool(NUM_THREADS);
	enqueue_task(tp, create_task(process_node, argument, free));
	wait_for_completion(tp);
	destroy_threadpool(tp);

	printf("%d", sum);

	return 0;
}

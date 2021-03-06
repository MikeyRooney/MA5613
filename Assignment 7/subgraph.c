#include "common.h"

static struct subgraph_entry *get_subgraph_entry_for_vertex(struct subgraph *s, int vert_number){
	struct list_entry *e = s->entries->head;
	while(e != NULL){
		struct subgraph_entry *se = e->data;
		if(se->vertex->number == vert_number){
			return se;
		}
		e = e->next;
	}
	return NULL;
}

static struct subgraph_entry *insert_vertex_into_subgraph(struct subgraph *s, struct vertex_cell *v){
	struct subgraph_entry *se = calloc(1, sizeof(struct subgraph_entry));
	se->vertex = v;
	append_entry_to_list(s->entries, se);
	v->subgraph_link = s;
	s->num_vertices++;
	return se;
}

// See report for details on how this works.
static void find_subgraph_from_starting_vertex(struct subgraph *s, struct vertex_cell *v){
	struct subgraph_entry *e = get_subgraph_entry_for_vertex(s, v->number);
	if(e == NULL){
		e = insert_vertex_into_subgraph(s, v);
	}
	e->connections_visited = 1;
	int i;
	for(i = 0; i < v->num_connections; i++){
		struct vertex_cell *v_conn = get_connection_by_index(v, i);
		struct subgraph_entry *e_conn = get_subgraph_entry_for_vertex(s, v_conn->number);
		int conn_visited = 0;
		if(e_conn != NULL){
			conn_visited = e_conn->connections_visited;
		}
		if(conn_visited == 0){
			find_subgraph_from_starting_vertex(s, v_conn);
		}
	}
}

// Note: the first vertex is handled outside of the for loop, so the for loop
// starts at i=1.
void find_subgraphs(){
	NUM_SUBGRAPHS = 0;
	subgraphs = calloc(1, sizeof(struct list));
	struct list_entry *cur = calloc(1, sizeof(struct list_entry));
	struct subgraph *s = calloc(1, sizeof(struct subgraph));
	s->entries = calloc(1, sizeof(struct list_entry));
	cur->data = s;
	subgraphs->head = cur;
	s->id = 0;
	find_subgraph_from_starting_vertex(s, ALL_VERTICES->head->data);
	NUM_SUBGRAPHS++;
	int i;
	for(i = 1; i < NUM_VERTICES; i++){
		struct vertex_cell *c = get_vertex_by_id(i);
		if(c->subgraph_link != NULL){
			continue;
		}
		cur->next = calloc(1, sizeof(struct list_entry));
		cur = cur->next;
		s = calloc(1, sizeof(struct subgraph));
		s->entries = calloc(1, sizeof(struct list_entry));
		s->id = 1;
		cur->data = s;
		find_subgraph_from_starting_vertex(cur->data, get_vertex_by_id(i));
		NUM_SUBGRAPHS++;
	}
	printf("Number of subgraphs: %d\n", NUM_SUBGRAPHS);
}


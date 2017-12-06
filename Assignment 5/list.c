#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Helper function used in find_before and find_after
static Cell * find_cell_with_word(const char *word, const List l){
	Cell *c = l.head;
	do {
		if(strcmp(c->word, word) == 0){
			return c;
		}
		c = c->next;
	} while(c != NULL);
	return NULL;
}

// Helper function to create a new cell and set its word.
static Cell * create_cell_with_word(const char *word){
	int wlen = strlen(word) + 1; // includes \0 byte
	Cell *c = calloc(1, sizeof(Cell));
	c->word = malloc(wlen);	
	memcpy(c->word, word, wlen);
	return c;
}

List insert_after(const char *find, const char *word, List l){
	Cell *found_cell = find_cell_with_word(find, l);
	Cell *new_cell = create_cell_with_word(word);
	if(l.tail == found_cell){
		l.tail = new_cell;
	}
	new_cell->prev = found_cell;
	if(found_cell->next != NULL){
		new_cell->next = found_cell->next;
		found_cell->next->prev = new_cell;
		found_cell->next = new_cell;
	} else {
		found_cell->next = new_cell;
	}
	return l;
}

// TODO: empty list, other situations like that
List insert_before(const char *find, const char *word, List l){
	Cell *found_cell = find_cell_with_word(find, l);
	Cell *new_cell = create_cell_with_word(word);
	if(l.head == found_cell){
		l.head = new_cell;
	}
	new_cell->next = found_cell;
	if(found_cell->prev != NULL){
		new_cell->prev = found_cell->prev;
		found_cell->prev->next = new_cell;
		found_cell->prev = new_cell;
	} else {
		found_cell->prev = new_cell;
	}
	return l;
}

List append(const char *word, List l){
	if(l.head == NULL){
		Cell *c = create_cell_with_word(word);
		l.head = c;
		l.tail = c;
		return l;
	}
	Cell *c = create_cell_with_word(word);
	c->prev = l.tail;
	l.tail->next = c;
	l.tail = c;
	return l;
}

// Prints list in reverse to verify that prev has been set correctly.
void print_list_reverse(const List l){
	printf("*** Printing list in reverse ***\n");
	if(l.tail == NULL){
		printf("List is empty.\n");
	}
	Cell *c = l.tail;
	int i = 0;
	do {
		printf("Cell %d contains: %s\n", i, c->word);
		c = c->prev;
		i++;
	} while(c != NULL);	
}

void print_list(const List l){
	printf("*** Printing list ***\n");
	if(l.head == NULL){
		printf("List is empty.\n");
	}
	Cell *c = l.head;
	int i = 0;
	do {
		printf("Cell %d contains: %s\n", i, c->word);
		c = c->next;
		i++;
	} while(c != NULL);	
}

// TODO: clean this up
/*
List reverse(List l){
	List rev = {.head=NULL, .tail=NULL};
	if(l.head == NULL){
		return rev;
	}
	Cell *old_cell = l.tail;
	Cell *prev_cell = calloc(1, sizeof(Cell));
	prev_cell->word = old_cell->word;
	Cell *next_cell = prev_cell; // handle case with 1 cell -> this will be tail and head
	rev.head = prev_cell;
	old_cell = old_cell->prev;
	while(old_cell != NULL){
		next_cell = calloc(1, sizeof(Cell));
		next_cell->word = old_cell->word;
		prev_cell->next = next_cell;
		next_cell->prev = prev_cell;
		prev_cell = next_cell;
		old_cell = old_cell->prev;
	} 
	rev.tail = next_cell;
	return rev;
}
*/

List reverse(List l){
	if(l.head == NULL){
		return l;
	}
	/*
	Cell *temp;
	temp = l.head;
	l.head = l.tail;
	l.tail = temp;
	*/
	Cell *c = l.head;
	Cell *temp;
	do {
		if(c->prev == NULL){ // is old head
			temp = c->next;
			c->next = NULL;
			c->prev = temp;
			c = temp;
		} else if(c->next == NULL){ // is old tail
			c->next = c->prev;
			c->prev = NULL;
			c = NULL;
		} else {
			temp = c->next;
			c->next = c->prev;
			c->prev = temp;
			c = temp;
		}
	} while(c != NULL);
	// Finally swap head and tail
	temp = l.head;
	l.head = l.tail;
	l.tail = temp;
	return l;
}

// TODO
void free_list(List l){

}

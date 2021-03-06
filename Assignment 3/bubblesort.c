#include <stdio.h>
#include <string.h>

void bubblesort(char string[]){
	int in_order = 0;
	int str_len = strlen(string);
	while(in_order == 0){
		in_order = 1;
		int i;
		for(i = 0; i < str_len - 1; i++){
			if(string[i] > string[i + 1]){
				// Swap using XOR - avoids needing temp variable 
				// See https://en.wikipedia.org/wiki/XOR_swap_algorithm
				string[i] ^= string[i + 1];
				string[i + 1] ^= string[i];
				string[i] ^= string[i + 1];
				in_order = 0;
			}
		}
	}
}

int main(void){
	char s[] = "the quick brown fox jumps over the lazy dog";
	printf("Unsorted string:\n%s\n", s);
	bubblesort(s);
	printf("Sorted string:\n%s\nNote that spaces are included as part of the sort.\n", s);
}


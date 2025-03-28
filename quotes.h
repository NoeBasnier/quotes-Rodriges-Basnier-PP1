#ifndef QUOTES_H
#define QUOTES_H

void load_quotes(const char *filename);
void print_all_quotes();
void add_quote(const char *new_quote);
void remove_quote(int index);
void print_random_quote();
void free_quotes();
void menu();

#endif
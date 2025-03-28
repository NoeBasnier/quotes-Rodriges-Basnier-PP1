#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quotes.h"

#define MAX_QUOTES 100
#define MAX_LENGTH 256

char **quotes = NULL;
int quote_count = 0;

void load_quotes(const char *filename) {
    FILE *file = fopen(filename, "r");
    quotes = malloc(MAX_QUOTES * sizeof(char*));
    if (!file) {
        printf("Fichier %s non trouve. Utilisation des citations par defaut.\n", filename);
        const char *default_quotes[] = {
            "Programmer - An organism that turns caffeine into code",
            "Why do programmers prefer dark mode? Because light attracts bugs.",
            "If debugging is the process of removing software bugs, then programming must be the process of putting them in.",
            "I don't always test my code, but when I do, I do it in production.",
            "Why do programmers always mix up Christmas and Halloween? Because Oct 31 == Dec 25!",
            "Why did the programmer quit his job? Because he didn't get arrays.",
            "Why do programmers prefer iOS development? Because the Swift.",
            "Why do programmers prefer dogs over cats? Because dogs have fetch and cats have catch.",
            "Why do programmers hate nature? It has too many bugs.",
            "There are only 10 types of people in the world: Those who understand binary and those who don't."
        };
        int nb_default = sizeof(default_quotes) / sizeof(default_quotes[0]);
        for (int i = 0; i < nb_default; i++) {
            quotes[i] = strdup(default_quotes[i]);
        }
        quote_count = nb_default;
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) && quote_count < MAX_QUOTES) {
        buffer[strcspn(buffer, "\n")] = 0;
        quotes[quote_count] = strdup(buffer);
        quote_count++;
    }
    fclose(file);
    printf("Citations chargees depuis le fichier %s.\n", filename);
}

void print_all_quotes() {
    printf("Liste des citations :\n");
    for (int i = 0; i < quote_count; i++) {
        printf("%d: %s\n", i + 1, quotes[i]);
    }
}

void add_quote(const char *new_quote) {
    if (quote_count >= MAX_QUOTES) {
        printf("Erreur : Nombre maximal de citations atteint.\n");
        return;
    }
    quotes[quote_count] = strdup(new_quote);
    quote_count++;
    printf("Citation ajoutee avec succès !\n");
}

void remove_quote(int index) {
    if (index < 1 || index > quote_count) {
        printf("Erreur : Index invalide.\n");
        return;
    }
    free(quotes[index - 1]);
    for (int i = index - 1; i < quote_count - 1; i++) {
        quotes[i] = quotes[i + 1];
    }
    quote_count--;
    printf("Citation supprimee avec succès !\n");
}

void print_random_quote() {
    if (quote_count == 0) {
        printf("Aucune citation disponible.\n");
        return;
    }
    int index = rand() % quote_count;
    printf("Citation aleatoire: %s\n", quotes[index]);
}

void free_quotes() {
    for (int i = 0; i < quote_count; i++) {
        free(quotes[i]);
    }
    free(quotes);
    printf("Memoire liberee.\n");
}

void menu() {
    int choice;
    char buffer[MAX_LENGTH];
    while (1) {
        printf("\nMenu :\n");
        printf("1. Afficher toutes les citations\n");
        printf("2. Ajouter une citation\n");
        printf("3. Supprimer une citation\n");
        printf("4. Afficher une citation aleatoire\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                print_all_quotes();
                break;
            case 2:
                printf("Entrez la nouvelle citation : ");
                fgets(buffer, MAX_LENGTH, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                add_quote(buffer);
                break;
            case 3: {
                printf("Entrez le numero de la citation à supprimer : ");
                int index;
                scanf("%d", &index);
                getchar();
                remove_quote(index);
                break;
            }
            case 4:
                print_random_quote();
                break;
            case 5:
                free_quotes();
                return;
            default:
                printf("Choix invalide.\n");
        }
    }
}
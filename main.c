#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "quotes.h"

int main() {
    srand(time(NULL));
    load_quotes("quotes.txt");
    menu();
    return 0;
}
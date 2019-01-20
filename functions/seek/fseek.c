#include <stdio.h>

#include <stdlib.h>     // exit()

int main() {

    FILE *f = fopen("words.txt", "r");
    if (!f) exit(1);

    char word[4];
    word[4] = 0;   // Words contain three characters.

    if (fseek(f, 4, SEEK_SET)) exit(2);

 //
 // We want to read 3 chars:
 //
    size_t size  = sizeof(char);
    size_t nmemb =           3 ;

    size_t nof_items_read = fread(word, size, nmemb, f);
    if (nof_items_read != 3) exit(3);

    printf("Word: %s\n", word);

 //
 // Advance file position indicator by one character:
 //
    if (fseek(f, 1, SEEK_CUR)) exit(4);

 //
 // Read another word
 //
    nof_items_read = fread(word, size, nmemb, f);
    if (nof_items_read != 3) exit(3);

    printf("Word: %s\n", word);

}

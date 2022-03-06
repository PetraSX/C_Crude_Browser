#include "defines.h"

int main()
{
    SITE_MEMORY *web_pages = NULL;      
    char buffer[1000] = {0};
    char substring_buffer[1000];
    char letter;
    char *substring;

    int has_keyword[1000] = {0};
    int selected_sites[1000] = {0};
    int no_selected_sites = 0;
    int no_sites;
    int index;
    int no_words = 0;

    int (*cmp)(const char *, const char *, const char *, const char *, const int, const int) = cmp_task2;  //Defining the pointer function for sorting

    read_dataBase(&web_pages);          //Sending the data_base by refference and getting it with double pointers for reading
    no_sites = web_pages->no_sites;

    while (1)                           //Infinite loop while reading character by character
    {
        letter = getchar();
        if (letter == ' ' || letter == '\n' || letter == '\0')          //When these character appear, one word has been read
        {
            for (index = 0; index < no_sites; index++)
            {
                strcpy(substring_buffer, web_pages[index].tag);         //Comparing it with every word in every site to determine what web pages
                substring = strtok(substring_buffer, " \n");            //contain that word
                while (substring != NULL)
                {
                    if (strcmp(substring, buffer) == 0 && has_keyword[index] == 0)
                    {
                        selected_sites[no_selected_sites++] = index;
                        has_keyword[index] = 1;
                    }
                    substring = strtok(NULL, " \n");
                }
            }

            for(index = 0; index < no_words; index++)
                buffer[index] = 0;
            no_words = 0;
            if(letter == '\n' || letter == '\0')                        //If the character is end line or terminator, the sequence is done
                break;
        }
        else
        {
            buffer[no_words++] = letter;
        }
    }

    sort(web_pages, selected_sites, no_selected_sites, cmp);            //Calling the sort function with task2 comparing function

    for (index = 0; index < no_selected_sites; index++)
        printf("%s\n", web_pages[selected_sites[index]].URL);

    for (index = 0; index < no_sites; index++)                          //Freeing the memory
    {
        free(web_pages[index].container);
        free(web_pages[index].tag);
    }
    free(web_pages);
    return 0;
}
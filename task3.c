#include "defines.h"

int main()
{
    SITE_MEMORY *web_pages = NULL;

    int no_sites;
    int index;
    int index_;
    int quout_flag = 0;
    int no_words = 0;
    int has_keyword[1000] = {0};
    int selected_sites[1000] = {0};
    int no_selected_sites = 0;

    char *substring = NULL;
    char letter;
    char querry[1000] = {0};
    char substring_buffer[1000] = {0};

    int (*cmp)(const char *, const char *, const char *, const char *, const int, const int) = cmp_task3; //Defining the pointer function for sorting

    read_dataBase(&web_pages);              //Sending the data_base by refference and getting it with double pointers for reading
    no_sites = web_pages->no_sites;

    while (1)                               //Infinite loop while reading character by character
    {
        letter = getchar();
        if (letter == '"')                  //quote flag to determine if a sequence is between ""
        {
            if (quout_flag == 0)
                quout_flag = 1;
            else
                quout_flag = 0;
        }
        else if (quout_flag == 0 && (letter == ' ' || letter == '\n' || letter == '\0'))  //When these character appear, one word has been read
        {
            for (index = 0; index < no_sites; index++)
            {
                strcpy(substring_buffer, web_pages[index].tag);         //Comparing it with every word in every site to determine what web pages
                substring = strtok(substring_buffer, " \n");            //contain that word
                while (substring != NULL)
                {
                    if (querry[0] == '-' && strcmp(substring, querry + 1) == 0)         //Resolving the '-' case
                    {
                        has_keyword[index] = -1;
                    }
                    else if ((strchr(querry, ' ') != NULL && strstr(web_pages[index].tag, querry) != NULL && has_keyword[index] == 0) ||
                             (strcmp(substring, querry) == 0 && has_keyword[index] == 0))
                    {
                        has_keyword[index] = 1;
                    }
                    substring = strtok(NULL, " \n");
                }
            }

            for (index = 0; index < no_words; index++)
                querry[index] = 0;
            no_words = 0;
            if (letter == '\n' || letter == '\0')               //If the character is end line or terminator, the sequence is done
                break;
        }
        else
        {
            querry[no_words++] = letter;
        }
    }

    for (index = 0; index < no_sites; index++)
    {
        if(has_keyword[index] == 1)
        {
            selected_sites[no_selected_sites++] = index;        //Selecting the sites that contain the simple words or "" words
        }
    }

    for (index = 0; index < no_selected_sites; index++)
    {
        if (has_keyword[selected_sites[index]] == -1)
        {
            for (index_ = index; index_ < no_selected_sites - 1; index_++)          //Eliminating the sites that contain the -words
            {
                selected_sites[index_] = selected_sites[index_ + 1];
            }
            no_selected_sites--;
        }
    }

    sort(web_pages, selected_sites, no_selected_sites, cmp);        //Calling the sort function with task3 compare function transmited by pointer

    for (index = 0; index < no_selected_sites; index++)
    {
        printf("%s\n", web_pages[selected_sites[index]].URL);
    }

    for (index = 0; index < no_sites; index++)                      //Freeing the memory
    {
        free(web_pages[index].container);
        free(web_pages[index].tag);
    }
    free(web_pages);
    return 0;
}
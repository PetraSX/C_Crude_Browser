#include "defines.h"

int main() 
{
    SITE_MEMORY *web_pages = NULL;
    int index;
    int no_sites;

    read_dataBase(&web_pages);          //Sending the data_base by refference and getting it with double pointers for reading

    for(index = 0; index < web_pages->no_sites; index++)
    {
        printf("%s %d %s\n", web_pages[index].URL, web_pages[index].no_visits, web_pages[index].title);     //printing the necessary things for the task
    }

    no_sites = web_pages->no_sites;
    for(index = 0; index < no_sites; index++)       //freeing the memory
    {
        free(web_pages[index].container);
        free(web_pages[index].tag);
    }
    free(web_pages);
    return 0;
}



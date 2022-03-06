#include "defines.h"

int main()
{
    SITE_MEMORY *web_pages = NULL;

    int no_sites;
    int index_i;
    int index_j;
    int website_exists;
    char buffer[50] = {0};
    int checksum_live = 0;

    char *container_copy;

    int string_length = 0;

    read_dataBase(&web_pages);          //Sending the data_base by refference and getting it with double pointers for reading
    no_sites = web_pages->no_sites;

    
    while(fgets(buffer, sizeof(buffer), stdin) != NULL)         //Reading while the new line is NULL
    {
        website_exists = 0;
        buffer[strlen(buffer) - 1] = '\0';                      //Replacing the newline character that is introduced after fgets with termiantor
        for (index_i = 0; index_i < no_sites; index_i++)
        {
            if (strcmp(web_pages[index_i].URL, buffer) == 0)
            {
                website_exists = 1;
                container_copy = calloc(web_pages[index_i].dimension + 1, sizeof(char));  //Making a copy of HTML code by dynamic allocation

                strcpy(container_copy, web_pages[index_i].container);
                string_length = strlen(container_copy);

                checksum_live = rotl(container_copy[0], 0) ^ rotr(container_copy[1], 1);   //Calculating the checksum by calling the 2 functions
                for(index_j = 2; index_j < string_length; index_j++)                       //for rotating the bits in all the character in the HTML code
                {
                    if(index_j % 2 == 0)
                        checksum_live = checksum_live ^ rotl(container_copy[index_j], index_j);
                    else
                        checksum_live = checksum_live ^ rotr(container_copy[index_j], index_j);
                }
                
                if(checksum_live == web_pages[index_i].checksum)
                {
                    printf("Website safe!\n");
                }
                else
                {
                    printf("Malicious website! Official key: %d. Found key: %d\n", web_pages[index_i].checksum, checksum_live);
                }
                free(container_copy);
            }
        }
        if (website_exists == 0)                    //if the flag is down, and no website was found in database
        {
            printf("Website not found!\n");
        }
    }

    for (index_i = 0; index_i < no_sites; index_i++)    //Freeing the memory
    {
        free(web_pages[index_i].container);
        free(web_pages[index_i].tag);
    }
    free(web_pages);
    return 0;
}
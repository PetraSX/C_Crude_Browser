#include "defines.h"

int read_dataBase(SITE_MEMORY **web_pages)  //Getting the data_base with double pointers for remembering the data saved after
{                                           //the functions ends
    FILE *master;
    FILE *HTML;

    int index;
    int numberOfsites = 0;
    int reallocation_index = 3;
    int bytes_dimension = 0;

    char html_name[30];
    char line[100];

    char *tag_start = NULL;
    char *tag_end = NULL;
    char *p_tag_start = NULL;
    int start_difference = 0;
    int end_difference = 0;

    *web_pages = calloc(3, sizeof(SITE_MEMORY));        //Dynamic Allocation of data_base with 3 elements

    master = fopen("master.txt", "r"); ///Opening master.txt

    if (!master) ///Checking if there was an error when opening the file
    {
        printf("File opening failed");
        return -1;
    }

    while (!feof(master))
    {
        fscanf(master, "%s", html_name);

        HTML = fopen(html_name, "r");
        if (!HTML)
        {
            printf("File opening failed");
            return -1;
        }

        ///Reading from every HTML file
        if (numberOfsites % 3 == 0 && numberOfsites > 0)    //Adding 3 more elements if the current memory is ocupied
        {
            reallocation_index += 3;
            *web_pages = realloc((*web_pages), reallocation_index * sizeof(SITE_MEMORY));
        }

        fscanf(HTML, "%s %d %d %d",                         //Reading the first line that is separated from the HTML code
               (*web_pages)[numberOfsites].URL,
               &(*web_pages)[numberOfsites].dimension,
               &(*web_pages)[numberOfsites].no_visits,
               &(*web_pages)[numberOfsites].checksum);
        fgetc(HTML);

        bytes_dimension = (*web_pages)[numberOfsites].dimension + 1;                    //Allocation for container and tag, adding 1 for the '\0'
        (*web_pages)[numberOfsites].container = calloc(bytes_dimension, sizeof(char));
        (*web_pages)[numberOfsites].tag = calloc(bytes_dimension, sizeof(char));

        while (fgets(line, sizeof(line), HTML))         ///Putting all the html code into struct to prepare for parsing
        {
            strcat((*web_pages)[numberOfsites].container, line);
        }

        numberOfsites++;
        ///

        fclose(HTML);
    }
    fclose(master);

    for (index = 0; index < numberOfsites; index++)                         //Parsing the title from the HTML code using pointer arithmetics
    {
        tag_start = strstr((*web_pages)[index].container, "<title>");
        tag_end = strstr((*web_pages)[index].container, "</title>");

        start_difference = tag_start - (*web_pages)[index].container;
        end_difference = tag_end - (*web_pages)[index].container;

        strncpy((*web_pages)[index].title, tag_start + start_difference, end_difference - 2 * start_difference);
        (*web_pages)[index].title[end_difference - 2 * start_difference] = '\0';
    }

    for (index = 0; index < numberOfsites; index++)                         //Parsing the paragraph in the same way as title, but there are some more
    {                                                                       //condition because the <p> tag can containg extra info for colors
        p_tag_start = strstr((*web_pages)[index].container, "<p");
        tag_start = strstr(p_tag_start, ">");
        tag_end = strstr((*web_pages)[index].container, "</p>");

        start_difference = tag_start - (*web_pages)[index].container;
        end_difference = tag_end - (*web_pages)[index].container;

        strncpy((*web_pages)[index].tag, tag_start + 1, end_difference - start_difference - 1);
        (*web_pages)[index].tag[end_difference - start_difference - 1] = '\0';
    }
    (*web_pages)->no_sites = numberOfsites;
    return 0;
}

int cmp_task2(const char title_1[], const char title_2[], const char tag_1[],       //Function to help sorting for task2 
              const char tag_2[], const int vis_1, const int vis_2)                 //(comparing the titles for "Schema lui Biju")
{

    if (strcmp(title_1, title_2) == 0)
    {
        if (vis_1 == vis_2)
            return 0;
        return vis_1 > vis_2 ? -1 : 1;
    }
    else if (strcmp(tag_1, tag_2) > 0)
        return 1;
    return 0;
}

int cmp_task3(const char title_1[], const char title_2[], const char tag_1[],       //Function to help sorting for task3
              const char tag_2[], const int vis_1, const int vis_2)                 //Comparing the number of vis per site
{
    if(vis_1 == vis_2)
        return 0;
    return vis_1 > vis_2 ? -1 : 1;
}

void sort(SITE_MEMORY *web_pages, int selected_sites[], int no_selected_sites,          //The sort function for task2/task3 calling the pointer
          int (*cmp)(const char title_1[], const char title_2[], const char tag_1[],    //functions cmp_task2/cmp_task3
                     const char tag_2[], const int vis_1, const int vis_2))
{
    int index_i;
    int index_j;
    int aux;

    for (index_i = 0; index_i < no_selected_sites - 1; index_i++)
    {
        for (index_j = index_i + 1; index_j < no_selected_sites; index_j++)
        {
            if (cmp(web_pages[selected_sites[index_i]].title, web_pages[selected_sites[index_j]].title,
                    web_pages[selected_sites[index_i]].tag, web_pages[selected_sites[index_j]].tag,
                    web_pages[selected_sites[index_i]].no_visits, web_pages[selected_sites[index_j]].no_visits) == 1)
            {
                aux = selected_sites[index_i];
                selected_sites[index_i] = selected_sites[index_j];
                selected_sites[index_j] = aux;
            }
        }
    }
}

unsigned char rotr(unsigned char x, int k)          //Rotating the bits in right direction using shifting operators
{                                                   //and getting the % of 8 because the number <<(8-k) needs to be positive
    k = k%8;                                        // and shifting 24 bits is the same as shifting 0 bits (24 % 8 = 0)
    return (x >> k)|(x << (8 - k));
}

unsigned char rotl(unsigned char x, int k)          //Rotating the bits in right direction using shifting operators
{
    k = k%8;
    return (x << k)|(x >> (8 - k));
}
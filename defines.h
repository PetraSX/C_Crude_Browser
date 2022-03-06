#ifndef _DEFINES_H
#define _DEFINES_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tx_bg_colors       //Enum for colors in task4(browser)
{
    white,
    black,
    red,
    green,
    blue,
    yellow
};

typedef struct          //Defining the "Data Base" that was introduced in assigment
{
    char URL[50];
    char title[50];
    char *container;    //Pointer for ALL HTML code between <html> tags
    char *tag;          //Pointer for Paragraph code

    int no_visits;
    int dimension;
    int checksum;
    int no_sites;
} SITE_MEMORY;

int read_dataBase(SITE_MEMORY **web_pages);     //Function for reading the data_base, writed in defines.c

int cmp_task2(const char title_1[], const char title_2[], const char tag_1[],       //Function to help sorting in task2
              const char tag_2[], const int vis_1, const int vis_2);

int cmp_task3(const char title_1[], const char title_2[], const char tag_1[],       //Function to help sorting in task3
              const char tag_2[], const int vis_1, const int vis_2);

void sort();                                                                        //The sort function for task2/task3

unsigned char rotr(unsigned char x, int k);                                         //Function for rotating bits in right direction for task 4

unsigned char rotl(unsigned char x, int k);                                         //Function for rotating bits in left direction for task4

#endif //_DEFINES_H
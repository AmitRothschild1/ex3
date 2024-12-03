/******************
Name: Amit Rothschild
ID: 322317637
Assignment: ex3
*******************/

#include <stdio.h>

#define start 0
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void printMenu(){
        printf("Welcome to the Cars Data Cube! What would you like to do?\n"
               "1.Enter Daily Data For A Brand\n"
               "2.Populate A Day Of Sales For All Brands\n"
               "3.Provide Daily Stats\n"
               "4.Print All Data\n"
               "5.Provide Overall (simple) Insights\n"
               "6.Provide Average Delta Metrics\n"
               "7.exit\n");
}

void setArrToMinusOne(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            for (int k = 0; k < NUM_OF_TYPES; k++)
                arr[i][j][k] = -1;
}

void addOneDay(int days[NUM_OF_BRANDS],int brand)
{
    days[brand]++;
}

void insertSum(int brand , int suv , int sedan , int coupe , int gt , int arr[][NUM_OF_BRANDS][NUM_OF_TYPES] , int day)
{
        arr[day][brand][start] = suv;
        arr[day][brand][addOne] = sedan;
        arr[day][brand][addAll] = coupe;
        arr[day][brand][stats] = gt;
}

void printBrandName(int brand)
{
    int index = 0;
    while (brands[brand][index] != '\0')
    {
        printf("%c", brands[brand][index]);
        index++;
    }
    printf(" ");
}


//void addAllCheck (int con);


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    setArrToMinusOne(cube);
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                //...
            int carBrand;
            int suvSum , sedanSum , coupeSum , gtSum;
            printf("enter a brand and daily sum for each type:");
            scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
            if (carBrand < start || carBrand > print)
            {
                printf("This brand is not valid\n");
                break;
            }
            insertSum(carBrand , suvSum , sedanSum , coupeSum , gtSum , cube , days[carBrand]);
            printf("The sums have been inserted successfully.\nThe sums of brand %d for day %d:\nSUV - %d$\nSedan - %d$\nCoupe - %d$\nGT - %d$\n",carBrand,days[carBrand],cube[days[carBrand]][carBrand][start],cube[days[carBrand]][carBrand][addOne],cube[days[carBrand]][carBrand][addAll],cube[days[carBrand]][carBrand][stats]);
            addOneDay(days,carBrand);
            printf("next day for brand %d is: %d\n",carBrand,days[carBrand]);
                break;

            //***************
            //End of case one
            //***************

            case addAll:
            printf("No data for brands ");
            for(int i = 0; i < NUM_OF_BRANDS; i++)
            {
                printBrandName(i);
            }
            printf("\nPlease complete the data\n");
            scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
            while (carBrand < start || carBrand > print)
            {
                printf("This brand is not valid\n");
            }

                break;

            /*
             ......
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}



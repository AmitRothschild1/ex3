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
int days[NUM_OF_BRANDS] = {0};
int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

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

void addOneDay(int brand)
{
    days[brand]++;
}

void insertSum(int brand , int suv , int sedan , int coupe , int gt , int arr[][NUM_OF_BRANDS][NUM_OF_TYPES])
{
        arr[days[brand]][brand][start] = suv;
        arr[days[brand]][brand][addOne] = sedan;
        arr[days[brand]][brand][addAll] = coupe;
        arr[days[brand]][brand][stats] = gt;
}

void printBrandName(int brand)
{
    int index = 0;
    while (brands[brand][index] != '\0')
    {
        printf("%c", brands[brand][index]);
        index++;
    }
}

void printTypeName(int type)
{
    int index = 0;
    while (types[type][index] != '\0')
    {
        printf("%c", types[type][index]);
        index++;
    }
}

//checks whether the requested car brand has sales information on the requested day
int brandSaleIsFull(int brand,int day)
{
    if(cube[day][brand][start] == -1)
        return 0;
    else
        return 1;
}

//If sal
int allBrandsSalesAreFull(int day)
{
    int count = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
     count += brandSaleIsFull(i,day);
    }
    if(count == NUM_OF_BRANDS)
        return 1;
    else
    return 0;
}

int totalSalesSum(int day)
{
    day = day - addOne;
    int sum = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
        for (int j = 0; j < NUM_OF_TYPES; j++)
            sum += cube[day][i][j];
    return sum;
}

int maxBrandSalesAmount(int day)
{
    day = day - addOne;
    int max = 0;
    int sum = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[day][i][j];
        }
            if(sum > max)
                max = sum;
            sum = 0;
    }
    return max;
}

int maxTypeSalesAmount(int day)
{
    day = day - addOne;
    int max = 0;
    int sum = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            sum += cube[day][j][i];
        }
            if(sum > max)
                max = sum;
            sum = 0;
    }
    return max;
}

int maxSalesBrand(int day)
{
    day = day - addOne;
    int max = 0;
    int sum = 0;
    int brand = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[day][i][j];
        }
            if(sum > max)
            {
                max = sum;
                brand = i;
            }
            sum = 0;
    }
    return brand;
}

int maxSalesType(int day)
{
    day = day - addOne;
    int max = 0;
    int sum = 0;
    int type = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            sum += cube[day][j][i];
        }
        if(sum > max)
        {
            max = sum;
            type = i;
        }
        sum = 0;
    }
    return type;
}

int bestSellingBrand()
{
    int sum = 0;
    int max = 0;
    int brand = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][i][j];
            }
        }
        if(sum > max)
        {
            max = sum;
            brand = i;
        }
        sum = 0;
    }
    return brand;
}


int bestSellingBrandAmount()
{
    int sum = 0;
    int max = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][i][j];
            }
        }
        if(sum > max)
        {
            max = sum;
        }
        sum = 0;
    }
    return max;
}

int bestSellingType()
{
    int sum = 0;
    int max = 0;
    int type = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][j][i];
            }
        }
        if(sum > max)
        {
            max = sum;
            type = i;
        }
        sum = 0;
    }
    return type;
}


int bestSellingTypeAmount()
{
    int sum = 0;
    int max = 0;
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][j][i];
            }
        }
        if(sum > max)
        {
            max = sum;
        }
        sum = 0;
    }
    return max;
}


int bestSellingDayAmount()
{
    int sum = 0;
    int max = 0;
    for(int i = 0; i < days[start]; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                sum += cube[i][j][k];
            }
        }
        if(sum > max)
        {
            max = sum;
        }
        sum = 0;
    }
    return max;
}



int bestSellingDay()
{
    int sum = 0;
    int max = 0;
    int day = 0;
    for(int i = 0; i < days[start]; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                sum += cube[i][j][k];
            }
        }
        if(sum > max)
        {
            max = sum;
            day = i;
        }
        sum = 0;
    }
    return day;
}



void salesInfoLine()
{
    int day = days[start];
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        printf("Sales for ");
        printBrandName(i);
        printf(":\n");
        for(int j = 0; j < day; j++)
        {
            printf("Day %d- ",j+addOne);
            for (int t = 0; t < NUM_OF_TYPES; t++)
            {
                printTypeName(t);
                printf(": %d ", cube[j][i][t]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

double brandDelta(int brand)
{
    int firstSum = 0;
    int lastSum = 0;
    double difference = 0;
    for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                firstSum += cube[start][brand][k];
                lastSum += cube[days[start]-addOne][brand][k];
            }
            difference += lastSum - firstSum;
    return difference/(days[start]-addOne);
}


int main() {
    setArrToMinusOne(cube);
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
            insertSum(carBrand , suvSum , sedanSum , coupeSum , gtSum , cube);
            printf("The sums have been inserted successfully.\nThe sums of brand %d for day %d:\nSUV - %d$\nSedan - %d$\nCoupe - %d$\nGT - %d$\n",carBrand,days[carBrand],cube[days[carBrand]][carBrand][start],cube[days[carBrand]][carBrand][addOne],cube[days[carBrand]][carBrand][addAll],cube[days[carBrand]][carBrand][stats]);
            addOneDay(carBrand);
            printf("next day for brand %d is: %d\n",carBrand,days[carBrand]);
                break;

            //***************
            //End of case one
            //***************

            case addAll:
                int currentSalesDay = days[start]; //Current sales day
            //program keep running until all sales will be successfully filled
            while (allBrandsSalesAreFull(currentSalesDay)==start)
            {
                //Prints input massage and lets the user know what fields are empty
                printf("No data for brands ");
                for(int i = 0; i < NUM_OF_BRANDS; i++)
                {
                    if(brandSaleIsFull(i,currentSalesDay)==start)
                    {
                        printBrandName(i);
                        printf(", ");
                    }
                }
                printf("\nPlease complete the data\n");
                //Sales input
                scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
                //keep showing text in case user entered invalid brands - stops when brand is valid
                while (carBrand < start || carBrand > print || brandSaleIsFull(carBrand,currentSalesDay)==addOne)
                {
                    printf("This brand is not valid\n");
                    printf("No data for brands ");
                    for(int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        if(!brandSaleIsFull(i,currentSalesDay))
                        {
                            printBrandName(i);
                            printf(", ");
                        }
                    }
                    printf("\nPlease complete the data\n");
                    scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
                }
                //after checking all data is valid - sales data enters the array
                insertSum(carBrand,suvSum,sedanSum,coupeSum,gtSum,cube);
                addOneDay(carBrand);
            }
                break; //back to menu


        case stats:
            int dayCase3;
            printf("What day would you like to analyze?\n");
            scanf("%d", &dayCase3);
            while (dayCase3<=0 || dayCase3>currentSalesDay+addOne)
            {
                printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
                scanf("%d", &dayCase3);
            }
            printf("In day number %d:\nThe sales total was %d\nThe best sold brand with %d sales was ",dayCase3,totalSalesSum(dayCase3),maxBrandSalesAmount(dayCase3));
            printBrandName(maxSalesBrand(dayCase3));
            printf("\nThe best sold type with %d sales was ",maxTypeSalesAmount(dayCase3));
            printTypeName(maxSalesType(dayCase3));
            printf("\n");
            break;


        case print:
            printf("*****************************************\n\n");
            salesInfoLine();
            printf("\n*****************************************\n");
            break;


        case insights:
            printf("The best-selling brand overall is ");
            printBrandName(bestSellingBrand());
            printf(": %d$\n",bestSellingBrandAmount());
            printf("The best-selling type of car is ");
            printTypeName(bestSellingType());
            printf(": %d$\n",bestSellingTypeAmount());
            printf("The most profitable day was day number %d: %d$\n",bestSellingDay()+addOne,bestSellingDayAmount());
            break;



        case deltas:
            if (days[start] <= 1)
            {
                printf("Not enough days for this process.\n");
                break;
            }
                for(int i = 0; i < NUM_OF_BRANDS; i++)
                {
                    printf("Brand: ");
                    printBrandName(i);
                    printf(", Average Delta: %f\n",brandDelta(i));
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



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

//This function prints the menu for user
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

//This function turn all cube values to -1
void setArrToMinusOne(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            for (int k = 0; k < NUM_OF_TYPES; k++)
                arr[i][j][k] = -1;
}

//This function add one day in the days array
void addOneDay(int brand,int days[NUM_OF_BRANDS])
{
    days[brand]++;
}

//This function enters user's input values to cube array
void insertSum(int brand , int suv , int sedan , int coupe , int gt , int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
        arr[days[brand]][brand][start] = suv;
        arr[days[brand]][brand][addOne] = sedan;
        arr[days[brand]][brand][addAll] = coupe;
        arr[days[brand]][brand][stats] = gt;
}

//This function prints the requested brand name
void printBrandName(int brand)
{
    int index = 0;
    while (brands[brand][index] != '\0') //loop stops when column is out of chars
    {
        printf("%c", brands[brand][index]); //prints every char on his place
        index++;
    }
}

//This function prints the requested type name
void printTypeName(int type)
{
    int index = 0;
    while (types[type][index] != '\0') //loop stops when column is out of chars
    {
        printf("%c", types[type][index]); //prints every char on his place
        index++;
    }
}

//checks whether the requested car brand has sales information on the requested day
int brandSaleIsFull(int brand,int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    if(cube[day][brand][start] == -1) //if the array location got no data - function value is zero
        return 0;
    else
        return 1;
}

//This function checks if all the car brands has sales information on the requested day
int allBrandsSalesAreFull(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int count = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
     count += brandSaleIsFull(i,day,cube);
    }
    if(count == NUM_OF_BRANDS)
        return 1; // All brands have data
    else
    return 0; // At least one brand is missing data
}

//This function calculate the sum of all cars in the requested day
int totalSalesSum(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    day = day - addOne;
    int sum = 0;
    for(int i = 0; i < NUM_OF_BRANDS; i++)
        for (int j = 0; j < NUM_OF_TYPES; j++)
            sum += cube[day][i][j];  // Sum all sales for all types and brands
    return sum;
}

//This function calculate the most selling car brand's sum of sales on the requested day
int maxBrandSalesAmount(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
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
            sum = 0; // Reset sum for next brand
    }
    return max;
}

//This function calculate the most selling car types sum of sales on the requested day
int maxTypeSalesAmount(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
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
            sum = 0; // Reset sum for next type
    }
    return max;
}

//This function checks what car brand has the highest sales on the requested day
int maxSalesBrand(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
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

//This function checks what car type has the highest sales on the requested day
int maxSalesType(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
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

//This function checks what car brand has the highest sales in all times
int bestSellingBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function calculate the most selling car brand's sum of sales in all times
int bestSellingBrandAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function checks what car type has the highest sales in all times
int bestSellingType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function calculate the most selling car types sum of sales in all times
int bestSellingTypeAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function calculates the most selling day sum of sales
int bestSellingDayAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function checks what day has the highest sum of sales
int bestSellingDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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


//This function prints out detailing sales amounts by brands and types on a specific day
void salesInfoLine(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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

//This function calculates the sales differences divided by the days differences
double brandDelta(int brand,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
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
    int days[NUM_OF_BRANDS] = {0};  // Tracks the current day for each brand
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];  // 3D array for storing sales data
    setArrToMinusOne(cube); // Initialize sales data cube
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){ //Program stops running only when user choose option number 7
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
            insertSum(carBrand , suvSum , sedanSum , coupeSum , gtSum , cube , days);
            printf("The sums have been inserted successfully.\nThe sums of brand %d for day %d:\nSUV - %d$\nSedan - %d$\nCoupe - %d$\nGT - %d$\n",carBrand,days[carBrand],cube[days[carBrand]][carBrand][start],cube[days[carBrand]][carBrand][addOne],cube[days[carBrand]][carBrand][addAll],cube[days[carBrand]][carBrand][stats]);
            addOneDay(carBrand,days);
            printf("next day for brand %d is: %d\n",carBrand,days[carBrand]);
                break;

            //***************
            //End of case one
            //***************

            // Populate data for all brands on the current day
            case addAll:
                int currentSalesDay = days[start]; //Current sales day
            //program keep running until all sales will be successfully filled
            while (allBrandsSalesAreFull(currentSalesDay,cube)==start)
            {
                //Prints input massage and lets the user know what fields are empty
                printf("No data for brands ");
                for(int i = 0; i < NUM_OF_BRANDS; i++)
                {
                    if(brandSaleIsFull(i,currentSalesDay,cube)==start)
                    {
                        printBrandName(i);
                        printf(" ");
                    }
                }
                printf("\nPlease complete the data\n");
                //Sales input
                scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
                //keep showing text in case user entered invalid brands - stops when brand is valid
                while (carBrand < start || carBrand > print || brandSaleIsFull(carBrand,currentSalesDay,cube)==addOne)
                {
                    printf("This brand is not valid\n");
                    printf("No data for brands ");
                    for(int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        if(!brandSaleIsFull(i,currentSalesDay,cube))
                        {
                            printBrandName(i);
                            printf(" ");
                        }
                    }
                    printf("\nPlease complete the data\n");
                    scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
                }
                //after checking all data is valid - sales data enters the array
                insertSum(carBrand,suvSum,sedanSum,coupeSum,gtSum,cube,days);
                addOneDay(carBrand,days);
            }
                break; //back to menu


            // Provide daily sales stats
        case stats:
            int dayCase3;
            printf("What day would you like to analyze?\n");
            scanf("%d", &dayCase3);
            while (dayCase3<=0 || dayCase3>currentSalesDay+addOne)
            {
                printf("Please enter a valid day.\nWhat day would you like to analyze?\n");
                scanf("%d", &dayCase3);
            }
            printf("In day number %d:\nThe sales total was %d\nThe best sold brand with %d sales was ",dayCase3,totalSalesSum(dayCase3,cube),maxBrandSalesAmount(dayCase3,cube));
            printBrandName(maxSalesBrand(dayCase3,cube));
            printf("\nThe best sold type with %d sales was ",maxTypeSalesAmount(dayCase3,cube));
            printTypeName(maxSalesType(dayCase3,cube));
            printf("\n");
            break;


        case print:
            printf("*****************************************\n\n");
            salesInfoLine(cube,days);
            printf("\n*****************************************\n");
            break;


        case insights:
            printf("The best-selling brand overall is ");
            printBrandName(bestSellingBrand(cube,days));
            printf(": %d$\n",bestSellingBrandAmount(cube,days));
            printf("The best-selling type of car is ");
            printTypeName(bestSellingType(cube,days));
            printf(": %d$\n",bestSellingTypeAmount(cube,days));
            printf("The most profitable day was day number %d: %d$\n",bestSellingDay(cube,days)+addOne,bestSellingDayAmount(cube,days));
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
                    printf(", Average Delta: %f\n",brandDelta(i,cube,days));
                }
            break;

            /*
             ......
             */
            //In case users option input is invalid
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}



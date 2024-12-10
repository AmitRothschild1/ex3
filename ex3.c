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

//This function prints the menu for user:
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

//This function turn all cube values to -1:
void setArrToMinusOne(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    // Loop through all days in the year
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        // Loop through all brands for the current day
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            // Loop through all product types for the current day and brand
            for (int k = 0; k < NUM_OF_TYPES; k++)
                // Set the sales data for the current day, brand, and type to -1
                arr[i][j][k] = -1;
}

//This function add one day in the days array:
void addOneDay(int brand,int days[NUM_OF_BRANDS])
{
    days[brand]++; //Add 1 to days main counter
}

//This function enters user's input values to cube array:
void insertSum(int brand,int suv,int sedan,int coupe,int gt,
    int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
        arr[days[brand]][brand][start] = suv;  // Insert the SUV sales for the current day and brand into the array
        arr[days[brand]][brand][addOne] = sedan;  // Insert the Sedan sales for the current day and brand into the array
        arr[days[brand]][brand][addAll] = coupe;  // Insert the Coupe sales for the current day and brand into the array
        arr[days[brand]][brand][stats] = gt;  // Insert the GT sales for the current day and brand into the array
}

//This function prints the requested brand name:
void printBrandName(int brand)
{
    int index = 0; // Initialize the index to start at the first character of the brand name
    while (brands[brand][index] != '\0') //loop stops when column is out of chars
    {
        printf("%c", brands[brand][index]); //prints every char on his place
        index++;  // Move to the next character in the string
    }
}

//This function prints the requested type name:
void printTypeName(int type)
{
    int index = 0; // Initialize the index to start at the first character of the type name
    while (types[type][index] != '\0') //loop stops when column is out of chars
    {
        printf("%c", types[type][index]); //prints every char on his place
        index++; // Move to the next character in the string
    }
}

//checks whether the requested car brand has sales information on the requested day:
int brandSaleIsFull(int brand,int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    if(cube[day][brand][start] == -1) //if the array location got no data - function value is zero
        return 0;
    else
        return 1;
}

//This function checks if all the car brands has sales information on the requested day:
int allBrandsSalesAreFull(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int count = 0; // Initialize a counter to keep track of brands with complete sales data
    // Loop through all brands to check their sales data for the specified day
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Increment count if the sales data for brand `i` on day `day` is complete
     count += brandSaleIsFull(i,day,cube);
    }
    // If all brands have complete sales data for the specified day
    if(count == NUM_OF_BRANDS)
        return 1; // All brands have data
    else
    return 0; // At least one brand is missing data
}

//This function calculate the sum of all cars in the requested day:
int totalSalesSum(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    if(!allBrandsSalesAreFull(start,cube)) //In case there are no sales at all:
        return 0; //Return sum is 0
    else
    {
        day = day - addOne; // `addOne` adjusts the day index, assumed to be defined and initialized
        int sum = 0; // Initialize the sum of sales to 0
        // Loop through all brands
        for(int i = 0; i < NUM_OF_BRANDS; i++)
            // Loop through all types for the current brand
                for (int j = 0; j < NUM_OF_TYPES; j++)
                    sum += cube[day][i][j];  // Sum all sales for all types and brands
        return sum; // Return the total sum of sales for the given day
    }
}

//This function calculate the most selling car brand's sum of sales on the requested day:
int maxBrandSalesAmount(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    day = day - addOne;  // `addOne` ensures the day parameter matches the zero-based array indexing
    int max = 0; // Initialize the maximum sales value to 0
    int sum = 0; // Initialize the sum of sales for a single brand to 0
    // Loop through all brands
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Calculate the total sales for the current brand across all types
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[day][i][j]; // Add sales for the current type to the brand's total
        }
        // Update the maximum sales value if the current brand's sales exceed the current maximum
            if(sum > max)
                max = sum;
            sum = 0; // Reset sum for next brand
    }
    return max; // Return the maximum sales value among all brands for the given day
}

//This function calculate the most selling car types sum of sales on the requested day:
int maxTypeSalesAmount(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    day = day - addOne; // `addOne` ensures the day parameter matches the zero-based array indexing
    int max = 0; // Initialize the maximum sales value to 0
    int sum = 0; // Initialize the sum of sales for a single brand to 0
    // Loop through all types
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        // Calculate the total sales for the current type across all brands
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            sum += cube[day][j][i]; // Add sales for the current type to the type's total
        }
        // Update the maximum sales value if the current type's sales exceed the current maximum
            if(sum > max)
                max = sum;
            sum = 0; // Reset sum for next type
    }
    return max; // Return the maximum sales value among all types for the given day
}

//This function checks what car brand has the highest sales on the requested day:
int maxSalesBrand(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    day = day - addOne; // `addOne` ensures the day parameter matches the zero-based array indexing
    int max = 0; // Initialize the maximum sales value to 0
    int sum = 0;  // Initialize the sum of sales for a single brand to 0
    int brand = 0; // Variable to store the brand index with the highest sales
    // Loop through all brands
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Calculate the total sales for the current brand across all types
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[day][i][j]; // Add sales for the current type to the brand's total
        }
        // Check if the current brand's total sales exceed the maximum found so far
            if(sum > max)
            {
                max = sum;  // Update the maximum sales value
                brand = i;  // Update the brand index with the current brand
            }
            sum = 0;  // Reset the sum for the next brand
    }
    return brand; // Return the index of the brand with the highest sales
}

//This function checks what car type has the highest sales on the requested day:
int maxSalesType(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    day = day - addOne; // `addOne` ensures the day parameter matches the zero-based array indexing
    int max = 0; // Initialize the maximum sales value to 0
    int sum = 0; // Initialize the sum of sales for a single brand to 0
    int type = 0; // Variable to store the type index with the highest sales
    // Loop through all types
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        // Calculate the total sales for the current type across all brands
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            sum += cube[day][j][i]; // Add sales for the current type to the type's total
        }
        // Check if the current type's total sales exceed the maximum found so far
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
            type = i; // Update the type index with the current brand
        }
        sum = 0; // Reset the sum for the next type
    }
    return type; // Return the index of the type with the highest sales
}

//This function checks what car brand has the highest sales in all times:
int bestSellingBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single brand to 0
    int max = 0; // Initialize the maximum sales value to 0
    int brand = 0;  // Variable to store the index of the best-selling brand
    // Loop through all brands
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Loop through all product types for the current brand
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            // Loop through all recorded days for the current brand
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][i][j]; // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Check if the current brand's total sales exceed the maximum found so far
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
            brand = i; // Update the index of the best-selling brand
        }
        sum = 0;  // Reset the sum for the next brand
    }
    return brand; // Return the index of the best-selling brand
}

//This function calculate the most selling car brand's sum of sales in all times:
int bestSellingBrandAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single brand to 0
    int max = 0; // Initialize the maximum sales value to 0
    // Loop through all brands
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Loop through all product types for the current brand
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            // Loop through all recorded days for the current brand
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][i][j];  // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Update the maximum sales value if the current brand's total sales exceed the maximum
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
        }
        sum = 0; // Reset the sum for the next brand
    }
    return max; // Return the highest sales total among all brands
}

//This function checks what car type has the highest sales in all times:
int bestSellingType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single type to 0
    int max = 0; // Initialize the maximum sales value to 0
    int type = 0;  // Variable to store the index of the best-selling type
    // Loop through all product types
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        // Loop through all recorded days for the current brand
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            // Loop through all recorded days for the current brand
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][j][i]; // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Check if the current type's total sales exceed the maximum found so far
        if(sum > max)
        {
            max = sum;  // Update the maximum sales value
            type = i;  // Update the index of the best-selling type
        }
        sum = 0; // Reset the sum for the next type
    }
    return type; // Return the index of the best-selling product type
}

//This function calculate the most selling car types sum of sales in all times:
int bestSellingTypeAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single type to 0
    int max = 0; // Initialize the maximum sales value to 0
    // Loop through all product types
    for(int i = 0; i < NUM_OF_TYPES; i++)
    {
        // Loop through all brands
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            // Loop through all recorded days for the current brand
            for(int k = 0; k < days[start]; k++)
            {
                sum += cube[k][j][i];   // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Update the maximum sales value if the current type's total sales exceed the current maximum
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
        }
        sum = 0; // Reset the sum for the next product type
    }
    return max; // Return the highest total sales value among all product types
}

//This function calculates the most selling day sum of sales:
int bestSellingDayAmount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single type to 0
    int max = 0; // Initialize the maximum sales value to 0
    // Loop through all recorded days
    for(int i = 0; i < days[start]; i++)
    {
        // Loop through all brands
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            // Loop through all product types for the current day and brand
            for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                sum += cube[i][j][k]; // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Update the maximum sales value if the current day's total sales exceed the current maximum
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
        }
        sum = 0;  // Reset the sum for the next day
    }
    return max; // Return the highest total sales value among all days
}

//This function checks what day has the highest sum of sales:
int bestSellingDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int sum = 0;  // Initialize the sum of sales for a single type to 0
    int max = 0; // Initialize the maximum sales value to 0
    int day = 0; // Variable to store the index of the best-selling day
    // Loop through all recorded days
    for(int i = 0; i < days[start]; i++)
    {
        // Loop through all brands
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            // Loop through all product types for the current day and brand
            for(int k = 0; k < NUM_OF_TYPES; k++)
            {
                sum += cube[i][j][k]; // Add the sales value for the current day, brand, and type to the sum
            }
        }
        // Update the maximum sales value and the corresponding day if current total exceeds the maximum
        if(sum > max)
        {
            max = sum; // Update the maximum sales value
            day = i; // Update the index of the best-selling day
        }
        sum = 0;  // Reset the sum for the next day
    }
    return day; // Return the index of the best-selling day
}


//This function prints out detailing sales amounts by brands and types on a specific day:
void salesInfoLine(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    // Retrieve the specific day value for processing the sales data of each brand
    int day = days[start]; // `start` represents the current brand index or starting point
    // Loop through all the brands to display their sales information
    for(int i = 0; i < NUM_OF_BRANDS; i++)
    {
        // Print the name of the current brand
        printf("Sales for ");
        printBrandName(i); // Function to print the brand name based on index `i`
        printf(":\n");
        // Loop through the days for which sales data is available for the current brand
        for(int j = 0; j < day; j++)
        {
            // Print the current day number (adjusted by `addOne` for display purposes)
            printf("Day %d- ",j+addOne); // `addOne` is a predefined offset to adjust day numbering
            // Loop through all product types for the current day and brand
            for (int t = 0; t < NUM_OF_TYPES; t++)
            {
                // Print the product type name and its corresponding sales value
                printTypeName(t); // Function to print the type name based on index `t`
                printf(": %d ", cube[j][i][t]); // Sales data for day `j`, brand `i`, and type `t`
            }
            printf("\n");
        }
        printf("\n");
    }
}

//This function calculates the sales differences divided by the days differences:
double brandDelta(int brand,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS])
{
    int firstSum = 0; //variable for first day sales sum - set to 0
    int lastSum = 0; //variable for last day sales sum - set to 0
    double difference = 0; //variable for difference sales sum - set to 0
    if (days[start] > 1) //In case there are enough days for the calculation:
    {
        for(int k = 0; k < NUM_OF_TYPES; k++) //makes progress for every brand:
        {
            firstSum += cube[start][brand][k]; //first day sales value
            lastSum += cube[days[start]-addOne][brand][k]; //last day sales value
        }

        difference = lastSum - firstSum; //difference of first day sum and last day sum
        return difference/(days[start]-addOne); //returns the difference of sales divided by difference of days
    }
    else //In case there are not enough days for the calculation:
        return difference; //return 0
}


int main()
{
    int days[NUM_OF_BRANDS] = {0};  // Tracks the current day for each brand
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];  // 3D array for storing sales data
    setArrToMinusOne(cube); // Initialize sales data cube
    int currentSalesDay = days[start];
    int choice; //variable for users menu choice
    printMenu();
    scanf("%d", &choice); //user chooses option
    while(choice != done) //Program stops running only when user choose option number 7
        {
        switch(choice) //navigates the user according to his choice
        {
            case addOne: //option one
                //...
            int carBrand; //variable for brand
            int suvSum , sedanSum , coupeSum , gtSum; //variables for every type sale sum of a day
            printf("enter a brand and daily sum for each type:"); //output
            scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum ); //user enters sums
            if (carBrand < start || carBrand > print) //in case user entered invalid brand
            {
                printf("This brand is not valid\n"); //output
                break; //back to menu
            }
            //if brand is valid:
            insertSum(carBrand , suvSum , sedanSum , coupeSum , gtSum , cube , days); //sums data enter to cube array
            printf("The sums have been inserted successfully."); //output
            //prints nice massage with the sums data:
            printf("\nThe sums of brand %d for day %d:\n",carBrand,days[carBrand]);
            printf("SUV - %d$\nSedan",cube[days[carBrand]][carBrand][start]);
            printf(" - %d$\nCoupe - ",cube[days[carBrand]][carBrand][addOne]);
           printf("%d$\nGT - %d$\n",cube[days[carBrand]][carBrand][addAll],cube[days[carBrand]][carBrand][stats]);
            addOneDay(carBrand,days);
            printf("next day for brand %d is: %d\n",carBrand,days[carBrand]);
                break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

            // Populate data for all brands on the current day:
            case addAll: //users choice 2
            currentSalesDay = days[start]; //Current sales day
            //program keep running until all sales will be successfully filled
            while (allBrandsSalesAreFull(currentSalesDay,cube)==start) //loop stops when all car data on the current day is full
            {
               if(allBrandsSalesAreFull(DAYS_IN_YEAR-addOne,cube))
               {
                   printf("All days are full of data");
                   break;
               }
                //Prints input massage and lets the user know what fields are empty:
                printf("No data for brands "); //output
                for(int i = 0; i < NUM_OF_BRANDS; i++) //makes output of every brand name unless the next condition is false:
                {
                    if(brandSaleIsFull(i,currentSalesDay,cube)==start) //in case the current brand has data on current day:
                    {
                        printBrandName(i); //prints brand name
                        printf(" "); //space
                    }
                }
                printf("\nPlease complete the data\n"); //output continues
                //Sales input:
                scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum );
                //keep printing text in case user entered invalid brands - stops when brand is valid
                while (carBrand < start || carBrand > print || brandSaleIsFull(carBrand,currentSalesDay,cube)==addOne)
                {
                    printf("This brand is not valid\n"); //output
                    printf("No data for brands "); //output
                    for(int i = 0; i < NUM_OF_BRANDS; i++) //makes output of every brand name unless the next condition is false:
                    {
                        if(!brandSaleIsFull(i,currentSalesDay,cube))
                        {
                            printBrandName(i); //prints brand name
                            printf(" "); //space
                        }
                    }
                    printf("\nPlease complete the data\n"); //ask user to input data
                    scanf(" %d %d %d %d %d", &carBrand , &suvSum , &sedanSum , &coupeSum , &gtSum ); //users sum input
                }
                //after checking all data is valid - sales data enters the array:
                insertSum(carBrand,suvSum,sedanSum,coupeSum,gtSum,cube,days);
                addOneDay(carBrand,days); //add 1 to the days array - in order to let user enter data to the next day
            }
                break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

            // Handles option 3: Provide daily stats for a specific day.
            // Calculates and displays total sales, best-selling brand, and best-selling type.
        case stats: //users choice 3
            currentSalesDay = days[start]; //redifining current day variable
            int dayCase3; //variable for users day choice
            printf("What day would you like to analyze?\n"); //output
            scanf("%d", &dayCase3); //users day input
            if(currentSalesDay != start) //In case sales were entered
            {
                while (dayCase3<=0 || dayCase3>currentSalesDay) //loop keep running in case day is invalid
                {
                    printf("Please enter a valid day.\nWhat day would you like to analyze?\n"); //ask user to input day
                    scanf("%d", &dayCase3); //users day input
                }
            }
           else //In case there are no sales at all
           {
               while (dayCase3 != addOne) //Loop stops when user choose 1
               {
                   printf("Please enter a valid day.\nWhat day would you like to analyze?\n"); //ask user to input day
                   scanf("%d", &dayCase3); //users day input
               }
           }
            printf("In day number %d:\nThe sales total was %d\n",dayCase3,totalSalesSum(dayCase3,cube)); //output of the day, total sales sum of users day choice
            printf("The best sold brand with %d sales was ",maxBrandSalesAmount(dayCase3,cube)); //output of the sales sum of the brand who sold the highest sum of cars in users day choice
            printBrandName(maxSalesBrand(dayCase3,cube)); //output of the brand who sold the highest sum of cars in users day choice
            printf("\nThe best sold type with %d sales was ",maxTypeSalesAmount(dayCase3,cube)); //output of the sales sum of the type who sold the highest sum of cars in users day choice
            printTypeName(maxSalesType(dayCase3,cube)); //output of the type who sold the highest sum of cars in users day choice
            printf("\n");
            break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

        case print: //users choice 4
            printf("*****************************************\n\n"); //line output
            salesInfoLine(cube,days); //print function data
            printf("\n*****************************************\n"); //line output
            break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

        case insights: //users choice 5
            printf("The best-selling brand overall is "); //output
            printBrandName(bestSellingBrand(cube,days)); //output of the brand who sold the highest sum of cars
            printf(": %d$\n",bestSellingBrandAmount(cube,days)); //amount output of the brand who sold the highest sum of cars
            printf("The best-selling type of car is "); //output
            printTypeName(bestSellingType(cube,days)); //output of the type who sold the highest sum of cars
            printf(": %d$\n",bestSellingTypeAmount(cube,days)); //amount output of the type who sold the highest sum of cars
            printf("The most profitable day was day number %d:",bestSellingDay(cube,days)+addOne); //output of the highest amount of sales day
            printf(" %d$\n",bestSellingDayAmount(cube,days)); //sum output of the highest amount of sales day
            break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

        case deltas: //users choice 6
                for(int i = 0; i < NUM_OF_BRANDS; i++) //calculates delta for every brand:
                {
                    printf("Brand: "); //output
                    printBrandName(i); //prints brand name
                    printf(", Average Delta: %f\n",brandDelta(i,cube,days)); //output of delta of current brand
                }
            break; //back to menu

            //**********************************************************************************************************
            //End of case
            //**********************************************************************************************************

            //In case users option input is invalid
            default: //in case users input is invalid
                printf("Invalid input\n"); //error output
        }
        printMenu(); //output of menu
        scanf("%d", &choice); //users option input
    }
    printf("Goodbye!\n"); //bye output
    return 0;
}



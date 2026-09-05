/*
Names: Iqraa Wahid, Zohra Azizi, Mehrsa Karbasforushha
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DAYS 366
#define SIZE4 200 //global variable: size of multiple arrays (Question 4)

// defining constants for max array sizes (Question 3)
#define MAX_DAYS3 400 //max number of days
#define MAX_LAKES3 7  //number of lakes including GL total
#define MAX_DATES3 10 /*max number of dates that can be stored for each lake, in case there are multiple max ice concentration days*/

//Question 5 constants
#define MAX_LINE5 200
#define DATA_FILE5 "data_2023-2024.dat"

//Question 1: Calculating the yearly average of ice concentration 
void calc_avg (int year, float avg[]) {
    FILE *file = fopen("data_2023-2024.dat", "r");
    if (!file) {
        printf("File does not exist!\n");
        exit (1);
    }
    
    char line[256];
    float sum[6] = {0.0}, total, sup, mich, hur, erie, ont, stc;
    int day, y, count = 0;
    
    //to skip the headers from line 1-7
    for (int i= 0; i < 7; i++) {
        fgets(line, 256, file); 
    }
    //To read the data starting from line 8 
    while (fgets(line, 256, file)) {
        if (strlen(line) < 10) continue;
        if (sscanf(line, "%d %d %f %f %f %f %f %f %f", &y, &day, 
                   &sup, &mich, &hur, &erie, &ont, &stc, &total) == 9) {
            if (y == year) {
                sum [0] += sup;  //Superior
                sum [1] += mich;  //Michigan
                sum [2] += hur;  //Huron
                sum [3] += erie;  //Erie
                sum [4] += ont;  //Ontario
                sum [5] += stc;  //St.Clair
                count++;
                
            }
        }
        
    }
        
    if (count > 0) {
        for (int i = 0; i < 6; i++) avg[i] = sum[i] / count;
        avg[6] =(sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5])/(6*count);
    }
    fclose(file);
}


//Question 3:
typedef struct {
    int year3;
    int day3;
} Date3;

//structure that stores max ice concentration records
typedef struct {
    double ice_value3; //max ice concentration in percent
    int day_count3; //number of days this concentration occurs
    Date3 dates3[MAX_DATES3]; //array of dates when max occurs
} MaxRecord3;

//function for reading ice concentrations from file
void read_data3(double ice_data3[MAX_LAKES3][MAX_DAYS3], Date3 dates3[MAX_DAYS3], int *num_days3) {
    FILE *file3;
    char line3[200];
    int i; 
    double ice_values3[MAX_LAKES3]; //temporarily stores lake values from each line
    
    file3 = fopen("data_2023-2024.dat", "r");
    if (file3 == NULL) {
        printf("No file to open :(\n");
        exit(1); //end program if file cannot be accessed or opened
    }
    
    // skipping first 5 header lines to ensure numbers will be read and displayed correctly
    for (i = 0; i < 5; i++) {
        fgets(line3, sizeof(line3), file3);
    }
    
    //initializing day counter and start reading data from file
    *num_days3 = 0;
    while (fgets(line3, sizeof(line3), file3) != NULL) {
        if (strlen(line3) < 10) continue; 
        //making sure lines that are blank are skipped
        
        //setting up each line in the order of year, day, and lake values just like in the file
        sscanf(line3, "%d %d %lf %lf %lf %lf %lf %lf %lf", 
               &dates3[*num_days3].year3, &dates3[*num_days3].day3, 
               &ice_values3[0], &ice_values3[1], &ice_values3[2], 
               &ice_values3[3], &ice_values3[4], &ice_values3[5], &ice_values3[6]);
        
        for (i = 0; i < MAX_LAKES3; i++) {
            ice_data3[i][*num_days3] = ice_values3[i];
        }
        (*num_days3)++; 
        //day counter 
    }
    fclose(file3);
}

//function that actually finds the max ice concentration for each lake
void find_max_ice3(double ice_data3[MAX_LAKES3][MAX_DAYS3], Date3 dates3[MAX_DAYS3], int num_days3) {
    const char *lake_names3[MAX_LAKES3] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Clair", "GL Total"};
    //writing lake names for correct display
    
    //array to store max concentration for each lake
    MaxRecord3 max_records3[MAX_LAKES3] = {0};
    int i, j;  
    
    //checking the values for each lake to find max excluding GL total
    for (i = 0; i < MAX_LAKES3 - 1; i++) {  //checks daily concentration for each lake
        for (j = 0; j < num_days3; j++) { 
            //if the current concentration is higher than the stored value, update the max record with current value
            if (ice_data3[i][j] > max_records3[i].ice_value3) {
                max_records3[i].ice_value3 = ice_data3[i][j];
                max_records3[i].day_count3 = 1;
                max_records3[i].dates3[0] = dates3[j];
            } 
            //if the current concentration is equal to stored value, add the date to records
            else if (ice_data3[i][j] == max_records3[i].ice_value3) {
                if (max_records3[i].day_count3 < MAX_DATES3) {
                    max_records3[i].dates3[max_records3[i].day_count3] = dates3[j];
                    max_records3[i].day_count3++;
                }
            }
        }
    }
    
    printf("\nQuestion 3:\n");
    for (i = 0; i < MAX_LAKES3 - 1; i++) {
        printf("%s:\n", lake_names3[i]);
        printf("Maximum ice concentration: %.2lf%%\n", max_records3[i].ice_value3);
        printf("Occurred on %d day(s):\n", max_records3[i].day_count3);
        // print lake name, max concentration and date(s) in which it occured
        for (j = 0; j < max_records3[i].day_count3; j++) {
            printf("  %d day %03d\n", max_records3[i].dates3[j].year3, 
                                    max_records3[i].dates3[j].day3);
        }
        printf("\n");
    }
}


//Question 4:
#define TOTAL_DAYS6 365 //Maximum number of days
#define NUM_LAKES6 6 //Number of lakes

//declaring array which will store names of the lakes
const char *names6[NUM_LAKES6] = {"Sup.", "Mich", "Huron", "Erie", "Ont", "St.Clr"};

//this structure will be used to store the ice concentrations for lakes on a given day
typedef struct {
    int day6;
    double ice_conc6[NUM_LAKES6];//array with lake concentration values
} LakeIceData6;

LakeIceData6 ice6[TOTAL_DAYS6];//related array
int tot_days6 = 0;//intial value for total days


//Question 7:
void calculate_avg_7(const char *file_name7, float avg7[], int year7, int *counter7){
    FILE *myfile7 = fopen(file_name7, "r");//open the file in reading mode
    if (myfile7==NULL) {
        printf("Error occuring in opening file %s!\n", file_name7);
        exit (1);//exit program
    }
    
    char line7[500];//declaring array line which will store lines from text file
    //skip the first 4 lines in the specfic text file
    for (int i=0; i<4; i++) {
        fgets(line7, sizeof(line7), myfile7);
    }
    
    float sum7[7] = {0.0}, sup7, mich7, huron7, erie7, ont7, stClr7, totalGl7; // 7 sums including GL Total
    int day7, y7;
    
    //while loop will end when??
    while (fgets(line7, sizeof(line7), myfile7)) {
        if (strlen(line7)<10) continue;//condition
        //if exactly 9 variables have been extracted from the line buffer then...
        if (sscanf(line7, "%d %d %f %f %f %f %f %f %f", &y7, &day7, &sup7, &mich7, &huron7, &erie7, &ont7, &stClr7, &totalGl7)==9) {
            if (y7==year7) {
                //calculating the sum of concentration percentage for each lake
                sum7[0] = sum7[0] + sup7;   // Superior
                sum7[1] = sum7[1] + mich7;  // Michigan
                sum7[2] = sum7[2] + huron7;   // Huron
                sum7[3] = sum7[3] + erie7;  // Erie
                sum7[4] = sum7[4] + ont7;   // Ontario
                sum7[5] = sum7[5] + stClr7;   // St. Clair
                sum7[6] = sum7[6] + totalGl7; // GL Total from data file
                (*counter7)++;
            }
        }
    }
    //calculate average concentration percentage for each lake:
    if (*counter7 > 0) {
        for (int i = 0; i < 7; i++) avg7[i] = sum7[i] / *counter7; // Average each column directly
    } else {
        printf("No data found for year %d in %s\n", year7, file_name7);
    }
    fclose(myfile7);
}


//Question 8: Extracting daily data for each lake to plot its graph 
void extract_daily_data(const char *filename, float data[][MAX_DAYS][6], int season_number, int start_year) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File %s does not exist\n", filename);
        exit(1);
    }
    char line[256];
    float sup, mich, hur, erie, ont, stc, total;
    int day, year;
    // to skip the header lines while reading the data 
    for (int i = 0; i < 5; i++) fgets(line, 256, file);
    
    /* Note:This part reads daily ice data from seasonal files of (2021-2022, 2022-2023, 2023-2024)
    Each season spans two years: late fall to winter, and early spring.The data is adjusted from 
    late fall to late spring for smoother analysis and saving data files for each lake seperately.*/
    
    while (fgets(line, 256, file)) {
        if (strlen(line) < 10) continue;
        if (sscanf(line, "%d %d %f %f %f %f %f %f %f", &year, &day, &sup, &mich, &hur, &erie, &ont, &stc, &total) == 9) {
            int adjusted_day;
            if (year == start_year && day >= 330) {
                adjusted_day = day-329; // late year
            }
            else if (year == start_year +1) {
                adjusted_day = day + 36; // Early next year 
            } else continue;
            if (adjusted_day >=1 && adjusted_day < MAX_DAYS) {
                data[season_number][adjusted_day][0] = sup;
                data[season_number][adjusted_day][1] = mich;
                data[season_number][adjusted_day][2] = hur;
                data[season_number][adjusted_day][3] = erie;
                data[season_number][adjusted_day][4] = ont;
                data[season_number][adjusted_day][5] = stc;
            }
        }
    }
    fclose(file);
}


int main(void) {
    //Question 1:
    float avg_2023[7] = {0}, avg_2024[7] = {0};
    calc_avg(2023, avg_2023);
    calc_avg(2024, avg_2024);
    
    printf("Question 1:\n");
    printf("Yearly Average Ice Concentration Percentages:\n");
    printf("Lake         | 2023 Ave %% | 2024 Ave %%\n");
    printf("----------------------------------------\n");
    printf("Superior     | %.2f        | %.2f\n", avg_2023[0], avg_2024[0]);
    printf("Michigan     | %.2f        | %.2f\n", avg_2023[1], avg_2024[1]);
    printf("Huron        | %.2f        | %.2f\n", avg_2023[2], avg_2024[2]);
    printf("Erie         | %.2f        | %.2f\n", avg_2023[3], avg_2024[3]);
    printf("Ontario      | %.2f        | %.2f\n", avg_2023[4], avg_2024[4]);
    printf("St. Clair    | %.2f        | %.2f\n", avg_2023[5], avg_2024[5]);
    printf("GL Total     | %.2f        | %.2f\n", avg_2023[6], avg_2024[6]);
    
    
   //Question 2: Finding the highest and lowest ice concertration
   char *lakes[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Clair"};
   
   // for 2023
   float max_2023 = avg_2023[0], min_2023 = avg_2023[0];
   char *max_lake_2023 = lakes[0], *min_lake_2023 = lakes[0];
   
   for (int i=0; i < 6; i++) {
       if (avg_2023[i] > max_2023){
           max_2023 = avg_2023[i];
           max_lake_2023 = lakes[i];
       }
       if (avg_2023[i] < min_2023){
           min_2023 = avg_2023[i];
           min_lake_2023 = lakes[i];
       }
   }
   
   // for 2024 
   float max_2024 = avg_2024[0], min_2024 = avg_2024[0];
   char *max_lake_2024 = lakes[0], *min_lake_2024 = lakes[0];
   
   for (int i=0; i < 6; i++) {
       if (avg_2024[i] > max_2024){
           max_2024 = avg_2024[i];
           max_lake_2024 = lakes[i];
       }
       if (avg_2024[i] < min_2024){
           min_2024 = avg_2024[i];
           min_lake_2024 = lakes[i];
       }
    }
   
    // Answer to Question 2:
    printf("\nQuestion 2:");
    printf("\nThe Highest and Lowest Ice Concerntrations:\n");
    printf("2023 - Highest: %s (%.2f%%), Lowest: %s (%.2f%%)\n", max_lake_2023, max_2023, min_lake_2023, min_2023);
    printf("2024 - Highest: %s (%.2f%%), Lowest: %s (%.2f%%)\n", max_lake_2024, max_2024, min_lake_2024, min_2024);
    
    
    //Question 3: Day, year, ice concentration percentage with the highest percentage for each lake
    double ice_data3[MAX_LAKES3][MAX_DAYS3]; 
    Date3 dates3[MAX_DAYS3];
    int num_days3;
    //array that stored concentration data and corresponding date(s)
    read_data3(ice_data3, dates3, &num_days3); //reads file
    find_max_ice3(ice_data3, dates3, num_days3); //find and display lakes and corresponding max ice concentrations
    
    //Question 4 - Highest ice concentration percentage (specific day, year, lake)
    printf("Question 4:\n");
    int years4[SIZE4];//the recorded years
    int days4[SIZE4];//the recorded days 
    float ice4 = 0; //max concentration of ice
    char lakes4[SIZE4][20];//name of lakes
    char line4[SIZE4]; //array for line buffer
    int counter4 = 0; //counter
    
    //declaring file:
    FILE *myfile4;
    //opening file in reading mode:
    myfile4=fopen("data_2023-2024.dat", "r");
    
    if(myfile4==NULL){
        printf("Error opening the file.");
        return 1;
    }
    
    //Skip the first 5 lines (that have something written in them)
    for (int i=0; i<4; i++) {
        fgets(line4, sizeof(line4), myfile4);
    }
    
    //will read the file and store the contents within it to the buffer line until the function fgets equals NULL, meaning when the end of file has been reached
    while(fgets(line4, sizeof(line4), myfile4)!=NULL){
        if(strlen(line4)<4)continue;//
        
        int year4, day4;
        //declaring variables that will represent the ice concentration of each lake
        double sup4, mich4, huron4, erie4, ont4, stClr4;
        
        //storing whats in the lines to the location of the variables that represent the concentrations of the lakes
        //if 8 variables from the line buffer are extracted then continue...
        if (sscanf(line4, "%d %d %lf %lf %lf %lf %lf %lf %*f", &year4, &day4, &sup4, &mich4, &huron4, &erie4, &ont4, &stClr4) < 8) {
            continue;
        }
        //array that will store each lakes concentrations:
        float conc4[] = {sup4, mich4, huron4, erie4, ont4, stClr4}; 
        //array for the names of the lakes:
        char *lake_names4[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Clair"};
        
        //finding the highest concentration:
        for (int i=0;i<6;i++) {
            if (conc4[i]>ice4) { 
                ice4=conc4[i]; 
                counter4=0;//resetting value of counter
                years4[counter4]=year4;
                days4[counter4]=day4; 
                strcpy(lakes4[counter4], lake_names4[i]); 
                counter4++;//updating value of counter
            }
            //finding same values that match %
            else{
                if (conc4[i]==ice4&&counter4<SIZE4) {
                    years4[counter4]=year4;
                    days4[counter4]=day4;
                    strcpy(lakes4[counter4], lake_names4[i]);
                    counter4++;
                }
            }
        }
    }
    //close file
    fclose(myfile4);
    
    //output results:
    printf("The highest ice concentration percentage found in the data file is %.2f%%\n", ice4);
    printf("These highest ice concentration percentages are found on: \n");
    
    //for loop to output all the times a lake have the highest concentration
    for (int j=0; j<counter4;j++) {
        printf("Year %d, Day %d, Lake %s", years4[j], days4[j], lakes4[j]);
        printf("\n");
    }
    
    
    //Question 5: One graph per lake of the ice concentration percentage of each daily average
     FILE *in5, *sup5, *mich5, *huron5, *erie5, *ont5, *stclair5;
    char line5[MAX_LINE5];
    int year5, day5;
    double sup_ice5, mich_ice5, huron_ice5, erie_ice5, ont_ice5, stclair_ice5, gl_total5;
    
    //opening data file to read
    in5 = fopen(DATA_FILE5, "r");
    if (in5 == NULL) {
        printf ("Cannot open file :(");
        return (1);
    } //end program if file cannot be access or opened
    
    // skipping header lines to read and display the information correctly
    int header_finder5 = 0;  
    while (!header_finder5 && fgets(line5, MAX_LINE5, in5)) {
        if (strstr(line5, "Year Day") != NULL) {
            fgets(line5, MAX_LINE5, in5);
            header_finder5 = 1;  //exiting loop
        }
    }
    
    //opening a file for each lake
    sup5 = fopen("sup5.dat", "w");
    mich5 = fopen("mich5.dat", "w");
    huron5 = fopen("huron5.dat", "w");
    erie5 = fopen("erie5.dat", "w");
    ont5 = fopen("ont5.dat", "w");
    stclair5 = fopen("stclair5.dat", "w");
    
    // reading data line by line and process
    while (fgets(line5, MAX_LINE5, in5)) {
        if (sscanf(line5, "%d %d %lf %lf %lf %lf %lf %lf %lf", 
                  &year5, &day5, &sup_ice5, &mich_ice5, &huron_ice5, 
                  &erie_ice5, &ont_ice5, &stclair_ice5, &gl_total5) >= 8) {
            //writing for the output files with day and ice concentration
            fprintf(sup5, "%d %.2lf\n", day5, sup_ice5);
            fprintf(mich5, "%d %.2lf\n", day5, mich_ice5);
            fprintf(huron5, "%d %.2lf\n", day5, huron_ice5);
            fprintf(erie5, "%d %.2lf\n", day5, erie_ice5);
            fprintf(ont5, "%d %.2lf\n", day5, ont_ice5);
            fprintf(stclair5, "%d %.2lf\n", day5, stclair_ice5);
        }
    }
    
    //closing all files at the end
    fclose(in5);
    fclose(sup5);
    fclose(mich5);
    fclose(huron5);
    fclose(erie5);
    fclose(ont5);
    fclose(stclair5);

    printf("\nQuestion 5:\nDaily data files generated for each lake from 2023-2024 data files.\n");
    
    
    //Question 6 - Data to graph a single graph of the ice concentration percentages:
    printf("\nQuestion 6:\n");
    FILE *myfile6;//declaring ORIGINAL file pointer
    myfile6 = fopen("data_2023-2024.dat", "r");//opening file in reading mode

    if (myfile6 == NULL) {
        printf("Error opening original file.\n");
        return 1;
    }
    
    //skip first 8 lines in the text file cotaining the data:
    char line6[500];
    for (int i = 0; i < 8; i++) {
        if (fgets(line6, sizeof(line6), myfile6) == NULL) {//unable to read lines in text file
            printf("Unable to read header lines.\n");
            fclose(myfile6);//close file
            return 1;
        }
    }
    
    //declaring variables:
    int year6, day6;
    double gl_total6;

    //while loop will take value from the textfile and store it in the corresponding locations of variables, until each time less than 10 values are stored
    while (fscanf(myfile6, "%d %d %lf %lf %lf %lf %lf %lf %lf", &year6, &day6,
        &ice6[tot_days6].ice_conc6[0],
        &ice6[tot_days6].ice_conc6[1],
        &ice6[tot_days6].ice_conc6[2],
        &ice6[tot_days6].ice_conc6[3],
        &ice6[tot_days6].ice_conc6[4],
        &ice6[tot_days6].ice_conc6[5],
        &gl_total6) < 10) {
        ice6[tot_days6].day6 = day6;//storing day values in array ice
        tot_days6++;//update value of days
        if (tot_days6 >= TOTAL_DAYS6) {
            break;//when maximum days value has been attained, while loop ends
        }
    }

    fclose(myfile6);//closing 2023-2024 file
    
    FILE *graphfile;//declaring file with graphing data
    graphfile=fopen("graphfile.txt", "w");//file opened in writing mode
    if (graphfile==NULL) {
        printf("Error opening file with graphing data.\n");
        return 1;
    }
    
    //writing first column 'days' into 'graphing_data.txt'
    fprintf(graphfile, "Day");
    for (int i=0; i<NUM_LAKES6; i++) {
        fprintf(graphfile, " %s", names6[i]);
    }
    fprintf(graphfile, "\n");//next line in 'graphing_data.txt'
    
    //using 2D array to write data (needed for graphing) into 'graphing_data.txt'
    for (int i=0; i<tot_days6; i++) {
        fprintf(graphfile, "%d", ice6[i].day6);
        for (int j=0; j<NUM_LAKES6; j++) {
            fprintf(graphfile, " %6.2f", ice6[i].ice_conc6[j]);
        }
        fprintf(graphfile, "\n");//next line in 'graphing_data.txt'
    }

    fclose(graphfile);//closing 'graphing_data.txt' file
    
    //output:
    printf("Data needed to make a single graph of the ice concentration percentages has been added to the 'graphfile.txt' file.\n");
    
    
    //Question7 - Yearly Average Ice Concentration Percentages:
    //declaring array variables for average of each year:
    float avg_2021_7[7]={0}, avg_2022a_7[7]={0}, avg_2022b_7[7]={0}, avg_2023_7[7]={0};
    
    //declaring/intializing counter variables:
    int counter_2021_7=0.0, counter_2022a_7=0.0, counter_2022b_7=0.0, counter_2023_7=0.0;
    
    //calling void functions to calculate the average of each year (using pointers)
    calculate_avg_7("data_2021-2022.dat", avg_2021_7, 2021, &counter_2021_7);
    calculate_avg_7("data_2021-2022.dat", avg_2022a_7, 2022, &counter_2022a_7);
    calculate_avg_7("data_2022-2023.dat", avg_2022b_7, 2022, &counter_2022b_7);
    calculate_avg_7("data_2022-2023.dat", avg_2023_7, 2023, &counter_2023_7);
    
    //output:
    printf("\nQuestion 7:\n");
    printf("Lake         | 2021 Ave %% | 2022 Ave %% (21-22)  | 2022 Ave %% (22-23) | 2023 Ave %%\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Superior     | %.2f       | %.2f               | %.2f               | %.2f\n", avg_2021_7[0], avg_2022a_7[0], avg_2022b_7[0], avg_2023_7[0]);
    printf("Michigan     | %.2f       | %.2f               | %.2f               | %.2f\n", avg_2021_7[1], avg_2022a_7[1], avg_2022b_7[1], avg_2023_7[1]);
    printf("Huron        | %.2f       | %.2f               | %.2f               | %.2f\n", avg_2021_7[2], avg_2022a_7[2], avg_2022b_7[2], avg_2023_7[2]);
    printf("Erie         | %.2f       | %.2f               | %.2f               | %.2f\n", avg_2021_7[3], avg_2022a_7[3], avg_2022b_7[3], avg_2023_7[3]);
    printf("Ontario      | %.2f       | %.2f                | %.2f               | %.2f\n", avg_2021_7[4], avg_2022a_7[4], avg_2022b_7[4], avg_2023_7[4]);
    printf("St. Clair    | %.2f       | %.2f               | %.2f              | %.2f\n", avg_2021_7[5], avg_2022a_7[5], avg_2022b_7[5], avg_2023_7[5]);
    printf("GL Total     | %.2f       | %.2f               | %.2f               | %.2f\n", avg_2021_7[6], avg_2022a_7[6], avg_2022b_7[6], avg_2023_7[6]);
    printf("----------------------------------------------------------------------------------\n");

    printf("- Notable Differences Observed:\n");
    printf("1. There is a dramatic increase in the percentage of ice concentration between the years 2021 and 2022. For instance, the percentage of ice concentration increases from %0.2f%% to %0.2f%% in the Superior lake. \n2. Furthermore, another notable difference observed is that the percentage of ice concentration significantly decreases during the time period of 2022 to 2022-2023. For lake Superior it goes from %0.2f%% to %0.2f%% and %0.2f%%.\n", avg_2021_7[0], avg_2022a_7[0], avg_2022a_7[0], avg_2022b_7[0], avg_2023_7[0]);
    printf("- These differences may be caused due to: \n1. Weather Patterns \n2. Climate Change \n3. Regional Variations \n     and etc.\n");
    
    
    //Question 8: Generating daily data files for each lake to plot their graphs 
    float data[3][MAX_DAYS][6] = {{{0}}};
    extract_daily_data("data_2021-2022.dat", data, 0, 2021);  // Season 0: 2021-2022
    extract_daily_data("data_2022-2023.dat", data, 1, 2022);  // Season 1: 2022-2023
    extract_daily_data("data_2023-2024.dat", data, 2, 2023);  // Season 2: 2023-2024
    FILE *fp[6];
    const char *lakes_files[] = {"superior.dat", "michigan.dat", "huron.dat", "erie.dat", "ontario.dat", "stclair.dat"};
  
    for (int i = 0; i < 6; i++) {
        fp[i] = fopen(lakes[i], "w"); //opening files for writing data
          fprintf(fp[i], "# Day 2021-2022 2022-2023 2023-2024\n"); //header
    }
    for (int day = 1; day < MAX_DAYS; day++) {
        for(int lake = 0; lake < 6; lake++) {
           fprintf(fp[lake], "%d %.2f %.2f %.2f\n", day, data[0][day][lake], data[1][day][lake], data[2][day][lake]);
        }
    }
    for (int i = 0; i < 6; i++) fclose(fp[i]); //closeing all the files
    printf("\nQuestion 8:\nDaily data files generated for each lake from 2021-2022, 2022-2023, 2023-2024 data files.\n");
    return (0);
}
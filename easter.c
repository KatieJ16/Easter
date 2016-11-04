#include <stdio.h>
int calculate_Easter_date(int year);

int calculate_Easter_date(int year) {
    /* This function finds the date of easter using the algorithm 
     * by Donald Knuth
     * the parameter y is the year you want to calculate easter for
     * output is an integer of the date: if positive, easter is in April. 
     * If the date is negative the date is in March 
     * Return value is 0 when th egiven year is out of range */

    /* Initializing all vaiarbles given by the algorithm 
     * given in the assignment. */
    int golden;
    int century;
    int skipped;
    int correction;
    int epact;
    int Sunday;
    int day;
    /* Account for when year is out of range. 
     * Return 0 and handle error in main() */
    if(year < 1582 || year > 39999) {
        return 0;
    }

    golden = (year % 19) + 1; 
    /* golden is the "golden year" in the 19-year Metonic cycle. */
    century = (year / 100) + 1; 
    /* century in the century */
    skipped = ((3 * century) / 4 - 12); 
    /* skipped is the skipped leap years. */
    correction = ((((8 * century) + 5) / 25) - 5); 
    /* correction is a correction factor for the moon's orbit. */
    day = (((5 * year) / 4)- skipped - 10); 
    /* March ((-day) mod 7 + 7 is a Sunday. */
    epact = ((11 * golden) + 20 + correction - skipped) % 30; 
    
    if(epact > 25 && golden > 11) {
        epact ++;
    }
    else if( epact == 24) {
        epact ++;
    }
    /* e is the "epact" which specifies when a full moon occurs. */
    
    Sunday = 44 - epact; 
    /* March Sunday is a "calandar full moon". */
    if(Sunday < 21) {
        Sunday += 30;
    }
    Sunday = Sunday + 7 - ((day + Sunday) % 7); 
    /* Sunday is a Sunday after the full moon. */
    
    if(Sunday > 31) {
        return Sunday - 31;
    } else {
        return -1 * Sunday;
    }

}
int main(void) {
    /* Main function
    * reads all the inputed years from a file 
    * and will find the date of easter for each year
    * output file is the dates of easter for every year */

    while(1) {/* repeat forever. Will break when EOF is reached. */
        /* initilize all neccescary variables */
        int year;
        int result;
        int date;
        result = scanf("%d", &year);
        if(result == EOF) {
            break; /* Stop when there are no more lines in the file. */
        }
        date = calculate_Easter_date(year);
        /* Account for when year is out of range and 0 is returned */
        if(date == 0) {
            fprintf(stderr, "Year out of range." 
                    "Can only input between the years of 1582 - 39999");
        } else if(date < 0) { /* Negative when Easter is in March. */
            printf("%d - March %d\n", year, -1 * date);
        } else { /* Positive when Easter is in April. */
            printf("%d - April %d\n", year, date);
        }
    }
    return 0;
}

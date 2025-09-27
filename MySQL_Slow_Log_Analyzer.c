#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES_ROWS 100
#define MAX_DATA_ROWS 100


struct RuleStruct {
    int rule_number;
    char SQL_key[255];
    char SQL_location[255];
} RuleMatrix[MAX_RULES_ROWS];

struct DataStruct {
    char SQL_Statement[255];
    char execution_date[10];
    int query_time;
    int lock_time;  
    int rows_examined;
} DataMatrix[MAX_DATA_ROWS];


void read_rules(struct RuleStruct rule_matrix[]);
void print_results();

int main()
{
      int i,j,k=0;
      char sql_buf[1000];      
      char *token;
      int token_count=0;
      int input_rule_number=0;
      int query_number=0;
      int line_number=1;
      bool new_query=true;

      struct RuleStruct rule_matrix[MAX_RULES_ROWS];
      struct DataStruct data_matrix[MAX_DATA_ROWS];
   
            
    printf("MySQL Slow Log Analyzer\n\n");

    // Read in the rules file into memory
    read_rules(rule_matrix);

    
    // ========================================================
    // main processing.
    // for each entry in the input file, process it.
    // check if rule is found - if not output it 
    // if rule found, record a hit in the Query Matrix for that date and that rule and that query time and that lock time.
    // ========================================================
    FILE *rFile;
    rFile = fopen ("input_raw_data_slim.txt", "r");
    if (rFile == NULL)
    {
      printf ("error opening file");
      return 0;
    }

   

    while (fgets(sql_buf, sizeof(sql_buf), rFile) != NULL) {
         

        
        if (new_query == true) {
            // Processing the first line which has no relevant data
            new_query = false;
            query_number++;
            line_number++;
            printf("** Processing Query #: %i\n", query_number);
            printf("        Processing line1:   %s", sql_buf);
        } else if ( line_number == 2) {
            // this is the SQL query data
            printf("        Processing line2:   %s", sql_buf);
            line_number++;
        } else if (line_number == 3) {
            // Extract the datetime
            printf("        Processing line3:   %s", sql_buf);
            line_number++;
        } else if (line_number == 4) {
            // No relevant data
            printf("        Processing line4:   %s", sql_buf);
            line_number++;
        } else if (line_number == 5) {
            // Extract the query time, lock time and rows examined
            new_query = true;
            printf("        Processing line5:   %s\n", sql_buf);
            line_number=1;
        }


        
        


    }


    fclose (rFile);
    

    // Print final results.
    print_results();
    
    

    return 0;
}

// ========================================================
// Read in the rules file into memory
// ========================================================
void read_rules(struct RuleStruct rule_matrix[])
{

    FILE *pFile;
    int input_rule_number=0;
    char input_SQL_key[255];
    char input_SQL_location[255];
    int rule_count=0;

    pFile = fopen ("input_query_rules.txt", "r");
    if (pFile == NULL)
    {
      printf ("error opening file");
      return;
    }

    printf("** Reading Rules\n",rule_count);
    while (fscanf(pFile,"%i,%1000[^,] , %100[^,\n]", &input_rule_number,&input_SQL_key, &input_SQL_location) != EOF)
    {
        rule_matrix[rule_count].rule_number = input_rule_number;
        strcpy(rule_matrix[rule_count].SQL_key, input_SQL_key);
        strcpy(rule_matrix[rule_count].SQL_location, input_SQL_location);
        printf("   Rule #%i\n",rule_matrix[rule_count].rule_number); 
        printf("       SQL Statement:  %s\n",rule_matrix[rule_count].SQL_key); 
        printf("       Location:       %s\n",rule_matrix[rule_count].SQL_location); 
        rule_count++;
    }
        printf("** Total Rules read = %d\n\n",rule_count);
    
    fclose (pFile);
}


// ========================================================
// Print final results.
// Evaluate the arguements.
// Loop through each record in the Rules Matrix
// If a summary report (Rule #, occurances, avg query time, avg lock time) then
    // Loop through each record in the Query Matrix.
    // if the rule matches then occurances++, sum query time, sum lock time)
    // After all records for th at rule are processed, calculate avg query time, avg lock time
    // reset the counters and sums to zero.
    // print out the record for that rule
    // move to next rule
//
// if a detailed report (Rule #, Date, query time, lock time, SQL location) then
    // Loop through each record in the Query Matrix.
    // find the value in the rules matrix and print out the record
    // move to next rule
// ========================================================
void print_results()
{

}

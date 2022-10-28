#include<iostream>
#include<sqlite3.h>
#include<string>
#include<vector>
#include"sqlite.h"

#include"charOperations.h"

const std::string db_name = "../database/props.db";

void i_came_here()
{
    static unsigned int call_count = 0;
    call_count++;
    std::cout<<"\n I came here for the "<<call_count<<"th time \n";
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) 
{
   int i;
   for(i = 0; i<argc; i++) 
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        printf("%s\n", argv[i] ? argv[i] : "NULL");

    }
   printf("\n");
   return 0;
}

sqlite3 * opendb(const char* filename)
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(filename, &db);

    if(rc) 
    {
       std::cout<<"Can't open database: %s\n"<<sqlite3_errmsg(db);
       return NULL;
    } 
    else 
    {
       std::cout<<"Opened database successfully\n";
       return db;
    }
}

void run_command(sqlite3 *db, char* entry)
{
   int rc;
   char* zErrMsg = 0;
   rc = sqlite3_exec(db, entry, callback, 0, &zErrMsg);
   if(rc != SQLITE_OK)
   {
      //fprintf(stderr, "SQL error: %s\n", zErrMsg);
      std::cout<<"SQL error: "<<zErrMsg<<"\n";
      sqlite3_free(zErrMsg);
   }
   else
   {
     std::cout<<"success \n";
      //fprintf(stdout, "changes successfully\n");
   }
}

void run_command(sqlite3 *db, const char* entry)
{
   int rc;
   char* zErrMsg = 0;
   rc = sqlite3_exec(db, entry, callback, 0, &zErrMsg);
   if(rc != SQLITE_OK)
   {
      //fprintf(stderr, "SQL error: %s\n", zErrMsg);
      std::cout<<"SQL error: "<<zErrMsg<<"\n";
      sqlite3_free(zErrMsg);
   }
   else
   {
     std::cout<<"success \n";
      //fprintf(stdout, "changes successfully\n");
   }
}


int sqlite()
{
    std::cout<<"\n *************** c++ interface for sqlite3 ********** \n ";
    std::cout<<"enter the filename : ";
    
    std::string folder = "../database/";
    std::string file;
    std::cin>>file;
    
    std::string res = folder + file + ".db";
    //const char* filename = res.c_str();
    //const char* work = "../Databases/mydb.db";

    sqlite3* db = opendb(res.c_str());

if(db!=nullptr)
{    
    std::cout<<"\n  The opened database is --> "<<res<<"\n";
    std::cout<<"establish commands here --> loop starts / issue quit to quit \n";
    while(true)
    {
        char* command = new char[300];
        std::cout<<"\nsqlite> ";
        //std::cin>>command;
        scanf(" %[^\n]s",command);

        // break for quit
        if(quit_compare(command))
        {
            std::cout<<"\n ********** bye ! *********\n\n";
            delete[] command;
            break;
        }

        // check command to dbms
        std::cout<<" ---- ur command to dbms is : ";
        charprint(command);
        std::cout<<" ---- ";
        // run the command
        run_command(db, command);

        delete[] command;
    }
    sqlite3_close(db);
    return 0;
}
    else
        return 0;

}

// int test()
// {
//     sqlite3* db = opendb(db_name.c_str());
//     if(db!=nullptr)
//     {
//         std::string command = "select gas_name from base_gas_prop where id='";
//         std::string temp;
//         for(int i=0;i<10;i++)
//         {
//             temp = command + intTochar(i+1) + "';";
//             //std::cout<<temp<<"\n";
//             run_command(db,temp.c_str());
//             temp.erase();
//         }
        

//         sqlite3_close(db);
//         return 1;
//     }
//     else
//         return 0;
// }

int test()
{
    char* test = new char[100];
    sqlite3_stmt*        stmt;

    // construct statement
    std::string gas_name = "Methane";
    snprintf(
        test,
        100,
        "select * from c_ideal where gas_name='%s'",
        gas_name.c_str()
    );

    std::cout<<"\n"<<test<<"\n";

    // open db and make sure its open
    sqlite3* db = opendb(db_name.c_str());

    //prepare statement sqlite3_prepare is a constructor for sstatement
    sqlite3_prepare(db, test, 100, &stmt, NULL);

    double tt = 1.618;

    // // run to DBMS line by line using step
    // if(sqlite3_step(stmt)==SQLITE_ROW)
    // {
    //     // use this command to fetch data 2 is the column number
    //     tt = sqlite3_column_double(stmt, 2);

    //     std::cout<<"my data in that cell is --> "<<tt;
    // }

    const unsigned char* text;
    bool done = false;
    while (!done) {
        printf("In select while\n");
        switch (sqlite3_step (stmt)) {
        case SQLITE_ROW:
            tt  = sqlite3_column_double(stmt);
            std::cout<<tt;
            break;

        case SQLITE_DONE:
            done = true;
            break;

        default:
            fprintf(stderr, "Failed.\n");
            return 1;
        }
    }


    //once done close commection destructer of statement
    sqlite3_finalize(stmt);

    //all done close db
    sqlite3_close(db);

    return 0;
}

int ref()
{
    const char*          username = "satyam";
    char                 q[999];
    sqlite3*             db;
    sqlite3_stmt*        stmt;
    int                  row = 0;
    int                  bytes;
    const unsigned char* text;


    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT ipaddr FROM items WHERE username = '%s'",
        username
    );

    if (sqlite3_open ("test.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database.\n");
        return 2;
    }

    printf("Query: %s\n", q);

    sqlite3_prepare(db, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        printf("In select while\n");
        switch (sqlite3_step (stmt)) {
        case SQLITE_ROW:
            bytes = sqlite3_column_bytes(stmt, 0);
            text  = sqlite3_column_text(stmt, 1);
            printf ("count %d: %s (%d bytes)\n", row, text, bytes);
            row++;
            break;

        case SQLITE_DONE:
            done = true;
            break;

        default:
            fprintf(stderr, "Failed.\n");
            return 1;
        }
    }

    sqlite3_finalize(stmt);

    return 0;
}
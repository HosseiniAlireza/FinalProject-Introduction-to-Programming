#include <iostream>
#include<stdio.h>
#include<io.h>
#include<conio.h>
#include<string.h>

struct date {
    int year, month, day;
};
//---------------------
struct student {
    int id;
    char name[21];
    float ave;
    struct date bday;
};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int menu();
void createFile();
void insRecord();
void delRecord();
void search();
void report();
void showAll();
void updateRecord();

//-----------------------------------
int main(int argc, char** argv) {
    
    while(1) {
        int selection = menu();
        switch(selection) {
            case 1:
                while(1) {
                    createFile();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 2:
                while(1) {
                    insRecord();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 3:
                while(1) {
                    delRecord();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 4:
                while(1) {
                    search();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 5:
                while(1) {
                    report();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 6:
                while(1) {
                    showAll();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 7:
                while(1) {
                    updateRecord();
                    cout << "\nPress any key to return to the main menu...";
                    getch();
                    break;
                }
                break;
            case 8:       
                return 0;
        }
    }

    return 0;
}
//------------------------------------
int menu()
{
  int sel;    
  cout << "\n1-create File\n";
  cout << "2-insert record\n";
  cout << "3-delete record\n";
  cout << "4-search\n";
  cout << "5-report\n";
  cout << "6-show all\n";
  cout << "7-update\n";
  cout << "8-exit\n";
  cout << "Enter your selection:";
  cin >> sel;
  return(sel);
}
//------------------------------------
void createFile()
{
    FILE *fp;
    fp = fopen("c:\\test.dat", "wb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    fclose(fp);
    cout << "File created successfully.\n";
}
//---------------------------------------
void insRecord()
{
    char ch = 'y';
    struct student st;
    FILE *fp;
    fp = fopen("c:\\test.dat", "ab");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    while (ch == 'y' || ch == 'Y')
    {
        cout << "\nEnter a student information:\n";
        cout << "id:";     cin >> st.id;
        cout << "name:";   cin >> st.name;
        cout << "ave:";    cin >> st.ave;
        cout << "year:";   cin >> st.bday.year;
        cout << "month:";  cin >> st.bday.month;
        cout << "day:";    cin >> st.bday.day;
        fwrite(&st, sizeof(struct student), 1, fp);
        cout << "Do you continue <y/n>:";
        ch = getch();
    } 
    fclose(fp);
}
//---------------------------------------
void delRecord()
{
    int counter = 0, x;
    struct student st;
    FILE *f, *fp;
    fp = fopen("c:\\test.dat", "rb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }

    f = fopen("c:\\temp.dat", "wb");
    if(f == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    
    cout << "Enter id for delete:";
    cin >> x;
    
    counter = filelength(fileno(fp)) / sizeof(struct student);
    while (counter--)
    {
        fread(&st, sizeof(struct student), 1, fp);
        if (x != st.id)
            fwrite(&st, sizeof(struct student), 1, f);
    }
    fclose(f);
    fclose(fp);
    remove("c:\\test.dat");
    rename("c:\\temp.dat", "c:\\test.dat");
    cout << "Record deleted successfully if it existed.\n";
}
//-------------------------------------------
void search()
{
    int counter = 0;
    char  x[21];
    struct student st;
    FILE *fp;
    fp = fopen("c:\\test.dat", "rb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    cout << "Enter name:";
    cin >> x;
    
    counter = filelength(fileno(fp)) / sizeof(struct student);
    while (counter--)
    {
        fread(&st, sizeof(struct student), 1, fp);
        if (strcmp(x, st.name) == 0)
        {
            cout << "\nid:" << st.id << " name:" << st.name << " ave:" << st.ave;
            cout << " Bday:" << st.bday.year << "-" << st.bday.month << "-" << st.bday.day << "\n";
        }
    }
    fclose(fp);
}
//-----------------------------------------
void report()
{
    int counter = 0;
    float total = 0, avg;
    struct student st;
    FILE *fp;
    fp = fopen("c:\\test.dat", "rb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }

    counter = filelength(fileno(fp)) / sizeof(struct student);
    if (counter == 0) {
        cout << "No records to display\n";
        fclose(fp);
        return;
    }

    while (counter--)
    {
        fread(&st, sizeof(struct student), 1, fp);
        total += st.ave;
    }
    avg = total / (filelength(fileno(fp)) / sizeof(struct student));
    cout << "Average Score of All Students: " << avg << "\n";
    fclose(fp);
}
//----------------------------------------
void showAll()
{
    int counter = 0;
    struct student st;
    FILE *fp;
    fp = fopen("c:\\test.dat", "rb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    
    counter = filelength(fileno(fp)) / sizeof(struct student);
    while (counter--)
    {
        fread(&st, sizeof(struct student), 1, fp);
        cout << "\nid:" << st.id << " name:" << st.name << " ave:" << st.ave;
        cout << " Bday:" << st.bday.year << "-" << st.bday.month << "-" << st.bday.day << "\n";
    }
    fclose(fp);
}
//----------------------------------------
void updateRecord()
{
    int counter = 0, x, found = 0;
    struct student st;
    FILE *fp, *f;
    fp = fopen("c:\\test.dat", "rb");
    if(fp == NULL)
    {
        cout << "File cannot open\n";
        return;
    }

    f = fopen("c:\\temp.dat", "wb");
    if(f == NULL)
    {
        cout << "File cannot open\n";
        return;
    }
    
    cout << "Enter id to update:";
    cin >> x;
    
    counter = filelength(fileno(fp)) / sizeof(struct student);
    while (counter--)
    {
        fread(&st, sizeof(struct student), 1, fp);
        if (x == st.id)
        {
            found = 1;
            cout << "\nEnter new information:\n";
            cout << "id:";     cin >> st.id;
            cout << "name:";   cin >> st.name;
            cout << "ave:";    cin >> st.ave;
            cout << "year:";   cin >> st.bday.year;
            cout << "month:";  cin >> st.bday.month;
            cout << "day:";    cin >> st.bday.day;
        }
        fwrite(&st, sizeof(struct student), 1, f);
    }
    if (!found)
        cout << "Record not found\n";

    fclose(f);
    fclose(fp);
    remove("c:\\test.dat");
    rename("c:\\temp.dat", "c:\\test.dat");
    cout << "Record updated successfully if it existed.\n";
}


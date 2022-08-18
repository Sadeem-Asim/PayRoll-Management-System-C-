#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <fstream>
#include<conio.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Data{
 string empId , month ,  designation , name, basicSalary , leaves;
 string allowedLeaves , perLeaveDeduction , salary;
};
string CapitalizeFirstLetter(string text)
{
	for (int x = 0; x < text.length(); x++){
		if (x == 0)
		text[x] = toupper(text[x]);
		else if (text[x - 1] == ' ')
		text[x] = toupper(text[x]);
        else
        text[x] = tolower(text[x]);
	}
	return text;
}
bool stringValidateAlphabetOnly(string input)
{
    bool success = true;
    char ascii;
    for(int i =0; i< input.length(); i++){
    ascii = input.at(i);
    if(ascii == 32)
    continue;
    if(ascii >= 0 && ascii < 65 || ascii > 90 && ascii <97
    || ascii > 122 && ascii <= 127)
    success = false;
}
return success;
}
bool stringValidateIntOnly(string input)
{
   bool success;
   char ascii;
   for(int i =0; i< input.length(); i++){
   success = false;
   ascii = input.at(i);
   if(ascii >= 48 && ascii <= 57)
   success = true;
   else
   {
   success = false;
   break;
   }
}
return success;
}
bool monthValidate(string input)
{
    bool success = true;
    if(input != "January" && input != "February"&& input != "March"&& input != "April"
    && input != "May"&& input != "June"&& input != "July"&& input != "August"
    && input != "September"&& input != "October"&& input != "November"&& input != "December" )
    {
        success = false;
        cout<<"You Have Entered An Invalid Month. Enter Again"<<endl;
    }
    return success;
}
void readFileLine(Data& employee , ifstream& file)
{
    getline(file , employee.empId , '-');
    getline(file , employee.name , '-');
    getline(file , employee.designation , '-');
    getline(file , employee.basicSalary , '-');
    getline(file , employee.month , '-');
    getline(file , employee.leaves , '-');
    getline(file , employee.allowedLeaves , '-');
    getline(file , employee.perLeaveDeduction , '-');
    getline(file , employee.salary , '\n');
}
void printingSlips()
{
    int count = 0;
    string month;
    bool success;
    do{
        cout<<"Enter The Month : ";
        cin>>month;
        month=CapitalizeFirstLetter(month);
        success = monthValidate(month);
    }while(success == false);
    Data employee;
    ifstream file("EmployeesManagementSystem.txt" , ios::in);
    readFileLine(employee , file);
    while(file)
    {
        if(employee.month == month)
        {
            count++;
            ofstream file;
            string filename = employee.empId + "_" + employee.name + "_" +employee.month + "_" +"SalarySlip.txt";
            file.open(filename);
            file<<"Salary Month : "<<employee.month<<endl;
            file<<"Employee Name : "<<employee.name<<endl;
            file<<"Designation : "<<employee.designation<<endl;
            file<<"Salary : "<<employee.salary<<endl;
            file.close();
            cout<<employee.name<<" Slip Has Been Generated . Thank You!"<<endl;
        }
        readFileLine(employee ,file);
    }
    file.close();
    if(count == 0)
        cout<<"No Employee Salary Found With Specific Month"<<endl;
}
void input(char flag2)
{
    Data a;
    int c;
    char flag = 'y';
    ofstream output;
    do{
        cout<<"Press\n1. If you want to continue Entering Data\n2. If want to Delete Previous Data and Enter New Data"<<endl;
        c=getche();
        if(c=='1')
            output.open("EmployeesManagementSystem.txt",ios::app);
        else if(c=='2')
            output.open("EmployeesManagementSystem.txt" ,ios::out | ios::trunc);
        else
            cout<<"Invalid Input\n"<<endl;
    }while(c!='1' && c!='2');

    bool success = false;
    int leaves , allowedLeaves , perLeaveDeduction , salary , basicSalary;
    int i =1;
    while(flag != 'n' && flag != 'N' )
    {
        cout<<setfill(' ');
        cout<<setw(65)<<"Enter Information of Employee "<<i<<endl;
        cout<<"Employee ID : ";
        getline(cin, a.empId);
        a.empId=CapitalizeFirstLetter(a.empId);
        while(success == false)
        {
            cout<<"Enter Employee Name : ";
            getline(cin, a.name);
            success = stringValidateAlphabetOnly(a.name);
            if(success == false)
                cout<<"Name Must Not Contain Any Digit"<<endl;
        }
        a.name=CapitalizeFirstLetter(a.name);
        do{
            cout<<"Designation : ";
            getline(cin, a.designation);
            success = stringValidateAlphabetOnly(a.designation);
            if(success == false)
                cout<<"Designation Must Not Contain Any Digit"<<endl;
        }while(success == false);
        a.designation=CapitalizeFirstLetter(a.designation);
        do{
            cout<<"Basic Salary : ";
            getline(cin, a.basicSalary);
            success = stringValidateIntOnly(a.basicSalary);
            if(success  == false)
                cout<<"Basic Salary Must Not Contain Any Character"<<endl;
        }while(success == false);
        do{
            cout<<"Month : ";
            getline(cin, a.month);
            a.month=CapitalizeFirstLetter(a.month);
            success = monthValidate(a.month);
        }while(success == false);
        a.month=CapitalizeFirstLetter(a.month);
        do{
            cout<<"Leaves : ";
            getline(cin, a.leaves);
            success = stringValidateIntOnly(a.leaves);
            if(success  == false)
                cout<<"Leaves Must Not Contain Any Character"<<endl;
        }while(success == false);
        do{
            cout<<"Allowed Leaves : ";
            getline(cin, a.allowedLeaves);
            success = stringValidateIntOnly(a.allowedLeaves);
            if(success  == false)
                cout<<"Allowed Leaves Must Not Contain Any Character"<<endl;
        }while(success == false);
        do{
            cout<<"Per Leave Deduction Rate : ";
            getline(cin, a.perLeaveDeduction);
            success = stringValidateIntOnly(a.perLeaveDeduction);
            if(success  == false)
                cout<<"Deduction Rate Must Not Contain Any Character"<<endl;
        }while(success == false);
        leaves = stoi(a.leaves); //this function changes strings to integer
        allowedLeaves = stoi(a.allowedLeaves);
        perLeaveDeduction = stoi(a.perLeaveDeduction);
        basicSalary = stoi(a.basicSalary);
        if(leaves>allowedLeaves)
        {
            salary = basicSalary - (leaves-allowedLeaves) * perLeaveDeduction;
            a.salary = to_string(salary); //this function changes integer to strings
        }
        else
            a.salary=a.basicSalary;
        // Writing to file
        output<<a.empId<<" -"<<a.name<<"-"<<a.designation<<"-"<<a.basicSalary<<"-"<<a.month
        <<"-"<<a.leaves<<"-"<<a.allowedLeaves<<"-"<<a.perLeaveDeduction<<"-"<<a.salary<<"\n";
        if(flag2 == 'n')
            break;
        i++;
        cout<<"Continue?(y/n)";
        flag = getche();
    }
}
int main ()
{
    do
{
        char choose;
        string menu = "Payroll Management System";
        cout<<setw(100)<<setfill('#')<<"\n"
        <<setw(86)<<setfill('#')<<"  "<<menu<<"  "<<setw(87)<<setfill('#')<<"\n"
        <<setw(100)<<setfill('#')<<"\n";
        cout<<"\n\n"<<endl;
        cout<<setw(100)<<setfill('*')<<"\n"
        <<"*"<<setw(100)<<setfill(' ')<<"  MAIN MENU  "<<setw(98)<<setfill(' ')<<"*"<<"\n"
        <<setw(100)<<setfill('*')<<"\n";
        cout<<"\n"<<endl;
        cout<<"1- Enter information manage salary of specific month\n2"<<
        "- Print Salary Slip\n3- Enter information of new employee\n4- Quit"<<endl;
        cout<<"\nEnter Your Choice >> ";
        choose=getche();
        system("CLS");
        if(choose=='1')
            input('y');
        else if(choose == '2')
            printingSlips();
        else if(choose == '3')
            input('n');
        else if (choose == '4')
            break;
    }while(true);
    cout<<" << Thanks For Choosing Our Services >>"<<endl;
    cout<<" << Made By Sadeem Asim , Shahroz Atiq and Ali Arshad >> "<<endl;
}
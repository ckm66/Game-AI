#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <fstream>
#include <typeinfo>
#include "Trade_Record_Format.h"


void Input_Trade_Record()
{
    std::fstream Trade_Record_Source;
    Trade_Record_Source.open("Apartment Trade Record.csv", std::ios::in);

    std::string line;
    std::string column;
    int count = 0;

    while (getline(Trade_Record_Source, line))
    {
        Trade_Record Flat;
        std::stringstream line_(line);
        count = 0;
        while (getline(line_, column, ','))
        {
            switch (count)
            {

            case 0:
            {
                Flat.Index = column;
                break;
            }

            case 1:
            {
                Flat.Memo_No = column;
                break;
            }

            case 2:
            {
                Flat.Usage = column;
                break;
            }

            case 3:
            {
                Flat.District = column;
                break;
            }

            case 4:
            {
                Flat.PRN_No = column;
                break;
            }

            case 5:
            {
                std::stringstream Time(column);
                Time >> std::get_time(&Flat.Occupation_Date, "%d/%m/%Y");
                break;
            }

            case 6:
            {
                Flat.Building_Name = column;
                break;
            }

            case 7:
            {
                Flat.Address = column;
                break;
            }

            case 8:
            {
                std::stringstream Time(column);
                Time >> std::get_time(&Flat.PASP, "%d/%m/%Y");
                break;
            }

            case 9:
            {
                Flat.Ins_Date = column;
                break;
            }

            case 10:
            {
                Flat.floor = stoi(column);
                break;
            }

            case 11:
            {
                Flat.Unit = column;
                break;
            }

            case 12:
            {
                Flat.Area = stod(column);
                break;
            }

            case 13:
            {
                Flat.Area_N_ft2 = stoi(column);
            }

            case 14:
            {
                Flat.Headroom = stod(column);
                break;
            }

            case 15:
            {
                Flat.View = column;
                break;
            }

            case 16:
            {
                Flat.Price_M = column;
                break;
            }

            case 17:
            {
                Flat.Price = column;
                break;
            }

            case 18:
            {
                Flat.Price_ft = stod(column);
                break;
            }

            case 19:
            {
                Flat.D_Date = column;
                break;
            }

            case 20:
            {
                Flat.Nature = column;
                break;
            }

            case 21:
            {
                Flat.Bldg_Remarks = column;
                break;
            }

            case 22:
            {
                Flat.Tran_Remarks = column;
                break;
            }
            }
            count++;
        }
        Flat.Find_Catorgotories();
        Trade_Records.push_back(Flat);
    }
}

void Input_Residental_Price_Index()
{
    int count = 0;
    int Year = 0;
    int Month = 0;
    std::fstream file;
    file.open("Residental Price Index.csv", std::ios::in);

    std::string line;
    std::string column;

    while (getline(file, line))
    {
        count = 0;
        struct tm Time = {0};
        std::stringstream line_(line);
        while (getline(line_, column, ','))
        {

            switch (count)
            {
            case 0:
            {
                std::stringstream column_(column);
                column_ >> std::get_time(&Time, "%m/%Y");
                if (Time.tm_year == 0)
                {
                    continue;
                }
                Year = 1900 + Time.tm_year;
                Month = 1 + Time.tm_mon;
                break;
            }

            case 1:
            {
                Residental_Price_Index[Year][Month][0] = stod(column);
                break;
            }

            case 2:
            {
                Residental_Price_Index[Year][Month][1] = stod(column);
                break;
            }

            case 3:
            {
                Residental_Price_Index[Year][Month][2] = stod(column);
                break;
            }

            case 4:
            {
                Residental_Price_Index[Year][Month][3] = stod(column);
                break;
            }

            case 5:
            {
                Residental_Price_Index[Year][Month][4] = stod(column);
                break;
            }
            }

            count++;
        }
    }
}

std::vector<std::string> Type_of_Location;
void Find_Type_of_Location()
{
    for (auto it : Trade_Records)
    {
        if (Type_of_Location.end() == std::find_if(Type_of_Location.begin(), Type_of_Location.end(), [&](const std::string &Building_Name)
                                                   { return Building_Name == it.Building_Name; }))
        {
            Type_of_Location.push_back(it.Building_Name);
        }
    }
}

std::vector<std::string> Type_of_View;
void Find_Type_of_View()
{
    for (auto it : Trade_Records)
    {
        if (Type_of_View.end() == std::find_if(Type_of_View.begin(), Type_of_View.end(), [&](const std::string &View)
                                               { return it.View == View; }))
        {
            Type_of_View.push_back(it.View);
        }
    }
}


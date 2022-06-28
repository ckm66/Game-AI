#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Test.h"
#include "Trade_Record_Format.h"

void Results_Checker(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double Factor_Sum);

// Time, Size, Floor, View, Headroom, Age, Location

void Time_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->PASP.tm_year != Comparation_Flat->PASP.tm_year || Reference_Flat->PASP.tm_mon != Comparation_Flat->PASP.tm_mon)
    {
        Factor_Sum += (Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] / Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory]);
        Factor_Sum -= 1;
    }
    return;
}

bool Size_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->Area != Comparation_Flat->Area)
    {
        if (Factor.Area_Cofficiency == false)
        {
            return false;
        }
        Factor_Sum += (Reference_Flat->Area - Comparation_Flat->Area) * Factor.Area;
    }
    return true;
}

bool Floor_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->floor != Comparation_Flat->floor)
    {
        if (Factor.Floor_Cofficiency == false)
        {
            return false;
        }

        Factor_Sum += (Reference_Flat->floor - Comparation_Flat->floor) * Factor.Floor;
    }
    return true;
}

bool View_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->View != Comparation_Flat->View)
    {
        if (Factor.View_Cofficiency == false)
        {
            return false;
        }

        Factor_Sum += (Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View]) - 1;
    }
    return true;
}

bool Headroom_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->Headroom != Comparation_Flat->Headroom)
    {
        if (Factor.Headroom_Cofficiency == false)
        {
            return false;
        }
        double Add{Reference_Flat->Headroom - Comparation_Flat->Headroom};
        Add *= Factor.Headroom;
        Factor_Sum += Add;
    }
    return true;
}

bool Location_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->Building_Name != Comparation_Flat->Building_Name)
    {
        if (Factor.Location_Cofficiency == false)
        {
            return false;
        }
        Factor_Sum += Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name];
        Factor_Sum -= 1;
    }
    return true;
}

bool Age_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum)
{
    if (Reference_Flat->Occupation_Date.tm_year != Comparation_Flat->Occupation_Date.tm_year)
    {
        if (Factor.Age_Cofficiency == false)
        {
            return false;
        }
        Factor_Sum = ((int)Reference_Flat->Occupation_Date.tm_year - (int)Comparation_Flat->Occupation_Date.tm_year) * Factor.Age;
    }
    return true;
}

std::vector<Trade_Record> Reference_Flat_Size;
std::vector<Trade_Record> Comparation_Flat_Size;

void Find_Cofficiency_Size()
{
    for (std::vector<Trade_Record>::iterator Reference_Flat{Trade_Records.begin()}; Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat{Trade_Records.begin()}; Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->Area_N_ft2 == Comparation_Flat->Area_N_ft2) // Skip the current comparation if same or having the same size
            {
                continue;
            }

            if (std::find_if(Reference_Flat_Size.begin(), Reference_Flat_Size.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_Size.end() &&
                std::find_if(Comparation_Flat_Size.begin(), Comparation_Flat_Size.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_Size.end())
            {
                continue;
            }

            double Factor_Sum{0};

            // Time Adjustor
            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            if (Age_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Location
            if (Location_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Headroom
            if (Headroom_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Floor
            if (Floor_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // View
            if (View_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = (Reference_Flat->Price_ft * 10.752688172 - Unit_Rate) / (Unit_Rate * (Reference_Flat->Area - Comparation_Flat->Area));

            if (Cofficiency > Factor.Area - 0.003 && Cofficiency < Factor.Area + 0.003)
            {
                Reference_Flat_Size.push_back(*Reference_Flat);
                Comparation_Flat_Size.push_back(*Comparation_Flat);
            }
        }

        if (Reference_Flat_Size.size() >= 3)
        {
            Factor.Area_Cofficiency = true;
        }
    }
}

std::vector<Trade_Record> Reference_Flat_Floor;
std::vector<Trade_Record> Comparation_Flat_Floor;

void Find_Cofficiency_Floor()
{
    for (std::vector<Trade_Record>::iterator Reference_Flat{Trade_Records.begin()}; Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat{Trade_Records.begin()}; Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->floor == Comparation_Flat->floor) // Skip the current comparation if same or having the same size
            {
                continue;
            }

            if (std::find_if(Reference_Flat_Floor.begin(), Reference_Flat_Floor.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_Floor.end() &&
                std::find_if(Comparation_Flat_Floor.begin(), Comparation_Flat_Floor.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_Floor.end())
            {
                continue;
            }

            double Factor_Sum{0};

            // Time Adjustor
            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            // Age
            if (Age_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Size
            if (Size_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Location
            if (Location_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Headroom
            if (Headroom_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // View
            if (View_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = (Reference_Flat->Price_ft * 10.752688172 - Unit_Rate) / (Unit_Rate * (Reference_Flat->floor - Comparation_Flat->floor));

            if (Cofficiency > Factor.Floor - 0.003 && Cofficiency < Factor.Floor + 0.003)
            {
                Reference_Flat_Floor.push_back(*Reference_Flat);
                Comparation_Flat_Floor.push_back(*Comparation_Flat);
            }
        }

        if (Reference_Flat_Floor.size() >= 3)
        {
            Factor.Floor_Cofficiency = true;
        }
    }
}

std::vector <Trade_Record> Reference_Flat_View;
std::vector <Trade_Record> Comparation_Flat_View;

void Find_Cofficiency_View()
{
    for (std::vector <Trade_Record>::iterator Reference_Flat = Trade_Records.begin(); Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat = Trade_Records.begin(); Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->View == Comparation_Flat->View) // Skip the current comparation if same or having the same size
            {
                continue;
            }

            if (std::find_if(Reference_Flat_View.begin(), Reference_Flat_View.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_View.end() &&
                std::find_if(Comparation_Flat_View.begin(), Comparation_Flat_View.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_View.end())
            {
                continue;
            }

            double Factor_Sum {0};

            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            if (Size_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum))
            {
                continue;
            }

            if (Floor_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Headroom_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Age_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Location_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = ((Reference_Flat->Price_ft * 10.752688172) / Unit_Rate);

            if (Cofficiency > Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 0.03 || Cofficiency < Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] + 0.03)
            {
                std::cout << Cofficiency << std::endl;
                Reference_Flat_Floor.push_back(*Reference_Flat);
                Comparation_Flat_Floor.push_back(*Comparation_Flat);
            }
               
        }
    }
}

std::vector <Trade_Record> Reference_Flat_Headroom;
std::vector <Trade_Record> Comparation_Flat_Headroom;

void Find_Cofficiency_Headroom()
{
    for (std::vector<Trade_Record>::iterator Reference_Flat{Trade_Records.begin()}; Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat{Trade_Records.begin()}; Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->Headroom == Comparation_Flat->Headroom) // Skip the current comparation if same or having the same size
            {
                continue;
            }

            if (std::find_if(Reference_Flat_Headroom.begin(), Reference_Flat_Headroom.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_Headroom.end() &&
                std::find_if(Comparation_Flat_Headroom.begin(), Comparation_Flat_Headroom.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_Headroom.end())
            {
                continue;
            }

            double Factor_Sum{0};

            // Time Adjustor
            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            // Age
            if (Age_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Size
            if (Size_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Floor
            if (Floor_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // Location
            if (Location_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            // View
            if (View_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = (Reference_Flat->Price_ft * 10.752688172 - Unit_Rate) / (Unit_Rate * (Reference_Flat->Headroom - Comparation_Flat->Headroom));

            if (Cofficiency > Factor.Headroom - 0.003 && Cofficiency < Factor.Headroom + 0.003)
            {
                Reference_Flat_Headroom.push_back(*Reference_Flat);
                Comparation_Flat_Headroom.push_back(*Comparation_Flat);
                Results_Checker(Reference_Flat, Comparation_Flat, Factor_Sum);
            }
        }

        if (Reference_Flat_Headroom.size() >= 3)
        {
            Factor.Headroom_Cofficiency = true;
        }
    }
}

std::vector <Trade_Record> Reference_Flat_Age;
std::vector <Trade_Record> Comparation_Flat_Age;

void Find_Cofficiency_Age()
{
    for (std::vector<Trade_Record>::iterator Reference_Flat = Trade_Records.begin(); Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat = Trade_Records.begin(); Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->Occupation_Date.tm_year == Comparation_Flat->Occupation_Date.tm_year) // Skip the current comparation if same or having the same size
            {
                continue;
            }

            if (std::find_if(Reference_Flat_Age.begin(), Reference_Flat_Age.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_Age.end() &&
                std::find_if(Comparation_Flat_Age.begin(), Comparation_Flat_Age.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_Age.end())
            {
                continue;
            }

            double Factor_Sum{0};

            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            if (Size_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Floor_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (View_Adjustor(Reference_Flat,Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Headroom_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Location_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = (Reference_Flat->Price_ft * 10.752688172 - Unit_Rate) / (Unit_Rate * ((int)Reference_Flat->Occupation_Date.tm_year - (int)Comparation_Flat->Occupation_Date.tm_year));

            if (Cofficiency > Factor.Age - 0.003 && Cofficiency < Factor.Age + 0.003)
            {
                Reference_Flat_Age.push_back(*Reference_Flat);
                Comparation_Flat_Age.push_back(*Comparation_Flat);
                //Results_Checker(Reference_Flat, Comparation_Flat, Factor_Sum);
            }
        }    
    }
}

std::vector <Trade_Record> Reference_Flat_Location;
std::vector <Trade_Record> Comparation_Flat_Location;

void Find_Cofficiency_Location()
{
    for (std::vector<Trade_Record>::iterator Reference_Flat = Trade_Records.begin(); Reference_Flat != Trade_Records.end(); Reference_Flat++)
    {
        for (std::vector<Trade_Record>::iterator Comparation_Flat = Trade_Records.begin(); Comparation_Flat != Trade_Records.end(); Comparation_Flat++)
        {
            if (Reference_Flat == Comparation_Flat || Reference_Flat->Building_Name == Comparation_Flat->Building_Name)
            {
                continue;
            }

             if (std::find_if(Reference_Flat_Age.begin(), Reference_Flat_Age.end(), [&](const Trade_Record &a)
                             { return a.Memo_No == Reference_Flat->Memo_No; }) != Reference_Flat_Age.end() &&
                std::find_if(Comparation_Flat_Age.begin(), Comparation_Flat_Age.end(), [&](const Trade_Record &b)
                             { return b.Memo_No == Comparation_Flat->Memo_No; }) != Comparation_Flat_Age.end())
            {
                continue;
            }

            double Factor_Sum{0};

            Time_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum);

            if (Age_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Size_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Headroom_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (Floor_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            if (View_Adjustor(Reference_Flat, Comparation_Flat, Factor_Sum) == false)
            {
                continue;
            }

            double Unit_Rate{Comparation_Flat->Price_ft * 10.752688172};
            Unit_Rate *= (1 + Factor_Sum);

            double Cofficiency{0};
            Cofficiency = (Reference_Flat->Price_ft * 10.752688172 / Unit_Rate);
            

            if (Cofficiency > Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 0.03 || Cofficiency < Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] + 0.03)
            {
                //Results_Checker(Reference_Flat, Comparation_Flat, Factor_Sum);
                Reference_Flat_Location.push_back(*Reference_Flat);
                Comparation_Flat_Location.push_back(*Comparation_Flat);
            }

        }
    }
}

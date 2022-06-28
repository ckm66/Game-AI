#pragma once
#include <iostream>
#include <vector>
#include "Algorithm.h"
#include "Data_Input.h"
#include "Trade_Record_Format.h"

void Time_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool Size_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool Floor_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool View_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool Headroom_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool Location_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

bool Age_Adjustor(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double &Factor_Sum);

void Print_All_Trade_Records()
{
    for (auto it : Trade_Records)
    {
        std::cout << it.Memo_No << '\n';
    }
}

void Print_All_Residental_Index()
{
    for (int Year = 1900; Year < 2023; Year++)
    {
        for (int Month = 1; Month < 13; Month++)
        {
            std::cout << Year << "/" << Month << ' ';
            for (int Categories = 0; Categories < 6; Categories++)
            {
                std::cout << Residental_Price_Index[Year][Month][Categories] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void Results_Checker(std::vector<Trade_Record>::iterator Reference_Flat, std::vector<Trade_Record>::iterator Comparation_Flat, double Factor_Sum)
{
    double Checker{0};
    std::cout << Reference_Flat->Memo_No << ' ' << Comparation_Flat->Memo_No << ' ' << Checker << ' ';
    Time_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    Size_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    Floor_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    Age_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    Headroom_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    View_Adjustor(Reference_Flat, Comparation_Flat, Checker);
    std::cout << Checker << ' ';
    std::cout << std::endl;
}






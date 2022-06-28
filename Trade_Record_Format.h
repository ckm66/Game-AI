#pragma once
#include <time.h>
#include <string>
#include <vector>
#include <map>

struct Factors
{
    double Area;
    double Floor;
    std::map <std::string, double> View;
    double Headroom;
    double Age;
    std::map <std::string, double> Location;

    bool Area_Cofficiency {true};
    bool Floor_Cofficiency {true};
    bool View_Cofficiency  {true};
    bool Headroom_Cofficiency {true};
    bool Age_Cofficiency {true};
    bool Location_Cofficiency {true};
} Factor;

struct Trade_Record
{
    std::string Index;
    std::string Memo_No;
    std::string Usage;
    std::string District;
    std::string PRN_No;
    struct tm Occupation_Date = {0};
    std::string Building_Name;
    std::string Address;
    struct tm PASP = {0};
    std::string Ins_Date;
    int floor;
    std::string Unit;
    double  Area;
    int Area_N_ft2;
    double Headroom;
    std::string View;
    std::string Price_M;
    std::string Price;
    double Price_ft;
    std::string D_Date;
    std::string Nature;
    int  Catergotory;
    std::string Bldg_Remarks;
    std::string Tran_Remarks;

    void Find_Catorgotories()
    {
        if (Area < 40)
        {
            Catergotory = 0;
        }

        else if (Area >= 40 && Area < 70)
        {
            Catergotory = 1;
        }

        else if (Area >= 70 && Area < 100)
        {
            Catergotory = 2;
        }

        else if (Area >= 100 && Area < 160)
        {
            Catergotory = 3;
        }

        else 
        {
            Catergotory = 4;
        }
    }
};

std::vector<Trade_Record> Trade_Records;

double Residental_Price_Index[2023][13][5];
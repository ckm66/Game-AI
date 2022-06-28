#pragma once
#include <algorithm>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <fstream>
#include <typeinfo>

// Time, Size, Floor, View, Headroom, Age, Location

void Generate_Size_File()
{
    if (Reference_Flat_Size.size() < 3)
    {
        std::cerr << "Insufficiency Data for proofing Size Cofficiency " << '\n';
        return;
    }

    std::fstream File;
    File.open("Pair Comparison for Size.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_Size.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_Size.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_Size.end() || Comparation_Flat != Comparation_Flat_Size.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Area Percentage
             << std::to_string(Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 1) << ','                                                                                                                                       // Location Percentage
             << "= (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Headroom) << ','                                                                                                                                      // Headroom Percentage
             << "= (K" + std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Floor) << ','                                                                                                                                         // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}

void Generate_Floor_File()
{
    if (Reference_Flat_Floor.size() < 3)
    {
        std::cerr << "Insufficinecy Data for proofing Floor Cofficiency" << '\n';
        return;
    }

    std::fstream File;
    File.open("Pair Comparison for Floor.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_Floor.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_Floor.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_Floor.end() || Comparation_Flat != Comparation_Flat_Floor.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "= (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Area) << ','                                                                                                                                          // Area Percentage
             << std::to_string(Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 1) << ','                                                                                                                                       // Location Percentage
             << "= (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Headroom) << ','                                                                                                                                      // Headroom Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (K" + std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}

void Generate_View_File()
{
    if (Reference_Flat_View.size() < 3)
    {
        std::cerr << "Insufficiencty Data for proving View Cofficiency" << '\n';
    }

    std::fstream File;
    File.open("Pair Comparison for View.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_View.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_View.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_View.end() || Comparation_Flat != Comparation_Flat_View.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "= (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Area) << ','                                                                                                                                          // Area Percentage
             << std::to_string(Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 1) << ','                                                                                                                                       // Location Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Headroom Percentage
             << "= (K" << std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ") * " + std::to_string(Factor.Floor) << ','                                                                                                                                       // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}

void Generate_Headroom_File()
{
    if (Reference_Flat_Headroom.size() < 3)
    {
        std::cerr << "Insufficiency Data for proofing Headroom Cofficiency" << '\n';
        return;
    }

    std::fstream File;
    File.open("Pair Comparison for Headroom.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_Headroom.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_Headroom.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_Headroom.end() || Comparation_Flat != Comparation_Flat_Headroom.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "= (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Area) << ','                                                                                                                                          // Area Percentage
             << std::to_string(Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 1) << ','                                                                                                                                       // Location Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Headroom Percentage
             << "= (K" << std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ") * " + std::to_string(Factor.Floor) << ','                                                                                                                                       // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}

void Generate_Age_File()
{
    if (Reference_Flat_Age.size() < 3)
    {
        std::cout << "Insufficiency Data for proofing Age Cofficiency" << '\n';
    }

    std::fstream File;
    File.open("Pair Comparison for Age.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_Age.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_Age.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_Age.end() || Comparation_Flat != Comparation_Flat_Age.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "= (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Area) << ','                                                                                                                                          // Area Percentage
             << std::to_string(Factor.Location[Reference_Flat->Building_Name] / Factor.Location[Comparation_Flat->Building_Name] - 1) << ','                                                                                                                                       // Location Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Headroom Percentage
             << "= (K" << std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ") * " + std::to_string(Factor.Floor) << ','                                                                                                                                       // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}

void Generate_Location_File()
{
    if (Reference_Flat_Location.size() < 3)
    {
        std::cerr << "Insufficiency Data for proofing Location Cofficiency" << '\n';
    }

    std::fstream File;
    File.open("Pair Comparison for Location.csv", std::ios::out);

    if (!File.is_open())
    {
        exit(0);
    }

    std::vector<Trade_Record>::iterator Reference_Flat = Reference_Flat_Location.begin();
    std::vector<Trade_Record>::iterator Comparation_Flat = Comparation_Flat_Location.begin();
    int Reference_Row{1};
    int Current_Row{1};
    std::string Temp{""};
    File << "Index" << ',' << "Memo No" << ',' << "Usage" << ',' << "District" << ',' << "PRN No" << ',' << "Occupation Date" << ',' << "Building Name" << ',' << "Address" << ',' << "PASP" << ',' << "Ins. Date" << ',' << "Floor" << ',' << "Unit" << ',' << "Area" << ',' << "Area(N)(ft2)" << ',' << "Headroom" << ',' << "View" << ',' << "Price(M)($)" << ',' << "Price($)" << ',' << "$/ft2(N)($)" << ',' << "D.Date" << ',' << "Nature" << ',' << "Bldg Remarks" << ',' << "Trans Remark" << ',' << "Unit Rate" << ',' << ',' << "Time Index" << ',' << "Time" << ',' << ',' << ',' << "Age" << ',' << "Area" << ',' << "Location" << ',' << "Headroom" << ',' << "Floor" << ',' << "View" << ',' << ',' << "Total" << ',' << "Adj Unit Rate" << ',' << ',' << "Diff" << std::endl;
    Current_Row++;
    while (Reference_Flat != Reference_Flat_Location.end() || Comparation_Flat != Comparation_Flat_Location.end())
    {
        char Occupation_Date[80];
        char PASP[80];

        if (Temp != Reference_Flat->Memo_No)
        {
            strftime(Occupation_Date, 80, "%d/%m/%Y", &Reference_Flat->Occupation_Date);
            strftime(PASP, 80, "%d/%m/%Y", &Reference_Flat->PASP);
            if (Temp != "")
            {
                File << std::endl;
                Current_Row++;
            }
            Reference_Row = Current_Row;
            File << Reference_Flat->Index << ','
                 << Reference_Flat->Memo_No << ','
                 << Reference_Flat->Usage << ','
                 << Reference_Flat->District << ','
                 << Reference_Flat->PRN_No << ','
                 << Occupation_Date << ','
                 << Reference_Flat->Building_Name << ','
                 << Reference_Flat->Address << ','
                 << PASP << ','
                 << Reference_Flat->Ins_Date << ','
                 << Reference_Flat->floor << ','
                 << Reference_Flat->Unit << ','
                 << Reference_Flat->Area << ','
                 << Reference_Flat->Area_N_ft2 << ','
                 << Reference_Flat->Headroom << ','
                 << Reference_Flat->View << ','
                 << Reference_Flat->Price_M << ','
                 << Reference_Flat->Price << ','
                 << Reference_Flat->Price_ft << ','
                 << Reference_Flat->D_Date << ','
                 << Reference_Flat->Nature << ','
                 << Reference_Flat->Bldg_Remarks << ',' << '?' << ','
                 << Reference_Flat->Price_ft * 10.752688172 << ',' << ',' << Residental_Price_Index[Reference_Flat->PASP.tm_year + 1900][Reference_Flat->PASP.tm_mon + 1][Reference_Flat->Catergotory] << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << ',' << Reference_Flat->Price_ft * 10.752688172 << std::endl;
            Current_Row++;
            Temp = Reference_Flat->Memo_No;
        }

        strftime(Occupation_Date, 80, "%d/%m/%Y", &Comparation_Flat->Occupation_Date);
        strftime(PASP, 80, "%d/%m/%Y", &Comparation_Flat->PASP);
        std::string Tran_Remarks = Comparation_Flat->Tran_Remarks;

        File << Comparation_Flat->Index << ','
             << Comparation_Flat->Memo_No << ','
             << Comparation_Flat->Usage << ','
             << Comparation_Flat->District << ','
             << Comparation_Flat->PRN_No << ','
             << Occupation_Date << ','
             << Comparation_Flat->Building_Name << ','
             << Comparation_Flat->Address << ','
             << PASP << ','
             << Comparation_Flat->Ins_Date << ','
             << Comparation_Flat->floor << ','
             << Comparation_Flat->Unit << ','
             << Comparation_Flat->Area << ','
             << Comparation_Flat->Area_N_ft2 << ','
             << Comparation_Flat->Headroom << ','
             << Comparation_Flat->View << ','
             << Comparation_Flat->Price_M << ','
             << Comparation_Flat->Price << ','
             << Comparation_Flat->Price_ft << ','
             << Comparation_Flat->D_Date << ','
             << Comparation_Flat->Nature << ','
             << Comparation_Flat->Bldg_Remarks << ',' << '?'
             << ',' << Comparation_Flat->Price_ft * 10.752688172 << ',' << ','
             << Residental_Price_Index[Comparation_Flat->PASP.tm_year + 1900][Comparation_Flat->PASP.tm_mon + 1][Comparation_Flat->Catergotory] << ','                                                                                                                             // Time Index
             << "= Z" + std::to_string(Reference_Row) + " / Z" + std::to_string(Current_Row) + " - 1" << ',' << ',' << ','                                                                                                                                                         // Time Percentage
             << "= " + std::to_string(Reference_Flat->Occupation_Date.tm_year - Comparation_Flat->Occupation_Date.tm_year) + " * " + std::to_string(Factor.Age) << ','                                                                                                             // Age Percentage                                                                                                                                        // Age Percentage
             << "= (M" + std::to_string(Reference_Row) + "- M" + std::to_string(Current_Row) + ") *" + std::to_string(Factor.Area) << ','                                                                                                                                          // Area Percentage
             << "" << ','                                                                                                                                                                                                                                                          // Location Percentage
             << "= (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ") * " + std::to_string(Factor.Headroom) << ','                                                                                                                                     // Headroom Percentage
             << "= (K" << std::to_string(Reference_Row) + "- K" + std::to_string(Current_Row) + ") * " + std::to_string(Factor.Floor) << ','                                                                                                                                       // Floor Percentage
             << std::to_string(Factor.View[Reference_Flat->View] / Factor.View[Comparation_Flat->View] - 1) << ',' << ','                                                                                                                                                          // View Percentage
             << "= AA" + std::to_string(Current_Row) + "+" + "AD" + std::to_string(Current_Row) + '+' + "AE" + std::to_string(Current_Row) + "+" + "AF" + std::to_string(Current_Row) + "+" + "AG" + std::to_string(Current_Row) + "+" + "AH" + std::to_string(Current_Row) << ',' // Percentage Sum
             << "= X" + std::to_string(Current_Row) + " * " + "(AK" + std::to_string(Current_Row) + "+ 1)" << ','                                                                                                                                                                  // Adj Unit Rate
             << "= (AL" + std::to_string(Reference_Row) + "- AL" + std::to_string(Current_Row) + ") / AL" + std::to_string(Current_Row) << ','                                                                                                                                     // Total Diff Percentage
             << "= AM" + std::to_string(Current_Row) + "/ (O" + std::to_string(Reference_Row) + "- O" + std::to_string(Current_Row) + ")";                                                                                                                                         // Diff Percentage
        File << std::endl;
        Current_Row++;
        Reference_Flat++;
        Comparation_Flat++;
    }
    File.close();
}
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
#include "Trade_Record_Format.h"
#include "Data_Input.h"

struct Get_Cofficiency
{
    void Floor()
    {

        std::cout << "Please Enter Floor Cofficiency:";
        std::cin >> Factor.Floor;
        Factor.Floor /= 100;
    }

    void Size()
    {
        std::cout << "Please Enter Size Cofficiency: ";
        std::cin >> Factor.Area;
        Factor.Area /= 100;
    }

    void Headroom()
    {
        std::cout << "Please Enter Headroom Cofficiency: ";
        std::cin >> Factor.Headroom;
        Factor.Headroom /= 100;
    }

    void Age()
    {
        std::cout << "Please Enter Age Cofficiency: ";
        std::cin >> Factor.Age;
        Factor.Age /= 100;
    }

    void View()
    {
        for (auto it : Type_of_View)
        {
            std::cout << "Please Enter the Cofficiency for " << it << ": ";
            double Cofficiency = 0;
            std::cin >> Cofficiency;
            Factor.View[it] = Cofficiency;
        }
    }

    void Location()
    {
        for (auto it : Type_of_Location)
        {
            std::cout << "Please Enter the Cofficiency for " << it << ": ";
            double Cofficiency = 0;
            std::cin >> Cofficiency;
            Factor.Location[it] = Cofficiency;
        }
    }
} Get_Cofficiency;
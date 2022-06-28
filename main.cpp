#include <iostream>
#include "Test.h"
#include "Trade_Record_Format.h"
#include "Data_Input.h"
#include "User_Input.h"
#include "Algorithm.h"
#include "File_Generator.h"

// Time, Size, Floor, View, Headroom, Age, Location

int main()
{   
    Input_Trade_Record();
    Input_Residental_Price_Index();
    Find_Type_of_Location();
    Find_Type_of_View();

    Get_Cofficiency.Floor();
    Get_Cofficiency.Size();
    Get_Cofficiency.Headroom();
    Get_Cofficiency.Age();
    Get_Cofficiency.View();
    Get_Cofficiency.Location();


    Find_Cofficiency_Size();
    Generate_Size_File();

    Find_Cofficiency_Floor();
    Generate_Floor_File();

    Find_Cofficiency_View();
    Generate_View_File();

    Find_Cofficiency_Headroom();
    Generate_Headroom_File();

    Find_Cofficiency_Age();
    Generate_Age_File();

    Find_Cofficiency_Location();
    Generate_Location_File();

    #ifdef Final_Version

    Input_Trade_Record();
    Input_Residental_Price_Index();
    Find_Type_of_Location();
    Find_Type_of_View();

    Get_Cofficiency.Floor();
    Get_Cofficiency.Size();
    Get_Cofficiency.Headroom();
    Get_Cofficiency.Age();
    Get_Cofficiency.View();
    Get_Cofficiency.Location();

    



    #endif



    return 0;
}
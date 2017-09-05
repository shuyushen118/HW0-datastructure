//
//  main.cpp
//  HW0
//
//  Created by Shen Shuyu on 9/1/17.
//  Copyright © 2017 Shen Shuyu. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
//subtraction and addition function
string addition(string, string);
string subtraction(string, string);


int main(int argc, const char * argv[]) {
    
    //read from a file and store value into a string vector
    vector<string> input;
    string inputNumber;
    //string to store the result;
    string result;
    //read file from argument 1
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);
    while (!inputFile.eof())
    {
        for (int count = 0; count < 3; count ++)
        {
            //read one number
            inputFile >> inputNumber;
            //store into vector
            input.push_back(inputNumber);
        }
            //first number
            string numStr1 = input.at(0);
            //second number
            string numStr2 = input.at(1);
            //after read in
            cout << "reads in " << endl;
            cout << input.at(0) << endl;
            cout << input.at(1) << endl;
            cout << input.at(2) << endl;
        cout << " end of read in " << endl;
            //decide operation
            if(input.at(2) == "+")
            {
                result = addition(numStr1,numStr2);
            }
            else if(input.at(2) == "-")
            {
                result = subtraction(numStr1, numStr2);
            }
            else
            {
                cout << "invalid operators in the inputfile" << endl;
            }
            cout <<" the difference is" << endl;
            cout << result << endl;
            cout << "the right result:" << endl;
            cout << 1000 - 99999 << endl;
        
        //write result to file
        outputFile << " the result is: " << endl;
        outputFile << result <<endl;
        //clear the vector
        input.erase(input.begin(),input.begin()+3);
        cout << " after erease" << endl;

        }
    //store input in a vector
//    while (inputFile >> inputNumber)
//    {
//        input.push_back(inputNumber);
//        
//    }
//    cout << input.at(0) << endl;
//    cout << input.at(1) << endl;
//    cout << input.at(2) << endl;
//    
//    //store number into strings
//    string numStr1 = input.at(0);
//    string numStr2 = input.at(1);
//    
//    //decide to add or subtract
//    if(input.at(2) == "+")
//    {
//        result = addition(numStr1,numStr2);
//    }
//    else if(input.at(2) == "-")
//    {
//        result = subtraction(numStr1, numStr2);
//    }
//    else
//    {
//        cout << "invalid operators in the inputfile" << endl;
//    }
//    
//    
//    cout <<" the difference is" << endl;
//    cout << result << endl;
//    cout << "the right result:" << endl;
//    cout << 1000 - 99999 << endl;
//    
//    //writes outputs to the file
////    ofstream outputFile(argv[2]);
//    outputFile << result;
//
    
    //close file
    outputFile.close();
    inputFile.close();
    
    return 0;
}


string addition (string str1, string str2)
{
    string result;
    bool change_sign = false;
    //check for addends magnitude
    //-+
    if(str1.at(0) == '-' && str2.at(0) != '-')
    {
        //erase - sign
        str1.erase(0,1);
        //if str2 has + sign erase it
        if (str2.at(0) == '+')
        {
            str2.erase(0,1);
        }
        result = subtraction (str2,str1);
    }
    //+-
    else if (str2.at(0) =='-' && str1.at(0) != '-')
    {
        str2.erase(0,1);
        //if str1 has positive sign erase it
        if (str1.at(0) == '+')
        {
            str1.erase(0,1);
        }
        result = subtraction (str1,str2);
    }
    else
    {
        //check for both addends have negative sign
        if (str1.at(0) == '-' && str2.at(0) == '-')
        {
            str2.erase(0,1);
            str1.erase(0,1);
            change_sign = true;
        }
        //if both number are positive and have possitve sign, erease signs
        if (str2.at(0) == '+')
        {
            str2.erase(0,1);
        }
        if (str1.at(0) == '+')
        {
            str1.erase(0,1);
        }

        //compare which string is longer
        string longStr;
        string shortStr;
        if (str1.length() > str2.length())
        {
            longStr = str1;
            shortStr = str2;

        }
        else if (str2.length() > str1.length())
        {
            longStr = str2;
            shortStr = str1;
//        cout << longStr << endl;
//        cout << shortStr << endl;
        }
        else
        {
            longStr = str1;
            shortStr = str2;
        }
        //initiliaize string sum
        result = '0' +  longStr;
//        cout << "setting result" << endl;
//        cout << result<< endl;
    
        //use reverse iterator go through the string from the back
        string::reverse_iterator short_itr;
        string::reverse_iterator result_itr;
    
        //set two iterators point to the end
        short_itr = shortStr.rbegin();
        result_itr = result.rbegin();
    
        //addition
        while (short_itr != shortStr.rend())
        {
            *result_itr += *short_itr - '0';//transfer from ascii value to reguler numberic value
            //if the sum is greater than 9 carry on to the next "digit
            if (*result_itr > '9')
            {
                *(result_itr + 1) += 1;
                *result_itr -= 10;
            }
        ++short_itr;
        ++result_itr;
        }
        //making sure two digit carry over happen
        while (result_itr != result.rend())
        {
            if (*result_itr > '9')
            {
                *(result_itr + 1) += 1;
                *result_itr -= 10;
            }
            ++result_itr;
        }
        while (result.at(0) == '0')
        {
            result.erase(0,1);
//            cout << "check resutl " << endl;
//            cout << result<< endl;
        }
        //update results with magnitude if needed
        if(change_sign)
        {
            result = '-' + result;
        }
     
    }
    return result;
}
//*****************************************subtraction**************************************
//subtraction function
string subtraction(string str1, string str2)
{
    //string to store result
        string result;
       bool specialCase = false;
    //check for magnitutde
    //+-
    if (str1.at(0) != '-' && str2.at(0) =='-'  )
    {
       
        str2.erase(0,1);
        if(str1.at(0) == '+')
        {
            str1.erase(0,1);
        }
        cout << str2 << endl;
        cout << str1 << endl;
        result = addition (str1,str2);
    }
    //-+
    else if (str1.at(0) =='-' && str2.at(0) !='-')
    {
        str1.erase(0,1);
        if(str2.at(0) == '+')
        {
            str2.erase(0,1);
        }
        cout << str2 << endl;
        cout << str1 << endl;
        result = '-' + addition (str1,str2);
    }
    //--
    else if ( str1.at(0) =='-' && str2.at(0) =='-')
    {
        str2.erase(0,1);
        str1.erase(0,1);
        result = subtraction (str2,str1);
    }
    else{
         //if both number are positive and have possitve sign, erease signs
        if (str2.at(0) == '+')
        {
            str2.erase(0,1);
        }
        if (str1.at(0) == '+')
        {
            str1.erase(0,1);
        }
        //compare two numbers
        string bigNum;
        string smallNum;
        if (str1 == str2)
        {
            result = '0';
            specialCase = true;
        }
        //compare strength
        if (str1.length() > str2.length())
        {
            bigNum = str1;
            smallNum = str2;
        }
        else if (str2.length() > str1.length())
        {
            bigNum = str2;
            smallNum = str1;
        }
        //compare digits
        else
        {
            //two iterators go through the list and compare "digits"
            string::iterator itr1 = str1.begin();
            string::iterator itr2 = str2.begin();
            while(itr1 != str1.end())
            {
                if(*itr1 > *itr2)
                {
                    bigNum = str1;
                    smallNum =str2;
                    break;
                }
                else if (*itr2 > *itr1)
                {
                    bigNum = str2;
                    smallNum = str1;
                    break;
                }
                ++itr1;
                ++itr2;
            }
    }
    cout << " comparsion result" << endl;
    cout << "big number is " << endl;
    cout << bigNum << endl;
    cout << "small number is" << endl;
    cout << smallNum << endl;
    
    
        //instantiate a string for result
        result = '0' + bigNum;
        string::reverse_iterator smallNum_itr;
        string::reverse_iterator result_itr;
        string::reverse_iterator temp;
    
        //set iterators at the end of the strings
        smallNum_itr = smallNum.rbegin();
        result_itr = result.rbegin();
    
        //doing subtraction
        while (smallNum_itr != smallNum.rend())
        {

        if( *result_itr >= *smallNum_itr)
        {
            *result_itr -= *smallNum_itr - '0';
//            cout << "result iterators"<< endl;
//            cout << *result_itr << endl;
            
        }
        else
        {
            if (*result_itr == '0')
            {
                temp = result_itr + 1;
//                cout << *temp << endl;
                while (*temp == '0')
                {
                    *temp = '9';
                    ++temp;
                }
                //update the non zero digit
                *temp -= 1;
                *result_itr +=10;
                *result_itr -= *smallNum_itr-'0';
//                cout << *result_itr <<endl;
            }
            else
            {
                *(result_itr + 1) -= 1;
                *result_itr += 10;
                *result_itr -= *smallNum_itr-'0';
            }
            
        }
        ++smallNum_itr;
        ++result_itr;
//        cout << "check result in the while loop" << endl;
//        cout << result << endl;
        }
//    cout << "check result" << endl;
//    cout << result << endl;
        while (result.at(0) == '0' && !specialCase)
        {
            result.erase(0,1);
    
        }
    
        if (bigNum == str2)
        {
            result = '-' +result;
        }
    }
    
    return result;
}








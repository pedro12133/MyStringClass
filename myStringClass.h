//
//  myStringClass.h
//  Final
//
//  Created by Pedro Beltran on 12/5/17.
//  Copyright © 2017 Pedro Beltran. All rights reserved.
//

#ifndef myStringClass_h
#define myStringClass_h
#include <iostream>
using namespace std;

class myStringClass
{
    //Overload the stream insertion and extraction operators
    friend ostream& operator<< (ostream&, const myStringClass*);
    friend ostream& operator<< (ostream&, const myStringClass&);
    friend istream& operator>> (istream&, myStringClass&);
public:
    //default constructor
    myStringClass()
    {userInput = nullptr; userInputLength = 0;}
    
    //overloaded constructors
    myStringClass(const char* str);
    
    //copy constructor
    myStringClass(const myStringClass& str);
    
    //destructor
    ~myStringClass()
    {delete [] userInput;}
    
    //getter
    int stringLength() const
    {return userInputLength;}
    
    //overload =
    myStringClass& operator=(const myStringClass&);
    
    //overload []
    char& operator[](int index)
    {return userInput[index];}
    
    //overload + the concatenation operator
    myStringClass& operator+(const myStringClass&);
    
    //the following all return a bool//
    //overload ==
    bool operator==(const myStringClass&);
    
    //overload !=
    bool operator!=(const myStringClass&);
    
    //overload <=
    bool operator<=(const myStringClass&);
    
    //overload <
    bool operator<(const myStringClass&);
    
    //overload >=
    bool operator>=(const myStringClass&);
    
    //overload >
    bool operator>(const myStringClass&);
    
    //overload +=
    myStringClass operator+=(myStringClass& right);
    
    //friend myStringClass& operator+=(myStringClass& left, const myStringClass& right);
    static void validateUserInput(myStringClass& myStringClassObject);
    static void validateUserInt(myStringClass& myStringClassObject);
    
private:
    char* userInput;   //Array to hold input
    int userInputLength;
};

//*******************************************
// Overloaded constructor                   *
//*******************************************
myStringClass::myStringClass(const char* str)
{
    //store values and allocate memory
    userInputLength = strlen(str);
    userInput = new char[userInputLength];
    int count = 0; //used to count loops
    
    //if str is not empty, copy elements into char *userInput
    while(count < userInputLength)
    {
        userInput[count] = str[count];
        count++;
    }
}

//*******************************************
// Copy constructor                         *
//*******************************************
myStringClass::myStringClass(const myStringClass& str)
{
    //copy size and allocate new memory
    userInputLength = str.stringLength();
    userInput = new char[userInputLength];
    
    //copy elements
    for(int i = 0; userInputLength > i; i++)
        userInput[i] = str.userInput[i];
}

//*******************************************
// Overloaded = operator                    *
//*******************************************
myStringClass& myStringClass::operator=(const myStringClass &rhs)
{
    //if userInput != NULL
    if(userInput)
        delete [] userInput;
    
    //store size and allocate memory
    userInputLength = rhs.stringLength();
    userInput = new char[userInputLength];
    
    //copy elements
    for(int i = 0; userInputLength > i; i++)
        userInput[i] = rhs.userInput[i];
    
    return *this;
}

//*******************************************
// Overloaded + operator                    *
//*******************************************
myStringClass& myStringClass::operator+(const myStringClass &rhs)
{
    int oldSize = userInputLength;
    myStringClass temp;
    int count = 0;
    int count2 = 0;
    
    
    //store new size and allocate new memory
    userInputLength = oldSize + rhs.stringLength();
    temp.userInput = new char[userInputLength];
    
    //copy old elements
    for(int i = 0; oldSize > i; i++)
        temp[i] = userInput[i];
    
    //delete old memory and store new size
    delete [] userInput;
    userInput = new char[userInputLength];
    
    //recopy old characters
    while(oldSize > count)
    {
        userInput[count] = temp.userInput[count];
        count++;
    }
    
    //append new chars
    while(userInputLength > count)
    {
        userInput[count] = rhs.userInput[count2];
        count++; count2++;
    }
    
    return *this;
}

//*******************************************
// Overloaded << operator                   *
//*******************************************
ostream& operator<< (ostream &ostrm, const myStringClass& str)
{
    for(int i = 0; str.stringLength() > i; i++)
    {
        ostrm << str.userInput[i];
    }
    return ostrm;
}

//*******************************************
// Overloaded >> operator                   *
//*******************************************
istream &operator >> (istream &istrm, myStringClass& str)
{
    char aChar = '\0'; //current char being inspected
    char *ptr1 = nullptr; //pointer used to copy to another
    char *ptr2 = nullptr; // ointer used to copy to another
    int count = 0; //counts the character in a user's input
    
    //user has been prompted
    cin.get(aChar);// retrive first character
    
    //while the character is is not the <ENTER> key
    while (aChar != 10)
    {
        count++;
        
        //if count is odd
        if(count%2 != 0)
        {
            //allocated memory equal to count
            ptr1 = new char[count];
            
            //copy from ptr2 if count > 2
            if( count > 2)
                strncpy( ptr1, ptr2, count);
            
            ptr1[count -1] = aChar; //append current char
            delete [] ptr2;  //delete ptr2's allocated memeory for reallocation
        }
        //if count is even
        else
        {
            ptr2 = new char [count]; // allocated memory equal to count
            strncpy( ptr2, ptr1, count); // copy from ptr1
            ptr2[count - 1] = aChar; //append current char
            delete [] ptr1; // delete ptr1's allocated memeory for reallocation
        }
        cin.get(aChar); //retrieve next char
    }
    
    str.userInput = new char[count]; //allocate memory
    str.userInputLength = count; //store length
    count = 0; //reset count
    
    // if count is odd
    if(str.userInputLength%2 != 0)
    {
        //copy characters from ptr1
        while(str.userInputLength > count)
        {
            str.userInput[count] =  ptr1[count];
            count++;
        }
        str.userInput[count] = '\0';
        delete [] ptr1;
        return istrm;
    }
    else
    {
        //copy characters from ptr2
        while(str.userInputLength > count)
        {
            str.userInput[count] =  ptr2[count];
            count++;
        }
        str.userInput[count] = '\0';
        delete [] ptr2;
        return istrm;
    }
}

//*******************************************
// Overloaded ==                            *
//*******************************************
bool myStringClass::operator==(const myStringClass &rhs)
{
    int count = 0; //counts loops
    
    //first check size
    if(userInputLength != rhs.stringLength())
        return false;
    
    //second check individual chars
    //while length > count
    while(userInputLength > count)
    {
        if(userInput[count] != rhs.userInput[count])
            return false;
        count++;
    }
    
    //if loop is completed, the strings match
    return true;
    
}

//*******************************************
// Overloaded !=                            *
//*******************************************
 bool myStringClass::operator!=(const myStringClass &rhs)
{
    int count = 0; //counts loops
    
    //first check size
    if(userInputLength != rhs.stringLength())
        return true;
    
    //second check individual chars
    //while length > count
    while(userInputLength > count)
    {
        if(userInput[count] != rhs.userInput[count])
            return true;
        count++;
    }
    
    //if loop is completed, the strings match
    return false;
}

//*******************************************
// Overloaded <                             *
//*******************************************
bool myStringClass::operator<(const myStringClass &rhs)
{
    int count = 0; //counts loops
    int shortestLen = userInputLength; //shortest length between strings
    bool leftIsLonger = false; //flagged if the length of the left is longer
    
    //if left is longer
    if(userInputLength > rhs.stringLength())
    {
        //change shorestLen
        shortestLen = rhs.stringLength();
        leftIsLonger = true;
    }
    
    //while count does not equal or exceed shortestLen
    while(shortestLen > count)
    {
        //if left char < right char, return true
        if(userInput[count] < rhs.userInput[count])
            return true;
        //if left char > right char, return false
        if(userInput[count] > rhs.userInput[count])
            return false;
        count++;
    }
    
    //if length of left is longer or the lengths are equal
    if(leftIsLonger || userInputLength == rhs.stringLength())
        return false;
    //else, left < right
    else
        return true;
}

//*******************************************
// Overloaded <=                            *
//*******************************************
bool myStringClass::operator<=(const myStringClass &rhs)
{
    int count = 0; //counts loops
    int shortestLen = userInputLength; //shortest length between strings
    bool leftIsLonger = false; //flagged if the length of the left is longer
    
    //if left is longer
    if(userInputLength > rhs.stringLength())
    {
        //change shorestLen
        shortestLen = rhs.stringLength();
        leftIsLonger = true;
    }
   
    //while count does not equal or exceed shortestLen
    while(shortestLen > count)
    {
        //if left char < right char, return true
        if(userInput[count] < rhs.userInput[count])
            return true;
        //if left char > right char, return false
        if(userInput[count] > rhs.userInput[count])
            return false;
        count++;
    }
    
    //if length of left is longer left
    if(leftIsLonger)
        return false;
    //else, left <= right
    else
        return true;
}

//*******************************************
// Overloaded >                             *
//*******************************************
bool myStringClass::operator>(const myStringClass &rhs)
{
    int count = 0; //counts loops
    int shortestLen = userInputLength; //shortest length between strings
    bool leftIsLonger = false;
    
    //if left is longer
    if(userInputLength > rhs.stringLength())
    {
        //change shorestLen
        shortestLen = rhs.stringLength();
        leftIsLonger = true;
    }
    
    //while count does not equal or exceed shortestLen
    while(shortestLen > count)
    {
        //if left char > right char, return true
        if(userInput[count] > rhs.userInput[count])
            return true;
        //if left char < right char, return false
        if(userInput[count] < rhs.userInput[count])
            return false;
        count++;
    }
    
    //if the left side is longer, left > right
    if(leftIsLonger)
        return true;
    else
        return false;
}

//*******************************************
// Overloaded >=                            *
//*******************************************
bool myStringClass::operator>=(const myStringClass &rhs)
{
    int count = 0; //counts loops
    int shortestLen = userInputLength; //shortest length between strings, left is assumed
    bool leftIsLonger = false;
    
    //if left is longer
    if(userInputLength > rhs.stringLength())
    {
        //change shorestLen
        shortestLen = rhs.stringLength();
        leftIsLonger = true;
    }
    
    //while count does not equal or exceed shortestLen
    while(shortestLen > count)
    {
        //if left char > right char, return true
        if(userInput[count] > rhs.userInput[count])
            return true;
        //if left char < right char, return false
        if(userInput[count] < rhs.userInput[count])
            return false;
        count++;
    }
    
    //if the left side is longer, left > right
    if(leftIsLonger || userInputLength == rhs.stringLength())
        return true;
    else
        return false;
}

//*******************************************
// Function validateUserInt()               *
// This function validates a myStringClass  *
// object for an integer. It only allows    *
// integer charaters that are not 0.        *
//*******************************************
void myStringClass::validateUserInt(myStringClass& myStringClassObject)
{
    int counter = 0; //counts chars in user string
    int length = myStringClassObject.userInputLength; //length of user string
    char currentChar = '\0'; //char being inspected
    
    //while counter < length or user string is not <enter>
    while( counter < length || strcmp(myStringClassObject.userInput, "") == 0 )
    {
        currentChar = myStringClassObject.userInput[counter];
        //If any char is not an int or is 0
        if(!isdigit(currentChar) || strcmp(myStringClassObject.userInput, "0") == 0)
        {
            cout << "Invalid. Try again: ";
            cin >> myStringClassObject;
            
            length = myStringClassObject.userInputLength; //reset length
            counter = 0; //reset counter
        }
        else
        {
            counter++;
        }
    }
}

//*******************************************
// Function validateUserInput()             *
// This function validates a myStringClass  *
// object for a word. It only allows letter *
// characters.                              *
//*******************************************
void myStringClass::validateUserInput(myStringClass& myStringClassObject)
{
    int counter = 0; //counts chars in user string
    int length = myStringClassObject.userInputLength; // length of user string
    char currentChar = '\0'; //char being inspected
    
    //while counter < length or user string is not <enter>
    while( counter < length || strcmp(myStringClassObject.userInput, "") == 0 )
    {
        currentChar = myStringClassObject.userInput[counter];
        
        //if any char is not an alphabetical char or is a space, try again
        if(!isalpha(currentChar) || isspace(currentChar))
        {
            cout << "Invalid. Try again: ";
            cin >> myStringClassObject;
            
            length = myStringClassObject.userInputLength; //reset length
            counter = 0; //reset counter
        }
        else
        {
            counter++;
        }
    }
}
#endif /* myStringClass_h */

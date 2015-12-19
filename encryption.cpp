/***********************************************************
 ** Author: Carlos Carrillo                                *
 ** Date:   10/27/2015                                     *
 ** Description: This is a file filter Class. This class   *
 *  reads an input file, transforms it in some way, and    *
 *  writes the results to an output file. It has a pure    *
 *  virtual function for transforming a character. It also *
 *  a subclass for each of these transformations:          *
 *  1. creates an unchanged copy of the original file      *
 *  2. transforms each character in the file to uppercase  *
 *  3. performs encryption                                 *
 **********************************************************/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//abstract file filter class
class Filter
{
    public:
    
        //default constructor
        Filter(){}
    
        //destructor
        ~Filter(){}
    
        //Pure virtual function.
        virtual char transform(char ch) = 0;
    
        //Method to to perform the actual filtering
        void doFilter(ifstream &in, ofstream &out);
    
};

/**************************************************
 *              Filter::doFilter()                *
 * This function uses the virtual transform       *
 * member function to transform individual        *
 * characters. is called to perform the actual    *
 * filtering.                                     *
 *************************************************/

void Filter::doFilter(ifstream &in, ofstream &out)
{
    char ch;
    char transCh;
    in.get(ch);
    
    while (!in.fail())
    {
        transCh = transform(ch);
        out.put(transCh);
        in.get(ch);
    }
}

/****************************************************
 *        class CopyFile : public Filter            *
 * The subclass overides the virtual transformation *
 * function to create an unchanged copy of the      *
 * original file.                                   *
 ***************************************************/

class CopyFile : public Filter
{
    public:
    
        char transform(char ch)
        {
            return ch;
        }
};

/****************************************************
 *       class Uppercase : public Filter            *
 * The subclass overides the virtual transformation *
 * function to transform each character in the     *
 * file to uppercase.                               *
 ***************************************************/

class Uppercase : public Filter
{
    public:
    
        char transform(char ch)
        {
            ch = toupper(ch);
            return ch;
        }
};

/****************************************************
 *       class Encryption : public Filter           *
 * The subclass overides the virtual transformation *
 * function to perform encryption.                  *
 ***************************************************/

class Encryption : public Filter
{
    private:
    
        int key;
    
    public:
        Encryption(int k){ key = k;}
        ~Encryption(){}
    
        char transform(char ch)
        {
            return ch + (key % 26);
        }

};

/*******************************************************
 *                       main                          *
 * The main calls the necessary functions to perform   *
 * the desired action.                                 *
 ******************************************************/

int main()
{
    ifstream inputFile;
    ofstream copyFile, upperCase, encryption;
    int encryptKey;
    int choice;
    
    do
    {
        do
        {
            //main menu
            cout<<"\n**PLEASE SELECT ONE OF THESE OPTIONS**\n"<<endl;
            cout<< "Enter 1 to create an UNCHANGED copy of the input file."<<endl;
            cout<< "Enter 2 to transform each character of the input file into UPPERCASE."<<endl;
            cout<< "Enter 3 to perform ENCRYPTION of the input file." <<endl;
            cout<< "Enter 4 to EXIT the program." <<endl;
            
            //Prompt the user to enter an option from the menu
            cout << "\nPlease enter your option: ";
            cin>>choice; //take the input value
            cout <<endl;
            
            if(choice == 1) //create an unchanged copy of the original file
            {
                cout << "**WELCOME TO THE COPY METHOD!**\n"<<endl;
                
                //open the text file with the data to be transformed
                inputFile.open("input.txt", ios::in);
                
                //verifies if the file can be opened
                if(inputFile.fail())
                  {
                    cout << "\nInput file cannot be opened!!\n";
                  }
                
                //opens the file to write the unchanged data
                copyFile.open("copyFileSample.txt", ios::out);
                
                //verifies if the file can be opened
                if(copyFile.fail())
                  {
                    cout << "\nEncrypted file cannot be opened!!\n";
                  }
                
                //create object to call the main function
                CopyFile myCopyFile;
                myCopyFile.doFilter(inputFile, copyFile);
                cout << "THE OUTPUT FILE IS NOW AN UNCHANGED COPY OF THE INPUT FILE" <<endl;
                cout << "(PLEASE OPEN YOUR OUTPUT FILE TO SEE THI COPY)\n"<<endl;
                
                //close both the input and output files
                inputFile.close();
                copyFile.close();
                
            }
            
            else if(choice == 2) //transforms each character in the file to uppercase
            {
                cout << "**WELCOME TO THE UPPERCASE METHOD!**\n"<<endl;
                
                //open the text file with the data to be transformed
                inputFile.open("input.txt", ios::in);
                
                //verifies if the file can be opened
                if(inputFile.fail())
                  {
                    cout << "\nInput file cannot be opened!!\n";
                  }
                
                //opens the file to write the data in uppercase
                upperCase.open("upperCaseSample.txt", ios::out);
                
                //verifies if the file can be opened
                if(upperCase.fail())
                  {
                    cout << "\nEncrypted file cannot be opened!!\n";
                  }
                
                //create object to call the main function
                Uppercase myUppercase;
                myUppercase.doFilter(inputFile, upperCase);
                cout << "**ALL THE INPUT CHARACTERS ARE NOW IN UPPERCASE**" <<endl;
                cout << "(PLEASE OPEN YOUR OUTPUT FILE TO SEE THE CHANGES)\n"<<endl;
                
                //close both the input and output files
                inputFile.close();
                upperCase.close();
            }
            
            else if(choice == 3)//performs encryption
            {
                cout << "**WELCOME TO THE ENCRYPTION METHOD!**"<<endl;
                
                //open the text file with the data to be transformed
                inputFile.open("input.txt", ios::in);
                
                //verifies if the file can be opened
                if(inputFile.fail())
                  {
                    cout << "\nInput file cannot be opened!!\n";
                  }
                
                //opens the file to write the encrypted data
                encryption.open("encryptionSample.txt", ios::out);
                
                //verifies if the file can be opened
                if(encryption.fail())
                  {
                    cout << "\nEncrypted file cannot be opened!!\n";
                  }
                
                //prompt the user for the encryption key
                cout << "\nEnter the encryption value: ";
                cin >> encryptKey;
                cout << "\n"<<endl;
                
                //pass the encryption key as an argument and
                //create the object to call the main function
                Encryption myEncryption(encryptKey);
                myEncryption.doFilter(inputFile, encryption);
                cout << "**THE INPUT FILE HAS BEEN TRANSFORMED/ENCRYPTED**" <<endl;
                cout << "(PLEASE OPEN YOUR OUTPUT FILE TO SEE THE CHANGES)\n"<<endl;
                
                //close both the input and output files
                inputFile.close();
                encryption.close();
            }
            
            else if(choice == 4)//EXIT the program
            {
                return 0;
            }
            
            else if (!isdigit(choice)) //input validation
            {
                cout << "Invalid option entered. Try again!\n" << endl;
                return 0;
            }
            
        }while(choice != 1 && choice != 2 && choice != 3 && choice != 4);
        
        char door = ' ';
        do
        {
            cout << "Enter any key to continue... ";
            cin >> door;
            cout << endl;
            
        }while(door == ' ');
        
    }while(choice);
    
    return 0;
}








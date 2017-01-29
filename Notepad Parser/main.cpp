// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main ()
{
    ofstream myfile1 ("output.txt");
    if (myfile1.is_open())
    {
        //myfile1 << "Hello this is a line\n";
        cout << "File opened\n";
    }
    else
        cout << "Unable to open file";

    string outputLine;
    string line;
    ifstream myfile ("Data.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            for (int i = 0; i < line.size(); i++)
            {
                char letter = line[i];
                string word;
                if (letter == 't')
                {
                    //cout << "Found a t in... ";
                    word = word + line[i];
                    word = word + line[i + 1];
                    word = word + line[i + 2];
                    word = word + line[i + 3];

                    string date;
                    if (!word.compare("tip="))
                    {
                        int x = 5;
                        char nextLetter = line[i + x];
                        //int commaCount = 0;
                        while (nextLetter != ',')
                        {
                            date = date + nextLetter;
                            x = x + 1;
                            nextLetter = line[i + x];
                        }
                        x = x + 2;
                        date = date + ' ';
                        nextLetter = line[i + x];
                        while (nextLetter != ',')
                        {
                            date = date + nextLetter;
                            x = x + 1;
                            nextLetter = line[i + x];
                        }
                        outputLine = date;
                        outputLine = outputLine + ',';

                        x = i + x + 2;
                        //Print POR vs ... next 10 characters
                        outputLine = outputLine + line[x];
                        outputLine = outputLine + line[x + 1];
                        outputLine = outputLine + line[x + 2];
                        outputLine = outputLine + line[x + 3];
                        outputLine = outputLine + line[x + 4];
                        outputLine = outputLine + line[x + 5];
                        outputLine = outputLine + line[x + 6];
                        outputLine = outputLine + line[x + 7];
                        outputLine = outputLine + line[x + 8];
                        outputLine = outputLine + line[x + 9];
                        outputLine = outputLine + ',';

                        //find Made or Missed
                        x = x + 10; //next letter is a '<'
                        x = x + 1; //next letter is 'b'
                        x = x + 1; //next letter is 'r'
                        x = x + 1; //next letter is '>'
                        x = x + 1; //don't care. proceed past >
                        nextLetter = line[x];
                        //cout << nextLetter << "\n";
                        while (nextLetter != '>')
                        {
                            x = x+1;
                            nextLetter = line[x];
                        }
                        x = x + 1;
                        string madeormiss;
                        madeormiss = madeormiss + line[x];
                        madeormiss = madeormiss + line[x + 1];
                        madeormiss = madeormiss + line[x + 2];
                        madeormiss = madeormiss + line[x + 3];
                        int j = x + 4;
                        if (!madeormiss.compare("Miss"))
                        {
                            madeormiss = madeormiss + line[x+4];
                            madeormiss = madeormiss + line[x+5];
                            j = x + 6;
                        }

                        outputLine = outputLine + madeormiss;
                        outputLine = outputLine + ',';
                        j = j + 1;
                        outputLine = outputLine + line[j] + ',';
                        j = j + 15;

                        //get distance
                        nextLetter = line[j];
                        while (nextLetter != ' ')
                        {
                            outputLine = outputLine + line[j];
                            j = j+1;
                            nextLetter = line[j];
                        }
                        outputLine = outputLine + ',';

                        //cout << line[j];
                        //cout << line[j + 1] << "\n";



                        //return 0;


                        //cout << outputLine << "\n";


                        //write to file
                        myfile1 << outputLine << "\n";
                        break;

                    }

                }
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    myfile1.close();
    return 0;
}

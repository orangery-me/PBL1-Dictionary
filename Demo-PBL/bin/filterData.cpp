#include <iostream>
#include <fstream>
#include <sstream>
#define MAX_LEN 200
using namespace std;

int main(){
    ifstream inFile;
    inFile.open("data.txt");
    ofstream outFile;
    outFile.open("output.txt");

    istringstream iss;

    if (inFile.is_open()){
        string line, word;    
        while (!inFile.eof()){ // eof: end of file

            getline(inFile, line);

            if (line[0]=='@'){
                line.erase(line.begin());
                iss.clear(); // clear out the state
                iss.str(line);

                iss>>word;
                cout<<word<<";";  
            }

            if (line[0]=='*'){
                line.erase(line.begin());
                iss.clear();
                iss.str(line);

                string words;
                while (iss.good()){
                    iss>>word;
                    if (word[word.length()-1]==','){
                        word.erase(word.end()-1);
                        words+= (word+" ");
                        break;
                    }
                    else 
                        words+= (word+" ");

                }
                words.erase(words.end()-1);
                cout<<words<<";";
            }

            if (line[0]=='-'){
                line.erase(line.begin());
                iss.clear();
                iss.str(line);

                string words;
                while (iss.good()){
                    iss>>word;
                    if (word[word.length()-1]==','){
                        word.erase(word.end()-1);
                        words+= (word+" ");
                        break;
                    }
                    else{
                        if (word[0]=='('){
                            while (word[word.length()-1]!=')')
                            iss>>word;
                        }
                        else
                        words+= (word+" ");
                    }                        
                }
                words.erase(words.end()-1);
                cout<<words<<endl;
            }
        } 
    }
}
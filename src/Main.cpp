#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "LibrarySystem.h"
using namespace std;

ofstream output;

int main(int argc, char *argv[]) {

    ifstream commandFile(argv[1]);
    output.open(argv[2]);
    LibrarySystem library;

    vector<string> tokens;
    int addMovie = 0, deleteMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0, returnMovie = 0;//to identify the sections
    if(!commandFile.fail()) {
        string line;
        while(getline(commandFile, line)){
            if(line != "\n"){
                istringstream iss(line);
                string token;
                while(getline(iss, token, '\t')){
                    tokens.push_back(token);
                }

                if(tokens.at(0) == "addMovie"){
                    if(addMovie == 0){
                        output << endl;
                        output << "===addMovie() method test===" << endl;
                    }
                    addMovie++;
                    deleteMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0, returnMovie = 0;
                    int movieID = stoi(tokens.at(1));
                    int year = stoi(tokens.at(3));
                    library.addMovie(movieID, tokens.at(2), year);
                }

                if(tokens.at(0) == "deleteMovie"){
                    if(deleteMovie == 0){
                        output << endl;
                        output << "===deleteMovie() method test===" << endl;
                    }
                    deleteMovie++;
                    addMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0, returnMovie = 0;
                    int movieID = stoi(tokens.at(1));
                    library.deleteMovie(movieID);
                }

                if(tokens.at(0) == "addUser"){
                    if(addUser == 0){
                        output << endl;
                        output << "===addUser() method test===" << endl;
                    }
                    addUser++;
                    addMovie = 0, deleteMovie = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0, returnMovie = 0;
                    int userID = stoi(tokens.at(1));
                    library.addUser(userID,tokens.at(2));
                }

                if(tokens.at(0) == "deleteUser"){
                    if(deleteUser == 0){
                        output << endl;
                        output << "===deleteUser() method test===" << endl;
                    }
                    deleteUser++;
                    addMovie = 0, deleteMovie = 0, addUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0, returnMovie = 0;
                    int userID = stoi(tokens.at(1));
                    library.deleteUser(userID);
                }

                if(tokens.at(0) == "checkoutMovie"){
                    if(checkoutMovie == 0){
                        output << endl;
                        output << "===checkoutMovie() method test===" << endl;
                    }
                    checkoutMovie++;
                    addMovie = 0, deleteMovie = 0, addUser = 0, deleteUser = 0, showMovie = 0, showUser =0, returnMovie = 0;
                    int movieID = stoi(tokens.at(1));
                    int userID = stoi(tokens.at(2));
                    library.checkoutMovie(movieID, userID);
                }

                if(tokens.at(0) == "returnMovie"){
                    if(returnMovie == 0){
                        output << endl;
                        output << "===returnMovie() method test===" << endl;
                    }
                    returnMovie++;
                    addMovie = 0, deleteMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, showUser =0;
                    int movieID = stoi(tokens.at(1));
                    library.returnMovie(movieID);
                }

                if(tokens.at(0) == "showUser"){
                    if(showUser == 0){
                        output << endl;
                        output << "===showUser() method test===" << endl;
                    }
                    showUser++;
                    addMovie = 0, deleteMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showMovie = 0, returnMovie = 0;
                    int userID = stoi(tokens.at(1));
                    library.showUser(userID);
                }

                if(tokens.at(0) == "showMovie"){
                    if(showMovie == 0){
                        output << endl;
                        output << "===showMovie() method test===" << endl;
                    }
                    showMovie++;
                    addMovie = 0, deleteMovie = 0, addUser = 0, deleteUser = 0, checkoutMovie = 0, showUser =0, returnMovie = 0;
                    int movieID = stoi(tokens.at(1));
                    library.showMovie(movieID);
                }

                if(tokens.at(0) == "showAllMovie"){
                    output << endl;
                    output << "===showAllMovie() method test===" << endl;
                    output << "Movie id - Movie name - Year - Status" << endl;
                    library.showAllMovies();
                }
            }
            tokens.clear();
        }
    }

    return 0;
}

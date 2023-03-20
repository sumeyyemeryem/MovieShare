#include <string>
using namespace std;

class LibrarySystem {

public:
    LibrarySystem();
    ~LibrarySystem();

    void addMovie(const int movieID, const string movieTitle, const int year);
    void deleteMovie(const int movieID);

    void addUser(const int userID, const string userName);
    void deleteUser(const int userID);

    void checkoutMovie(const int movieID, const int userID);
    void returnMovie(const int movieID);

    void showAllMovies();
    void showMovie(const int movieID);
    void showUser(const int userID);


};



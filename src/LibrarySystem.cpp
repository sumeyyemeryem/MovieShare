#include "LibrarySystem.h"
#include "iostream"
#include <fstream>
using namespace std;
extern ofstream output;

LibrarySystem::LibrarySystem() {
    output << "===Movie Library System===" << endl;
}

LibrarySystem::~LibrarySystem() {
    cout << "destructor has been called" << endl;
}

struct Movie{
    int id;
    string title;
    int year;

    Movie* next;
};

struct User{
    int id;
    string userName;

    //checkout list data of the user
    Movie* first;
    Movie* last;

    User* next;
    User* prev;
};
Movie* head1 = NULL;//empty movie list

User* head2 = NULL; //empty list of users

void LibrarySystem::addMovie(const int movieID, const string movieTitle, const int year) {

    Movie* temp = new Movie();
    temp->id = movieID;
    temp->title = movieTitle;
    temp->year = year;
    temp->next = head1;

    if(head1 == NULL){
        temp->next = temp;
        head1 = temp;
        output << "Movie " << movieID << " has been added" << endl;
        return;
    }
    //check if the movie exist
    Movie* last = head1;
    while(last->next != head1){//if break condition never occurs loop will terminate when it reaches last element in the list
        if(last->id == movieID){
            break;
        }
        last = last->next;
    }
    if (last->id == movieID){
        output << "Movie " << movieID << " already exists" << endl;
        return;
    }

    last->next = temp;
    head1 = temp; //insert at front
    output << "Movie " << movieID << " has been added" << endl;

}

void LibrarySystem::deleteMovie(const int movieID) {

    //check the unchecked outs list
    // If linked list is not empty
    if (head1 != NULL){
        // If the list contains only a single node
        if(head1->id==movieID && head1->next==head1)
        {
            free(head1);
            head1=NULL;

            output << "Movie " << movieID << " has not been checked out" << endl;
            output << "Movie " << movieID << " has been deleted" << endl;
            return;
        }

        Movie *last= head1,*d;

        // If head is to be deleted
        if(head1->id==movieID)
        {
            // Find the last node of the list
            while(last->next!=head1)
                last=last->next;

            // Point last node to the next of head
            last->next=head1->next;
            free(head1);
            head1=last->next;
            output << "Movie " << movieID << " has not been checked out" << endl;
            output << "Movie " << movieID << " has been deleted" << endl;
            return;
        }

        // Either the node to be deleted is not found or the end of list is not reached
        while(last->next!=head1 && last->next->id!=movieID)
        {
            last=last->next;
        }

        // If node to be deleted was found
        if(last->next->id==movieID)
        {
            d=last->next;
            last->next=d->next;
            free(d);
            output << "Movie " << movieID << " has not been checked out" << endl;
            output << "Movie " << movieID << " has been deleted" << endl;
            return;
        }
    }

    //check the users check out lists
    User* user = head2;
    if (head2 != NULL) {
        do {
            if(user->first != NULL){
                // If the list contains only a single node
                if(user->first->id==movieID && user->first->next==user->first)
                {
                    free(user->first);
                    user->first=NULL;

                    output << "Movie " << movieID << " has been checked out" << endl;
                    output << "Movie " << movieID << " has been deleted" << endl;
                    return;
                }

                Movie *last= user->first,*d;

                // If head is to be deleted
                if(user->first->id==movieID)
                {
                    // Find the last node of the list
                    while(last->next!=head1)
                        last=last->next;

                    // Point last node to the next of head
                    last->next=user->first->next;
                    free(user->first);
                    user->first=last->next;
                    output << "Movie " << movieID << " has been checked out" << endl;
                    output << "Movie " << movieID << " has been deleted" << endl;
                    return;
                }


                while(last->next!=user->first && last->next->id!=movieID)
                {
                    last=last->next;
                }

                // If node to be deleted was found
                if(last->next->id==movieID)
                {
                    d=last->next;
                    last->next=d->next;
                    free(d);
                    output << "Movie " << movieID << " has been checked out" << endl;
                    output << "Movie " << movieID << " has been deleted" << endl;
                    return;
                }
            }
            user = user->next;
        } while (user != head2);
    }

    output << "Movie " << movieID << " does not exist" << endl;//return conditions never occured


}

void LibrarySystem::addUser(const int userID, const string userName) {

    //check if list is empty, if yes make new node the head of list
    if (head2 == NULL) {
        User* newNode = new User();
        newNode->userName = userName;
        newNode->id = userID;
        newNode->first = NULL; //empty list of movies
        newNode->last = NULL;

        newNode->next = newNode->prev = newNode;//since there is only one element new node points to itself
        head2 = newNode;
        output << "User " << userID << " has been added" << endl;
        return;
    }

    User* last = head2;
    while(last->next != head2){//if break condition never occurs loop will terminate when it reaches last element in the list
        if(last->id == userID){
            break;
        }
        last = last->next;
    }
    if(last->id == userID){
        output << "User " << userID << " already exists" << endl;
        return;
    }


    User* newNode = new User();
    newNode->userName = userName;
    newNode->id = userID;
    newNode->first = NULL; //empty list of movies
    newNode->last = NULL;

    // head is going to be next of new_node
    newNode->next = head2;
    head2->prev = newNode;
    //last preivous of new node
    newNode->prev = last;
    //new node next of old last
    last->next = newNode;
    output << "User " << userID << " has been added" << endl;

}

void LibrarySystem::deleteUser(const int userID) {

    if(head2 != NULL){
        User* temp = head2;
        User* tail = head2->prev;
        // If the list contains only a single node
        if(head2->id == userID && head2->next == head2) {
            free(head2);
            head2 = NULL;
            output << "User " << userID <<" has been deleted" << endl;
            return;
        }

        if(head2->id == userID) {//if the requested user is at the beginning of the list
            tail->next = head2->next;
            free(head2);
            head2 = tail->next;
            head2->prev = tail;
            output << "User " << userID <<" has been deleted" << endl;
            return;
        }

        //else
        while(temp->next != head2){
            if(temp->next->id == userID){//jump out of the loop if you reach the element one before the requested element
                break;
            }
            temp = temp->next;//loop terminates after reaching the last element so if jump out case never occurs at the end temp1 points to the last element
        }
        if(temp->next == head2){//if temp1 reaches the last element it means requested movie doesn't exist
            output <<  "User " << userID << " does not exist" << endl;
            return;
        }

        //delete the user
        User* temp1 = temp->next;
        temp->next = temp1->next;
        temp->prev = temp1->prev;
        free(temp1);
        output << "User " << userID <<" has been deleted" << endl;
    }
    else{
        output <<  "User " << userID << " does not exist" << endl;
    }
}

void LibrarySystem::checkoutMovie(const int movieID, const int userID) {

    Movie* movie = head1;
    User* user = head2;

    while(movie->next != head1){
        if(movie->id == movieID){
            break;
        }
        movie = movie->next;
    }
    if(movie->id != movieID){
        output << "Movie " << movieID << " does not exist for checkout" << endl;
        return;
    }

    while (user->next != head2){
        if (user->id == userID){
            break;
        }
        user = user->next;
    }
    if(user->id != userID){//if the loop reaches to the last node and last nodes id also does not equal to the given user id, this means user does not exit
        output << "User " << userID << " does not exist for checkout" << endl;
        return;
    }

    //if all the conditions are provided add the movie to the users checkout list
    Movie* newMovie = new Movie() ;
    newMovie->id = movie->id;
    newMovie->year = movie->year;
    newMovie->title = movie->title;

    newMovie->next = user->first;

    if (user->first != NULL)
    {
        Movie* temp = user->first;
        while (temp->next != user->first)
            temp = temp->next;
        temp->next = newMovie;
    }
    else
        newMovie->next = newMovie; //For the first node
    user->first = newMovie;

    output << "Movie " << movieID << " has been checked out by User " << userID << endl;


    //delete the movie from unchecked outs list
    if (head1 != NULL){
        // If the list contains only a single node
        if(head1->id==movieID && head1->next==head1)
        {
            free(head1);
            head1=NULL;
            return;
        }

        Movie *last= head1,*d;

        // If head is to be deleted
        if(head1->id==movieID)
        {
            // Find the last node of the list
            while(last->next!=head1)
                last=last->next;

            // Point last node to the next of head i.e.
            // the second node of the list
            last->next=head1->next;
            free(head1);
            head1=last->next;
            return;
        }

        while(last->next!=head1 && last->next->id!=movieID)
        {
            last=last->next;
        }

        // If node to be deleted was found
        if(last->next->id==movieID)
        {
            d=last->next;
            last->next=d->next;
            free(d);
            return;
        }
    }

}

void LibrarySystem::returnMovie(const int movieID) {

    Movie* movie = head1;
    //check the unchecked outs list
    while(movie->next != head1){
        if(movie->id == movieID){
            break;
        }
        movie = movie->next;
    }
    if(movie->id == movieID){
        output << "Movie " << movieID << " has not been checked out" << endl;
        return;
    }

    //check the users check out lists
    User* user = head2;
    if (head2 != NULL) {
        do {
            if(user->first != NULL){
                if(user->first->id==movieID && user->first->next==user->first)
                {
                    //return the movie to the unchecked outs list
                    Movie* temp = new Movie();
                    temp->id = user->first->id;
                    temp->title = user->first->title;
                    temp->year = user->first->year;
                    temp->next = head1;

                    if (head1 != NULL)
                    {
                        Movie* last = head1;
                        while (last->next != head1)
                            last = last->next;
                        last->next = temp;
                    }
                    else
                        temp->next = temp; //For the first node
                    head1 = temp;

                    //delete the movie from users check out list
                    free(user->first);
                    user->first=NULL;

                    output << "Movie " << movieID << " has been returned" << endl;
                    return;
                }

                Movie *last= user->first,*d;

                // If head is to be deleted
                if(user->first->id==movieID)
                {
                    //return the movie to the unchecked outs list
                    Movie* temp = new Movie();
                    temp->id = user->first->id;
                    temp->title = user->first->title;
                    temp->year = user->first->year;
                    temp->next = head1;

                    if (head1 != NULL)
                    {
                        Movie* last1 = head1;
                        while (last1->next != head1)
                            last1 = last1->next;
                        last1->next = temp;
                    }
                    else
                        temp->next = temp; //For the first node
                    head1 = temp;

                    //delete the movie from users check out list
                    while(last->next!=head1)
                        last=last->next;

                    last->next=user->first->next;
                    free(user->first);
                    user->first=last->next;

                    output << "Movie " << movieID << " has been returned" << endl;
                    return;
                }

                // Either the node to be deleted is not found or the end of list is not reached
                while(last->next!=user->first && last->next->id!=movieID)
                {
                    last=last->next;
                }

                // If node to be deleted was found
                if(last->next->id==movieID)
                {
                    //return the movie to the unchecked outs list
                    Movie* temp = new Movie();
                    temp->id = last->next->id;
                    temp->title = last->next->title;
                    temp->year = last->next->year;
                    temp->next = head1;

                    if (head1 != NULL)
                    {
                        Movie* last1 = head1;
                        while (last1->next != head1)
                            last1 = last1->next;
                        last1->next = temp;
                    }
                    else
                        temp->next = temp; //For the first node
                    head1 = temp;

                    d=last->next;
                    last->next=d->next;
                    free(d);

                    output << "Movie " << movieID << " has been returned" << endl;
                    return;
                }
            }
           user = user->next;
        } while (user != head2);
    }

    output << "Movie " << movieID << " not exist in the library" << endl;//return conditions never occured


}

void LibrarySystem::showAllMovies() {

    //unchecked outs list
    if(head1 != NULL){
        Movie* movie = head1;
        do{
            output << movie->id << " " << movie->title << " " << movie->year << " Not checked out" << endl;
            movie = movie->next;
        }while (movie != head1);
    }

    //users check out lists
    if(head2 != NULL){
        User* user = head2;
        Movie* temp;
        do{
            if(user->first != NULL){
                temp = user->first;
                do{
                    output << temp->id << " " << temp->title << " " << temp->year << " Checked out by User " << user->id << endl;
                    temp = temp->next;
                }while (temp != user->first);
            }
            user = user->next;
        }while (user != head2);
    }
}

void LibrarySystem::showMovie(const int movieID) {

    //check the unchecked outs list
    if (head1 != NULL) {
        Movie *movie = head1;
        do {
            if (movie->id == movieID) {
                output << movie->id << " " << movie->title << " " << movie->year << " Not checked out" << endl;
                return;
            }
            movie = movie->next;
        } while (movie != head1);
    }

    //check the users check out list
    if (head2 != NULL) {
        User *user = head2;
        do {
            if(user->first != NULL){
                Movie* temp = user->first;
                do {
                    if(temp->id == movieID){
                        output << temp->id << " " << temp->title << " " << temp->year << " Checked out by User " << user->id << endl;
                        return;
                    }
                    temp = temp->next;
                } while (temp != user->first);
            }
            user = user->next;
        } while (user != head2);
    }

    //return condition never occured
    output << "Movie with the id " << movieID << " does not exist" << endl;
}

void LibrarySystem::showUser(const int userID) {

    User* user = head2;
    do{
        if(user->id == userID){
            output << "User id: " << user->id << " User name: " << user->userName << endl;
            output << "User " << userID << " checked out the following Movies:" << endl;
            if(user->first != NULL){
                Movie* movie = user->first;
                output << "Movie id - Movie name - Year" << endl;
                do{
                    output << movie->id << " " << movie->title << " " << movie->year << endl;
                    movie = movie->next;
                }while (movie != user->first);
            }
        }
        user = user->next;
    }while (user != head2);

}



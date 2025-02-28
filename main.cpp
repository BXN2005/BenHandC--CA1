#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;



struct Movie
{
    string title;
    int year;
    string genre;
    double rating;
    int boxoffice;
};

void display(const Movie &movie)
{
    cout <<left
    <<setw(25)<< movie.title
    <<setw(6) <<movie.year
    <<setw(12)<< movie.genre
    <<setw(8)<<fixed << setprecision(2) <<movie.rating
    <<setw(10)<<movie.boxoffice
    <<endl;

}

void readMovies(const string &filename, vector<Movie> &movies) {
    ifstream fin(filename);

    if (!fin) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    bool isHeader = true;

    while (getline(fin, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string title, genre, yearStr, ratingStr, boxofficeStr;

        getline(ss, title, ',');
        getline(ss, yearStr, ',');
        getline(ss, genre, ',');
        getline(ss, ratingStr, ',');
        getline(ss, boxofficeStr, ',');

        Movie movie;
        movie.title = title;
        movie.year = stoi(yearStr);
        movie.genre = genre;
        movie.rating = stod(ratingStr);
        movie.boxoffice = stoi(boxofficeStr);

        movies.push_back(movie);
    }

    fin.close();
}

void displayMovies(const vector<Movie> &movies) {
    if (movies.empty()) {
        cout << "No movies available to display." << endl;
        return;
    }

    cout << left << setw(25) << "Title"
         << setw(6) << "Year"
         << setw(12) << "Genre"
         << setw(8) << "Rating"
         << setw(10) << "Box Office"
         << endl;
    cout << string(61, '-') << endl;

    for (auto &movie : movies) {
        display(movie);
    }
}

int searchMovieByTitle(const vector<Movie> &movies, const string &searchTitle) {
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].title == searchTitle) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Movie> movies;
    readMovies("movies.txt", movies);
    displayMovies(movies);

    string searchTitle;
    cout << "\nEnter a movie title to search: ";
    getline(cin, searchTitle);

    int index = searchMovieByTitle(movies, searchTitle);

    if (index != -1) {
        cout << "Movie found:\n";
        display(movies[index]);
    } else {
        cout << "Movie not found.\n";
    }

    return 0;
}





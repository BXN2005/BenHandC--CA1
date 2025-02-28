#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
void displayTitle() {
    cout << left << setw(25) << "Title"
         << setw(6) << "Year"
         << setw(12) << "Genre"
         << setw(8) << "Rating"
         << setw(10) << "Box Office"
         << endl;
    cout << string(61, '-') << endl;
}


int searchMovieByTitle(const vector<Movie> &movies, const string &searchTitle) {
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].title == searchTitle) {
            return i;
        }
    }
    return -1;
}

map<string, int> countMoviesByGenre(const vector<Movie> &movies) {
    map<string, int> genreCount;

    for (auto &movie : movies) {
        genreCount[movie.genre]++;
    }

    return genreCount;
}

void displayMoviesByGenre(const vector<Movie> &movies, const string &genre) {
    bool found = false;

    cout << "\nMovies in Genre: " << genre << endl;
    displayTitle();

    for (const auto &movie : movies) {
        if (movie.genre == genre) {
            display(movie);
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found in this genre.\n";
    }
}

int findBoxOfficeResults(const vector<Movie> &movies, Movie &highest, Movie &lowest) {
    if (movies.empty()) {
        cout << "No movies available.\n";
        return 0;
    }

    highest = movies[0];
    lowest = movies[0];
    int totalBoxOffice = 0;


    for (auto &movie : movies) {
        totalBoxOffice += movie.boxoffice;

        if (movie.boxoffice > highest.boxoffice) {
            highest = movie;
        }

        if (movie.boxoffice < lowest.boxoffice) {
            lowest = movie;
        }
    }

    int averageBoxOffice = totalBoxOffice / movies.size();
    return averageBoxOffice;
}

vector<Movie> searchMoviesByTitles(const vector<Movie> &movies, const string &searchTitle) {
    vector<Movie> results;

    for (auto iter = movies.begin(); iter != movies.end(); ++iter) {
        if (iter->title.find(searchTitle) != string::npos) {
            results.push_back(*iter);
        }
    }

    return results;
}

void searchMoviesByText(const vector<Movie> &movies) {
    string searchText;
    cout << "Enter word to search for: ";
    cin >> searchText;

    vector<Movie> foundMovies = searchMoviesByTitles(movies, searchText);

    if (foundMovies.empty()) {
        cout << "No movies found with this word.\n";
    } else {
        cout << "\nMovies containg the word: " << searchText << "\n";
        displayTitle();

        for (auto &movie : foundMovies) {
            display(movie);
        }
    }
}

int main() {
    vector<Movie> movies;
    readMovies("movies.txt", movies);
    displayMovies(movies);

    string searchTitle;
    cout << "\nEnter a movie title to search: \n";
    getline(cin, searchTitle);

    int index = searchMovieByTitle(movies, searchTitle);

    if (index != -1) {
        cout << "Movie found:\n";
        displayTitle();
        display(movies[index]);
    } else {
        cout << "Movie not found.\n";
    }

    map<string, int> genreCounts = countMoviesByGenre(movies);

    cout << "\nMovie Count by Genre:\n";
    cout << string(61, '-') << endl;
    for (auto &pair : genreCounts) {
        cout << left << setw(12) << pair.first << ": " << pair.second << endl;
    }

    string searchGenre;
    cout << "\nEnter a genre to search for: ";
    getline(cin, searchGenre);

    displayMoviesByGenre(movies, searchGenre);

    Movie highestBoxOffice, lowestBoxOffice;
    int avgBoxOffice = findBoxOfficeResults(movies, highestBoxOffice, lowestBoxOffice);

    cout << "\nBox Office Statistics:\n";
    cout << string(61, '-') << endl;
    cout << "Highest Box Office: " << highestBoxOffice.title << " $" << highestBoxOffice.boxoffice << "\n";
    cout << "Lowest Box Office: " << lowestBoxOffice.title << " $" << lowestBoxOffice.boxoffice << "\n";
    cout << "Average Box Office: $" << avgBoxOffice << endl;

    searchMoviesByText(movies);

    return 0;
}





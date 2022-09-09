// SetsTheory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;
using namespace chrono;

void log_timer(steady_clock::time_point t1, steady_clock::time_point t2, string message) {
    // calculate time taken for execution
    duration<double, milli> result = t2 - t1;

    // log the time
    cout << result.count() << message + "\n";
}

set <string> get_set(string file_name)
{
    //start timer for perfomance measurment
    auto t1 = high_resolution_clock::now();

    // open the file
    ifstream file;
    file.open(file_name);
    string word;
    word.clear();

    // create empty Set
    set <string> A;

    // insert words to Set
    while (file >> word)
    {
        A.insert(word);
    }

    if (A.size() == 0)
    {
        cout << "Empty or corrupted txt file \n";
    }

    // stop perfomance measurment
    auto t2 = high_resolution_clock::now();

    // log perfomance in milliseconds
    log_timer(t1, t2, "ms to parse the file -> " + file_name);

    // log the size of the Set
    cout << A.size();
    cout << " is the size of the Set of the file " + file_name + "\n\n";

    // return set
    return A;
}

vector <string> get_vector(string file_name)
{
    //start timer for perfomance measurment
    auto t1 = high_resolution_clock::now();

    // open the file
    ifstream file;
    file.open(file_name);
    string word;
    word.clear();

    // create empty vector
    vector <string> v;

    // insert words to vector
    while (file >> word)
    {
        v.push_back(word);
    }

    // stop perfomance measurment
    auto t2 = high_resolution_clock::now();

    // log perfomance in milliseconds
    log_timer(t1, t2, "ms to parse the file with vector (slow) -> " + file_name);

    // log the size of the Set
    cout << v.size();
    cout << " is the size of the vector of the file (it is not unique) " + file_name + "\n\n";

    return v;
}

// MANUAL INTERSECTION AKA A⋂B WITHOUT USING set_intersection, DO NOT DO THIS
// ASSYMTOMIC TIME IS O(|setA| * |setB|), IT IS SLOW
int findIntersection(vector<string> A, vector<string> B)
{
    vector <string> intersection;

    int sizeA = A.size();

    int sizeB = B.size();

    int big = (sizeA > sizeB) ? sizeA : sizeB;

    int small = (sizeA > sizeB) ? sizeB : sizeA;

    for (int i = 0; i < big;++i)
    {
        for (int j = 0; j < small; ++j)
        {
            if (A[i] == B[j])
            {
                //cout << A[i] + "->" + B[j] + "\n";
                intersection.push_back(A[i]);
            }
        }
    }

    // sort vector and remove duplicates so we can finnaly know |A|
    sort(intersection.begin(), intersection.end());
    intersection.erase(unique(intersection.begin(), intersection.end()), intersection.end());
    return intersection.size();
}

int main()
{
    // small files for testing purpose
    string file_name_A = "test1.txt";
    string file_name_B = "test2.txt";

    // orriginal files, i believe we will need a couple of days to actually find intersections in vectors
    // BUT you can uncomment this and see how fast is Set for both Tolstoy and Dostoevsky
    //string file_name_A = "war_and_peace.txt";
    //string file_name_B = "crime_and_punishment.txt";


    // create sets of words from both books
    set <string> A = get_set(file_name_A);
    set <string> B = get_set(file_name_B);

    set <string> intersect;

    // start intersection perfomance measurment
    auto t1 = high_resolution_clock::now();

    // find A⋂B for sets
    // assymptotic time is O(min(|setA|, |setB|))
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(intersect, intersect.begin()));

    // stop intersection perfomance measurment
    auto t2 = high_resolution_clock::now();

    // log perfomance
    log_timer(t1, t2, "ms to find the intersection");

    cout << "The intersection size is -> ";
    cout << intersect.size() << "\n\n";

    // create lists of words from both books
    vector <string> vectorA = get_vector(file_name_A);
    vector <string> vectorB = get_vector(file_name_B);

    // start manual array intersection measurment
    auto vectorT1 = high_resolution_clock::now();

    // finw intersection with slow method
    int size = findIntersection(vectorA, vectorB);

    // stop manual array intersection measurment
    auto vectorT2 = high_resolution_clock::now();

    // log perfomance
    log_timer(vectorT1, vectorT2, "ms to find the intersection with arrays");

    cout << "The slow array intersection size is -> ";
    cout << size << endl;
}

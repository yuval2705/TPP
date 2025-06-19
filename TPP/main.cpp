#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;


void main()
{
	// EX1:
    cout << endl << "----- EX1 -----" << endl;
    vector<int> v1 = {1, 2, 3, 4, 5, 4, 4, 4, 8, 9, 10, 11};
    copy(v1.cbegin(), v1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "---------------" << endl;

	// EX2:
    cout << endl << "----- EX2 -----" << endl;
    cout << count(v1.begin(), v1.end(), 4) << endl;
    cout << "---------------" << endl;

    // EX3:
    cout << endl << "----- EX3 -----" << endl;
    cout << count_if(v1.begin(), v1.end(), bind(greater<int>{}, placeholders::_1, 4)) << endl;
    cout << "---------------" << endl;


    // EX4:
    cout << endl << "----- EX4 -----" << endl;
    remove_if(v1.begin(), v1.end(), bind(less<int>{}, placeholders::_1, 8));
    copy(v1.cbegin(), v1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "---------------" << endl;


	// EX5:
    cout << endl << "----- EX5 -----" << endl;
    copy(v1.cbegin(), v1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "---------------" << endl;
	
    
    // EX6:
    cout << endl << "----- EX6 -----" << endl;
    vector<int> v6 = {};
    cout << "---------------" << endl;


    // EX7:
    cout << endl << "----- EX7 -----" << endl;
    transform(next(v1.cbegin()), v1.cend(), v1.cbegin(), back_inserter(v6), minus<>{});
    copy(v6.cbegin(), v6.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "---------------" << endl;


    // EX8:
    cout << endl << "----- EX8 -----" << endl;
    copy(v6.cbegin(), v6.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "---------------" << endl;


    // EX9:
    cout << endl << "----- EX9 -----" << endl;
    cout << accumulate(v6.begin(), v6.end(), 0) << endl;
    cout << "---------------" << endl;
}
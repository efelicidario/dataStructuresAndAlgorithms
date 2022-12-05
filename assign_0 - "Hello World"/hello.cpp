// Tyler Felicidario
// CSUSM ID # 200460031
// 2 September 2022
// CS 311
// Dr. Xiaoyu Zhang

// Include header file
// and standard library.
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	// User must enter another command
	// other than './hello'
	if (argc == 1)
	{
		cout << "\nThis program needs a command line argument!\n" << endl;
	}
	else
	{
		// argv[1] grabs the second argument at index 1
		cout << "\nHello " << argv[1] << "! Welcome to CS 311\n" << endl;
	}
	return 0;
}

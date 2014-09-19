#include <iostream>
#include <cstdlib>

#include "timer.h"

using namespace std;

int main()
{
	Timer myTimer;

	cout << "How long does it take to print 1 million numbers?" << endl;
	myTimer.Start();

	for (int i=0; i<1000000; i++)
		cout << i << "  ";
	myTimer.Stop();

	cout << endl << endl;
	cout << "That took " << myTimer.Seconds() << " seconds. " << endl;

  cout << "Press Enter to continue...";
  cin.get();
	return EXIT_SUCCESS;  // comes with cstdlib
}
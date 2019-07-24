/*

Problem description:

Four people come to a river in the night. There is a narrow bridge, but it can only hold two people at a time. 
They have one torch and, because it's night, the torch has to be used when crossing the bridge. 
Person A can cross the bridge in 1 minute, B in 2 minutes, C in 5 minutes, and D in 10 minutes. 
When two people cross the bridge together, they must move at the slower person's pace.

This program calculates the fastest time they can cross the bridge.
*/

#include <iostream>
#include <unistd.h>
#include <ctime>
#include "yaml-cpp/yaml.h"


using namespace std;

void sortArray(int count, int *arraytime);
int method1(int count, int *arraytime);
int method2(int count, int *arraytime);


int main (int argc, char **argv)
{
	int numOfPerson;
	int totalTime1, totalTime2;

	YAML::Node testfile = YAML::LoadFile("userdata.yaml");

	if (testfile["timeused"])
	{
		cout << "found yaml file correct node " << endl;		
		std::vector<int> arrayTimeInMinute = node["timeused"].as<std::vector<int>>();	
		numOfPerson = testfile["timeused"].size()
		
	}
	else
	{
		cout << "can't found correct node in userdata.yaml" << endl;	
		return -1;
	}
	

	cout<<"Total " << numOfPerson << " people need cross bridge " << endl;

	// sort the time from fast to slow
	sortArray(numOfPerson, arrayTimeInMinute);

	if(numOfPerson == 1)
		totalTime1 = arrayTimeInMinute[0];

	else if(numOfPerson == 2)
		totalTime1 = arrayTimeInMinute[1];

	else
	{

		totalTime1 = method1(numOfPerson, arrayTimeInMinute);
		totalTime2 = method2(numOfPerson, arrayTimeInMinute);
		if (totalTime2 < totalTime1)
			totalTime1 = totalTime2;
		
	}
	

	cout<<"The shortest time for all people cross the bridge is " << totalTime1 << " minutes " << endl;
	return 0;
	
}


void sortArray(int count, int *arraytime)
{
   int temp;

	for(int i = 0; i < (count-1); i++)
		for( int j = i+1; j < count; j++)
		{
			if(arraytime[i] > arraytime[j])
			{
				temp = arraytime[i];
				arraytime[i] = arraytime[j];
				arraytime[j] = temp;
			}
		}
}


/* AB>, A<, CD>, B<, AB>  ;even number of people

AB>, A<, DE>, B< , AC>, A<, AB> odd number 
*/
int method1(int count, int *arraytime)
{
	int totaltime = 0;
	int i;
	if(count%2 == 0) //even number case
	{
		for( i = 3; i < count; i+2); 
			totaltime += arraytime[i];
		totaltime += arraytime[1]*(count-1);
		totaltime += arraytime[0]*(count/2-1);
	}
	else  //odd number case
	{
		for( i = 2; i < count; i+2); 
			totaltime += arraytime[i];
		totaltime += arraytime[1]*(count-2);
		totaltime += arraytime[0]*(count-1)/2;		
	}
	return 	totaltime;
}

/* AB>, A<, AC>, A<, AE> , A<
this method benefit when time(B) is much larger than time(A)
*/
int method2(int count, int *arraytime)
{
	int totaltime = 0;
	int i;	
	
	for( i = 1; i < count; i++); 
			totaltime += arraytime[i];
		totaltime += arraytime[0]*(count-2);		
		
	return 	totaltime;
}
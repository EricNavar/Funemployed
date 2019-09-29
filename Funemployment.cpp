#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <conio.h>
#include <chrono>
using namespace std;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

vector<string> jobs(40);
vector<string> traits(200);

vector<string> getInput(string file)
{
	vector<string> result;
	ifstream infile(file);
	if (!infile.is_open())
		cout << "could not open " << file << endl;
	string token;
	while (getline(infile, token))
		result.push_back(token);
	infile.close();
	return result;
}

int main()
{
	//initialize
	vector<string> jobs = getInput("Jobs.txt");
	vector<string> traits = getInput("Traits.txt");
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	auto rng = default_random_engine(seed);
	shuffle(begin(jobs), end(jobs), rng);
	shuffle(begin(traits), end(traits), rng);
	unsigned int jobsIndex = 0;
	unsigned int traitsIndex = 0;
	unsigned int jobsSize = jobs.size();
	unsigned int traitsSize = traits.size();
	//game loop
	bool game = true;
	int c;
	//there should only be 4 traits per person
	int traitCount = 0;
	system("cls");
	cout << "Job: " << jobs[jobsIndex++] << endl;
	while (game)
	{
		c = 0;
		switch ((c = _getch())) {
		case KEY_LEFT:
			traitCount = 0;
			system("cls");
			cout << "Job: " << jobs[++jobsIndex] << endl;
			jobsIndex = jobsIndex % jobsSize;
			break;
		case KEY_RIGHT:
			if (traitCount == 4)
			{
				traitCount = 0;
				system("cls");
				cout << "Job: " << jobs[jobsIndex] << endl;
			}
			cout << traits[traitsIndex++] << endl;
			traitsIndex = traitsIndex % traitsSize;
			traitCount++;
			break;
		case KEY_ESC:
			game = false;
			break;
		}
	}

	return 0;
}
#include"classes.h"
#include"functions.h"

int main() {
	char line[200];
	char* webpage, * link;
	clock_t begin, end;
	double time = 0;
	begin = clock();
	ifstream file;
	for (int i = 0; i < n; i++) hashtable[i] = new website();
	for (int i = 0; i < n; i++) hash2[i] = new keyword();
	file.open("websites.txt");
	comparisons++;
	if (!file.is_open()) {
		cout << "Websites file not found! try again\n";
	}
	else {
		while (!file.eof()) {			//got all the input from the first file
			file.getline(line, 200);
			webpage = strtok(line, ",");
			//for (int i = 0; i < strlen(webpage); i++) cout << webpage[i];	//this is correct
			checkhash(webpage);
			//link = webpage;
			while (true) {
				link = strtok(NULL, ",");
				comparisons++;
				if (link == NULL) break;
				addinlink(webpage, link);
				addoutlink(webpage, link);
			}
		}
		file.close();

		char* web2, * key, line2[200];		//getting all the input from the second file
		file.open("keywords.txt");
		comparisons++;
		if (!file.is_open()) {
			cout << "Keywords file not found! try again\n";
		}
		else {
			while (!file.eof()) {
				file.getline(line2, 200);
				web2 = strtok(line2, ",");
				checkhash(web2);
				while (true) {
					key = strtok(NULL, ",");
					comparisons++;
					if (key == NULL) break;
					checkword(web2, key);	//implement this
					addkey(web2, key);
					//addkeyword(web2, keyword);	//I do not think that this function is necessary
				}
			}
			file.close();
		}

		
		bool exitcode = false;
		int choice;
		char first[100], keys[100];
		end = clock();
		time += (double)(end - begin) / CLOCKS_PER_SEC;
		while (!exitcode) {
			cout << "Do you want to: \n(1) Update file\n(2) Search\n(3) Display all stored data\n(4) Exit\nNote: exiting will result in immediate deletion of all stored data\n";
			cin >> choice;
			switch (choice) {
			case 1:
				begin = clock();
				update();
				end = clock();
				time += (double)(end - begin) / CLOCKS_PER_SEC;
				cout << "Information updated!\n";
				break;
			case 2:
				begin = clock();
				pagerank();
				end = clock();
				time += (double)(end - begin) / CLOCKS_PER_SEC;
				cout << "Input the search query\n";
				cin >> first;
				begin = clock();
				cin.getline(keys, 100);
				strcat(first, keys);
				cout << "\nSearching\n";
				separatekeys(first);
				end = clock();
				time += (double)(end - begin) / CLOCKS_PER_SEC;
				break;
			case 3:
				begin = clock();
				testdata();
				end = clock();
				time += (double)(end - begin) / CLOCKS_PER_SEC;
				break;
			case 4:
				exitcode = 1;
				break;
			default:
				cout << "Invalid input! Try again...\n";
			}
		}
		cout << "The run time is " << time << " seconds\n";
		cout << "The number of comparisons is " << comparisons << endl;
		cout << "Thank you for using my search engine -AA\n";
	}

	return 0;
}

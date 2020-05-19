#pragma once

int comparisons, totalwebs;
const int n = 10;
const double damping = 0.85;
website* hashtable[n];
keyword* hash2[n];

void testdata() {
	website* cur;
	keyword* cur2;
	for (int i = 0; i < n; i++) {
		comparisons++;
		if (hashtable[i]->name != "none") {
			cout << "Website " << i << endl << hashtable[i]->name << endl << "Inlinks:  " << hashtable[i]->inlinks.size() << endl;
			for (int j = 0; j < hashtable[i]->inlinks.size(); j++) cout << hashtable[i]->inlinks[j] << "\n";
			cout << "Outlinks:   " << hashtable[i]->outlinks.size() << endl;
			for (int j = 0; j < hashtable[i]->outlinks.size(); j++) cout << hashtable[i]->outlinks[j] << "\n";
			cout << "Impressions " << hashtable[i]->impressions << endl << "Clicks: " << hashtable[i]->clicks << endl;
			cur = hashtable[i]->collisions;
			while (cur->name != "none") {
				cout << "Collision: \n";
				cout << cur->name << "\n";
				cout << "Inlinks:" << cur->inlinks.size() << endl;
				for (int k = 0; k < cur->inlinks.size(); k++) cout << cur->inlinks[k] << "\n";
				cout << "Outlinks:" << cur->outlinks.size() << endl;
				for (int k = 0; k < cur->outlinks.size(); k++) cout << cur->outlinks[k] << "\n";
				cout << "Impressions: " << cur->impressions << endl << "Clicks: " << cur->clicks << endl;
				cur = cur->collisions;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		comparisons++;
		if (hash2[i]->word != "none") {
			cout << "Keyword " << i << endl;
			cur2 = hash2[i];
			cout << cur2->word << endl;
			cout << "Websites:\n";
			for (int j = 0; j < cur2->websites.size(); j++) cout << cur2->websites[j] << "\n";
			cur2 = hash2[i]->collisions;
			while (cur2->word != "none") {
				cout << "Collision\n";
				cout << cur2->word << "\n";
				cout << "its websites\n";
				for (int j = 0; j < cur2->websites.size(); j++) cout << cur2->websites[j] << "\n";
				cur2 = cur2->collisions;
			}
		}
	}
}

int hashcode(char* name) {
	int sum = 0;

	for (int i = 0; i < strlen(name); i++) {
		comparisons++;
		if (name[i] != ' ') {
			sum += (int)name[i];
		}
	}

	return sum % n;
}

void checkhash(char* name) {		//checks if the website is stored, if not stores it in the right spot
	int index = hashcode(name);
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == "none") {
		cursor->name = name;
		totalwebs++;
		cursor->collisions = new website();
	}
	else {
		comparisons++;
		if (cursor->name == name) {
			return;
		}
		else {
			while (cursor->collisions->name != "none") {
				cursor = cursor->collisions;
				comparisons++;
				if (cursor->name == name)
					return;
				comparisons++;
				if (cursor == NULL) {
					cout << "Error in checkhash function! Find bug\n";
					exit(1);
				}
			}
			cursor = cursor->collisions;
			cursor->name = name;
			totalwebs++;
			cursor->collisions = new website();
			return;
		}
	}
}

void addinlink(char* webpage, char* link) {		//goes to the link and adds webpage to the inlinks of it
	comparisons++;
	if (webpage != link) {
		checkhash(link);
		int index = hashcode(link);
		website* cursor;
		cursor = hashtable[index];
		comparisons++;
		if (cursor->name == link) {
			cursor->inlinks.push_back(webpage);
		}
		else {
			while (cursor->name != link) {
				cursor = cursor->collisions;
				comparisons++;
				if (cursor == NULL) {
					cout << "Error in addinlink/hash functions! Find bug!\n";
					exit(1);
				}
			}

			for (int i = 0; i < cursor->inlinks.size(); i++) {
				comparisons++;
				if (cursor->inlinks[i] == webpage) return;
			}

			cursor->inlinks.push_back(webpage);
		}
	}
}

void addoutlink(char* webpage, char* link) {	//goes to webpage and adds link to the outlinks
	comparisons++;
	if (webpage != link) {
		checkhash(link);
		int index = hashcode(webpage);
		website* cursor;
		cursor = hashtable[index];
		comparisons++;
		if (cursor->name == webpage) {
			cursor->outlinks.push_back(link);
		}
		else {
			while (cursor->name != webpage) {
				cursor = cursor->collisions;
				comparisons++;
				if (cursor == NULL) {
					cout << "Error in addoutlink/hash functions! Find bug!\n";
					exit(1);
				}
			}

			for (int i = 0; i < cursor->outlinks.size(); i++) {
				comparisons++;
				if (cursor->outlinks[i] == link) return;
			}

			cursor->outlinks.push_back(link);
		}
	}
}

void addkey(char* webpage, char* key) {
	int index = hashcode(webpage);
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == webpage) {
		for (int i = 0; i < cursor->keywords.size(); i++) {
			comparisons++;
			if (cursor->keywords[i] == key) {
				return;
			}
		}
		cursor->keywords.push_back(key);
	}
	else {
		while (cursor->collisions->name != webpage) {
			cursor = cursor->collisions;
			comparisons++;
			if (cursor == NULL) {
				cout << "Error in addkey function! Check bug\n";
				exit(1);
			}
		}
		cursor = cursor->collisions;
		for (int i = 0; i < cursor->keywords.size(); i++) {
			comparisons++;
			if (cursor->keywords[i] == key) return;
		}
		cursor->keywords.push_back(key);
	}
}

void checkword(char* website, char* key) { //checks if the word is hashed, if not it adds it
	int index = hashcode(key);
	keyword* cursor = hash2[index];
	comparisons++;
	if (cursor->word == "none") {
		cursor->word = key;
		cursor->websites.push_back(website);
		cursor->collisions = new keyword;
	}
	else {
		comparisons++;
		if (cursor->word == key) {
			for (int i = 0; i < cursor->websites.size(); i++) {
				comparisons++;
				if (cursor->websites[i] == website) return;
			}
			cursor->websites.push_back(website);
		}
		else {
			while (cursor->collisions->word != "none") {
				cursor = cursor->collisions;
				comparisons++;
				if (cursor->word == key) {
					for (int i = 0; i < cursor->websites.size(); i++) {
						comparisons++;
						if (cursor->websites[i] == website) return;
					}
					cursor->websites.push_back(website);
					return;
				}
			}
			cursor = cursor->collisions;
			cursor->word = key;
			cursor->websites.push_back(website);
			cursor->collisions = new keyword();
		}
	}
}

void deleteincoming(char* webpage, char* link) {		//goes to outgoing of the link and delete the webpage from it
	int index = hashcode(link);
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == link) {
		for (int i = 0; i < cursor->outlinks.size(); i++) {
			comparisons++;
			if (cursor->outlinks[i] == webpage) {
				cursor->outlinks.erase(cursor->outlinks.begin() + i);
				break;
			}
		}
	}
	else {
		while (cursor->name != link) {
			cursor = cursor->collisions;
			comparisons++;
			if (cursor == NULL) {
				cout << "Error in delete incoming function\n";
				exit(1);
			}
		}
		for (int i = 0; i < cursor->outlinks.size(); i++) {
			comparisons++;
			if (cursor->outlinks[i] == webpage) {
				cursor->outlinks.erase(cursor->outlinks.begin() + i);
				break;
			}
		}
	}
}

void deleteoutgoing(char* webpage, char* link) {		//goes to the incoming of the link and delete the website from it
	int index = hashcode(link);
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == link) {
		for (int i = 0; i < cursor->inlinks.size(); i++) {
			comparisons++;
			if (cursor->inlinks[i] == webpage) {
				cursor->inlinks.erase(cursor->inlinks.begin() + i);
				break;
			}
		}
	}
	else {
		while (cursor->name != link) {
			cursor = cursor->collisions;
			comparisons++;
			if (cursor == NULL) {
				cout << "Error in delete outgoing function\n";
				exit(1);
			}
		}
		for (int i = 0; i < cursor->inlinks.size(); i++) {
			comparisons++;
			if (cursor->inlinks[i] == webpage) {
				cursor->inlinks.erase(cursor->inlinks.begin() + i);
				break;
			}
		}
	}
}

void deletekeyword(char* webpage, char* key) {
	int index = hashcode(key);
	keyword* cursor = hash2[index];
	keyword* cursor2 = cursor;
	comparisons++;
	if (cursor->word == key) {
		for (int i = 0; i < cursor->websites.size(); i++) {
			comparisons++;
			if (cursor->websites[i] == webpage) {
				cursor->websites.erase(cursor->websites.begin() + i);
				break;
			}
		}
	}
	else {
		while (cursor->word != key) {
			cursor2 = cursor;
			cursor = cursor->collisions;
			comparisons++;
			if (cursor == NULL) {
				cout << "Error in delete keyword function\n";
				exit(1);
			}
		}

		for (int i = 0; i < cursor->websites.size(); i++) {
			comparisons++;
			if (cursor->websites[i] == webpage) {
				cursor->websites.erase(cursor->websites.begin() + i);
				break;
			}
		}
	}
}

void deletewebsite(char* webpage) {
	int index = hashcode(webpage);
	char* auxchar;
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == webpage) {
		for (int i = 0; i < cursor->inlinks.size(); i++) {		//deleting all the incoming links
			auxchar = &cursor->inlinks[i][0];
			deleteincoming(webpage, auxchar);
		}
		for (int i = 0; i < cursor->outlinks.size(); i++) {
			auxchar = &cursor->outlinks[i][0];
			deleteoutgoing(webpage, auxchar);
		}
		for (int i = 0; i < cursor->keywords.size(); i++) {
			auxchar = &cursor->keywords[i][0];
			deletekeyword(webpage, auxchar);
		}
		hashtable[index] = hashtable[index]->collisions;
		totalwebs--;
		delete cursor;		//calls destructor
	}
	else {
		website* cursor2 = NULL;
		while (cursor->name != webpage) {
			cursor2 = cursor;		//basically it is the one before it
			cursor = cursor->collisions;
			comparisons++;
			if (cursor == NULL) {
				cout << "Website you want to delete does not exist!\n";
				return;
			}
		}
		for (int i = 0; i < cursor->inlinks.size(); i++) {		//deleting all the incoming links
			auxchar = &cursor->inlinks[i][0];
			deleteincoming(webpage, auxchar);
		}
		for (int i = 0; i < cursor->outlinks.size(); i++) {
			auxchar = &cursor->outlinks[i][0];
			deleteoutgoing(webpage, auxchar);
		}
		for (int i = 0; i < cursor->keywords.size(); i++) {
			auxchar = &cursor->keywords[i][0];
			deletekeyword(webpage, auxchar);
		}
		cursor2->collisions = cursor->collisions;
		totalwebs--;
		delete cursor;		//calls destructor which deals with everything
	}
}

void updatewebsite(char* webpage, int impress, int cls, char* newlinks) {
	int index = hashcode(webpage);
	website* cursor = hashtable[index];
	char* extra;
	comparisons++;
	if (cursor->name == webpage) {
		cursor->impressions = impress;
		cursor->clicks = cls;
		extra = strtok(newlinks, " ");
		while (true) {
			comparisons++;
			if (extra == NULL) break;
			comparisons++;
			if (*extra == 'A') {
				extra = strtok(NULL, " ");
				addinlink(webpage, extra);
				addoutlink(webpage, extra);
			}
			else {		//then it has to be R
				comparisons++;
				if (*extra == 'R') {
					extra = strtok(NULL, " ");
					deleteoutgoing(webpage, extra);		//go to the incoming of the extra and delete webpage from it
					deleteincoming(extra, webpage);		//go to the outgoing of the webpage and delete extra from it
				}
				else {
					cout << "error in update website\n";
				}
			}
			extra = strtok(NULL, " ");
		}
	}
}

void update() {
	ifstream file;
	char* code, * webpage, line[200];

	file.open("update.txt");
	comparisons++;
	if (!file.is_open()) {
		cout << "File not found!\n";
	}
	else {
		cout << "Updating\n";
		while (!file.eof()) {
			file.getline(line, 200);
			code = strtok(line, ",");
			comparisons++;
			if (*code == 'A') {
				webpage = strtok(NULL, ",");
				comparisons++;
				if (webpage == NULL) {
					cout << "error here\n";
					exit(1);
				}
				checkhash(webpage);
			}
			else {
				comparisons++;
				if (*code == 'R') {
					webpage = strtok(NULL, ",");
					deletewebsite(webpage);
				}	
				else {	//update
					comparisons++;
					if (*code == 'U') {
						webpage = strtok(NULL, ",");
						char* web = webpage;
						int impressions = atoi(strtok(NULL, ","));
						int clicks = atoi(strtok(NULL, ","));
						char* links = strtok(NULL, ",");
						cout << endl;
						updatewebsite(web, impressions, clicks, links);
					}
					else {
						cout << "Error in update function! Find bug\n";
						exit(1);
					}
				}
			}
		}

	}
}

int getoutlinks(string webpage) {
	char* aux = &webpage[0];
	int index = hashcode(aux);
	website* cursor = hashtable[index];
	comparisons++;
	if (cursor->name == webpage) {
		return cursor->outlinks.size();
	}
	else {
		while (cursor->name != webpage) {
			cursor = cursor->collisions;
			comparisons++;
			if (cursor->name == "none") {
				cout << "Error in getoutlinks function! Find bug\n";
				exit(1);
			}
		}
		return cursor->outlinks.size();
	}
}

void search(vector<char*> keys, bool quotations) {
	int index;
	keyword* cursor;
	vector<string> webpages;
	double rank;
	if (!quotations) {
		for (int i = 0; i < keys.size(); i++) {		//fetching all relevant websites
			index = hashcode(keys[i]);
			cursor = hash2[index];
			comparisons++;
			if (cursor->word == keys[i]) {
				for (int i = 0; i < cursor->websites.size(); i++) {
					webpages.push_back(cursor->websites[i]);
				}
			}
			else {
				while (cursor->word != keys[i]) {
					cursor = cursor->collisions;
					comparisons++;
					if (cursor == NULL) {
						cout << "Incorrect keyword! find bug\n";
						return;
					}
				}
				for (int i = 0; i < cursor->websites.size(); i++) {
					webpages.push_back(cursor->websites[i]);
				}
			}
		}
	}
	else {		//need to fetch all the common websites
		int ext, ext2;
		for (int i = 0; i < keys.size(); i++) {		//fetching all the websites in the keywords
			index = hashcode(keys[i]);
			cursor = hash2[index];
			char* aux;
			aux = strtok(keys[i], " ");
			comparisons++;
			if (cursor->word == aux) {
				for (int i = 0; i < cursor->websites.size(); i++) {
					webpages.push_back(cursor->websites[i]);
				}
			}
			else {
				while (cursor->word != aux) {
					cursor = cursor->collisions;
					comparisons++;
					if (cursor == NULL) {
						cout << "Incorrect keyword! find bug\n";
						return;
					}
				}
				for (int i = 0; i < cursor->websites.size(); i++) {
					webpages.push_back(cursor->websites[i]);
				}
			}
		}
		//now i need to remove the incorrect websites
		int h;
		bool found = false;
		bool both = false;
		for (int i = 0; i < webpages.size(); i++) {
			for (int j = 0; j < keys.size(); j++) {
				found = false;
				char* aux = strtok(keys[j], " ");
				h = hashcode(keys[j]);
				keyword* c = hash2[h];
				if (c->word == aux) {
					for (int k = 0; k < c->websites.size(); k++) {
						comparisons++;
						if (c->websites[k] == webpages[i]) {
							found = true;
							break;
						}
					}
				}
				else {
					while (c->word != aux) {
						c = c->collisions;
						comparisons++;
						if (c == NULL) {
							cout << "Error in search function2! Find bug\n";
							exit(1);
						}
					}
					for (int k = 0; k < c->websites.size(); k++) {
						comparisons++;
						if (c->websites[k] == webpages[i]) {
							found = true;
							break;
						}
					}
				}
				comparisons++;
				if (!found) {
					webpages.erase(webpages.begin() + i);
					break;
				}
			}
			
		}
	}

	int extra;
	char* aux1;
	website* cur;
	vector<string> results;
	vector<double> ranks;
	bool inserted = false;

	for (int i = 0; i < webpages.size(); i++) {
		inserted = false;
		aux1 = &webpages[i][0];
		extra = hashcode(aux1);
		cur = hashtable[extra];
		if (cur->name == webpages[i]) {
			if (results.size() == 0) {
				results.push_back(webpages[i]);
				ranks.push_back(cur->pscore);
			}
			else {
				for (int j = 0; j < results.size(); j++) {
					if (cur->pscore > ranks[i]) {
						ranks.insert(ranks.begin() + i, cur->pscore);
						results.insert(results.begin() + i, webpages[i]);
						inserted = true;
						break;
					}
				}
				if (!inserted) {
					ranks.push_back(cur->pscore);
					results.push_back(webpages[i]);
				}
			}
		}
		else {
			while (cur->name != webpages[i]) {
				cur = cur->collisions;
				if (cur == NULL) {
					cout << "Error in search function\n";
					exit(1);
				}
			}

			comparisons++;
			if (results.size() == 0) {
				results.push_back(webpages[i]);
				ranks.push_back(cur->pscore);

			}
			else {
				for (int j = 0; j < results.size(); j++) {
					comparisons++;
					if (cur->pscore > ranks[i]) {
						ranks.insert(ranks.begin() + i, cur->pscore);
						results.insert(results.begin() + i, webpages[i]);
						inserted = true;
						break;
					}
				}
				comparisons++;
				if (!inserted) {
					ranks.push_back(cur->pscore);
					results.push_back(webpages[i]);
				}
			}
		}
	}

	string temp;
	double temp1;

	for (int i = 0; i < results.size(); i++) {
		for (int j = 0; j < results.size() - i - 1; j++) {
			if (ranks[j+1] > ranks[j]) {
				temp1 = ranks[j];
				temp = results[j];
				ranks[j] = ranks[j + 1];
				results[j] = results[j + 1];
				ranks[j + 1] = temp1;
				results[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < results.size(); i++) {
		cout << "Website " << i + 1 << ": " << results[i] << endl;
	}
}

void pagerank() {
	website* cur, * cur2;
	int extra, extra2;
	double ext, cons;
	char* aux;
	for (int i = 0; i < n; i++) {
		if (hashtable[i]->name != "none") {
			cur = hashtable[i];
			cur->p_rank = 1.0 / totalwebs;
			cur = hashtable[i]->collisions;
			while (cur->name != "none") {
				cur->p_rank = 1.0 / totalwebs;
				cur = cur->collisions;
			}
		}
	}

	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < n; i++) {
			if (hashtable[i]->name != "none") {
				cur = hashtable[i];
				for (int j = 0; j < cur->inlinks.size(); j++) {
					//use the prank formula
					aux = &cur->inlinks[j][0];
					extra2 = hashcode(aux);
					cur2 = hashtable[extra2];
					if (cur2->name == aux) {
						cur->p_rank += cur2->p_rank/cur2->outlinks.size();
					}
					else {
						while (cur2->name != aux) {
							cur2 = cur2->collisions;
							if (cur2 == NULL) {
								cout << "Error in pagerank function! Find bug\n";
								exit(1);
							}
						}
						cur->p_rank += cur2->p_rank/cur2->outlinks.size();
					}
					cons = (0.1 * cur->impressions) / (1 + 0.1 * cur->impressions);
					cur->p_rank = cur->p_rank * damping + (1 - damping);
					if (cur->impressions == 0) {
						cur->pscore = cur->p_rank;
					}
					else {
						cur->pscore = (0.4 * cur->p_rank) + (0.6 * (((1 - cons) * cur->p_rank) + ((cons) * (cur->clicks / cur->impressions))));
					}
				}
				cur = hashtable[i]->collisions;
				while (cur->name != "none") {
					for (int j = 0; j < cur->inlinks.size(); j++) {
						//use the prank formula
						aux = &cur->inlinks[j][0];
						extra2 = hashcode(aux);
						cur2 = hashtable[extra2];
						if (cur2->name == aux) {
							cur->p_rank += cur2->p_rank/cur2->outlinks.size();
						}
						else {
							while (cur2->name != aux) {
								cur2 = cur2->collisions;
								if (cur2 == NULL) {
									cout << "Error in pagerank function! Find bug\n";
									exit(1);
								}
							}
							cur->p_rank += cur2->p_rank/cur2->outlinks.size();
						}

						cons = (0.1 * cur->impressions) / (1 + 0.1 * cur->impressions);
						cur->p_rank = cur->p_rank * damping + (1 - damping);
						if (cur->impressions == 0) {
							cur->pscore = cur->p_rank;
						}
						else {
							cur->pscore = (0.4 * cur->p_rank) + (0.6 * (((1 - cons) * cur->p_rank) + ((cons) * (cur->clicks / cur->impressions))));
						}
					}
					cur = cur->collisions;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (hashtable[i]->name != "none") {
			cur = hashtable[i];
			if (cur->outlinks.size() == 0) {		//distributing the sink values
				for (int l = 0; l < n; l++) {
					if (hashtable[l]->name != "none") {
						cur2 = hashtable[l];
						cur2->p_rank += (cur->p_rank / (totalwebs - 1));
						cur2 = cur2->collisions;
						while (cur2->name != "none") {
							cur2->p_rank += (cur->p_rank / (totalwebs - 1));
							cur2 = cur2->collisions;
						}
					}
				}
			}
		}
	}
}

void separatekeys(char* keys) {
	vector<char*> separatedkeys;
	bool quotations = false;
	char* aux;
	aux = strtok(keys, " ");
	comparisons++;
	if (aux[0] == '"') {
		quotations = true;
		aux[0] = ' ';
		separatedkeys.push_back(aux);
	}
	else {
		separatedkeys.push_back(aux);
	}
	while (true) {
		aux = strtok(NULL, " ");
		comparisons++;
		if (aux == NULL) break;
		comparisons++;
		if (aux[strlen(aux) - 1] == '"')
			aux[strlen(aux) - 1] = ' ';
		separatedkeys.push_back(aux);
	}
	search(separatedkeys, quotations);
}

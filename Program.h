/*
 * mainProgram.h
 *
 *  Created on: 20 May 2020
 *      Author: johnathanliao
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_


class Program{
public:
	void run();
	//getting input from user
	void execute(int);
	//executing function base on user's input
private:
	IdeasBank bank;
};

void Program::run(){
	int input=1;
	cout<<"Welcome to the ideas bank!"<<endl;
	while(input!=8){
		cout<<endl<<"Menu:"<<endl;
		cout<<"1. Import idea from file"<<endl;
		cout<<"2. Input an idea"<<endl;
		cout<<"3. Print all the ideas"<<endl;
		cout<<"4. Print an idea by ID"<<endl;
		cout<<"5. Search related idea from ideas bank"<<endl;
		cout<<"6. Search related idea from index table"<<endl;
		cout<<"7. Delete an idea"<<endl;
		cout<<"8. Quit"<<endl;
		cin>>input;
		execute(input);
	}
}

void Program::execute(int input){
	switch(input){
		case 1:{
			string address;
			cout<<"Please enter the file name:";
			cin>>address;
			bank.importFile(address);
			break;
		}
		case 2:{
			string name,content,word="";
			vector<string>keyword;
			cout<<"Please enter your name:";
			cin>>name;
			getline(cin,name);
			do{
				cout<<"Please enter your keyword(enter -1 to finish):";
				cin>>word;
				keyword.push_back(word);
			}while(word!="-1");
			cout<<"Please enter the content:";
			cin>>content;
			getline(cin,content);
			Idea idea(name,content,keyword);
			bank.insertIdea(idea);
			break;
		}
		case 3:{
			bank.print();
			break;
		}
		case 4:{
			int id;
			cout<<"Please enter the id:";
			cin>>id;
			bank.print(id);
			break;
		}
		case 5:{
			string word;
			cout<<"Please enter the word:";
			cin>>word;
			bank.search(word);
			break;
		}
		case 6:{
			string word;
			cout<<"Please enter the word:";
			cin>>word;
			bank.indexSearch(word);
			break;
		}
		case 7:{
			int id;
			cout<<"Please enter the id for the idea to be remove:";
			cin>>id;
			bank.remove(id);
			break;
		}
	}
}


#endif /* PROGRAM_H_ */

/*
 * IdeasBank.h
 *
 *  Created on: 8 May 2020
 *      Author: johnathanliao
 */

#ifndef IDEASBANK_H_
#define IDEASBANK_H_



class IdeasBank{
public:
	void insertIdea(Idea);
	//insert an new idea to the database
	void print(int);
	//print a selected item
	void print();
	//print all the item
	void remove(int);
	//remove an selected item from the database
	void importFile(string);
	//import data from an txt file
	void indexSearch(string);
	//search the related idea from the index table
	void search(string);
	//search without using index
private:
	map<int,Idea>database;
	IndexTable indexTable;
};

void IdeasBank::insertIdea(Idea newIdea){
	pair<map<int, Idea>::iterator, bool> insert;
	insert=database.insert(pair<int,Idea>(newIdea.id,newIdea));
	if(!insert.second){
		cout<<"insertion fail!";
	}else{indexTable.insert(newIdea);}
}

void IdeasBank::print(int id){
	map<int,Idea>::iterator selected;
	selected=database.find(id);
	if(selected!=database.end()){
		Idea idea=selected->second;
		set<int>result=indexTable.relative(idea.keyword,id);
		idea.print();
		cout<<"relative ideas:";
		for(set<int>::iterator i=result.begin();i!= result.end();i++){
			cout<<*i<<" ";
		}
		cout<<endl<<endl;
	}else{
	cout<<"item not found!"<<endl;
	}
}

void IdeasBank::print(){
	for(map<int,Idea>::iterator i=database.begin();i != database.end();i++){
		Idea idea=i->second;
		set<int> result=indexTable.relative(idea.keyword,idea.id);
		idea.print();
		cout<<"relative idea:";
		for(set<int>::iterator i = result.begin(); i != result.end();i++){
			cout<<*i<<" ";
		}
		cout<<endl<<endl;
	}
}

void IdeasBank::remove(int id){
	map<int,Idea>::iterator iterator=database.find(id);
	indexTable.remove(iterator->second);
	if(!database.erase(id)){
		cout<<"fail to delete the item!";
	}
}

void IdeasBank::importFile(string name){
	ifstream file(name);
		if(file.is_open()){
		string line,proposer,content,k;
		vector<string> keyword;
		while(getline(file,line)){
			string temp;
			stringstream stream(line);
			getline(stream,temp,':');
			if(temp=="Name"){
				getline(stream,proposer);
			}else if(temp=="Keyword"){
				getline(stream,k);
				stringstream key(k);
				while(getline(key,temp,',')){
					keyword.push_back(temp);
				}
			}else if(temp=="Content"){
				while(getline(file,temp) && temp!="#end#"){
					content=content+temp+"\n";
				}
				Idea idea(proposer,content,keyword);
				insertIdea(idea);
				content="";
				keyword.clear();
			}
		}
	}else{cout<<"fail to open the file please try again!"<<endl;}
	file.close();
}

void IdeasBank::indexSearch(string word){
	set<int> result;
	regex reg("\\w+");
	if(regex_match(word,reg) && indexTable.search(word,result)){
		for(set<int>::iterator i= result.begin(); i != result.end();i++){
			database.find(*i)->second.print();
		}
	}else{
		cout<<"no match result!"<<endl;
	}
}

void IdeasBank::search(string word){
	regex reg("\\w+");
	bool found=false;
	if(regex_search(word,reg)){
		for(map<int,Idea>::iterator i=database.begin(); i!= database.end(); i++){
			Idea idea=i->second;
			if(idea.search(word)){
				idea.print();
				found=true;
			}
		}
	}
	if(!found){
		cout<<"no match result!"<<endl;
	}
}

#endif /* IDEASBANK_H_ */

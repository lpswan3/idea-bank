/*
 * Idea.h
 *
 *  Created on: 7 May 2020
 *      Author: johnathanliao
 */

#ifndef IDEA_H_
#define IDEA_H_

class Idea{
	friend class IdeasBank;
	friend class IndexTable;
public:
	Idea(string,string,vector<string>);
	//constructor of the class
	bool retrieval(string word);
	//check if the word is exist in the idea
	void print();
	//print the idea
	bool search(string);
private:
	static int idNum;
	//total number of item been create;
	int id;
	string proposer;
	string content;
	vector<string>keyword;
	bool keyword_search(string);
	//search the keyword for the given word
	bool content_search(string);
	//search the content for the given word
};


Idea::Idea(string proposer,string content,vector<string>keyword){
	id=idNum;
	this->proposer=proposer;
	this->content=content;
	this->keyword=keyword;
	idNum+=1;
}


bool Idea::keyword_search(string word){
	for(vector<string>::iterator i = keyword.begin();i != keyword.end();i++){
		if(*i==word){
			return true;
		}
	}
	return false;
}

bool Idea::content_search(string word){
	istringstream ss(content);
	while(ss){
		string s;
		ss>>s;
		if(s==word){
			return true;
		}
	}
	return false;
}

bool Idea::retrieval(string word){
	regex reg("\\w+");
	istringstream ss(content);
	while(ss){
		string s;
		ss>>s;
		if(regex_match(s,reg) && s==word){
			return true;
		}
	}
	return false;
}

void Idea::print(){
	cout<<"ID:"<<id<<endl;
	cout<<"Proposer:"<<proposer<<endl;
	cout<<"Keyword:";
	for(vector<string>::iterator i=keyword.begin();i!=keyword.end();i++){
		cout<<*i;
		if(i!=(--keyword.end())){
			cout<<",";
		}
	}
	cout<<endl;
	cout<<"Cotent:"<<content<<endl<<endl;
}

bool Idea::search(string word){
	if(content_search(word)||keyword_search(word)){
		return true;
	}
	return false;
}

int Idea::idNum=1;

#endif /* IDEA_H_ */

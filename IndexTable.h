/*
 * indexTable.h
 *
 *  Created on: 18 May 2020
 *      Author: johnathanliao
 */

#ifndef INDEXTABLE_H_
#define INDEXTABLE_H_

struct Index{
	string key;
	set<int> *idList;
};

void removeList(Index index){
	delete index.idList;
}

class IndexTable{
public:
	void traversal(void(IndexTable::*process)(string,int),Idea);
	//traverse the keyword and the content of an given idea
	void insert(Idea);
	//insert the data in the index table
	void remove(Idea);
	//remove all the id of an idea from the index
	bool search(string,set<int>&);
	//search and return a list of relative idea's id for a give word
	set<int> relative(vector<string>,int);
	//return a list of relative idea's id of an idea
	~IndexTable();
	//destructor of the indextable
private:
	AvlTree <Index,string>table;
	void removeIndex(string,int);
	void insertIndex(string,int);
};

void IndexTable::insert(Idea idea){
	traversal(&IndexTable::insertIndex,idea);
}

void IndexTable::insertIndex(string word,int id){
	Index index;
	if(!table.AVL_Retrieve(word,index)){
		index.idList=new set<int>;
		index.idList->insert(id);
		index.key=word;
		table.AVL_Insert(index);
	}else{
		index.idList->insert(id);
	}
}

void IndexTable::remove(Idea idea){
	traversal(&IndexTable::removeIndex,idea);
}

void IndexTable::removeIndex(string word,int id){
	Index index;
	if(table.AVL_Retrieve(word,index) && index.idList->find(id)!=index.idList->end()){
		index.idList->erase(id);
		if(index.idList->empty()){
			delete index.idList;
			table.AVL_Delete(index.key);
		}
	}
}


bool IndexTable::search(string word,set<int>&result){
	Index index;
	if(table.AVL_Retrieve(word,index)){
		result=*(index.idList);
		return true;
	}
	return false;
}

void IndexTable::traversal(void(IndexTable::*process)(string input,int id),Idea idea){
	vector<string>keyword=idea.keyword;
	int id=idea.id;
	regex reg("\\w+");
	istringstream ss(idea.content);
	for(int i = 0; i < keyword.size();i++){
		(this->*process)(keyword[i],id);
	}
	while(ss){
		string s;
		ss>>s;
		if(regex_match(s,reg)){
			(this->*process)(s,id);
		}
	}
}
set<int> IndexTable::relative(vector<string>keyword,int id){
	set<int>result;
	for(int i = 0; i < keyword.size();i++){
		string word=keyword[i];
		Index index;
		if(table.AVL_Retrieve(word,index)){
			set<int>::iterator i=index.idList->begin();
			while(i!=index.idList->end()){
				if(*i!=id){
					result.insert(*i);
				}
				i++;
			}
		}
	}
	return result;
}

IndexTable::~IndexTable(){
	table.AVL_Traverse(removeList);
}

#endif /* INDEXTABLE_H_ */

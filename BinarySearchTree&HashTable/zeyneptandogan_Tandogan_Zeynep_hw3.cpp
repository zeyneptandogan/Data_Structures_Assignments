//Zeynep Tandogan 25200
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <chrono>
#include "strutils.h"
#include "Binarysearchtree.h" 
#include "HashTable.h"

//in this homework, i prefer to use open addressing way with quadratic probing while forming the hash table and finally i make the comparison
//that this homework wants us to do. 

struct DocumentItem {
	string documentName;
	int count;
	DocumentItem(){//constructor for struct
	}
	DocumentItem(string filename,int num):documentName(filename),count(num)
	{
	}
};

struct WordItem {
	string word;
	vector<DocumentItem*> details;

	WordItem(string wordnew):word(wordnew),details(vector<DocumentItem*>())//Constructor for struct
	{
		
	}
};
WordItem* ITEM_NOT_FOUND=NULL;//global item not found object

vector<string> words(string word){//return a vector as a result
	vector <string> wordsinword;
	ToLower(word);//no interest about capital or lower letter
	
	for(int i=0;i<word.length();i++){
		if(!(word.at(i)>='a' && word.at(i)<='z')){
			string temp= word.substr(0,i);
			string left=word.substr(i+1,word.length());
			word=temp+" " +left;//put a space in the place of non alphabetic char

		}
	}
	istringstream iss(word);
	while(iss>>word){
		wordsinword.push_back(word);//push words one by one to the vector
	}
	return wordsinword;
}

void createhashtable(vector<string>filenames,HashTable <string, WordItem *>& table){
	DocumentItem *item;
	WordItem *current;
	int count=0;
	for (int i=0;i<filenames.size();i++){
		ifstream infile;
		string filename=filenames[i];//open files one by one
		infile.open(filename);
		string line;
		string wholeword;
	
		while(getline(infile,line)){
			istringstream iss(line);
			while (iss>>wholeword){
				vector<string> tmp=words(wholeword);
				for(int j=0;j<tmp.size();j++){
					string word=tmp[j];
					if(table.find(word)==ITEM_NOT_FOUND){//if the word is not added to the tree before
						count++;
						item=new DocumentItem(filename,1);//count is set to 1 
						current=new WordItem(word);
						current->details.push_back(item);
						table.insert(count,word,current);//insert that word and its info

					}
					else{
						WordItem *thenode=table.find(word);//reach the node that includes that word
						vector<DocumentItem*> * ptemp =&(thenode->details);//take the location of the node.
						bool found=false; 
						for(int i=0;i<ptemp->size();i++){
							if((*ptemp)[i]->documentName==filename){
								(*ptemp)[i]->count++;//if the file is the same with the one in the node just increment the count
								found=true;
							}
						}
						if(!found){
							item=new DocumentItem(filename,1);//add the filename since it is not added before although the word is added by other file
							ptemp->push_back(item);
						}
					}
				}
			}
		}
		infile.close();
	}
	cout<<endl<<endl;
	cout<<"After preprocessing, the unique word count is "<<count<<". Current load ratio is "<<fixed << setprecision(6)<<table.calculateload()<<endl;

}
void createbinarytree(vector<string>filenames,BinarySearchTree<string, WordItem *> & myTree){

	DocumentItem *item;
	WordItem *current;
	for (int i=0;i<filenames.size();i++){
		ifstream infile;
		string filename=filenames[i];//open files one by one
		infile.open(filename);
		string line;
		string wholeword;
		int times=0;
		while(getline(infile,line)){
			times++;
			istringstream iss(line);
			while (iss>>wholeword){
				vector<string> tmp=words(wholeword);
				for(int j=0;j<tmp.size();j++){
					string word=tmp[j];
					if(myTree.find(word)==ITEM_NOT_FOUND){//if the word is not added to the tree before
						item=new DocumentItem(filename,1);//count is set to 1 
						current=new WordItem(word);
						current->details.push_back(item);
						myTree.insert(word,current);//insert that word and its info

					}
					else{
						WordItem *thenode=myTree.find(word);//reach the node that includes that word
						vector<DocumentItem*> * ptemp =&(thenode->details);//take the location
						bool found=false; 
						for(int i=0;i<ptemp->size();i++){
							if((*ptemp)[i]->documentName==filename){
								(*ptemp)[i]->count++;//if the file is the same with the one in the node just increase the count
								found=true;
							}
						}
						if(!found){
							item=new DocumentItem(filename,1);//just add the filename ,the word is already inserted.
							ptemp->push_back(item);
						}
					}
				}
			}
		}
	}

}
bool belongthatfile(vector<DocumentItem*> temp,vector<string>filenames,int j){//check if it is in that file
	for(int k=0;k<temp.size();k++){
		if(temp[k]->documentName==filenames[j]){//search through all document names
			return true;
		}
	}
	return false;//if not belong to that file
}

void search_where_they_are(int i,BinarySearchTree <string, WordItem *> & myTree, vector<string>searchedones,vector<string>filenames){

	bool notprint;
	int notincludewords=0;
	for (int j=0;j<filenames.size();j++){
		notprint=false;
		vector< WordItem*> results;
		for (int i=0;i<searchedones.size();i++){ 
			string theone=searchedones[i];
			WordItem* node= myTree.find(theone);//find the place
			if(node!=ITEM_NOT_FOUND){
				vector<DocumentItem*> temp=node->details;
				if(belongthatfile(temp,filenames,j)){
					vector<DocumentItem*> temp=node->details;
					results.push_back(node);
				}
			
				else{
					notprint=true;//if not all numbers are found in the file
					break;
				}
			}
			else{
				notprint=true;//if that word is not found at all
			}
		}
		if(i==0){
			if(!notprint){//the word is found and pushed to the results that include document ýtems
				cout<<"in Document "<<filenames[j]<< ", ";
				for(int z=0;z<results.size();z++){
					vector<DocumentItem*> temp=results[z]->details;
					string word=results[z]->word;
					for(int k=0;k<temp.size();k++){
						if(temp[k]->documentName==filenames[j]){
							cout<<word <<" found "<<temp[k]->count<<" times";
							if(z!=searchedones.size()-1){//if we dont reach the end
								cout<<", ";
							}
							else{
								cout<<"."<<endl;//this is the end
								break;
							}
						}			
					}
				}
			}
			if(notprint){
				notincludewords++;
				if(notincludewords==filenames.size())//notincludewords show the count of the files that does not have the query line
					cout<<"No document contains the given query"<<endl;
			}
		}
	}
}
void search_where_they_are(int i,HashTable<string, WordItem *> & table, vector<string>searchedones,vector<string>filenames){

	bool notprint;
	int notincludewords=0;
	for (int j=0;j<filenames.size();j++){
		notprint=false;
		vector< WordItem*> results;
		for (int i=0;i<searchedones.size();i++){ 
			string theone=searchedones[i];
			WordItem* node= table.find(theone);
			if(node!=ITEM_NOT_FOUND){
				vector<DocumentItem*> temp=node->details;
				if(belongthatfile(temp,filenames,j)){
					vector<DocumentItem*> temp=node->details;
					results.push_back(node);
				}
			
				else{
					notprint=true;//if not all numbers are found
					break;
				}
			}
			else{
				notprint=true;//if that word is not found at all
			}
		}
		if(i==0){
			if(!notprint){//the word is found and pushed to the results that include document ýtems
				cout<<"in Document "<<filenames[j]<< ", ";
				for(int z=0;z<results.size();z++){
					vector<DocumentItem*> temp=results[z]->details;
					string word=results[z]->word;
					for(int k=0;k<temp.size();k++){
						if(temp[k]->documentName==filenames[j]){
							cout<<word <<" found "<<temp[k]->count<<" times";
							if(z!=searchedones.size()-1){//if we dont reach the end
								cout<<", ";
							}
							else{
								cout<<"."<<endl;//this is the end
								break;
							}
						}			
					}
				}
			}
			if(notprint){
				notincludewords++;
				if(notincludewords==filenames.size())//notincludewords show the count of the files that does not have the query line
					cout<<"No document contains the given query"<<endl;
			}
		}
	}
}
void searchedones(HashTable <string, WordItem *>&table,BinarySearchTree<string, WordItem *>&myTree,vector<string>filenames){
	string queried_line;
	cout<<"Enter queried words in one line: ";

	cin.ignore(); 
	getline(cin,queried_line);

	istringstream iss(queried_line);
	string wholeword;
	vector<string> searchedones;
	while(iss>>wholeword){//while iss is giving words to us
		vector<string> tmp= words(wholeword);
		for(int j=0;j<tmp.size();j++){
			searchedones.push_back(tmp[j]);
		}
	}
	int k = 300;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		search_where_they_are(i,myTree,searchedones,filenames);
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		search_where_they_are(i,table,searchedones,filenames);
	}

	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << (BSTTime.count() / k )<< "\n";//take the average duration
	cout << "\nTime: " << (HTTime.count() / k )<< "\n";	//take the average duration
	cout<<"Speed Up: " <<fixed << setprecision(5)<<(double) BSTTime.count()/(double)HTTime.count()<<endl;
}
int main(){
	BinarySearchTree<string, WordItem *> myTree(ITEM_NOT_FOUND);//for tree
	HashTable <string, WordItem *> table(ITEM_NOT_FOUND);//for hash table
	
	int numberfiles;

	cout<<"Enter number of input files:";
	cin>>numberfiles;
	vector<string>filenames(numberfiles);//form a vector that stores filenames 
	cout<<"Enter 1. file name: ";
	string x;
	int idx=1;
	int count=0;
	while(count<numberfiles && cin>>x){//while taking the inputs and not reach at the end with files
		filenames[count]=x;
		count++;
		idx++;
		if(count!=numberfiles){
			cout<<"Enter "+itoa(idx)+". file name: ";
		}
	}
	createhashtable(filenames,table);//create the table
	createbinarytree(filenames,myTree);//create whole the tree
	searchedones(table,myTree,filenames);//this is for the result part
	return 0;
}
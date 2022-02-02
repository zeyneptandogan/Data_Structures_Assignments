//Zeynep Tandogan-25200
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "strutils.h"
#include "AVLsearchtree.h" 
using namespace std;

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
bool isaNumber(string str) //this is for not to take numbers from the file
{ 
    for (int z = 0; z < str.length(); z++) {
        if (isdigit(str[z]) == false) {
            return false; 
		}
	}
    return true; 
	
} 

WordItem* ITEM_NOT_FOUND=NULL;
bool belongthatfile(vector<DocumentItem*> temp,vector<string>filenames,int j){//check if it is in that file
	for(int k=0;k<temp.size();k++){
		if(temp[k]->documentName==filenames[j]){//search through all
			return true;
		}
	}
	return false;
}

void search_where_they_are(AVLSearchTree <string, WordItem *> & myTree, vector<string>words,vector<string>filenames){

	bool notprint;
	int notincludewords=0;
	for (int j=0;j<filenames.size();j++){
		notprint=false;
		vector< WordItem*> results;
		for (int i=0;i<words.size();i++){ 
			string theone=words[i];
			WordItem* node= myTree.find(theone);
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
		if(!notprint){//the word is found and pushed to the results that include document ýtems
			cout<<"in Document "<<filenames[j]<< ", ";
			for(int z=0;z<results.size();z++){
				vector<DocumentItem*> temp=results[z]->details;
				string word=results[z]->word;
				for(int k=0;k<temp.size();k++){
					if(temp[k]->documentName==filenames[j]){
						cout<<word <<" found "<<temp[k]->count<<" times";
						if(z!=words.size()-1){//if we dont reach the end
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


void createavltree(vector<string>filenames,AVLSearchTree<string, WordItem *> & myTree){

	DocumentItem *item;
	WordItem *current;
	for (int i=0;i<filenames.size();i++){
		ifstream infile;
		string filename=filenames[i];//open files one by one
		infile.open(filename);
		string line;
		string word;
		while(getline(infile,line)){
			istringstream iss(line);
			while (iss>>word){
				if(!isaNumber(word)){
					ToLower(word);
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
	}

}

int main(){

	AVLSearchTree<string, WordItem *> myTree(ITEM_NOT_FOUND);

	vector<string>words;
	int numberfiles;

	cout<<"Enter number of input files:";
	cin>>numberfiles;
	vector<string>filenames(numberfiles);//form a vector that stores filenames 
	cout<<"Enter 1. file name: ";
	string x,queried_line;
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
	createavltree(filenames,myTree);//create whole the tree

	cout<<"Enter queried words in one line: ";

	cin.ignore();
	getline(cin,queried_line);//take the line and divide it into pieces with iss
	istringstream iss(queried_line);
	string word;

	while(iss>>word){//while iss is giving words to us
		ToLower(word);//make all the words lower since it does not matter whether it starts with capital letter or not
		words.push_back(word);

	}
	search_where_they_are(myTree,words,filenames);
	return 0;
}
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
#include "sortalgorithms.h"
#include <ctime>
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
	bool operator <(const WordItem & temp){//these are for overloading that will use in the class
		return word<temp.word;
	}
	bool operator >(const WordItem & temp){
		return word>temp.word;
	}
	bool operator <= (const WordItem &temp){
		return word<=temp.word;
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
	//cout<<endl<<endl;
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
WordItem* findtheindex(string word,vector<WordItem *>& myvec){
	//this is for the vector, if we find it return it ,if it is not there return ýtem_not_found which represent the word is not included in the vector.
	for (int i=0;i<myvec.size();i++){
		if(myvec[i]->word==word){
			return myvec[i];
		}
	}
	return ITEM_NOT_FOUND;
}

void createvector(vector<string>filenames,vector<WordItem *> & myvec){

	DocumentItem *item;
	WordItem *current;
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
					if(findtheindex(word,myvec)==ITEM_NOT_FOUND){//if the word is not added to the tree before
						item=new DocumentItem(filename,1);//count is set to 1 
						current=new WordItem(word);
						current->details.push_back(item);
						myvec.push_back(current);//insert that word and its info

					}
					else{
						WordItem *thenode=findtheindex(word,myvec);//reach the node that includes that word
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
	long long sum=0;
	//auto BSTTime=0;
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

int binarySearch(vector <WordItem*> &myvec1, int l, int r, string word) {
	//in this function, we do searching by halving the vector and looking which part we can find the word and this process is done recursively.
	if (l <= r) {
		int mid = (l + r)/2;
		if (myvec1[mid]->word== word)
			return mid ;
		if (myvec1[mid]->word > word)
			return binarySearch(myvec1, l, mid - 1, word); 
		if (myvec1[mid]->word < word)
			return binarySearch(myvec1, mid + 1, r, word); 
	}
	return -1;
}
void binarysearch_findplace(int i,vector <WordItem*> &myvec1,vector<string>searchedones,vector<string>filenames){
	//this is for the search with vector and the binary search.
	bool notprint;
	int notincludewords=0;
	for (int j=0;j<filenames.size();j++){
		notprint=false;
		vector< WordItem*> results;
		for (int i=0;i<searchedones.size();i++){ 
			string theone=searchedones[i];
			int k=binarySearch(myvec1,0,myvec1.size()-1,theone);
			WordItem* node= myvec1[k];//find the place
			//WordItem* node= findtheindex(theone,myvec1);//find the place
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
					//vector<DocumentItem*> temp=results[z]->details;
					string word=results[z]->word;
					int k=binarySearch(myvec1,0,myvec1.size()-1,word);//the index that comes from binary search
					if(k!=1){
						vector<DocumentItem*> temp=myvec1[k]->details;
						for (int k=0;k<temp.size();k++){
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
	//this is for the search with hash table

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
void searchedones(HashTable <string, WordItem *>&table,vector<WordItem*> myvec,BinarySearchTree<string, WordItem *>&myTree,vector<string>filenames){
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
			searchedones.push_back(tmp[j]);//store them in a vector
		}
	}
	//sorting part timing
	//this part is all about sorting and their timing issues. Since i used a class, i first form the class object and then use sorting algorithms.
	//afterwards, i use auto to measure time.
	//another important thing is that i take 6 copies of the original vector in order not to use a sorted version in the sort algorithms.

	vector<WordItem*> myvec1=myvec;
	Sortalgorithms<WordItem*> temp(myvec1);
	auto start = std::chrono::high_resolution_clock::now();
	temp.insertionSort();
	auto insertiontime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);   

	vector<WordItem*> myvec2=myvec;
	Sortalgorithms<WordItem*> temp1(myvec2);
	start = std::chrono::high_resolution_clock::now();
	temp1.mergeSort();  
	auto mergetime= std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	vector<WordItem*> myvec3=myvec;
	Sortalgorithms<WordItem*> temp2(myvec3);
	start = std::chrono::high_resolution_clock::now();
	temp2.heapsort();     
	auto heaptime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	vector<WordItem*> myvec4=myvec;
	Sortalgorithms<WordItem*> temp3(myvec4);
	start = std::chrono::high_resolution_clock::now();
	temp3.medianquicksort();     
	auto medianquicktime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	vector<WordItem*> myvec5=myvec;
	Sortalgorithms<WordItem*> temp4(myvec5);
	start = std::chrono::high_resolution_clock::now();
	temp4.firstquicksort();   
	auto firstquicktime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	vector<WordItem*> myvec6=myvec;
	Sortalgorithms<WordItem*> temp5(myvec6);
	start = std::chrono::high_resolution_clock::now();
	temp5.randomquicksort(); 
	auto randomquicktime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);


	//BST,HT and BS
	int k = 100;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
		search_where_they_are(i,myTree,searchedones,filenames);
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
		search_where_they_are(i,table,searchedones,filenames);

	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
		binarysearch_findplace(i,myvec1,searchedones,filenames);
	auto BSTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

	cout<<endl;
	cout << "Binary Search Tree Time: " << (BSTTime.count() / k )<< endl;//take the average duration
	cout << "Hash Table Time: "  << (HTTime.count() / k )<< endl;	//take the average duration
	cout << "Binary Search Time: "  << (BSTime.count() / k )<< endl;	//take the average duration
	cout<<endl;
	cout<< "Quick Sort(median) Time: " <<medianquicktime.count()<<endl;
	cout<< "Quick Sort(first) Time: "<<firstquicktime.count()<<endl;
	cout<<"Quick Sort(random) Time: "<<randomquicktime.count()<<endl;
	cout<<"Heap Sort  Time: " <<heaptime.count()<<endl;
	cout<<"Merge Sort Time: "<<mergetime.count()<<endl;
	cout<<"Insertion  Time: "<<insertiontime.count()<<endl<<endl;

	cout<<"Speed Up BST/HST: "<<fixed << setprecision(5)<<(double) BSTTime.count()/(double)HTTime.count()<<endl;
	cout<<"Speed Up Insertion/Quick Sort(Median): "<<(double) insertiontime.count()/(double)medianquicktime.count()<<endl;
	cout<<"Speed Up Merge Sort/Quick Sort(Median): "<<(double) mergetime.count()/(double)medianquicktime.count()<<endl;
	cout<<"Speed Up Heap Sort/Quick Sort(Median): "<< (double) heaptime.count()/(double)medianquicktime.count()<<endl<<endl;
	
	cout<<"Speed Up Binary Search Tree Time / Binary Search: " <<(double) BSTTime.count()/(double)BSTime.count()<<endl;
	cout<<"Speed Up Binary Search / Hash Table Time: "<<(double)BSTTime.count()/(double) HTTime.count()<<endl;

}
int main(){
	BinarySearchTree<string, WordItem *> myTree(ITEM_NOT_FOUND);//for tree
	HashTable <string, WordItem *> table(ITEM_NOT_FOUND);//for hash table
	vector<WordItem*> myvec;
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
	createvector(filenames,myvec);//create the vector
	searchedones(table,myvec,myTree,filenames);//this is for the result part
	system("pause");
	return 0;
}
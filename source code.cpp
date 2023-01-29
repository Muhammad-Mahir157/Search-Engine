#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

char* strcopy(const char* arr)		//copying a char* array
{
	 int i =0;
	char* temp=new char[strlen(arr)+1];
	while(arr[i]!='\0')
		{
		temp[i]=arr[i++];
		}
	temp[i]='\0';

	 return temp;
}
  char** tokenizer(char* str,int s)  // creating tokens
  {
	  int k=0;
	 char* temp=strcopy(str);
	    char** tok_list=new char*[s];
	  char* token=strtok(temp," ");
		for(;token!='\0';k++)
		{
			tok_list[k]=strcopy(token);
			  token=strtok(NULL," ");
		}
		return tok_list;
  }
	char* mergertxt(const char txt1[],const char txt2[])  // Using merger function to append .txt with "doc-file-name"
	{
		int s1=0,s2=0,x=0,y=0;
		 s1=strlen(txt1);
		 s2=strlen(txt2);
    	char* merge=new char[s1+s2+1];
			for(;x<s1;x++)
				merge[x]=txt1[x];
			for(;x<s1+s2;x++)
			{
				merge[x]=txt2[y++];	
			}
		 merge[x]='\0';
	  return merge;
	}
   	char* readf(const char* l)
	{
		ifstream finput(mergertxt(l,".txt"));    // mergering the text for reading the file
		char* buffer=new char[300];
	
		if (finput.is_open())
		{
			     finput.getline(buffer, 300, '-1');	    // here -1 indicates eof

		}
    	return buffer;
	}
   char* doc_Read(const char* l)
   {
	   
		ifstream finput(mergertxt(l,".txt"));    // mergering the text for reading the file
		char* buffer=new char[300];
	
		if (finput.is_open())
		{
			     finput.getline(buffer, 300, '\n');	    // here -1 indicates eof

		}
    	return buffer;
   }
 bool strcmpar(const char * str1,const char* str2) // Comparing two const char* arrays
 {
	 if(strlen(str1)!=strlen(str2))
		 return false;

	 for(int y=0;y<strlen(str1);y++)
	 {
		 if(str1[y]!=str2[y])
			 return false;
	 }
	 return true;
 }
 int wordcount(char* str_line)		// Counting number of words in a doc
	{
		int count=0;
		char* temp=strcopy(str_line);
	 char* token=strtok(temp," ");
		 for(int i=0;token!='\0';i++)
		 {
			 count++;
		      token=strtok(NULL," ");
		 }

		 return count;
	}
template<class T>
class dlist							// Doubly linked list
{
	class Node					// Node class
	{
	public:
		T da;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
public:
dlist()								//Constructor
	{
		head= new Node;
		tail= new Node;
		head->next=tail;
		head->prev=nullptr;
		tail->next=nullptr;
		tail->prev=head;
	}
class Iterator						// Iterator class
{

	 Node* curr;
	friend class dlist;
public:
	Iterator(Node* k=nullptr)
	{
		curr=k;
	}
	Iterator(const Iterator & it)
	{
		this->curr=it.curr;
	}
	Iterator & operator++()
	{
		this->curr=curr->next;
		return *this;
	}
	Iterator & operator++(int)
	{
		Iterator tp=*this;
		this->curr=curr->next;
		return tp;
	}
	Iterator & operator--()
	{
		this->curr=curr->prev;
		return *this;
	}
	 bool operator!=(const Iterator &itr) 
        {      
		  return(curr!=itr.curr);
        }
		T & operator*(){
			return curr->da;
		}
};
 Iterator insert(T in,Iterator temp)				
	 {
		 Node* itnear=temp.curr;
		 Node* p=new Node;
	   p->da=in;
	   p->next=itnear;
	   p->prev=itnear->prev;
	   itnear->prev->next=p;
	   itnear->prev=p;
		   Iterator rt(p);
		   return rt;
	 }
 void insertatHead(T da)
	 {
		 Iterator ith(head->next);
		  insert(da,ith);
	 }
 void insertatTail(T da)
	 {
		 Iterator itl(tail);
		 insert(da,itl);
	 }
 Iterator deleteat(Iterator temp)
	 {
		 Node* del=temp.curr;
		 Iterator rt(del->next);
		  del->prev->next=del->next;
		 del->next->prev=del->prev;
		 delete del;
		 return rt;
	 }
  void deleteatHaid()
	  {
		    if(head->next!=tail)
			{
		  Iterator ith(head->next);
		    deleteat(ith);
			}
	  }
  void deleteatTail()
	  {
		   if(head->next!=tail)
		   {
		  Iterator itT(tail);
		    deleteat(--itT);
		   }
	  }
  Iterator begin()
	{
		Iterator temp(head->next);
		return temp;
	}
	Iterator end()
	{
		Iterator temp(tail);
		return temp;
	}
	void print()
	{
		Iterator itr;
		for(itr=begin();itr!=end();++itr)
		{
			cout<<*(itr)<<" ";
		}
		cout<<endl<<endl;
	}
  ~dlist()										// Destructor of doubly linked list
  {
	  while(head->next!=tail)
	  {
		  deleteatHaid();
	  }
  }
};
class docInfo
{
	char* docid;
	int tfreq;
public:
	friend class search_engin;
	friend class termInfo;
	docInfo()						//default constructor
		{
			docid='\0';
			tfreq=0;
		}
	docInfo(const char* id,int f)	//Overload constructor 
		{
			tfreq=f;
			docid=strcopy(id);
		}
	int retfreq()					// return frequency
	{
		return tfreq;
	}
	char* retdoc()					// return docid 
	{
		return strcopy(docid);
	}

	friend ostream & operator<<( ostream & out,const docInfo & obj)		//Overloading "<<" operator for display of data
	{
		out<<" -::- "<<obj.docid<<"   "<<obj.tfreq;
		return out;
	}
	~docInfo()
		{
		 }
};
class termInfo
{
	  dlist<docInfo> object;
	char* k_term;
	friend class search_engin;
public:
	termInfo()							//default constructor
	{
		k_term='\0';
	}
	termInfo(const char* term,int f)	//Overload constructor 
	{
		k_term=strcopy(term);
	}
void f_increment(const char* doc)		//incrementing frequency if both key_term and doc are already
	{
		dlist<docInfo>::Iterator tempobj;
		tempobj=object.begin();
		for(  ;tempobj!=object.end();++tempobj)
		{
			if(strcmpar((*tempobj).docid,doc))
			{
				(*tempobj).tfreq++;		
			}
		}
	}
 bool check_doc(const char* doc)		// Checking document whether it is already present or not for a specific key-term
  {
		dlist<docInfo>::Iterator tempobj;
		tempobj=object.begin();
		for(  ;tempobj!=object.end();++tempobj)
		{
			if(strcmpar((*tempobj).docid,doc)==true)
				return true;
		}
		return false;
  }
 char** getdoclist(int size)
 {
	 char** doclist=new char*[size];
	  dlist<docInfo>::Iterator tempobj;	
		  tempobj=object.begin();
		  for( int i=0 ;tempobj!=object.end();++tempobj)
	     	{
				
				doclist[i]=(*tempobj).retdoc();
				 i++;
		    }
		  return doclist;
 }
 int getdoclist_size()
 {
	  int x=0;
	  dlist<docInfo>::Iterator tempobj;	
		  tempobj=this->object.begin();
		  for(  ;tempobj!=this->object.end();++tempobj)
	     	{
				x++;
		    }
		return x;
 }
 void setkey(const char* nm)							// a setter of key-term
 {
	 k_term=strcopy(nm);
 }

 void Insert(const char* docname)						//Inserting doc through insertataTail function of dlist
 {
	 object.insertatTail(docInfo(docname,1));
 }
 int getcollectivef(const char* docno,int word_count)		//returns collective frequency of a doc
	{
			 int collect=0;
		 dlist<docInfo>::Iterator tempobj;
		tempobj=object.begin();
		
			for(  ;tempobj!=object.end();++tempobj)
			{
				if(strcmpar((*tempobj).docid,docno))
				{
					collect=collect+(*tempobj).tfreq;		
				}
			}
		
		return collect;
	}
	int gettermf(const char* docno)				//returns that specific/query term frequency of a doc
	{
		dlist<docInfo>::Iterator tempobj;
		tempobj=object.begin();
		for(  ;tempobj!=object.end();++tempobj)
		{
			if(strcmpar((*tempobj).docid,docno))
			{
				return 1;		
			}
		}
		return 0;
	}
	~termInfo()
	{
	 }
};
class search_engin
{
	termInfo* index;
	int array_size;
	int max_size;
public:
	search_engin()						//default constructor
		{
			array_size=0;
			max_size=0;
		}
	search_engin(int max)				//Overload constructor 
		{
			max_size=max;
		  index=new termInfo[max_size];
		  array_size=0;
		}
  void creat_index(char** line,int n)
	{		                                                     //document where it is present
		 int size=0,docno=0;
		for(int i=0;i<n;i++)
		{
			char* temp= readf(line[i]);		// reading file through readf function
			 size= wordcount(temp);								//counting words of doc and storin it in size var
			char** tok_list= tokenizer(temp,size);				//craeting tokens and storing them in tok_list
		 for(int f=0;f<size;f++)
			 {
				  docno=check_key(tok_list[f]);					   //if a key-term is not already present then check_key function
																  // will return -7 and store it in docno variable
				 if(docno==-7)								  	   //if docno has -7 then that key term will be added along with								  
				 {                                                      //document where it is present
					 index[array_size].setkey(tok_list[f]);
					 index[array_size].Insert(line[i]);
					 array_size++;
				 }
				 else if(!index[docno].check_doc(line[i]))				//If key-term already is present but there is a new doc where that key term is present then add that doc
					 index[docno].Insert(line[i]);												
				  else
				     index[docno].f_increment(line[i]);				//if both key-term and doc are present then increment term frequecy in that doc
			 }
		}
	}

  int check_key(const char* term)	//Checking whether a key-term is already present or not
  {
	  for(int k=0;k<array_size;k++)
	  {
		  if(strcmpar(term,index[k].k_term))
			  return k;								 //if already present then returns that index number where it is present
	  }
	  return -7;									//If not present then return -7 to add that key-term 
  }
    void print()					//Printing all the data of docs
	  {
		  cout<<endl<<endl;
		for(int i=0;i<array_size;i++)
		 {
			cout<<index[i].k_term<<"  ";
			index[i].object.print();
		 }
	  }
 //Part B: ranking of docs
	char** collab(char** all_token,int count ,int & union_size,int tot_Docs)		//Creates a union set of all the query term docs
	{
		bool flag=true;
		char**uniondocs=new char*[tot_Docs];
		int unionsize=0;
		int kterm_check=0,doclist_size=0;
		char** doclist;
	
		for(int j=0; j<count; j++)
		{
			kterm_check=check_key(all_token[j]);
			if(kterm_check!=-7)
			{
				doclist_size=index[kterm_check].getdoclist_size();
			
				doclist=index[kterm_check].getdoclist(doclist_size);
			
			for(int k=0;k<doclist_size;k++)
				{
				
					flag=true;
					for(int l=0;l<unionsize;l++)
					{
					
						if(strcmpar(doclist[k],uniondocs[l]))
							flag=false;		
					}

					if(flag)
					uniondocs[unionsize++]=strcopy(doclist[k]);

				}
			}
		}
		union_size=unionsize;
		return uniondocs;
	}
	void swap_doc(char* & lesser,char* & greater)
	{
		char* temp;
		temp=strcopy(lesser);
		lesser=strcopy(greater);
		greater=temp;
	}
	void swap_freq(int & first,int & second)
	{
		int temp=0;
		temp=first;
		first=second;
		second=temp;
	}
	bool check_equal(int s,int arr[])
	{
		for(int k=0; (k+1)<s ;k++)
		 {
			 if(arr[k]!=arr[k+1])
				 return false;
		 }
		return true;
	}
 void search_documents(char* query ,int totnoofDocs)		//			this function create ranks all the docs 
	{
			int total_ranks=0,key_check=0;
			bool flag=true;
			 int tot_words=wordcount(query);								
				 char** alltokens= tokenizer(query,tot_words);	
			char** unionof=collab(alltokens,tot_words,total_ranks,totnoofDocs);
			for(int i=0; i<total_ranks;i++)
			{	
				cout<<unionof[i]<<" ";
			}
			int* colfreq=new int[total_ranks];
			int* termfreq=new int[total_ranks];
			 for(int k=0; k<total_ranks ;k++)
				{
					colfreq[k]=0;
					termfreq[k]=0;
				}
		for(int y=0; y<tot_words ;y++)
			{
				key_check=check_key(alltokens[y]);
				if(key_check!=-7)
					{
			   for(int k=0; k<total_ranks ;k++)
			   {
					colfreq[k]=colfreq[k]+index[key_check].getcollectivef(unionof[k],tot_words);
					termfreq[k]=termfreq[k]+index[key_check].gettermf(unionof[k]);
				//	cout<<endl<<colfreq[k]<<" "<<termfreq[k];
					
					}
			   }
		   }
		          for(int a=0; a<total_ranks ;a++)
					{
					  for(int z=0; z<total_ranks-1 ;z++)					
						 {
							 if(termfreq[z]<termfreq[z+1])										// Rule No 1 for ranking docs
							 {

								 swap_doc(unionof[z],unionof[z+1]);
								 swap_freq(termfreq[z],termfreq[z+1]);
								 swap_freq(colfreq[z],colfreq[z+1]);

							 }
							 else if(colfreq[z]<colfreq[z+1] && termfreq[z]==termfreq[z+1])     // Rule No 2 for ranking docs
							 {

								 swap_doc(unionof[z],unionof[z+1]);
								 swap_freq(termfreq[z],termfreq[z+1]);
								 swap_freq(colfreq[z],colfreq[z+1]);

							 }
							 else if(unionof[z]<unionof[z+1] && colfreq[z]==colfreq[z+1] && termfreq[z]==termfreq[z+1])  // Rule No 3 for ranking docs
							 {

								 swap_doc(unionof[z],unionof[z+1]);
								 swap_freq(termfreq[z],termfreq[z+1]);
								 swap_freq(colfreq[z],colfreq[z+1]);

							 }
						 }
				    }
			
			cout<<"\n After Ranking: "<<endl;
		for(int a=0; a<total_ranks ;a++)								//Printing after ranks
		{
			cout<<unionof[a]<<" ->";
		}
		//system("pause");
	 }
   void addDocto_index(char* file_name)
   {
	   int size=0,docno=0;
	   char* dname=new char[10];
	    
			char* temp= readf(file_name);		// reading file through readf function
			 size= wordcount(temp);								//counting words of doc and storin it in size var
			char** tok_list= tokenizer(temp,size);				//craeting tokens and storing them in tok_list
			  dname=strcopy(tok_list[0]);
		 for(int f=1;f<size;f++)
			 {
				  docno=check_key(tok_list[f]);					   //if a key-term is not already present then check_key function
																  // will return -7 and store it in docno variable
				 if(docno==-7)								  	   //if docno has -7 then that key term will be added along with								  
				 {                                                      //document where it is present
					 index[array_size].setkey(tok_list[f]);
					 index[array_size].Insert(dname);
					 array_size++;
				 }
				 else if(!index[docno].check_doc(dname))				//If key-term already is present but there is a new doc where that key term is present then add that doc
					 index[docno].Insert(dname);												
				  else
				     index[docno].f_increment(dname);				//if both key-term and doc are present then increment term frequecy in that doc
			}
   }
   char** extend(char **arr,int size)
  {
    char** temp=arr;
      arr=new char*[size+1];
    
		for(int i=0;i<size;i++)
		{
        	arr[i]=temp[i];
		}
       delete[] temp;
      return arr;   
}
	~search_engin()
		 {
			delete[]index;
		 }
};

void main()
{
	int s=0;
	char* temp=doc_Read("alldocnames");			// All doc names are written in this file
	s=wordcount(temp);
	char** line=tokenizer(temp,s);				// An array having all the names of docs
	
	search_engin obj(120);
	obj.creat_index(line,s);					//creating index

	 obj.search_documents("list stack linked",s);	//searching query using search_documents function
	  obj.addDocto_index("add");					// this add file contians the document and keyterms to be added
	  obj.print();									//printiing

	  system("pause");

}
# Introduction:
A small search engine that can help its users to retrieve documents related to the search query from a collection of documents.

# Main Idea:
The idea is to examine all documents of the collection and output only those that contain the words from the search query. For example, if the search query has the word “velocity”, then we have to find all those documents that contain the word “velocity”.

# Specifications:
The job of a search engine is to efficiently retrieve the set of desired documents and then rank them according to their relevance. To make things faster, an index of important terms/words is maintained. For each word in the index, a list is maintained that keeps the record of documents in which that term appears along with some other important information like term frequency, and list of positions where that word occurs.

# Terminologies:
TF: Term Frequency, which measures how frequently a term occurs in a document.

TF(t,d) = Number of times term t appear in document d

# Explanation of workflow:
Take a look at the brief sample below, where the documents are
Doc 1 breakthrough drug schizophrenia drug released july
Doc 2 new schizophrenia drug breakthrough drug
Doc 3 new approach treatment schizophrenia
Doc 4 new hopes schizophrenia patients schizophrenia cure

Terms will be stored in an array. For each term, there is a list that contains document ID, and term frequency. See the following figure for the structure of the index. The word drug is present in Doc1 and Doc2 two times in each document.

![img1](https://user-images.githubusercontent.com/82761065/215339545-c8e9c749-2b4d-444e-9b36-05c53609c51d.png)

# Algorithm
For Index creation:
1. Collect the documents to be indexed:
2. Tokenize the text, turning each document into a list of tokens/terms/words
3. Remove stop words (of, for, the etc.), producing a list of important words
4. Put each unique term in an array. For each unique term create a list of documents where that term exists. A sample Index is shown in the above figure.

For Docment Retrieval:
1. Input search query
2. Tokenize the text in the query
3. Remove stop words
4. For each query term, search it in the index, collect the list of documents. If there
is more than one word in the query, take the union of all the lists.
5. Rank the retrieved documents.

Ranking Rules:

Rule1: Documents containing more query terms must be ranked higher than the documents containing lesser query terms.

Rule2: If two documents have the same number of query terms then rank the document higher that has higher collective term frequency.

Rule3: If two documents have the same number of query terms and the same collective term frequency then rank the document alphabetically by Doc ID

# Other Functionalities:
Search_Documents: 
Given the query word(s), tokenize them by white space, compute the list of documents related to query and output a ranked list of related documents as explained in Algorithm2 and Table1.

Add_Doc_to_Index: 
Given a file name: open it, read it, and tokenize words on white space. Also, compute the term frequency of each unique word in the file. For each unique word, if the word is already present in the index, add the Doc ID and computed term frequency at the end of the corresponding Doc_Info list. Otherwise, add the new word at the end of the array Index. If array Index is already full double its size and then add. 



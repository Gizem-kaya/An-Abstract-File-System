# A Virtual File System program in C. 

The aim of the program is practicing on dynamic memory allocation. 
I used realloc and malloc functions but you can change the functions as you want. 

The program takes commands from an input file. The name of the input file is taken as an argument.
The program reads a command from each line of the input file. These commands are like:

  * create -n file1.txt -t this is the text 
  
      -> creates a file with the name file1.txt the text is "this is the text". As I said before the files are abstract files not creating a real txt file.
  
  *  create -t the text of the other file -n file2.doc
  
      -> creates a file with the name file2.doc the text is "the text of the other file".
   
  * delete -n file1.txt
  
      -> deletes the file1.txt.
  
  * remove -n file1.txt -s 11 -l 3
  
      -> deletes the contents of the given file until it reaches the length(-l 3) from the given initial index(-s 11).
  
  * append -n file2.doc -t this text should be added at the end of the other
  
      -> appends the entered text to the end of the file's text.
  
  * replace -n file2.doc -ow the -nw new
  
      -> replaces a word in the text with a new word.
  
  * print -a
  
      -> prints all the files and files' texts.
  
  * print -e doc
  
      -> prints all the files that has the same extension with the word given in command.
  
  * print -c
  
      -> prints all the files and files' texts according to the order.
  
  * print -n file1.txt 
  
      -> prints the file's text.
  
  * print -n file2.doc -cs
  
      -> prints the sentence count that the file's text has.
  
  * print -n file1.txt -cw 
  
      -> prints the word count that the file's text has.

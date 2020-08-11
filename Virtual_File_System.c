#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define file_name_size 100
#define max_extension_size 10
#define max_text_size 500
#define max_command_size 10

	
typedef struct file {								// A struct for each file.	

	char text[max_text_size];
	char file_name[max_text_size];
	int name_size;
	int extension_size;
	int text_size;
	char name[file_name_size];
	char extension[max_extension_size];
	int number;
	
} file ;



int create_file(file ** files, FILE ** input_p, int file_counter, FILE * output_p, int number_of_files){		

	char temporary[max_text_size];	
	
	files[file_counter] = (file*)malloc(sizeof(file));
	
	fscanf(*input_p,"%s",temporary);
		
	char c;
	int counter = 0;
	int i = 0;

	for(i=0; i<2; i++){
	
		if (!strcmp(temporary, "-n") || c == '-'){
		
			
			if (!strcmp(temporary, "-n")) fprintf(output_p,"%s ",temporary);
			else fprintf(output_p,"-n ");

			
			fscanf(*input_p,"%s",temporary);
			if(!strcmp(temporary, "-t")){
				fprintf(output_p,"\nCreate -n command has no name");
				while( c != '\n'){
					c = getc(*input_p);
				}
				
				return 1;
			}
			
			
			char delim[] = ".";
			char *ptr = strtok(temporary, delim);
			strcpy(files[file_counter]->name, ptr);				
			fprintf(output_p, "%s.",files[file_counter]->name);
			int k;
			for(k = 0; files[file_counter]->name[k] !='\0';k++){}
			files[file_counter]->name_size = k;
				
			ptr = strtok(NULL, delim);		
			strcpy(files[file_counter]->extension,ptr);
			fprintf(output_p,"%s ",files[file_counter]->extension);
			for(k = 0; files[file_counter]->extension[k] !='\0';k++){}
			files[file_counter]->extension_size = k;
			
			if (i == 0) {
				fscanf(*input_p,"%s",temporary);
		
			}
			i++;
			
		
			files[file_counter]->name[files[file_counter]->name_size] = '\0';
			files[file_counter]->extension[files[file_counter]->extension_size] = '\0';
		}

		if (!strcmp(temporary, "-t")){
			
			fprintf(output_p,"%s ",temporary);
			
			c = getc(*input_p);
			c = getc(*input_p);

			counter = 0;
			while(c != '\n' && c != '-'){
				
				files[file_counter]->text[counter] = c;
 				counter++ ;
 				c = getc(*input_p);	
 				if(c == ' '){
 					c = getc(*input_p);	
 					if (!(c != '\n' && c != '-')){
 						files[file_counter]->text[counter] = '\0';

					}
					else{
						files[file_counter]->text[counter] = ' ';
						counter++;
						files[file_counter]->text[counter] = c;
						
					}
				}
				else if(c == '\n'){
					files[file_counter]->text[counter] = '\0';
				}
				

			}
			if(counter == 0 && (c == '-' || c == '\n')){
				files[file_counter]->text[0] = '\0';
			}
			
			
			files[file_counter]->text_size = counter;
			fprintf(output_p,"%s ",files[file_counter]->text);
			if (i == 0)fscanf(*input_p,"%s",temporary);
		
		}
		if(strcmp(temporary, "-n") && strcmp(temporary, "-t") && c != '-'){
			fprintf(output_p,"\nCreate command parameter error");
			while( c != '\n'){
				c = getc(*input_p);
			}
			return 1;
		}
	}
	
	int s = 0, s1 = 0;
	for(s =0; s < files[file_counter]->name_size ; s++){
		if ((files[file_counter]->name)[s] == '\0'){
			break;
		}
		(files[file_counter]->file_name)[s] = (files[file_counter]->name)[s];
		
	}
	for(s1 = 0; s< (files[file_counter]->name_size + files[file_counter]->extension_size); s++){
		(files[file_counter]->file_name)[s] = (files[file_counter]->extension)[s1];
		s1++;
	}
		
	files[file_counter]->number = number_of_files + 1;
	fprintf(output_p,"\n");
	return 0;

}


int delete_file(file ** files, FILE ** input_p, int *file_counter, FILE * output_p){
	
	char temporary[max_text_size];	
	
	int found = 0;
	
	fscanf(*input_p,"%s",temporary);
	
	if (!strcmp(temporary, "-n")){
		fprintf(output_p,"-n ");
		
		fscanf(*input_p,"%s",temporary);
		
		
		fprintf(output_p,"%s\n",temporary);
		char delim[] = ".";
		char *ptr = strtok(temporary, delim);
		char *ptr2 = strtok(NULL, delim);
		int i;
		for(i=0; i<*file_counter; i++){
	
			if(strcmp(files[i]->name,ptr) == 0){
									
					if(!strcmp(files[i]->extension,ptr2)){
						free(files[i]);		
						for(;i<*file_counter; i++){
							files[i] = files[i+1];
							
						}
						*file_counter = *file_counter -1;
						i = *file_counter;
						found = 1;
					}
				
			}
					
					
		}

	}
	else {
		fprintf(output_p,"Delete command error\n");
		return 1;
	}
	
	if(found == 0){
		
		fprintf(output_p,"There is no such file\n");
		return 1;
	}
	
	return 0;
}

int print_a_e_c(file ** files, FILE ** input_p, int file_counter, char* command, FILE * output_p){
	
	char temporary[max_text_size];	
	

	
	int i;
	if(files){
		
		if(!strcmp(command, "-a")){
			fprintf(output_p,"-a\n");		
			
			for(i=0; i<file_counter; i++){
				fprintf(output_p,"Filename %d: %s.%s\n",files[i]->number,files[i]->name, files[i]->extension);
			}
		}
		else if(!strcmp(command, "-e")){
			fprintf(output_p,"-e ");
			
			fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s\n",temporary);
			for(i=0; i<file_counter; i++){
				if(!strcmp(files[i]->extension, temporary) && files[i]->name){
					if(files[i]->text_size < 1)	{
						fprintf(output_p,"Filename %d: %s\nText: Empty File\n",files[i]->number,files[i]->name);
					}
					else {
						fprintf(output_p,"Filename %d: %s\nText: %s\n",files[i]->number,files[i]->name,files[i]->text);	
					}	
				}		
			}	
		}
		else if(!strcmp(command, "-c")){
			fprintf(output_p,"-c\n");
			
			for(i=0; i<file_counter; i++){	
				if(files[i]->text_size < 1)	{
					fprintf(output_p,"Num: %d\nName: %s\nText: Empty File\n",files[i]->number,files[i]->name);
				}
				else{
					fprintf(output_p,"Num: %d\nName: %s\nText: %s\n",files[i]->number,files[i]->name,files[i]->text);
						
				}
					
	
				
			}
	
		}
		else{
			fprintf(output_p,"Invalid print command\n");
		}
		
		
	}
	else{
		printf("There is no data\n");
	}
	
	
	

	return 0;
}


int word_count(char * word, char * sentence){
	
    int i, j, found, count;
    int word_len, sentence_len;
    word_len = strlen(word);      
    sentence_len = strlen(sentence); 

    count = 0;
    for(i=0; i <= word_len-sentence_len; i++){
        found = 1;
        for(j=0; j<sentence_len; j++){
            if(word[i + j] != sentence[j]){
                found = 0;
                break;
            }
        }

        if(found == 1){
            count++;
        }
    }

    return count;
}





int print_n(file ** files, FILE ** input_p, int file_counter, FILE * output_p){
	
	char temporary[max_text_size];
	
	fprintf(output_p,"-n ");
	fscanf(*input_p,"%s",temporary);
	fprintf(output_p,"%s ",temporary);
	
	int found = 0;

	
	char delim[] = ".";
	char *ptr = strtok(temporary, delim);
	char *ptr2 = strtok(NULL, delim);
	int i;
	for(i=0; i<file_counter; i++){
	
		if(strcmp(files[i]->name, ptr) == 0){
			
			if(!strcmp(files[i]->extension, ptr2)){
				
				
					fscanf(*input_p,"%s",temporary);
					
				if(!strcmp(temporary, "-t")){
					fprintf(output_p,"-t\n");
					if(files[i]->text_size < 1) fprintf(output_p,"Text: Empty File\n");
					else {
						fprintf(output_p,"Text: %s\n",files[i]->text);
					}
				}
				
				else if(!strcmp(temporary, "-cs")){			
					int a, cs = 0;
					fprintf(output_p,"-cs\n");
					for(a = 0;a<sizeof(files[i]->text); a++){			
						if((files[i]->text[a] == '.')|| (files[i]->text[a] == '!')||(files[i]->text[a] == '?')){	
							cs++;
						}		
					}
						fprintf(output_p,"Number Of Sentences : %d\n",cs);
				}
				else if(!strcmp(temporary, "-cw")){
					
					fscanf(*input_p,"%s",temporary);
					fprintf(output_p,"-cw %s\n",temporary);
					fprintf(output_p,"Text: %s\n",files[i]->text);
					int count = word_count(files[i]->text, temporary);
					fprintf(output_p,"Number Of Occurrence of \"%s\" : %d\n", temporary, count);
				}
					
				found = 1;
				
			
			}
					
		}		
	}	
	
	if(found == 0){
		fprintf(output_p,"There is no such file\n");
	}

	return 0;
}



int remove_text(file ** files, FILE ** input_p, int file_counter, FILE * output_p){
	
	char temporary[max_text_size];
	fscanf(*input_p,"%s",temporary);
	
	int found = 0;
	
	if(!strcmp(temporary, "-n")){
		
		fprintf(output_p,"%s ", temporary);
		fscanf(*input_p,"%s",temporary);
		fprintf(output_p,"%s ", temporary);
		
		char delim[] = ".";
		char *ptr = strtok(temporary, delim);
		char *ptr2 = strtok(NULL, delim);	
		int i;
		for(i=0; i<file_counter; i++){
	
			if(strcmp(files[i]->name, ptr) == 0){
			

				if(!strcmp(files[i]->extension, ptr2)){
					
					fscanf(*input_p,"%s",temporary);
					fprintf(output_p,"%s ", temporary);
					
					if(!strcmp(temporary,"-s")){
						
						int index, length, a;
						fscanf(*input_p,"%s",temporary);
						index = atoi(temporary);
						fprintf(output_p,"%d ", index);
						fscanf(*input_p,"%s",temporary);
						
						if(!strcmp(temporary,"-l")){
							fprintf(output_p,"%s ", temporary);
							fscanf(*input_p,"%s",temporary);
							length = atoi(temporary);
							fprintf(output_p,"%d\n", length);
							
							if((index + length ) > files[i]->text_size){
								fprintf(output_p,"Length is too much for this text\n");
							}
							else{
								for(a=0; a<files[i]->text_size; a++){
									files[i]->text[index+a]= files[i]->text[index+a+length];
								}
								files[i]->text[index+a] = '\0';
								files[i]->text_size = files[i]->text_size - length;
							
							}
								
						}

							
					
					}
					found = 1;
				}
			}
		}
	}
	else {
		fprintf(output_p,"Invalid remove command\n");
	}
	
	if(found == 0){
		fprintf(output_p,"There is no such file\n");
	}
	
	return 0;
}

int append_text(file ** files, FILE ** input_p, int file_counter, FILE * output_p){
	
	char temporary[max_text_size];
	char buffer[max_text_size];	
	char c = '\0';
	fscanf(*input_p,"%s",temporary);
	int found = 0;
	int count_of_file;
	int counter = 0;
	int a = 0;
	for(a=0; a<2; a++){
	
		if (!strcmp(temporary, "-n") || c == '-'){
		
			
			if (!strcmp(temporary, "-n")) fprintf(output_p,"%s ",temporary);
			else fprintf(output_p,"-n ");
			
			fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s ", temporary);
		
			char delim[] = ".";
			char *ptr = strtok(temporary, delim);
			char *ptr2 = strtok(NULL, delim);	
			int i;
			for(i=0; i<file_counter; i++){
	
				if(strcmp(files[i]->name, ptr) == 0){
			

					if(!strcmp(files[i]->extension, ptr2)){
					
						
						count_of_file = i;
						found = 1;
							
					}
				}		
			}			
			if (a == 0) fscanf(*input_p,"%s",temporary);	
			a++;
			
		}
		if(!strcmp(temporary, "-t")){	
		
			fprintf(output_p,"%s ",temporary);	
			c = getc(*input_p);
			c = getc(*input_p);
			
			
			while(c != '\n' && c != '-'){
				
		
				buffer[counter] = c;
 				counter++ ;
 				c = getc(*input_p);	
				if(c == ' '){
 					c = getc(*input_p);	
 					if (!(c != '\n' && c != '-')){
 						buffer[counter] = '\0';
					}
					else{
						buffer[counter] = ' ';
						counter++;
						buffer[counter] = c;
						
					}
				}
				else if(c == '\n'){
					buffer[counter] = '\0';
				}
						
			}			
			if (a == 0)fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s ",buffer);
			
		}
	}
	
	if(found == 0){
		fprintf(output_p,"\nThere is no such file\n");
		return 0;
	}
	
	fprintf(output_p,"\n");
	int b;
	
	for(b=0; b<strlen(buffer);b++){
		
		files[count_of_file]->text[files[count_of_file]->text_size + b ] = buffer[b];
	}
		files[count_of_file]->text[files[count_of_file]->text_size + b] = '\0';
		
		files[count_of_file]->text_size += counter;
	
		

	return 0;
}





int replace_word_helper(file ** files, char * old_word, char * new_word, int file_number, FILE * output_p){
	

	int i, j, k, l, found, count;
    int old_word_len, sentence_len, new_word_len;
    old_word_len = strlen(old_word);      
    sentence_len = strlen(files[file_number]->text); 
	new_word_len = strlen(new_word);

	
    count = 0;
    for(i=0; i <= sentence_len-old_word_len; i++){
        found = 1;
        for(j=0; j<old_word_len; j++){
            if(files[file_number]->text[i + j] != old_word[j]){
                found = 0;
                break;
            }
        }

        if(found == 1){
        	if(new_word_len <= old_word_len){	
 
        		for(k=0; k<new_word_len; k++){
        	
					files[file_number]->text[i + j - old_word_len + k] = new_word[k];

				}
			
				for(l=0; l<=sentence_len ; l++){
					if(files[file_number]->text[i + j - old_word_len + k + l ])
						files[file_number]->text[i + j - old_word_len + k + l] = files[file_number]->text[i + j - old_word_len + k + l + (old_word_len-new_word_len)];
				}
				
			}
			else{
				
				int last = i+j;			
        		for(k=0; k < new_word_len ; k++){
        
					files[file_number]->text[i + j - old_word_len + k] = new_word[k];
					
					if(k >= (old_word_len-1)){
						
						for( l = sentence_len-1; l > last-1; l--){
							files[file_number]->text[ l + 1 ] = files[file_number]->text[l];
						}
						last++;
						sentence_len ++;												
					}				
				}
				
				for( l = last; l <sentence_len; l++){
					files[file_number]->text[ l ] = files[file_number]->text[l+1];
				}
				last--;
				sentence_len --;			
			}     	
            count++;
        }
        
        
        
        
        
    }
    
    if(count == 0){
        	fprintf(output_p,"There is no such word\n");
		}
	else {
		files[file_number]->text_size += new_word_len - old_word_len;
	}
    return count;
}







int replace_word(file ** files, FILE ** input_p, int file_counter, FILE * output_p){
	
	char temporary[max_text_size];	
	char old_word[max_text_size];	
	char new_word[max_text_size];
	
	int found = 0;
	int file_number;
	
	int x;
	for(x=0; x<3; x++){
		
		fscanf(*input_p,"%s",temporary);
		
		if(!strcmp(temporary, "-n")){
			fprintf(output_p,"%s ",temporary);
			fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s ",temporary);
			char delim[] = ".";
			char *ptr = strtok(temporary, delim);
			char *ptr2 = strtok(NULL, delim);
			int i;
			for(i=0; i<file_counter; i++){
	
				if(strcmp(files[i]->name,ptr) == 0){
						
	
						if(!strcmp(files[i]->extension,ptr2)){
							found = 1;
							file_number = i;
						}
				}
			}
		}
		else if(!strcmp(temporary, "-ow")){
			fprintf(output_p,"%s ",temporary);
			fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s ",temporary);
			strcpy(old_word, temporary);
		}
		else if(!strcmp(temporary, "-nw")){
			fprintf(output_p,"%s ",temporary);
			fscanf(*input_p,"%s",temporary);
			fprintf(output_p,"%s ",temporary);
			strcpy(new_word, temporary);
		}
		
	}
	fprintf(output_p,"\n");
	if(found == 1){
		replace_word_helper(files, old_word, new_word, file_number, output_p);	
	}
	else{
		fprintf(output_p,"There is no such file\n");
	}
	return 0;
}






int main(int argc, char *argv[]) {
	
	
	FILE * output_p = fopen("output.txt", "w");
	
	char command[max_command_size];
	
	if(!argv[1]){
		fprintf(output_p,"You didn\'t enter the argument");
		return 0;
	}
	
	FILE * input_p = fopen(argv[1], "r");
	
	int number_of_files = 0;
	int file_counter = 0;
	int error_controller = 0;

	file ** files = (file**)malloc(sizeof(file*));

	while(fscanf(input_p,"%s",command) == 1 ){
	
		if (!strcmp(command, "create")){
			
			fprintf(output_p,"%s ",command);
			
			files = realloc(files,(file_counter + 1)*sizeof(file*));			
			
			error_controller = create_file(files, &input_p, file_counter, output_p, number_of_files);
			
			number_of_files++;
			
			if(error_controller == 0){
				file_counter ++;
			}
		}
		else if (!strcmp(command, "delete")){
			fprintf(output_p,"%s ",command);
			error_controller =  delete_file(files, &input_p, &file_counter, output_p);
			if(error_controller == 0){
				files = realloc(files,(file_counter)*sizeof(file*));
			}
			
		}
		else if (!strcmp(command, "remove")){
			fprintf(output_p,"%s ",command);
			remove_text(files, &input_p, file_counter, output_p);
		}
		else if (!strcmp(command, "append")){
			fprintf(output_p,"%s ",command);
			append_text(files, &input_p, file_counter, output_p);
		}
		else if (!strcmp(command, "replace")){
			fprintf(output_p,"%s ",command);
			replace_word(files, &input_p, file_counter, output_p);
		}
		else if (!strcmp(command, "print")){
			
			fprintf(output_p,"%s ",command);
			fscanf(input_p,"%s",command);
			
			if(!strcmp(command, "-a") || !strcmp(command, "-e") || !strcmp(command, "-c")){
				print_a_e_c(files, &input_p, file_counter, command, output_p);
				
				
			}
			else if(!strcmp(command, "-n")){
				print_n(files, &input_p, file_counter, output_p);
			}
			else {
				fprintf(output_p,"Invalid print command\n");
			}
					
	
		}
				
	
	}
	
	fclose(output_p);
	fclose(input_p);


	int i;
	for(i=0; i<file_counter; i++){
		free(files[i]);
	}
	free(files);
	


	return 0;
}



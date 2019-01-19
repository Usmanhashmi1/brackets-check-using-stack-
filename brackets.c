#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


FILE *start, *advance; // Global variables for file handling to avoid confusion for other methods (For brackets section)
char word[100];        // characters to be stored in. (For brackets Section)



//*****************************/*Structures to be used further */***********************************************
					
					
struct StackNode {              // structure for making a node for data to get from text file
	char data;
	struct StackNode* node;
};

struct StackNode* newNode(char c){   // Making a stack from data which are relevant for us here it is : Brackets 
	struct StackNode* root = (struct StackNode*) malloc(sizeof(struct StackNode));
	(*root).data = c;
	(*root).node = NULL;
	return root;
}


//**************************Functions below all are used for brackets balance start from here********************


int isEmpty(struct StackNode *root){    // To check weather stack is empty or not 
	return !root;
}

void push(struct StackNode** root, char c){  // To PUSH a bracket in stack which is called from analyzed();
	struct StackNode* node = newNode(c);
	(*node).node = *root;
	*root = node;
}

int pop(struct StackNode** root){        	// to POP a bracket from stack which is called from analyzed();
	if(isEmpty(*root))
	{
		return 0;
	}
	struct StackNode* temporary = *root;
	*root = (*root)->node;
	free(temporary);
	return 1;
}

char top(struct StackNode* root){         // to check top one 
	if(isEmpty(root))
	{
		return 'x';
	}
	return (*root).data;
}

void toaccept(){      // for file handling 
	long startWord = ftell(start);
	long endWord = ftell(advance);

	fread(word, endWord - startWord, 1, start);

	fseek(start, endWord, SEEK_SET);
}

void torefuse(){
	fseek(advance, ftell(start), SEEK_SET);
}

char getcharacter(){
	return fgetc(advance);
}

int isfeof(){                    // making a our function for End of File so that we can get a character at a time to check accordingly
	char c = getcharacter();
	torefuse();
	return c == EOF;
}


int analyzed(struct StackNode** root){    // The major methods which is actually presence of brackets and manipulating stack according it's order
	int i = 0;
	char c = getcharacter();
	while(c != ' ' && c != '\t' && c != '\n' && c != EOF)
	{
		if( c == '(' || c == '[' || c == '{')   // Same logic used provided in task manual 
		{
			push(root, c);
			//printf("Push: %c\n", c);          //These print statements are only for checking working of code can be removed 
												//if needed won't affected the code also there are commented 
													
			return 0;
		}
		else
		{
			if(c == ')'|| c == ']'|| c== '}')
			{
				if(top(*root) == '{' && c == '}')
				{
					pop(root);
					return 0;
				}
				else if(top(*root) == '[' && c == ']')
				{
					pop(root);
					
					return 0;
				}
				else if(top(*root) == '(' && c== ')')
				{
					pop(root);

					return 0;
				}
				else
				{
					if(i > 0)
					{
					//	printf("There is an error with the brackets.\n");
						return -1;
					}
					//printf("There is an error with the brackets.\n");
					return -1;
				}
			}
		}
		c = getcharacter();
		i++;
	}
	return 0;
}



int main(int argc, char **arg){

	
	//*******************Main function code for checking Brackets***************
	struct StackNode* root = NULL;         
	int x = 0;
	start = fopen("text.txt", "r");
	advance = fopen("text.txt", "r");
	while(!isfeof())
	{
		x = analyzed(&root);
		if(x == -1)
		{
			break;
		}
		int i=0;
		while(i<100)
		{
			toaccept();
			word[i] = (char)0;
			i++;
		}
	}
	if(!isEmpty(root) || x == -1)
	{
		printf("Oops Not balanced \n");
	}
	else
	{
		printf("\nParentheses are Balanced........ hope you don't stuck in logical error :)''\n\n\n");
	}
	fclose(start);
	fclose(advance);

	
    return 0;
	
}


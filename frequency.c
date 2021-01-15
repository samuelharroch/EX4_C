#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean;

typedef struct Node {
char letter;
int numOfWord;
struct Node* children[NUM_LETTERS];
int pos;

} Node;


Node* createNode(char letter){
    
    //create new Node
    Node* newNode= (Node*)malloc(sizeof(Node));
    if(newNode==NULL){
        printf("failed to allocate memory, exit from the program");
        exit(1);       
    }
    
    newNode->letter=letter;
    newNode->numOfWord=0;
    
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        newNode->children[i]=NULL;
    }
    
    return newNode;

}


void putWord(Node*root,char *str){
    
    
    char* ptr= str;
    char letter;
    int i=-1;

    Node** current=&root;
    
    while (*ptr )
    {
        letter= *ptr;
        if((*current)->children[letter-'a'] == NULL){
            
            (*current)->children[letter-'a']= createNode(letter);
            (*current)->pos=i;
            
        }
        
        current=&((*current)->children[letter-'a']);
        i++;
        ptr++;
    }
    (*current)->numOfWord++;
    (*current)->pos=i;
    
}


void printTrie(Node* root, char* str){
    if(root==NULL){
       return;
    }
    str[root->pos]=root->letter;
   
    if (root->numOfWord > 0)
    {
       str[root->pos+1]=0;
        printf("%s %d\n", str, root->numOfWord);
    }
    
    for (int i = 0; i < NUM_LETTERS; i++){

        printTrie(root->children[i], str);
       
    } 

}

void printTrie_r(Node* root, char* str){
    if(root==NULL){
        return;
    }
    str[root->pos] = root->letter;

    for (int i = NUM_LETTERS -1 ; i >=0 ; i--){
        printTrie_r(root->children[i], str);
        
    }
     if (root->numOfWord > 0){
            str[root->pos + 1] = 0;
            printf("%s %d\n", str, root->numOfWord);
        }

}

void freeTrie(Node* root){
    if(root == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){
        freeTrie(root->children[i]);
    }
    free(root);
}

int main(int argc, char const *argv[])
{
    char* str= str=(char*)malloc(1);
    if(str==NULL){
        printf("failed to allocate memory, exit from the program");
        exit(1);       
    }

    int i =0;
    Node* root= createNode(0);
    
    while(1)
    {
        char c = getchar();
        if(isspace(c) || c == EOF){
            str = realloc(str, i+1);
            str[i]=0;
            if (strlen(str))
            {   
              putWord(root, str);
            }
            i=0;
            if(c == EOF) break;
        }
        else if(isalpha(c)){
            c = tolower(c);
            str = realloc(str, i+1);
            if(str==NULL){
                printf("failed to allocate memory, exit from the program");
                exit(1);       
            }
            str[i]= c;
            i++;
        }
    }

    
    if(argc == 1)
        printTrie(root, str);
    else if(argc == 2 && strcmp(argv[1],"r")==0)
        printTrie_r(root, str);

    free(str);
    freeTrie(root);

    return 0;
}
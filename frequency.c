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

    Node** current=&root;
    
    while (*ptr!= '\0' )
    {
        letter= *ptr;
        if((*current)->children[letter-'a'] == NULL){
            
            (*current)->children[letter-'a']= createNode(letter);
            
        }
        
        current=&((*current)->children[letter-'a']);

        ptr++;
    }
    (*current)->numOfWord++;
    
}


void printTrie(Node* root, char* str, int pos){
    if(root==NULL){
       return;
    }
    //  str=realloc(str,strlen(str)+1);
    //  if(str==NULL){
    //     printf("failed to allocate memory, exit from the program");
    //     exit(1);       
    // }
    *(str+ strlen(str))=root->letter;
    *(str+ strlen(str))='\0';
    
    if (root->numOfWord > 0)
    {
        printf("%s %d\n", str, root->numOfWord);
    }
    
    for (int i = 0; i < NUM_LETTERS; i++){
        pos=i;
        printTrie(root->children[i], str,pos);
        //  if (pos==NUM_LETTERS-1)
        // {
        //     *(str+ strlen(str)-1)='\0';
        //     //str=realloc(str,strlen(str)-1);
        // }
    } 

}

void printTrie_r(Node* root, char* str, int pos){
    if(root==NULL){
        return;
    }
    str=realloc(str,strlen(str)+1);
    if(str==NULL){
        printf("failed to allocate memory, exit from the program");
        exit(1);       
    }
    *(str+ strlen(str))=root->letter;
    
    for (int i = NUM_LETTERS -1 ; i >=0 ; i--){
        pos=i;
        printTrie_r(root->children[i], str,pos);
        
    }
     if (root->numOfWord > 0){
             printf("%s %d\n", str, root->numOfWord);
       
        }
     if (pos==0)
        {
            *(str+ strlen(str)-1)='\0';
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
    Node* root= createNode(*str);
    
    while(1)
    {
        char c = getchar();
        if(isspace(c) || c == EOF){
            str = realloc(str, i+1);
            str[i]=0;
            if (strlen(str))
            {
              printf("str %s\n",str);   
              putWord(root, str);
            }
            i=0;
            // free(str);
            // str=(char*)malloc(0);
            // if(str==NULL){
            //     printf("failed to allocate memory, exit from the program");
            //      exit(1);       
            // }
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

    printf("last str %s\n",str);
    // str=(char*)malloc(0);
    // str[0]=0;

    if(argc == 1)
        printTrie(root, str,0);
    else if(argc == 2 && strcmp(argv[1],"r")==0)
        printTrie_r(root, str,0);

    free(str);
    freeTrie(root);

    return 0;
}
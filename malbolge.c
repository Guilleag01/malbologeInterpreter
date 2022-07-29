#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct TernaryNumber10{
    int number[10];
} TernaryNumber10;

void initilizeMemory();
TernaryNumber10 decToTernary(int dec);
int ternaryToDec(TernaryNumber10 ternary);
void printTernary(TernaryNumber10 ternary, char mode);
void loadMemory(char * filename);
void run();
void incrementC();
void incrementD();
void jmp();
void out();
void in();
void rotr();
void dValToD();
void crz();
TernaryNumber10 crazyOperation(TernaryNumber10 t1, TernaryNumber10 t2);
void cypher(bool lastIsJump);
void printBase9(TernaryNumber10 t);

TernaryNumber10 * memory;
TernaryNumber10 a = {{0,0,0,0,0,0,0,0,0,0}};
TernaryNumber10 c = {{0,0,0,0,0,0,0,0,0,0}};
TernaryNumber10 d = {{0,0,0,0,0,0,0,0,0,0}};

bool stopExecution = false;

int main(){
    initilizeMemory();
    printf("File to execute: ");
    char filename[20];
    scanf("%s", filename);
    loadMemory(filename);
    run();
}

void initilizeMemory(){
    memory = (TernaryNumber10 *)malloc(sizeof(TernaryNumber10) * 59049); // 3^10 direcciones de memoria
}

TernaryNumber10 decToTernary(int dec){
    TernaryNumber10 ternary;
    for (int i = 9; i >= 0; i--){
        ternary.number[i] = dec % 3;
        dec /= 3;
    }
    return ternary;
}

int ternaryToDec(TernaryNumber10 ternary){
    int value = 0;
    for (int i = 9; i >= 0; i--){
        value += ternary.number[i] * pow(3,9-i);
    }
    return value;
}

void printTernary(TernaryNumber10 ternary, char mode){
    if (mode == 'd'){
        printf("%d\n", ternaryToDec(ternary));
    }else if (mode == 't'){
        for (int i = 0; i < 10; i++){
            printf("%d", ternary.number[i]);
        }
        printf("\n");
    }else if(mode == 'n'){
        printBase9(ternary);
        printf("\n");
    }
}

void loadMemory(char * filename){
    FILE * file;
    
    file = fopen(filename, "rb");
    
    int pos = 0;
    if (file == NULL){
        printf("File can't be opened\n");
    }else{
        char ch;
        ch = fgetc(file);
        do{ 
            if(ch != ' ' && ch != '\t' && ch != '\n'){
                if(((int)ch) < 33 || ((int)ch) > 126){
                    printf("Eror while loading program.\nIllegal symbol at: %d\n", pos);
                    fclose(file);
                    exit(0);
                }
                memory[pos] = decToTernary((int)ch);
                pos++;
            }         
            ch = fgetc(file);   
        }while(ch != EOF);
    }

    fclose(file);

    for (int i = pos; i < 59049; i++){
        memory[i] = crazyOperation(memory[i - 2], memory[i - 1]);
    }
}

void run(){
    while(!stopExecution){
        
        int decC = ternaryToDec(c);
        int decD = ternaryToDec(d);
        
        int operation = (ternaryToDec(memory[decC]) + decC) % 94;
        bool lastIsJump = false;
        
        switch (operation){
        case 4:
            jmp();
            lastIsJump = true;
            break;
        
        case 5:
            out();
            break;
        
        case 23:
            in();
            break;
        
        case 39:
            rotr();
            break;
        
        case 40:
            dValToD();
            break;
        
        case 62:
            crz();
            break;

        case 68:
            break;

        case 81:
            stopExecution = true;
            break;
        
        default:
            break;
        }
        
        cypher(false);
        incrementC();
        incrementD();
    }
}

void incrementC(){
    c = decToTernary((ternaryToDec(c) + 1) % 59049);
}

void incrementD(){
    d = decToTernary((ternaryToDec(d) + 1) % 59049);
}

// +------------------+
// |    OPERATIONS    |
// +------------------+

void jmp(){
    c = memory[ternaryToDec(d)];
}

void out(){
    //printf("\n--%c--\n\n", ternaryToDec(a));
    printf("%c", ternaryToDec(a));
    fflush(stdout);
}

void in(){
    a = decToTernary((int)getchar());
}

void rotr(){
    TernaryNumber10 t = memory[ternaryToDec(d)];
    int aux = t.number[9];
    for (int i = 9; i > 0; i--){
        t.number[i] = t.number[i - 1];
    }
    t.number[0] = aux;
    memory[ternaryToDec(d)] = t;
    a = t;
}

void dValToD(){
    d = memory[ternaryToDec(d)];
}

void crz(){
    TernaryNumber10 result = crazyOperation(memory[ternaryToDec(d)], a);
    memory[ternaryToDec(d)] = result;
    a = result;
}

TernaryNumber10 crazyOperation(TernaryNumber10 t1, TernaryNumber10 t2){
    TernaryNumber10 result;
    int operationTable[3][3] = {{1, 0, 0},
                                {1, 0, 2},
                                {2, 2, 1}};
    for (int i = 0; i < 10; i++){
        result.number[i] = operationTable[t1.number[i]][t2.number[i]];
    }
    return result;
}

void cypher(bool lastIsJump){
    int result = ternaryToDec(memory[ternaryToDec(c)]) % 94;
    char * cypherTable = "9m<.TVac`uY*MK'X~xDl}REokN:#?G\"i@5z]&gqtyfr$(we4{WP)H-Zn,[%\\3dL+Q;>U!pJS72FhOA1CB6v^=I_0/8|jsb";
    memory[ternaryToDec(c)] = decToTernary((int)cypherTable[result]);
}

void printBase9(TernaryNumber10 t){
    for (int i = 0; i < 5; i++){
        printf("%d", t.number[i*2]*3 + t.number[i*2+1]);
    }
}

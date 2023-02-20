#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define cX 0
#define cY 1

#define BLOCK 0
#define CLOSED 1
#define NOPASSED 2
#define PASSED 3

int randef(int min, int max){
    return (rand()%(max-min+1))+min;
}

void printdisp(char* input,int ylength,int xlength){
    for(int count1=0;count1<ylength;count1++){
        for(int count2=0;count2<xlength;count2++){
            printf("%c",*(input+xlength*count1+count2));
        }
        printf("\n");
    }
}

void fullFill(char* input,int size,char select){
    for(int count=0;count<size;count++){
        *(input+count)=select;
    }
}

void frame(char* input,int number,char select){
    for(int count=0;count<number;count++){
        *(input+number*0+count)=select;
    }
    for(int count=1;count<number-1;count++){
        *(input+number*count+0)='@';
        *(input+number*count+(number-1))=select;
    }
    for(int count=0;count<number;count++){
        *(input+number*(number-1)+count)=select;
    }
}

void place(char* input,int number,int x,int y,char select){
    if((x > number)||(y > number)) {
        puts("place error");
        return;
    }
    *(input+number*(y-1)+(x-1))=select;
}

char search(char* input,int number,int x,int y){
    return *(input+number*(y-1)+(x-1));
}

void gridrandplace(char* input,int number){
    int x, y;
    x=2*randef(1,(number-3)/2)+1;
    y=2*randef(1,(number-3)/2);
    if(randef(0,1)==0){
        place(input,number,x,y,' ');
    }
    else{
        place(input,number,y,x,' ');
    }
}

void line(char* input,int number,int x,int y,int direction,int length,char select){
    if((x > number)||(y > number)) return;
    switch(direction){
        case 1:
        if(y < length) return;
        for(int count=0;count<length;count++) *(input+number*(y-1-count)+(x-1))=select;
        break;

        case 2:                
        if(number-y+1 < length) return;
        for(int count=0;count<length;count++) *(input+number*(y-1+count)+(x-1))=select;
        break;

        case 3:
        if(number-x+1 < length) return;
        for(int count=0;count<length;count++) *(input+number*(y-1)+(x-1)+count)=select;
        break;

        case 4:
        if(x < length) return;
        for(int count=0;count<length;count++) *(input+number*(y-1)+(x-1)-count)=select;
        break;

        default:
        return;
    }
}

int start(char* input,int number,int coordinate[]){
    int x=2*randef(1,(number-3)/2);
    coordinate[cX]=x;
    coordinate[cY]=2;
    place(input,number,x,1,' ');
}

void firstSnake(char* input,char* event,int number,int coordinate[]){
    int direction = DOWN;
    int dirList[4] ={0,0,0,0};
    int dirListLeng = 0;

    while(1){
        if(search(event,number,coordinate[cX],coordinate[cY]) == PASSED){
            printf("break end\n");
            break;
        }

        if(search(input,number,coordinate[cX],coordinate[cY]-1) != ' '){//up
            if(coordinate[cY]-1 != 1){
                dirList[dirListLeng] = UP;
                dirListLeng++;
                //printf("upOk\n");
            } 
        }
        if(search(input,number,coordinate[cX],coordinate[cY]+1) != ' '){//down
            if(coordinate[cY]+1 != number){
                dirList[dirListLeng] = DOWN;
                dirListLeng++;
                //printf("downOk\n");
            } 
        }
        if(search(input,number,coordinate[cX]+1,coordinate[cY]) != ' '){//right
            if(coordinate[cX]+1 != number){
                dirList[dirListLeng] = RIGHT;
                dirListLeng++;
                //printf("rightOk\n");
            }
        } 
        if(search(input,number,coordinate[cX]-1,coordinate[cY]) != ' '){//left
            if(coordinate[cX]-1 != 1){
                dirList[dirListLeng] = LEFT;
                dirListLeng++;
                //printf("leftOk\n");
            }
        } 
        if(dirListLeng == 0){
            printf("end\n");
            break;
        }

        direction = dirList[randef(0,dirListLeng-1)];

        switch(direction){
            case UP:
            place(event,number,coordinate[cX],coordinate[cY],PASSED);
            place(input,number,coordinate[cX],coordinate[cY]-1,' ');
            coordinate[cY]-=2;
            break;

            case DOWN:
            place(event,number,coordinate[cX],coordinate[cY],PASSED);
            place(input,number,coordinate[cX],coordinate[cY]+1,' ');
            coordinate[cY]+=2;
            break;

            case RIGHT:
            place(event,number,coordinate[cX],coordinate[cY],PASSED);
            place(input,number,coordinate[cX]+1,coordinate[cY],' ');
            coordinate[cX]+=2;
            break;

            case LEFT:
            place(event,number,coordinate[cX],coordinate[cY],PASSED);
            place(input,number,coordinate[cX]-1,coordinate[cY],' ');
            coordinate[cX]-=2;
            break;
            
            default:
            puts("snake error");
        }
        //printf("(%d,%d) %d\n",coordinate[cX],coordinate[cY],direction);
        dirListLeng = 0;
    }
}

void snake(char* input,char* event,int number,int coordinate[]){
    int direction = DOWN;
    int dirList[4] ={0,0,0,0};
    int dirListLeng = 0;
    int orderLeng = 0,orderListLeng = 0;
    int* orders;
    orders = (int*)malloc(sizeof(int)*(number/2)*(number/2));
    if(orders == NULL){
        printf("malloc error\n");
        return;
    }
    int* orderList;
    orderList = (int*)malloc(sizeof(int)*(number/2)*(number/2)*2);
    if(orderList == NULL){
        printf("malloc error\n");
        return;
    }

        while(1){
            char searchReturn = search(event,number,coordinate[cX],coordinate[cY]);
            if(searchReturn == NOPASSED || searchReturn == PASSED){
                printf("break end\n");
                break;
            }

            if(search(input,number,coordinate[cX],coordinate[cY]-1) != ' '){//up
                if(coordinate[cY]-1 != 1){
                    dirList[dirListLeng] = UP;
                    dirListLeng++;
                    //printf("upOk\n");
                } 
            }
            if(search(input,number,coordinate[cX],coordinate[cY]+1) != ' '){//down
                if(coordinate[cY]+1 != number){
                    dirList[dirListLeng] = DOWN;
                    dirListLeng++;
                    //printf("downOk\n");
                } 
            }
            if(search(input,number,coordinate[cX]+1,coordinate[cY]) != ' '){//right
                if(coordinate[cX]+1 != number){
                    dirList[dirListLeng] = RIGHT;
                    dirListLeng++;
                    //printf("rightOk\n");
                }
            } 
            if(search(input,number,coordinate[cX]-1,coordinate[cY]) != ' '){//left
                if(coordinate[cX]-1 != 1){
                    dirList[dirListLeng] = LEFT;
                    dirListLeng++;
                    //printf("leftOk\n");
                }
            } 
            if(dirListLeng == 0){
                printf("end\n");
                break;
            }

            orders[orderLeng] = toOrder(number,coordinate);
            orderLeng++;
            if(dirListLeng >= 3){
                orderList[orderListLeng*2] = coordinate[cX];
                orderList[orderListLeng*2+1] = coordinate[cY];
                orderListLeng++;
            }

            direction = dirList[randef(0,dirListLeng-1)];

            switch(direction){
                case UP:
                place(event,number,coordinate[cX],coordinate[cY],NOPASSED);
                place(input,number,coordinate[cX],coordinate[cY]-1,' ');
                coordinate[cY]-=2;
                break;

                case DOWN:
                place(event,number,coordinate[cX],coordinate[cY],NOPASSED);
                place(input,number,coordinate[cX],coordinate[cY]+1,' ');
                coordinate[cY]+=2;
                break;

                case RIGHT:
                place(event,number,coordinate[cX],coordinate[cY],NOPASSED);
                place(input,number,coordinate[cX]+1,coordinate[cY],' ');
                coordinate[cX]+=2;
                break;

                case LEFT:
                place(event,number,coordinate[cX],coordinate[cY],NOPASSED);
                place(input,number,coordinate[cX]-1,coordinate[cY],' ');
                coordinate[cX]-=2;
                break;
                
                default:
                puts("snake error");
            }
            //printf("(%d,%d) %d\n",coordinate[cX],coordinate[cY],direction);
            dirListLeng = 0;
        }
        
    while(1){
        if(search(event,number,coordinate[cX],coordinate[cY])==PASSED){//snakeを終了させる時の処理
            for(int count=0;count<orderLeng+2;count++){
                *(event+orders[count]) = PASSED;
            }
            free(orders);
            free(orderList);
            break;
        }

        printdisp(input,number,number);
        printf("orlisl: %d\n",orderListLeng);
        for(int count=0;count<orderListLeng*2;count++){
            printf("%d, ",orderList[count]);
        }
        printf("\n");
        int randOrder = randef(1,orderListLeng);
        coordinate[cX] = orderList[2*(randOrder-1)];
        coordinate[cY] = orderList[2*(randOrder-1)+1];
        place(event,number,coordinate[cX],coordinate[cY],CLOSED);
        orderListLeng = 0;
        printf("(%d,%d)\n",coordinate[cX],coordinate[cY]);
        printf("snakkfasa end\n");
 
    }
    printf("snake end\n");
}

int scan(char* input,int size,char scan){
    int amount = 0;
    for(int count=0;count<size;count++){
        if(*(input+count) == scan){
            amount++;
        }
    }
    return amount;
}

void mazeSet(char* input,char* event,int number){
    int closed = scan(event,number*number,CLOSED);
    int coordinate[2];
    int length, count;

    while(closed>0){
        coordinate[cX] = 2;
        coordinate[cY] = 2;
        length=randef(1,closed);
        count = 1;

        while(1){
            if(search(event,number,coordinate[cX],coordinate[cY])==CLOSED){
                if(count==length) break;
                count++;
            }
            coordinate[cX] += 2;
            if(coordinate[cX] >= number){
                coordinate[cY] += 1;
                coordinate[cX] = 2;
            }
        }
        
        printf("length:%d (%d,%d) closed: %d\n",length,coordinate[cX],coordinate[cY],closed);
        snake(input,event,number,coordinate);
        closed = scan(event,number*number,CLOSED);
    }
}

int grid(char* input,int number,char select){
    for(int count=1;count<=number;count+=2){
        line(input,number,count,1,DOWN,number,select );
        line(input,number,1,count,RIGHT,number,select);
    }
}

int main(){
    srand((unsigned int)time(NULL));

    int number=1;
    int size;
    int coordinate[2];
    scanf("%d",&number);
    printf("%d\n",number);
    size=number*number;

    char* maze;
    maze = (char*)malloc(sizeof(char)*size);
    if(maze==NULL){
        printf("malloc error\n");
        return -1;
    }

    char* event;
    event = (char*)malloc(sizeof(char)*size);
    if(event==NULL){
        printf("malloc error\n");
        return -1;
    }

    fullFill(event,size,CLOSED);
    frame(event,number,BLOCK);
    grid(event,number,BLOCK);


    fullFill(maze,size,' ');
    frame(maze,number,'@');
    grid(maze,number,'@');
    start(maze,number,coordinate);

    firstSnake(maze,event,number,coordinate);
    mazeSet(maze,event,number);

    printdisp(maze,number,number);

    free(maze);
    free(event);
    return 0;   
}
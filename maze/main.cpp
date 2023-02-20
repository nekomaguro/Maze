#include"standard.h"
#include"game.h"
#include"random.h"

int main(){

    try{
        static char stdout_buf[BUFSIZ];
        if(setvbuf(stdout,stdout_buf,_IOFBF,sizeof(stdout_buf)) != 0){
            throw std::runtime_error("stream error");
        }
    }
    catch(std::runtime_error error){
        printf("%s\n",error.what());
        exit(EXIT_FAILURE);
    }
    catch(std::logic_error error){
        printf("%s\n",error.what());
        exit(EXIT_FAILURE);
    }


    Random random;

    Game newGame;
    
    return 0;
}


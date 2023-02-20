#include"standard.h"
#include"game.h"


Game::Game(){
    buf = new Buf(mazeNumber*2+2,mazeNumber+2);
    print = new Print;

    playingOption = new Option(5,15,19);
    playingOption->optionSet(RESTART+1,(char*)OptionRestart,OptionRestartX,4,4);
    playingOption->optionSet(RESET+1,(char*)OptionReset,OptionResetX,4,7);
    playingOption->optionSet(SETTING+1,(char*)OptionSetting,OptionSettingX,4,10);
    playingOption->optionSet(EXIT+1,(char*)OptionExit,OptionExitX,4,13);
    playingOption->optionSet(CANCEL+1,(char*)OptionClose,OptionCloseX,4,16);

    goalOption = new Option(4,37,19);
    goalOption->optionSet(RESTART+1,(char*)OptionRestart,OptionRestartX,10,12);
    goalOption->optionSet(RESET+1,(char*)OptionReset,OptionResetX,24,12);
    goalOption->optionSet(SETTING+1,(char*)OptionSetting,OptionSettingX,10,14);
    goalOption->optionSet(EXIT+1,(char*)OptionExit,OptionExitX,24,14);

    questions = (YNQuestion**)malloc(sizeof(YNQuestion*)*4);
    if(questions == NULL){
        throw std::runtime_error("malloc error");
    }

    questions[RESTART] = new YNQuestion(25,11,8,5);
    questions[RESTART]->stringSet((char*)OptionRestartText,OptionRestartTextX,4,4);

    questions[RESET] = new YNQuestion(23,11,8,5);
    questions[RESET]->stringSet((char*)OptionResetText,OptionResetTextX,4,4);

    questions[SETTING] = new YNQuestion(35,11,8,5);
    questions[SETTING]->stringSet((char*)OptionSettingText,OptionSettingTextX,4,4);

    questions[EXIT] = new YNQuestion(31,11,8,5);
    questions[EXIT]->stringSet((char*)OptionExitText,OptionExitTextX,4,4);

    state = State::Setting;

    while(1){
        switch(state){

            case State::Setting:
                setting();
                state = State::Maze;
                break;

            case State::Maze:
                gameStart();
                break;

            case State::End:
                return; 
        }
    }

}

Game::~Game(){
    delete buf;
    delete print;
}

void Game::setting(){
    char key;
    loopEnd = 0;
    length = 65;
    system("cls");

    print->printDisp((char*)SettingText,SettingTextX,SettingTextY);
    printf("%d  \n",length);
    printf("%s\n", SettingKeyText);
    fflush(stdout);

    while(loopEnd == 0){

        if(kbhit()){
            key = getch();
            Game::keySet(key);

            print->printDisp((char*)SettingText,SettingTextX,SettingTextY);
            printf("%d  \n",length);
            printf("%s\n", SettingKeyText);
            fflush(stdout);

            Sleep(10);
            while(kbhit()){
                getch();
            }

        }
    }
}

void Game::gameStart(){

    buf->fullFill('O');

    maze = new Maze(length);
    maze->createMaze();
    maze->rangeSet(mazeNumber*2,mazeNumber,mazeNumber*2/2+1,mazeNumber/2+1);

    player = new Player('@');
    player->setCodinat(maze->getStartX(),maze->getStartY());
    maze->rangeCodinatSet(maze->getStartX(),maze->getStartY());

    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
    buf->input(player->getCharacP(),OBJECT_SIZE,OBJECT_SIZE,player->getX() - (maze->getRangeX() - 1) + 1,player->getY() - (maze->getRangeY()- 1) + 1);

    system("cls");
    print->printDisp(buf->getBuf(),mazeNumber*2+2,mazeNumber+2);

    gameLoop();

    delete maze;
    delete player;
}

void Game::gameLoop(){
    char key;
    loopEnd = 0;

    while(loopEnd == 0){
        if(kbhit()){
            key = getch();
            Game::keySet(key);

            switch(state){
                case State::Maze:
                    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
                    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
                    buf->input(player->getCharacP(),OBJECT_SIZE,OBJECT_SIZE,player->getX() - (maze->getRangeX() - 1) + 1,player->getY() - (maze->getRangeY()- 1) + 1);
                    break;

                case State::YesNoQ:
                    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
                    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
                    buf->input(player->getCharacP(),OBJECT_SIZE,OBJECT_SIZE,player->getX() - (maze->getRangeX() - 1) + 1,player->getY() - (maze->getRangeY()- 1) + 1);
                    buf->input(questions[questionNum]->getQue(),questions[questionNum]->getXleng(),questions[questionNum]->getYleng(),(mazeNumber*2+2)/2-questions[questionNum]->getXleng()/2,(mazeNumber+2)/2-questions[questionNum]->getYleng()/2);
                    break;

                case State::Option:
                    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
                    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
                    buf->input(player->getCharacP(),OBJECT_SIZE,OBJECT_SIZE,player->getX() - (maze->getRangeX() - 1) + 1,player->getY() - (maze->getRangeY()- 1) + 1);
                    buf->input(playingOption->getDialog(),playingOption->getXleng(),playingOption->getYleng(),(mazeNumber*2+2)/2-playingOption->getXleng()/2,(mazeNumber+2)/2-playingOption->getYleng()/2);
                    break;

                case State::GoalOption:
                    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
                    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
                    buf->input(goalOption->getDialog(),goalOption->getXleng(),goalOption->getYleng(),(mazeNumber*2+2)/2-goalOption->getXleng()/2,(mazeNumber+2)/2-goalOption->getYleng()/2);
                    buf->input((char*)GoalText,GoalTextX,GoalTextY,(mazeNumber*2+2)/2-goalOption->getXleng()/2+4,(mazeNumber+2)/2-goalOption->getYleng()/2+3);
                    break;

                case State::GoalEnd:
                    maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
                    buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
                    buf->input((char*)EndText,EndTextX,EndTextY,(mazeNumber*2+2)/2-EndTextX/2,(mazeNumber+2)/2-EndTextY/2);
                    loopEnd = 1;
                    state = State::End;
                    break;

            }
            print->printDisp(buf->getBuf(),mazeNumber*2+2,mazeNumber+2);

            Sleep(10);
            while(kbhit()){
                getch();
            }

        }
    }

    //maze->sliceMazeSet(maze->getRangeX(),maze->getRangeY(),maze->getRangeXleng(),maze->getRangeYleng());
    //buf->input(maze->getSliceMaze(),maze->getSliceXleng(),maze->getSliceYleng(),2,2);
    //print->printDisp(buf->getBuf(),mazeNumber*2+2,mazeNumber+2);
    
}

void Game::keySet(char key){
    switch(state){
        case State::Setting:
            switch(key){
                case 'w':
                    length += 2;
                    if(length > mazeLengthMax) length -= 2;
                    break;

                case 's':
                    length -= 2;
                    if(length < mazeLengthMin) length += 2;
                    break;

                case 'e':
                    loopEnd = 1;
                    break;
            }
            break;

        case State::Maze:
            switch(key){
                case 'w':
                    setEvent(player->getX(),player->getY()-1);
                    break;

                case 'a':
                    setEvent(player->getX()-1,player->getY());
                    break;

                case 's':
                    setEvent(player->getX(),player->getY()+1);
                    break;

                case 'd':
                    setEvent(player->getX()+1,player->getY());
                    break;

                case 'e':
                    state = State::Option;
                    break;
            }
            break;

        case State::YesNoQ:
            switch(key){
                case 'a':
                    questions[questionNum]->setYes();
                    break;

                case 'd':
                    questions[questionNum]->setNo();
                    break;

                case 'e':
                    if(questions[questionNum]->getYorN() == 'Y'){
                        switch(questionNum){
                            case RESTART:
                                player->setCodinat(maze->getStartX(),maze->getStartY());
                                maze->rangeCodinatSet(maze->getStartX(),maze->getStartY());
                                state = State::Maze;
                                break;

                            case RESET:
                                loopEnd = 1;
                                state = State::Maze;
                                break;

                            case SETTING:
                                loopEnd = 1;
                                state = State::Setting;
                                break;

                            case EXIT:
                                loopEnd = 1;
                                state = State::End;
                                break;
                        }
                        questions[questionNum]->setNo();
                    }
                    else if(questions[questionNum]->getYorN() == 'N'){
                        state = State::Option;
                    }
                    break;
            }
            
            break;

        case State::Option:
            switch(key){
                case 'w':
                    playingOption->setUp();
                    break;

                case 's':
                    playingOption->setDown();
                    break;

                case 'e':
                    switch(playingOption->getWhich()-1){
                        case RESTART:
                            state = State::YesNoQ;
                            questionNum = RESTART;
                            break;

                        case RESET:
                            state = State::YesNoQ;
                            questionNum = RESET;
                            break;

                        case SETTING:
                            state = State::YesNoQ;
                            questionNum = SETTING;
                            break;

                        case EXIT:
                            state = State::YesNoQ;
                            questionNum = EXIT;
                            break;

                        case CANCEL:
                            state = State::Maze;
                            break;
                    }       
            }
            break;

        case State::GoalOption:
            switch(key){
                case 'a':
                    goalOption->setUp();
                    break;

                case 'd':
                    goalOption->setDown();
                    break;

                case 'e':
                    switch(goalOption->getWhich()-1){
                            case RESTART:
                                player->setCodinat(maze->getStartX(),maze->getStartY());
                                maze->rangeCodinatSet(maze->getStartX(),maze->getStartY());
                                state = State::Maze;
                                break;

                            case RESET:
                                loopEnd = 1;
                                state = State::Maze;
                                break;

                            case SETTING:
                                loopEnd = 1;
                                state = State::Setting;
                                break;

                            case EXIT:
                                state = State::GoalEnd;
                                break;
                    }       
            }
            break;
    }
}

void Game::setEvent(int x,int y){
    switch(maze->search(maze->getEvent(),x,y)){
        case BLOCK: case START:
            break;

        case GOAL:
            state = State::GoalOption;
            break;

        default:
            player->setCodinat(x,y);
            maze->rangeCodinatSet(x,y);
    }

}
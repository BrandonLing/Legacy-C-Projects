#include "EventProcessCore.h"

void EventProcessCore::init()
{

}

void EventProcessCore::quit()
{

}

void EventProcessCore::processQueue()
{
    if (introFlag)
    {
//MAIN GAME
        if (GameData.GameState == 0)//Town
        {
            std::list<int>::iterator qIter;
            for (qIter = EventQueue.eQueue.begin(); qIter != EventQueue.eQueue.end(); qIter++)
            {
                //Fill arguments origin, id, and flag
                int origin = *qIter;

                std::advance(qIter, 1);
                int id = *qIter;

                std::advance(qIter, 1);
                int flag = *qIter;

                //Quit Program Handler Event
                if ((origin == -1) && (id == -1) && (flag == -1))
                    quitFlag = true;

                else if (origin == 1)//mouse movement
                {
                    float xrel = id;
                    float yrel = flag;
                    int playerID = GameData.getEntityID(GameData.playerCharacter, 0);
                    GameData.EntityVec[playerID].x = GameData.EntityVec[playerID].x + xrel;
                    GameData.EntityVec[playerID].y = GameData.EntityVec[playerID].y - yrel;
                    //std::cout << GameData.EntityVec[playerID].x << "," << GameData.EntityVec[playerID].y << "\n";
                    //std::cout << xrel << "," << yrel << "\n";

                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                }

                else if (origin == 2) //left mouse clicked
                {
                    //get cursor box location in cartesian
                    float xc, yc;
                    int cursorBoxID = GameData.getEntityID("Marker", 2); //finds cursor target box
                    xc = GameData.EntityVec[cursorBoxID].x;
                    yc = GameData.EntityVec[cursorBoxID].y;

                    //clear from queue
                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;

                    int rangeID = GameData.getEntityID("Range Indicator", 7);

                    //check flag
                    if (cursorBoxID >= 0)
                    {
                        GameData.selectTargetMonster(xc, yc);
                        if (rangeID >= 0)
                        {
                            GameData.EntityVec[rangeID].flag = GameData.targetMonster;
                            GameData.EntityVec[rangeID].visible = true;
                        }
                    }

                    //if monster is selected, update reachable nodes for highlighting range of movement
                    if (GameData.targetMonster >= 0)
                    {
                        GameData.updateReachableNodes(GameData.targetMonster);
                    }

                }

                else if (origin == 3) //right mouse clicked
                {
                    //get destination location in cartesian
                    float xDest, yDest;
                    int cursorBoxID = GameData.getEntityID("Marker", 2); //finds cursor target box
                    int monsterID = GameData.targetMonster;
                    if (monsterID != -1)
                    {
                        //Memorize Mouse Location
                        GameData.xLocSave = GameData.EntityVec[0].x; //0 is always the cursor
                        GameData.yLocSave = GameData.EntityVec[0].y;

                        //Change GameState
                        GameData.GameState = 2;

                        //Clear event queue
                        EventQueue.eQueue.clear();
                    }

                    if ((cursorBoxID != -1) && (monsterID != -1))
                    {
                        xDest = GameData.EntityVec[cursorBoxID].x;
                        yDest = GameData.EntityVec[cursorBoxID].y;

                        //set monster destination coords
                        GameData.EntityVec[monsterID].xDest = xDest;
                        GameData.EntityVec[monsterID].yDest = yDest;
                    }

                    //clear from queue
                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;

                    //std::cout << monsterID << "\n";
                    int rangeID = GameData.getEntityID("Range Indicator", 7);
                    GameData.EntityVec[rangeID].visible = false;
                    GameData.targetMonster = -1;

                }

                //Keyboard Input Handler
                else if (origin == 0) //0 means it comes from InputCore as keyboard command
                {
                    switch(flag)
                    {
                        case 1:
                        {
                            switch (id) //Keycode
                            {
                                case SDLK_UP:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_LEFT:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_RIGHT:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_DOWN:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_SPACE:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_RETURN:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                            }
                            break;
                        }
                        case 0:
                        {
                            switch (id) //Keycode
                            {
                                case SDLK_ESCAPE:
                                {
                                    //std::cout << "Menu GameState\n";
                                    //Memorize Mouse Location
                                    GameData.xLocSave = GameData.EntityVec[0].x; //0 is always the cursor
                                    GameData.yLocSave = GameData.EntityVec[0].y;

                                    //Change GameState
                                    GameData.GameState = 1;

                                    //Clear event queue
                                    EventQueue.eQueue.clear();
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_UP:
                                    *qIter = -1; //change flag because event was handled
                                    //std::cout << "UP Released\n";
                                    break;
                                case SDLK_LEFT:
                                    *qIter = -1; //change flag because event was handled
                                    //std::cout << "LEFT Released\n";
                                    break;
                                case SDLK_RIGHT:
                                    *qIter = -1; //change flag because event was handled
                                    //std::cout << "RIGHT Released\n";
                                    break;
                                case SDLK_DOWN:
                                    *qIter = -1; //change flag because event was handled
                                    //std::cout << "DOWN Released\n";
                                    break;
                            }
                        }
                        break;
                    }
                }
            }
        }//endif gamestate

//SUBMENU CHARACTER SELECTED
        else if (GameData.GameState == 2)
        {
            std::list<int>::iterator qIter;
            for (qIter = EventQueue.eQueue.begin(); qIter != EventQueue.eQueue.end(); qIter++)
            {
                //Fill arguments origin, id, and flag
                int origin = *qIter;

                std::advance(qIter, 1);
                int id = *qIter;

                std::advance(qIter, 1);
                int flag = *qIter;

                //Quit Program Handler Event
                if ((origin == -1) && (id == -1) && (flag == -1))
                    quitFlag = true;

                else if (origin == 1)//mouse movement
                {
                    float xrel = id;
                    float yrel = flag;
                    int playerID = GameData.getEntityID(GameData.playerCharacter, 0);
                    GameData.EntityVec[playerID].x = GameData.EntityVec[playerID].x + xrel;
                    GameData.EntityVec[playerID].y = GameData.EntityVec[playerID].y - yrel;
                    //std::cout << GameData.EntityVec[playerID].x << "," << GameData.EntityVec[playerID].y << "\n";
                    //std::cout << xrel << "," << yrel << "\n";

                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                }

                else if (origin == 2) //left mouse clicked
                {
                    //get cursor box location in cartesian
                    float xc, yc;
                    int cursorBoxID = GameData.getEntityID("Marker", 2); //finds cursor target box
                    xc = GameData.EntityVec[cursorBoxID].x;
                    yc = GameData.EntityVec[cursorBoxID].y;

                    //clear from queue
                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;

                    //Re-center cursor to previous position
                    GameData.EntityVec[0].x = GameData.xLocSave;
                    GameData.EntityVec[0].y = GameData.yLocSave;
                    GameData.GameState = 0;
                }


            }
        }

//MAIN MENU
        else if (GameData.GameState == 1)
        {
            std::list<int>::iterator qIter;
            for (qIter = EventQueue.eQueue.begin(); qIter != EventQueue.eQueue.end(); qIter++)
            {
                //Fill arguments origin, id, and flag
                int origin = *qIter;

                std::advance(qIter, 1);
                int id = *qIter;

                std::advance(qIter, 1);
                int flag = *qIter;

                //Quit Program Handler Event
                if ((origin == -1) && (id == -1) && (flag == -1))
                {
                    quitFlag = true;
                }

                else if (origin == 1)//mouse movement
                {
                    float xrel = id;
                    float yrel = flag;
                    int playerID = GameData.getEntityID(GameData.playerCharacter, 0);
                    GameData.EntityVec[playerID].x = GameData.EntityVec[playerID].x + xrel;
                    GameData.EntityVec[playerID].y = GameData.EntityVec[playerID].y - yrel;
                    //std::cout << GameData.EntityVec[playerID].x << "," << GameData.EntityVec[playerID].y << "\n";
                    //std::cout << xrel << "," << yrel << "\n";

                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                }

                else if (origin == 2)//left mouse click
                {
                    int cursorID = GameData.getEntityID(GameData.playerCharacter, 0);
                    //std::cout << GameData.EntityVec[playerID].x << "," << GameData.EntityVec[playerID].y << "\n";

                    std::string buttonPressed = GameData.findMenuButton(cursorID);

                    //release click from queue
                    std::advance(qIter, -2);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;
                    std::advance(qIter, 1);
                    *qIter = 0;

                    //Handle click
                    GameData.handleMenuScreenClick(buttonPressed);
                }

                //Keyboard Input Handler
                else if (origin == 0) //0 means it comes from InputCore as keyboard command
                {
                    switch(flag)
                    {
                        case 1:
                        {
                            switch (id) //Keycode
                            {
                                case SDLK_UP:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_LEFT:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_RIGHT:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                                case SDLK_DOWN:
                                {
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                            }
                            break;
                        }
                        case 0:
                        {
                            switch (id) //Keycode
                            {
                                case SDLK_ESCAPE:
                                {
                                    //std::cout << "Main Game GameState\n";
                                    //Re-center cursor to previous position
                                    GameData.EntityVec[0].x = GameData.xLocSave;
                                    GameData.EntityVec[0].y = GameData.yLocSave;

                                    //Change GameState
                                    GameData.GameState = 0;

                                    EventQueue.eQueue.clear();
                                    *qIter = -1; //change flag because event was handled
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

//TITLE SCREEN
    else //TITLE SCREEN. intro flag is false
    {//Title Screen Controls
        std::list<int>::iterator qIter;
        for (qIter = EventQueue.eQueue.begin(); qIter != EventQueue.eQueue.end(); qIter++)
        {
            //Fill arguments origin, id, and flag
            int origin = *qIter;

            std::advance(qIter, 1);
            int id = *qIter;

            std::advance(qIter, 1);
            int flag = *qIter;

            //Quit Program Handler Event
            if ((origin == -1) && (id == -1) && (flag == -1))
            {
                introFlag = true;
                quitFlag = true;
            }

            else if (origin == 1)//mouse movement
            {
                float yrel = flag;
                int playerID = GameData.getEntityID("Title Pointer", 4);

                //Clamp cursor to bounds
                float lowerYBound = -8.7; float higherYBound = 3.3;
                float yCheck = GameData.EntityVec[playerID].y;

                if ((yCheck >= lowerYBound) && (yCheck <= higherYBound))
                {
                    GameData.EntityVec[playerID].y = GameData.EntityVec[playerID].y - yrel;
                }

                //Snap to top and bottom bounds
                yCheck = GameData.EntityVec[playerID].y;
                if (yCheck > higherYBound)
                {
                    GameData.EntityVec[playerID].y = higherYBound;
                }
                else if (yCheck < lowerYBound)
                {
                    GameData.EntityVec[playerID].y = lowerYBound;
                }

                //find what button is selected
                int button = GameData.findTitleButton(playerID);
                GameData.EntityVec[playerID].flag = button;

                if (button != -1)
                {
                    //highlight button TODO
                }


                //std::cout << GameData.EntityVec[playerID].y << "\n";

                std::advance(qIter, -2);
                *qIter = 0;
                std::advance(qIter, 1);
                *qIter = 0;
                std::advance(qIter, 1);
                *qIter = 0;
            }

            else if (origin == 2)//left mouse click
            {
                int playerID = GameData.getEntityID("Title Pointer", 4);

                int buttonPressed = GameData.EntityVec[playerID].flag;

                //release click from queue
                std::advance(qIter, -2);
                *qIter = 0;
                std::advance(qIter, 1);
                *qIter = 0;
                std::advance(qIter, 1);
                *qIter = 0;

                //Handle click
                GameData.handleTitleScreenClick(buttonPressed);
            }
        }
    }
}

#include "Game.h"
#include <iostream>
#include <sstream>
#include "Data.h"
#include "GameState.h"
#include <string>
#include "utils.h"
Game::Game()
{
}
Game::~Game()
{
}
void Game::init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	bool success = true;

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( title, xPos, yPos, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
			int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
			        printf( "SDL_image could not initialize! %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
//				SDL_SetHint (SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
//				if( !Mix_Init(MIX_INIT_WAVPACK)||Mix_OpenAudio( 44100,AUDIO_S16SYS, 2, 2048 ) < 0 )
//                {
//                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
//                    success = false;
//                }

			}
		}

        isRunning = true;


	if( !success )


	{
		printf( "Failed to initialize!\n" );
	}
}
void Game::handleEvents(SDL_Event event)
{
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
        {
           switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                {
                    isPressed = true;
                    dx = -1;
                    break;
                }
            case SDLK_RIGHT:
                {
                    isPressed = true;
                    dx = 1;
                    break;
                }
            case SDLK_UP:
                {
                    rotate_ = true;
                    break;
                }
            case SDLK_DOWN:
                fast = true;
                break;
            }
            break;
        }
        case SDL_QUIT:
            done = true;
            isRunning = false;
            break;
        }
    }
}
void Game::loadMedia()
{
    bool success = true;
    backGround = IMG_LoadTexture(gRenderer, "img/background.png");
    if(backGround == NULL){
        printf("Couldn't load backGround.\n%s\n", IMG_GetError());
        success = false;
    }
    gFont = TTF_OpenFont("Font/Lato-Black.ttf", 30);
    if (gFont == NULL)
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    gFont1 = TTF_OpenFont("Font/Lato-Black.ttf", 20);
    if (gFont1 == NULL)
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
//void showMessGameOver(){
//    bool done = false;
//    bool pause = false;
//    Uint32 moveTime = 0;
//    Game game;
//    GameState game1;
//    const SDL_MessageBoxButtonData buttons[] = {
//        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Exit" },
//        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Continue" },
//    };
//    const SDL_MessageBoxColorScheme colorScheme = {
//        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
//            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
//            {   255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
//            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
//            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
//            { 255,   0, 255 }
//        }
//    };
//    const SDL_MessageBoxData messageboxdata = {
//        SDL_MESSAGEBOX_ERROR, /* .flags */
//        NULL, /* .window */
//        "Tetris", /* .title */
//        "     Game Over!!!    ", /* .message */
//        SDL_arraysize(buttons), /* .numbuttons */
//        buttons, /* .buttons */
//        &colorScheme /* .colorScheme */
//    };
//    int buttonid;
//    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
//        SDL_Log("error displaying message box");
//        return;
//    }
//    switch(buttonid)
//    {
//        case -1: SDL_Log("No button selected");
//        break;
//        case 0: done = true;
//        break;
//        case 1: {
//            game.init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
//            pause = false;
//            game1.initPiece();
//            game1.initBoard();
//            moveTime = SDL_GetTicks();
//        }
//        break;

//    }
//}
void Game::playGame()
{
    GameState game;
    int speed = 0,randomPiece = -1,gameSpeed = 1000;
    game.initBoard();
    init();
    game.initPiece();
    LTexture ltext;
    while (!done) {
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, backGround, NULL, NULL);
          int gridWidth = 10;
          int gridHeight = 20;
          int cellWidth = (SCREEN_WIDTH / 1.2) / gridWidth;
          int cellHeight = (SCREEN_HEIGHT / 1.2) / gridHeight;


          int smallerSize = std::min(cellWidth, cellHeight);
          cellWidth = cellHeight = smallerSize;


        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        for (int x = 0; x < gridWidth; ++x)
            {
            for (int y = 0; y < gridHeight - 1; ++y)
              {
                int posX = (SCREEN_WIDTH - gridWidth * cellWidth) / 2 + x * cellWidth;
                int posY = (SCREEN_HEIGHT - gridHeight * cellHeight) / 2 + y * cellHeight;
                SDL_Rect cellRect = {posX, posY, cellWidth, cellHeight};
                SDL_RenderDrawRect(gRenderer, &cellRect);
              }
            }
            handleEvents(event);
            if (pause) moveTime = SDL_GetTicks();

            else
            {
                    game.moveLeftRight(dx);
                  if(game.isCollision())
                        game.restorePieces();
                    if(rotate_ && randomPiece != 6)
                    {
                        game.rotate_();
                        if(game.isCollision())
                            game.restorePieces();
                    }

                    if(SDL_GetTicks()> moveTime || beginGame)
                    {
                        if(!isPressed)
                           game.moveDown();
                        bool check = game.isCollision();
                    if(check || beginGame)
                        {

                    if(check){
                               game.getColorLanded(randomColor);
 //                              game.initMark();
                             //game.deletePiece(randomColor);
                               //game.deleteAlonePiece();
                            }
                            game.checkAndClearFilledRows(point, target, level);
                            randomPiece = rand()% 7;
                            randomColor = rand()% 6 + 1;
                            game.generatePiece(randomPiece);
                        }
                        if(fast){
                            switch(gameSpeed)
                            {
                                case 2000: moveTime += (gameSpeed - 1000);
                                break;
                                case 1000: moveTime +=(gameSpeed - 900);
                                break;
                                case 100: moveTime +=(gameSpeed - 10);
                                break;
                            }

                            fast = false;
                        }
                        else
                             moveTime += gameSpeed;
                             beginGame = false;
                    }
            }

            dx = 0;
            rotate_ = false;
            isPressed = false;
            std:: string score = "SCORE " + std::to_string(point);
            SDL_Color textColor1 = {255, 0, 0};
            if (!Score.loadFromRenderedText(gRenderer, gFont, score, textColor1)) {
             printf("Failed to render text texture!\n");
                }
            Score.render(gRenderer, 310, 170);
            std:: string line = "LINE   " + std::to_string(target);
            SDL_Color textColor2 = {255, 0, 0};
            if (!Line.loadFromRenderedText(gRenderer, gFont, line, textColor2)) {
             printf("Failed to render text texture!\n");
                }
            Line.render(gRenderer, 850, 170);
            std::string levelText = "LEVEL " + std::to_string(level);
            SDL_Color levelColor = {255, 255, 255};
               if (!LevelTexture.loadFromRenderedText(gRenderer, gFont1, levelText, levelColor)) {
                  printf("Failed to render text texture!\n");
                  }
            LevelTexture.render(gRenderer, 410, 390);
//            playingMusic = Mix_LoadMUS(playingM.c_str());
//               if (playingMusic == NULL) {
//                    printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
//               }
//                Mix_PlayMusic(playingMusic, 0);
            if (game.checkGameOver())
              {
                 done = true;
                 isRunning = false;
              }
           game.renderNextPieces(gRenderer, randomColor,randomPiece);
           game.showIdlePiece(gRenderer);
           game.showActivePiece(gRenderer,randomColor);
           SDL_RenderPresent(gRenderer);
        }
}
void Game::init()
{
    rotate_ = false,fast = false,isPressed = false,beginGame = true;
    moveTime = 0;
    pause = false;
    done = false;
    point = 0;
    target = 0;
    level = 1;
}
void Game :: clean()
  {
      SDL_DestroyRenderer( gRenderer );
      SDL_DestroyWindow( gWindow);
      gWindow = NULL;
      gRenderer = NULL;
      gFont = NULL;
      gFont1 = NULL;
      TTF_Quit();
      IMG_Quit();
//      Mix_FreeMusic(playingMusic);
//      Mix_CloseAudio();
//      Mix_Quit();
      SDL_Quit();
//      TTF_CloseFont(gFont);
  }
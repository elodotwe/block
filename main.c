#include <SDL2/SDL.h>

typedef struct {
    int paddleWidth;
    int paddlePosition;
    int playfieldWidth;
    int playfieldHeight;
} GameContext;

void drawPaddle(SDL_Renderer* renderer, GameContext* gameContext);
void processMouse(GameContext* gameContext, int x, int y, int isClicked);
int min(int x, int y);
int max(int x, int y);
int clamp(int value, int min, int max);

int main() {
    GameContext gameContext;
    gameContext.paddleWidth = 50;
    gameContext.paddlePosition = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init failure, %s\n", SDL_GetError());
		return 1;
	}
    SDL_Window* window = SDL_CreateWindow("Block", 100, 100, 300, 528, SDL_WINDOW_SHOWN);

	if (window == 0) {
		printf("SDL_Window error, %s\n", SDL_GetError());
		return 1;
	}

    SDL_SetWindowResizable(window, SDL_FALSE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == 0) {
		printf("SDL_CreateRenderer error, %s\n", SDL_GetError());
		return 1;
	}

    SDL_GetRendererOutputSize(renderer, &(gameContext.playfieldWidth), &(gameContext.playfieldHeight));

	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}

            if (e.type == SDL_MOUSEMOTION) {
                processMouse(&gameContext, e.motion.x, e.motion.y, e.motion.state & SDL_BUTTON_LMASK);
            }
		}
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);

        drawPaddle(renderer, &gameContext);
		
		SDL_RenderPresent(renderer);
	}
	return 0;
}

void drawPaddle(SDL_Renderer* renderer, GameContext* gameContext) {
    SDL_Rect paddleRect;
    paddleRect.x = gameContext->paddlePosition;
    paddleRect.y = gameContext->playfieldHeight - 30;
    paddleRect.h = 20;
    paddleRect.w = gameContext->paddleWidth;

    SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
    SDL_RenderFillRect(renderer, &paddleRect);
}

void processMouse(GameContext* gameContext, int x, int y, int isClicked) {
    int rightBound = gameContext->playfieldWidth - gameContext->paddleWidth / 2;
    int leftBound = gameContext->paddleWidth / 2;

    int paddleCenter = clamp(x, leftBound, rightBound);

    gameContext->paddlePosition = paddleCenter - gameContext->paddleWidth / 2;
}

int clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

int min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

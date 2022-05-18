#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

#define IMAX 100

int main() {
    int sizewx = 1280;
    int sizewy = 720;

    SDL_Rect windowSize = {10, 10, sizewx, sizewy};

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error : %s\n", SDL_GetError());
        goto Quit;
    }

    window = SDL_CreateWindow("Fractal",windowSize.x, windowSize.y, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error : %s\n", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "Erreur : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    SDL_Color color = {.r = 82, .g = 165, .b = 255};


    //-1.82;-1.72
    //-1.7879010657;-1.7879 (le plus petits)
    double xmin = -1.82;
    double xmax = -1.72;

    if(xmin >= xmax){
        printf("Xmin doit être inférieur à xmax\n");
        exit(1);
    }

    double sizex = fabs(xmax-xmin);
    double sizey = sizex*sizewy/sizewx;
    double resolution = sizex/sizewx;

    int x0 = sizewx/2-(xmin+xmax)/2/resolution;
    int y0 = sizewy/2;

    double ratio = sizewx/sizex;
    //variable utilisé dans la boucle
    double c_r,c_i,z_r,z_i,i,tmp;
    SDL_Rect rect;
    rect.w = 1;
    rect.h = 1;

    for (double x = xmin; x < xmax; x+=resolution) {
        for (double y=-sizey;y < sizey;y+=resolution) {
            // printf("%f %f\n",x,y);
            c_r = x;
            c_i = y;
            z_r = 0;
            z_i = 0;
            i = 0;

            while (z_r*z_r+z_i*z_i < 4 && i < IMAX) {
                tmp = z_r;
                z_r = z_r*z_r - z_i*z_i + c_r;
                z_i = 2*z_i*tmp + c_i;
                i++;
            }

            if(i != IMAX){
                rect.x=x*ratio+x0;
                rect.y=y*ratio+y0;
                SDL_SetRenderDrawColor(renderer, color.r*i/IMAX,color.g*i/IMAX,color.b*i/IMAX,255);
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }

    printf("Done\n");

    SDL_RenderPresent(renderer);
    int status = 1;
    while (status) {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                status = 0;
                break;
            }
        }
    }


    Quit:
    if(renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if(window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;

}

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <math.h>

#define IMAX 100

int main() {
    unsigned int sizewx = 1920;
    unsigned int sizewy = 1080;

    SDL_Color color = {.r = 82, .g = 165, .b = 255};

    float xmin = -1.82;
    float xmax = -1.10;

    if(xmin >= xmax){
        printf("Xmin doit être inférieur à xmax\n");
        exit(1);
    }

    printf("%u %u\n",sizewx,sizewy);
    SDL_Surface* surface = SDL_CreateRGBSurface(0,sizewx,sizewy,32,0,0,0,0);
    if(surface == NULL){
        fprintf(stderr, "Error: %s\n",SDL_GetError());
        exit(1);
    }

    if(SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0))){
        fprintf(stderr, "Error: %s\n",SDL_GetError());
        exit(1);
    }

    float sizex = fabsf(xmax-xmin);
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
            //printf("%f %f\n",x,y);
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
                SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format, color.r*i/IMAX,color.g*i/IMAX,color.b*i/IMAX));
            }
        }
    }
    IMG_SavePNG(surface, "factalwallpaper.png");

    if(surface != NULL) {
        SDL_FreeSurface(surface);
    }
    SDL_Quit();
    return 0;

}

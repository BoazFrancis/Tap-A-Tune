//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
//you need tempmusic.wav tempmusic1.wav tempmusic2.wav file in the same folder
#include <SDL.h>
#include <SDL_mixer.h>

int main(int argc, char** argv)
{
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface *screen;
        Mix_Chunk* effect1;
        Mix_Chunk* effect2;
        Mix_Music* music;
        Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
        music = Mix_LoadMUS("tempmusic.wav");
        effect1 = Mix_LoadWAV("tempsound1.wav");
        effect2 = Mix_LoadWAV("tempsound2.wav");
        Mix_PlayMusic(music, -1);
        screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
        int running = 1;
        const int FPS = 30;
        Uint32 start;
        int b[4] = {0,0,0,0};
        SDL_Rect rect;
        rect.x = 10;
        rect.y = 10;
        rect.w = 20;
        rect.h = 20;
        Uint32 color2 = SDL_MapRGB(screen->format, 0xff,0xff,0xff);
        Uint32 color = SDL_MapRGB(screen->format, 0,0,0);
        while(running == 1) {
                start = SDL_GetTicks();
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        running = 0;
                                        break;
                                case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym) {
                                                case SDLK_UP:
                                                        b[0] = 1;
                                                        break;
                                                case SDLK_LEFT:
                                                        b[1] = 1;
                                                        break;
                                                case SDLK_DOWN:
                                                        b[2] = 1;
                                                        break;
                                                case SDLK_RIGHT:
                                                        b[3] = 1;
                                                        break;
                                                case SDLK_1:
                                                        Mix_PlayChannel(-1,effect1,0);
                                                        break;
                                                case SDLK_2:
                                                        Mix_PlayChannel(-1,effect2,0);
                                                        break;
                                        }
                                        break;
                                case SDL_KEYUP:
                                        switch(event.key.keysym.sym) {
                                                case SDLK_UP:
                                                        b[0] = 0;
                                                        break;
                                                case SDLK_LEFT:
                                                        b[1] = 0;
                                                        break;
                                                case SDLK_DOWN:
                                                        b[2] = 0;
                                                        break;
                                                case SDLK_RIGHT:
                                                        b[3] = 0;
                                                        break;

                                        }
                                        break;
                        }
                }

                SDL_FillRect(screen, &rect, color);

                //logic
                if(b[0])
                        rect.y--;
                if(b[1])
                        rect.x--;
                if(b[2])
                        rect.y++;
                if(b[3])
                        rect.x++;

                //render
                SDL_FillRect(screen, &rect, color2);
                SDL_Flip(screen);

                if(1000/FPS > SDL_GetTicks()-start) {
                        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
                }
        }
        Mix_FreeChunk(effect1);
        Mix_FreeChunk(effect2);
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return 0;
}

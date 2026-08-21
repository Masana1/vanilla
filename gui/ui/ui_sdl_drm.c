// --- Ponts de compatibilité pour remplacer ui_sdl.c nativement ---

static SDL_Window* drm_window = NULL;
static vanilla_drm_ctx_t* drm_ctx = NULL;

int vui_init_sdl(void* vui, int fullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        vpilog("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    uint32_t flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN;
    drm_window = SDL_CreateWindow("Vanilla DRM",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, flags);
    if (!drm_window) {
        vpilog("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    if (!vui_sdl_drm_initialize(&drm_ctx, drm_window)) {
        vpilog("vui_sdl_drm_initialize failed\n");
        SDL_DestroyWindow(drm_window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

int vui_update_sdl(void* vui)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
    }

    // Si tu récupères la frame courante depuis ton décodeur/vui, 
    // c'est ici qu'intervient l'appel à vui_sdl_drm_present(drm_ctx, frame);

    return 1;
}

void vui_close_sdl(void* vui)
{
    if (drm_ctx) {
        vui_sdl_drm_free(&drm_ctx);
    }
    if (drm_window) {
        SDL_DestroyWindow(drm_window);
    }
    SDL_Quit();
}

// --- Ponts de compatibilité SDL->DRM pour main.c ---
static SDL_Window *drm_window = NULL;
static vanilla_drm_ctx_t *drm_ctx = NULL;

int vui_init_sdl(void *vui, int fullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        vpilog("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    uint32_t flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN;
    drm_window = SDL_CreateWindow("Vanilla DRM", 
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  1280, 720, flags);
    if (!drm_window) {
        vpilog("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    if (!vui_sdl_drm_initialize(&drm_ctx, drm_window)) {
        vpilog("vui_sdl_drm_initialize failed\n");
        SDL_DestroyWindow(drm_window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

int vui_update_sdl(void *vui)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
    }
    return 1;
}

void vui_close_sdl(void *vui)
{
    if (drm_ctx) {
        vui_sdl_drm_free(&drm_ctx);
    }
    if (drm_window) {
        SDL_DestroyWindow(drm_window);
    }
    SDL_Quit();
}

#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {
    
	viper::file::SetCurrentDirectory("Assets/Platformer");
	viper::Logger::Info("current directory: {}", viper::file::GetCurrentDirectory());

	// Intialize engine
	viper::Logger::Warning("Viper Engine is initializing...");
    viper::GetEngine().Initialize();

	//Initialize game
	std::unique_ptr<viper::Game> game = std::make_unique<PlatformerGame>();
	game->Initialize();

    SDL_Event e;
    bool quit = false;
   
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Update input system
		viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

		// Clear the renderer
		viper::vec3 color{ 0, 0, 0};

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		game->Draw(viper::GetEngine().GetRenderer());
       
        viper::GetEngine().GetRenderer().Present();
    }

	game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
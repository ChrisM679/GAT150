#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {

	viper::file::SetCurrentDirectory("Assets");

	// Intialize engine
    viper::GetEngine().Initialize();

	//Initialize game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

    // Create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }

    auto texture = viper::Resources().Get<viper::Texture>("textures/playership.png", viper::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;
    float rotate = 0;
   
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

        // Update input system
		viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

		// Clear the renderer
		viper::vec3 color{ 0, 0, 0};

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		game->Draw(viper::GetEngine().GetRenderer());

		// Draw stars
        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

		rotate += viper::GetEngine().GetTime().GetDeltaTime() * 0.5f;
        viper::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, rotate, 0.5f);

        for (auto& star : stars) {
            star += speed * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(256), viper::random::getInt(256), viper::random::getInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }
       
        viper::GetEngine().GetRenderer().Present();
    }

	game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}
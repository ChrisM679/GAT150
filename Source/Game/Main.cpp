#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {

	viper::file::SetCurrentDirectory("Assets");
	viper::Logger::Info("current directory: {}", viper::file::GetCurrentDirectory());

	// command line arguments
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
		viper::Logger::Debug("arg[{}]: {}", i, argv[i]);
	}
    
    // streams
	/*std::cout << "Hello, Viper Engine!" << std::endl;
    int age{ 0 };
	std::cout << "Enter your age: ";
    if (std::cin >> age) {
		std::cout << "INVALID INPUT" << std::endl;
    }
	std::cout << "You are : " << (age * 365) << "days old" << std::endl;*/

    //file
	std::fstream stream("test.txt");
    if (!stream) {
        std::cout << "Failed to open file" << std::endl;
    }
	//std::cout << stream.rdbuf();
	std::string line;
    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
    }

    //user data type
	viper::vec3 v{ 10.0f, 20.0f, 54 };
	std::cout << v << std::endl;

	std::string vstr("{ 10.0f, 20.0f, 54 }");
	std::stringstream sstream(vstr);

	viper::vec2 v2;
	sstream >> v2;
	std::cout << v2 << std::endl;


    // read/show the data from the json file
    std::string name;
    int age;
    float speed;
    bool isAwake;
    viper::vec2 position;
    viper::vec3 color;

    // load the json data from a file
    std::string buffer;
    viper::file::ReadTextFile("json.txt", buffer);

    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::json::Load("json.txt", document);

    // read the age data from the json
    viper::json::Read(document, "age", age);

    // show the age data
    std::cout << age << std::endl;

    // read the json data
    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    return 0;

	// Intialize engine
	viper::Logger::Warning("Viper Engine is initializing...");
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
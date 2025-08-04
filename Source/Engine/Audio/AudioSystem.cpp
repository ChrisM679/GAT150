#include "AudioSystem.h"

#include "../Core/StringHelper.h"

#include<fmod_errors.h>

#include <iostream>

namespace viper {

    /// <summary>
    /// Checks if an FMOD operation was successful and logs an error message if it was not.
    /// </summary>
    /// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
    /// <returns>true if the FMOD operation was successful (FMOD_OK); false otherwise.</returns>
    bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
        if (result != FMOD_OK) {
            std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
            return false;
        }
        return true;
    }

    /// <summary>
    /// Initializes the audio system using FMOD.
    /// </summary>
    /// <returns>Returns true if the audio system was successfully initialized; otherwise, returns false.</returns>
    bool AudioSystem::Initialize() {
        FMOD_RESULT result = FMOD::System_Create(&m_system);
        if (!CheckFMODResult(result))return false;
        void* extradriverdata = nullptr;
        result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
        if (!CheckFMODResult(result))return false;
        return true;
    }

    void AudioSystem::Shutdown() {
        CheckFMODResult(m_system->release());
    }

    void AudioSystem::Update() {
        CheckFMODResult(m_system->update());
    }

    /// <summary>
    /// Adds a new sound to the audio system using the specified file and name.
    /// </summary>
    /// <param name="filename">The path to the sound file to be loaded.</param>
    /// <param name="name">The name to associate with the sound. If empty, the filename is used as the key.</param>
    /// <returns>True if the sound was successfully added; false if the sound already exists or loading failed.</returns>
    bool AudioSystem::AddSound(const char* filename, const std::string& name)
    {
        std::string key = name.empty() ? filename : name;
        key = tolower(key);
        if (m_sounds.find(key) != m_sounds.end()) {
            std::cerr << "Sound with name '" << key << "' already exists." << std::endl;
            return false;
        }
        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = m_system->createSound(filename, FMOD_DEFAULT, 0, &sound);
        if (!CheckFMODResult(result)) return false;
        m_sounds[key] = sound;
        return true;
    }
    bool AudioSystem::PlaySound(const std::string& name)
    {
        std::string key = name;
        if (m_sounds.find(key) == m_sounds.end()) {
            std::cerr << "Sound with name '" << key << "' does not exist." << std::endl;
            return false;
        }
        FMOD_RESULT result = m_system->playSound(m_sounds[name], 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;
        return true;

    }

}

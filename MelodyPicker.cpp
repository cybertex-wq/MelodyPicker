#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

class MelodyPicker {
public:
    bool loadAndPlayMelody(const std::string& filename) {
        if (!music.openFromFile(filename)) {
            std::cerr << "Error: Could not load the melody file: " << filename << std::endl;
            return false;
        }
        music.play();
        return true;
    }

    void displayAvailableMelodies() const {
        std::cout << "Available melodies:\n";
        for (const auto& melody : melodies) {
            std::cout << melody << std::endl;
        }
    }

    void addMelody(const std::string& filename) {
        melodies.push_back(filename);
    }

private:
    sf::Music music;
    std::vector<std::string> melodies;
};

int main() {
    MelodyPicker picker;
    picker.addMelody("melody1.ogg");
    picker.addMelody("melody2.ogg");

    picker.displayAvailableMelodies();

    std::string selectedMelody;
    std::cout << "Enter the name of the melody to play: ";
    std::cin >> selectedMelody;

    if (!picker.loadAndPlayMelody(selectedMelody)) {
        return 1;
    }

    std::cout << "Now playing: " << selectedMelody << std::endl;

    while (picker.loadAndPlayMelody(selectedMelody)) {
        if (sf::Music::getStatus() != sf::SoundSource::Playing)
            break;
    }

    return 0;
}

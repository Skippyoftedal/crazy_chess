//
// Created by Tobias on 11/26/24.
//

#include "FontLoader.h"

FontLoader & FontLoader::getInstance() {
    static FontLoader instance;
    return instance;
}

bool FontLoader::load_font(const std::string &fontPath) {
    return font.loadFromFile(fontPath);
}

const sf::Font& FontLoader::get_font() const {
    return font;
}

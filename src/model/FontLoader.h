//
// Created by Tobias on 11/26/24.
//

#ifndef FONTLOADER_H
#define FONTLOADER_H
#include <SFML/Graphics/Font.hpp>


class FontLoader {
public:
  static FontLoader& getInstance();

  bool load_font(const std::string& fontPath);

  const sf::Font& get_font() const;

  FontLoader(const FontLoader&) = delete;

  FontLoader& operator=(const FontLoader&) = delete;
private:
  sf::Font font;

  FontLoader() = default;

};




#endif //FONTLOADER_H

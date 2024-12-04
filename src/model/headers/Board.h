//
// Created by Tobias on 11/21/24.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "PromotionChoice.h"
#include "PromotionModal.h"
#include "Tile.h"


class Board final : public sf::Drawable {
    static constexpr int SIDE_LENGTH = 8;

    static constexpr std::array<std::tuple<int, int>, 4> rook_directions = {{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};

    static constexpr std::array<std::tuple<int, int>, 8> queen_directions = {
        {
            {0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        }
    };

    static constexpr std::array<std::tuple<int, int>, 4> bishop_directions = {
        {
            {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        }
    };

    static constexpr std::array<std::tuple<int, int>, 8> king_directions = {
        {
            {0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        }
    };

    static constexpr std::array<std::tuple<int, int>, 4> pawn_directions = {
        {
            {0, 1}, {1, 1}, {-1, 1}, {0, 2}
        }
    };

    static constexpr std::array<std::tuple<int, int>, 4> pawn_opposite = {
        {
            {0, -1}, {1, -1}, {-1, -1}, {0, -2}
        }
    };


    static constexpr std::array<std::tuple<int, int>, 8> knight_directions = {
        {
            {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}
        }
    };


    //bool current_user_color = White;

    int pixel_width;
    sf::Font font;
    std::vector<std::vector<Tile> > tiles;
    std::optional<std::tuple<int, int> > selected_tile;
    PromotionModal promotion_modal;

    int get_tile_width() const {
        return pixel_width / SIDE_LENGTH;
    }

    Tile &get_tile(int bl_index_x, int bl_index_y);

    static bool is_in_bounds(int bl_index_x, int bl_index_y);

    void clear_selected();

    void clear_available();

    void move_piece(const std::tuple<int, int> &pos_from, const std::tuple<int, int> &pos_to);

    void show_available_moves(const std::tuple<int, int> &pos_from);



    void add_piece(const std::string &, Piece *piece);

    static std::string pos_to_string_pretty(const std::tuple<int, int> &pos);

    static std::string pos_to_string(const std::tuple<int, int> &pos);

     std::tuple<int, int> get_bottom_left_index_from_string(const std::string &position);

     std::tuple<int, int> get_bottom_left_position_from_string(const std::string &string_rep);

     std::tuple<int, int> get_bottom_left_position_from_mouse(sf::Vector2i position) const;

    std::vector<std::tuple<int, int> > get_possible_moves(const std::tuple<int, int> &pos_from);

    template<std::size_t N>
    std::vector<std::tuple<int, int> > get_possible_moves_pawn(Piece *piece,
                                                               const std::tuple<int, int> &pos_from,
                                                               const std::array<std::tuple<int, int>, N> &directions
                                                              );

    template<std::size_t N>
    std::vector<std::tuple<int, int> > get_possible_moves_infinite_direction(Piece *piece, const std::tuple<int, int> &pos_from,
                                                                             const std::array<std::tuple<int, int>, N> &
                                                                             directions);

    template<std::size_t N>
    std::vector<std::tuple<int, int> > get_possible_moves_singular(Piece *piece, const std::tuple<int, int> &pos_from,
                                                                   const std::array<std::tuple<int, int>, N> &
                                                                   directions);

public :
    Board(int pixel_width);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void on_mouse_clicked(sf::Vector2i position);

    void fill_board();
};


#endif //BOARD_H

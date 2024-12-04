#include <iostream>
#include <__ranges/split_view.h>
#include "headers/Board.h"
#include "headers/Bishop.h"
#include "headers/King.h"
#include "headers/Knight.h"
#include "headers/Pawn.h"
#include "headers/Rook.h"
#include "headers/Tile.h"
#include "headers/Queen.h"


Board::Board(int pixel_width) : pixel_width(pixel_width),
                                tiles(std::vector(SIDE_LENGTH, std::vector<Tile>(SIDE_LENGTH))) {

    for (int col_index = 0; col_index < SIDE_LENGTH; col_index++) {
        for (int row_index = 0; row_index < SIDE_LENGTH; row_index++) {
            sf::RectangleShape rectangle_shape;

            rectangle_shape.setPosition(sf::Vector2f(
                    static_cast<float>(col_index * get_tile_width()),
                    static_cast<float>(7 * get_tile_width() - row_index * get_tile_width()))
            );
            rectangle_shape.setSize(sf::Vector2f(get_tile_width(), get_tile_width()));




            sf::Color default_color;
            if ((row_index + col_index + 1) % 2) {
                default_color = (sf::Color::Blue);
            } else {
                default_color = (sf::Color::White);
            }

            auto text = pos_to_string({col_index, row_index});
            Tile tile(rectangle_shape, default_color, text);
            tiles[col_index][row_index] = tile;
        }
    }
    fill_board();
}

std::tuple<int, int> Board::get_bottom_left_index_from_string(const std::string &position) {
    if (position.length() != 2) {
        throw std::runtime_error("position has to be 2 chars long");
    }

    char const first = position[0];
    char const second = position[1];
    return {first - 'a', second - '1'};
}


std::tuple<int, int> Board::get_bottom_left_position_from_mouse(sf::Vector2i const position) const {
    auto x_index = std::clamp(position.x / get_tile_width(), 0, 7);
    auto y_index = std::clamp(7 - (position.y / get_tile_width()), 0, 7);
    return {x_index, y_index};
}


template<std::size_t N>
std::vector<std::tuple<int, int> > Board::get_possible_moves_pawn(
    Piece *piece,
    const std::tuple<int, int> &pos_from,
    const std::array<std::tuple<int, int>, N> &directions) {
    std::vector<std::tuple<int, int> > available_positions;

    int original_x = std::get<0>(pos_from);
    int original_y = std::get<1>(pos_from);

    for (auto &direction: directions) {
        if (std::abs(std::get<1>(direction)) == 2 && piece->has_moved()) {
            continue;
        };

        int current_x = original_x + std::get<0>(direction);
        int current_y = original_y + std::get<1>(direction);

        if (is_in_bounds(current_x, current_y)) {
            Tile &t = tiles[current_x][current_y];

            if (current_x != original_x) {
                if (t.has_piece() && piece->getColor() != t.get_piece()->getColor()) {
                    available_positions.emplace_back(current_x, current_y);
                }
            } else {
                if (!t.has_piece()) {
                    available_positions.emplace_back(current_x, current_y);
                }
            }
        }
    }
    return available_positions;
}

template<std::size_t N>
std::vector<std::tuple<int, int> > Board::get_possible_moves_infinite_direction(
    Piece *piece,
    const std::tuple<int, int> &pos_from,
    const std::array<std::tuple<int, int>, N> &directions) {
    std::vector<std::tuple<int, int> > available_positions;

    for (auto &direction: directions) {
        int current_x = std::get<0>(pos_from) + std::get<0>(direction);
        int current_y = std::get<1>(pos_from) + std::get<1>(direction);
        while (is_in_bounds(current_x, current_y)) {
            Tile &t = tiles[current_x][current_y];
            if (t.has_piece()) {
                if (piece->getColor() == t.get_piece()->getColor()) {
                    break;
                }
                available_positions.emplace_back(current_x, current_y);
                break;
            }
            available_positions.emplace_back(current_x, current_y);
            current_x += std::get<0>(direction);
            current_y += std::get<1>(direction);
        }
    }
    return available_positions;
}

template<std::size_t N>
std::vector<std::tuple<int, int> > Board::get_possible_moves_singular(
    Piece *piece,
    const std::tuple<int, int> &pos_from,
    const std::array<std::tuple<int, int>, N> &directions) {
    std::vector<std::tuple<int, int> > available_positions;

    for (auto &direction: directions) {
        int current_x = std::get<0>(pos_from) + std::get<0>(direction);
        int current_y = std::get<1>(pos_from) + std::get<1>(direction);

        if (is_in_bounds(current_x, current_y)) {
            Tile &t = tiles[current_x][current_y];

            if (t.has_piece()) {
                if (piece->getColor() == t.get_piece()->getColor()) {
                    continue;
                }
                available_positions.emplace_back(current_x, current_y);
            } else {
                available_positions.emplace_back(current_x, current_y);
            }
        }
    }
    return available_positions;
}

std::vector<std::tuple<int, int> > Board::get_possible_moves(const std::tuple<int, int> &pos_from) {
    Piece *piece = tiles[std::get<0>(pos_from)][std::get<1>(pos_from)].get_piece();
    std::cout << "calculating moves for " << piece->getPieceName() << std::endl;
    std::vector<std::tuple<int, int> > available_positions;

    if (const auto rook = dynamic_cast<Rook *>(piece)) {
        available_positions = get_possible_moves_infinite_direction<rook_directions.size()>(
            rook, pos_from, rook_directions);
    } else if (const auto queen = dynamic_cast<Queen *>(piece)) {
        available_positions = get_possible_moves_infinite_direction<queen_directions.size()>(
            queen, pos_from, queen_directions);
    } else if (const auto bishop = dynamic_cast<Bishop *>(piece)) {
        available_positions = get_possible_moves_infinite_direction<bishop_directions.size()>(bishop,
            pos_from, bishop_directions);
    } else if (const auto king = dynamic_cast<King *>(piece)) {
        available_positions = get_possible_moves_singular<king_directions.size()>(king, pos_from, king_directions);
    } else if (const auto knight = dynamic_cast<Knight *>(piece)) {
        available_positions = get_possible_moves_singular<knight_directions.
            size()>(knight, pos_from, knight_directions);
    } else if (auto *pawn = dynamic_cast<Pawn *>(piece)) {
        if (pawn->getColor() == White) {
            available_positions = get_possible_moves_pawn<pawn_directions.size()>(pawn,
                pos_from, pawn_directions);
        } else {
            available_positions = get_possible_moves_pawn<pawn_opposite.size()>(pawn,
                pos_from, pawn_opposite);
        }
    }
    return available_positions;
}

void Board::show_available_moves(const std::tuple<int, int> &pos_from) {
    const auto available_positions = get_possible_moves(pos_from);

    for (auto &a: available_positions) {
        tiles[std::get<0>(a)][std::get<1>(a)].set_available(true);
    }
}

void Board::on_mouse_clicked(sf::Vector2i mouse_pos) {
    const std::tuple<int, int> calculated_pos = get_bottom_left_position_from_mouse(mouse_pos);
    //std::cout << "Clicked " << pos_to_string(calculated_pos) << std::endl;

    if (selected_tile.has_value()) {
        move_piece(selected_tile.value(), calculated_pos);
        clear_available();
        clear_selected();
    } else {
        Tile &tile = tiles[std::get<0>(calculated_pos)][std::get<1>(calculated_pos)];

        if (!tile.has_piece()) {
            return;
        }
        selected_tile = calculated_pos;
        show_available_moves(calculated_pos);
        tile.set_selected(!tile.is_selected());
    }
}

void Board::move_piece(const std::tuple<int, int> &pos_from, const std::tuple<int, int> &pos_to) {
    std::cout << "Moving from " << pos_to_string_pretty(pos_from)
            << " to " << pos_to_string_pretty(pos_to);

    if (pos_from == pos_to) {
        return;
    }

    auto moves = get_possible_moves(pos_from);

    auto res = std::ranges::find_if(moves,
                                    [pos_to](const std::tuple<int, int> &p) {
                                        return std::get<0>(p) == std::get<0>(pos_to) && std::get<1>(p) == std::get<1>(
                                                   pos_to);
                                    });

    if (res == moves.end()) {
        return;
    }


    Tile &tile_from = tiles[std::get<0>(pos_from)][std::get<1>(pos_from)];
    Tile &tile_to = tiles[std::get<0>(pos_to)][std::get<1>(pos_to)];


    tile_to.set_piece(tile_from.get_piece());
    tile_to.get_piece()->set_has_moved(true);


    if (std::get<1>(pos_to) == 7 || std::get<1>(pos_to) == 0) {
        if (auto pawn = dynamic_cast<Pawn *>(tile_to.get_piece())) {
            tile_to.set_piece(new Queen(tile_to.get_piece()->getColor()));
        }
    }

    tile_from.set_piece(nullptr);
}


void Board::fill_board() {
    add_piece("d1", new Queen(White));
    add_piece("e1", new King(White));

    add_piece("a1", new Rook(White));
    add_piece("h1", new Rook(White));

    add_piece("c1", new Bishop(White));
    add_piece("f1", new Bishop(White));

    add_piece("b1", new Knight(White));
    add_piece("g1", new Knight(White));


    add_piece("d8", new Queen(Black));
    add_piece("e8", new King(Black));

    add_piece("a8", new Rook(Black));
    add_piece("h8", new Rook(Black));

    add_piece("b8", new Bishop(Black));
    add_piece("g8", new Bishop(Black));

    add_piece("c8", new Knight(Black));
    add_piece("f8", new Knight(Black));


    for (char c = 'a'; c < 'i'; c++) {
        add_piece(std::format("{}2", c), new Pawn(White));
        add_piece(std::format("{}7", c), new Pawn(Black));
    }
}


void Board::add_piece(const std::string &position, Piece *const piece) {
    auto const pos = get_bottom_left_index_from_string(position);

    //std::cout << "Placing " << piece->getPieceName() << " on " << pos_to_string(pos) << std::endl;

    tiles[std::get<0>(pos)][std::get<1>(pos)].set_piece(piece);
}


void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &v: tiles) {
        for (auto &tile: v) {
            target.draw(tile);
        }
    }
    target.draw(promotion_modal);
}

std::string Board::pos_to_string(const std::tuple<int, int> &pos) {
    return "{" + std::to_string(std::get<0>(pos)) + ", " + std::to_string(std::get<1>(pos)) + "}";
}

std::string Board::pos_to_string_pretty(const std::tuple<int, int> &pos) {
    return std::string(1, static_cast<char>('a' + std::get<0>(pos)))
           + std::to_string(std::get<1>(pos) + 1
           );
}

bool Board::is_in_bounds(int index_x, int index_y) {
    return index_x < SIDE_LENGTH && index_x > -1 && index_y < SIDE_LENGTH && index_y > -1;
}

void Board::clear_selected() {
    selected_tile = std::nullopt;
    for (auto &row: tiles) {
        for (auto &tile: row) {
            tile.set_selected(false);
        }
    }
}

void Board::clear_available() {
    for (auto &row: tiles) {
        for (auto &tile: row) {
            tile.set_available(false);
        }
    }
}

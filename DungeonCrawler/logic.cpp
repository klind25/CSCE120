#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream file;
    
    file.open(fileName); // Open
    if (!file.is_open()) { // Check if open
        return nullptr;
    }

    file >> maxRow;
    if (file.fail() || maxRow <= 0) {
        return nullptr;
    }
    file >> maxCol;
    if ((maxRow > INT32_MAX / maxCol) || file.fail() || maxCol <= 0) { // Too big or too small
        return nullptr;
    }
    file >> player.row; // Player out of bounds
    if (player.row >= maxRow || file.fail()) {
        return nullptr;
    }
    file >> player.col;
    if (player.col >= maxCol || file.fail()) {
        return nullptr;
    }

    char** map = createMap(maxRow, maxCol);

    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            file >> map[i][j];
        }
    }
    map[player.row][player.col] = TILE_PLAYER;

    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if (input == MOVE_UP) {
        nextRow -= 1;
    }
    else if (input == MOVE_DOWN) {
        nextRow += 1;
    }
    else if (input == MOVE_LEFT) {
        nextCol -= 1;
    }
    else if (input == MOVE_RIGHT){
        nextCol += 1;
    }

}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    if (maxRow <= 0 || maxCol <= 0) {return nullptr;}
    char** map = new char* [maxRow]; // New array

    for (int i = 0; i < maxRow; ++i) {
        map[i] = new char [maxCol]; // Double array
        for (int j = 0; j < maxCol; ++j) {
            map[i][j] = TILE_OPEN; // Initialize
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map != nullptr) {
        for (int i = 0; i < maxRow; ++i){
            delete[] map[i]; // Delete all of them
        }
        delete[] map; // No memory leaks
    
        map = nullptr; // Assign map
    }
    maxRow = 0; // Update row

}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr || maxRow <= 0 || maxCol <= 0) {return nullptr;} // Bad row, col

    int row = 2 * maxRow;
    int col = 2 * maxCol;
    char** array = createMap(row, col); // New array

    for (int i = 0; i < maxRow; ++i) { // Copy old array into new
        for (int j = 0; j < maxCol; ++j) {
            
            array[i][j] = map[i][j]; // Quadrant A

            if (map[i][j] == TILE_PLAYER) { // Quadrant B
                array[i][j+maxCol] = TILE_OPEN;
            }
            else {
                array[i][j+maxCol] = map[i][j];
            }

            if (map[i][j] == TILE_PLAYER) { // Quadrant C
                array[i+maxRow][j] = TILE_OPEN;
            }
            else {
                array[i+maxRow][j] = map[i][j];
            }

            if (map[i][j] == TILE_PLAYER) { // Quadrant D
                array[i+maxRow][j+maxCol] = TILE_OPEN;
            }
            else {
                array[i+maxRow][j+maxCol] = map[i][j];
            }

        }
    }

    deleteMap(map, maxRow); // Delete old
        
    maxRow = row; // Update
    maxCol = col;    

    return array;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    
    if ((map[nextRow][nextCol] == TILE_PILLAR) || (map[nextRow][nextCol] == TILE_MONSTER) || nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0) {
        return STATUS_STAY; // Invalid moves
    }

    if (map[nextRow][nextCol] == TILE_EXIT && player.treasure <= 0) { // Not enough treasure
        return STATUS_STAY;
    }
    else if (map[nextRow][nextCol] == TILE_EXIT && player.treasure > 0) {
        map[player.row][player.col] = TILE_OPEN; // Update icon
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow; // Update player
        player.col = nextCol;

        return STATUS_ESCAPE; // Moving onto exit
    }

    if (map[nextRow][nextCol] == TILE_TREASURE) { // Moving onto treasure
        map[player.row][player.col] = TILE_OPEN; // Update icon
        map[nextRow][nextCol] = TILE_PLAYER;

        player.treasure += 1; // Update treasure

        player.row = nextRow; // Update player
        player.col = nextCol;
        return STATUS_TREASURE;
    }

    if (map[nextRow][nextCol] == TILE_AMULET) { // Moving onto amulet
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow; // Update player
        player.col = nextCol;

        return STATUS_AMULET;
    }

    if (map[nextRow][nextCol] == TILE_OPEN) { // Moving onto open   
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;

        player.row = nextRow; // Update player
        player.col = nextCol;

        return STATUS_MOVE;
    } 

    if (map[nextRow][nextCol] == TILE_DOOR) { // Moving onto door   
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        
        player.row = nextRow; // Update player
        player.col = nextCol;

        return STATUS_LEAVE;
    }

    return STATUS_STAY;

}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {

    for (int i = player.row+1; i < maxRow; ++i) { // Check Down
        if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
        else if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i - 1][player.col] = TILE_MONSTER;
        }
    }

    for (int i = player.row-1; i >= 0; --i) { // Check Up
        if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
        else if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER;
        }
    }

    for (int i = player.col+1; i < maxCol; ++i) { // Check Right
        if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
        else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i - 1] = TILE_MONSTER;
        }
    }

    for (int i = player.col-1; i >= 0; --i) { // Check Left
        if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
        else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i + 1] = TILE_MONSTER;
        }
    }
    
    if (map[player.row][player.col] == TILE_MONSTER) { // Check if dead
        return true;
    }

    return false;
}

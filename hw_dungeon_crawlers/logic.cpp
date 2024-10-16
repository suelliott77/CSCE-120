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
    // checks is the file actually opens 
    std::ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()) {
        cout << "ERROR: Unable to open: " << fileName << endl;
        return nullptr;
    }

    // dimensions
    fin >> maxRow;
    if (fin.fail()) { // checks both of the dimensions if it fails or not 
        return nullptr;
    }
    fin >> maxCol;
    if (fin.fail()) {
        return nullptr;
    }
    // looks at the dimensions, makes sure its less than max 
    if (INT32_MAX / maxCol < maxRow) {
        return nullptr;
    }

    // location
    fin >> player.row;
    if (fin.fail()) { // checks both to make sure it didnt fail 
        return nullptr;
    }
    fin >> player.col;
    if (fin.fail()) {
        return nullptr;
    }

    // checks the dimensions and that they are valid
    if ((player.row < 0) || (player.col < 0) || 
    (player.col >= maxCol) || (player.row >= maxRow) || 
    (maxRow <= 0) || (maxCol <= 0)) {
        return nullptr;
    }
    if ((maxCol > 999999) || (maxRow > 999999)) {
        return nullptr;
    }

    char** dungeon = createMap(maxRow,maxCol);   

    if (dungeon == nullptr) {         
        //cout << "ERROR: Map did not load." << endl;  
        deleteMap(dungeon, maxRow);       
        return nullptr;     
    }

    bool isExit = false;
    // makes the map and puts player in the map
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            fin >> dungeon[i][j];
            if (fin.fail()) {
                deleteMap(dungeon, maxRow);
                return nullptr;
            }

            if (i == player.row && j == player.col) { // puts player in the map
                dungeon[i][j] = TILE_PLAYER;
            }

            if ((dungeon[i][j] == TILE_EXIT) || (dungeon[i][j] == TILE_DOOR)) {
                isExit = true;
            }
        }
    }
    //checks after all characters are put in 
    char trash;
    fin >> trash;
    if(!fin.fail() && !isspace(trash)){
        deleteMap(dungeon, maxRow);
        return nullptr;
    }

    if (isExit) { // checks is there are doors or not 
        return dungeon;
    }
    else {
        deleteMap(dungeon, maxRow);
        return nullptr;
    }



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
    switch(input) {
        case MOVE_LEFT:
            nextCol--;
            break;
        case MOVE_DOWN:
            nextRow++;
            break;
        case MOVE_UP:
            nextRow--;
            break;
        case MOVE_RIGHT:
            nextCol++;
            break;
        default:
            break;
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
    char** tiles = new char*[maxRow];
    char* curr;
    
    for (int i = 0; i < maxRow; i++) {
        curr = new char[maxCol];
        for (int j = 0; j < maxCol; j++) {
            curr[j] = TILE_OPEN;
        }
        tiles[i] = curr;
    }

return tiles;

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
    for (int i = 0; i < maxRow; ++i) {
        if (map == nullptr) {
            break;
        }

        delete[] map[i];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
        
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
    if ((map == nullptr) || (maxRow < 1) || (maxCol < 1)) {
        return nullptr;
    }

    int temp_max_row = 2*maxRow;
    int temp_max_col = 2*maxCol;

    char** new_map = new char*[temp_max_row];
    char* curr;
    
    for (int j = 0; j < temp_max_row; j++) {
        curr = new char[temp_max_col];
        new_map[j] = curr;
    }
        
    int playerR = 0;
    int playerC = 0;

    for (int a = 0; a < maxRow; a++) {
        for (int b = 0; b < maxCol; b++) {
            if (map[a][b] == 'o') {
                playerR = a;
                playerC = b;
            }
        }
    }
    
    map[playerR][playerC] = TILE_OPEN;
    for (int a = 0; a < temp_max_row; a++) {
        for (int b = 0; b < temp_max_col; b++) {
            new_map[a][b] = map[a % maxRow][b % maxCol];
        }
    }
    new_map[playerR][playerC] = 'o';

    deleteMap(map, maxRow);

    maxRow = temp_max_row;
    maxCol = temp_max_col;

    return new_map;
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
    
    if(nextCol >= maxCol || nextCol < 0) {         
        nextRow = player.row;         
        nextCol = player.col;         
        return 0;     
    }     

    if(nextRow >= maxRow || nextRow < 0) {         
        nextRow = player.row;        
        nextCol = player.col;         
        return 0;     
    }     

    if(map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) {         
        nextRow = player.row;         
        nextCol = player.col;         
        return 0;     
    }     

    if(map[nextRow][nextCol] == TILE_TREASURE) {         
        player.treasure++;         
        map[player.row][player.col] = TILE_OPEN;         
        map[nextRow][nextCol] = TILE_PLAYER;          
        player.row = nextRow;         
        player.col = nextCol;         
        return 2;     
    }     

    if(map[nextRow][nextCol] == TILE_AMULET) {         
        map[player.row][player.col] = TILE_OPEN;         
        map[nextRow][nextCol] = TILE_PLAYER;          
        player.row = nextRow;         
        player.col = nextCol;         
        return 3;     
    }     

    if(map[nextRow][nextCol] == TILE_DOOR) {         
        map[player.row][player.col] = TILE_OPEN;         
        map[nextRow][nextCol] = TILE_PLAYER;          
        player.row = nextRow;         
        player.col = nextCol;         
        return 4;     
    }   

    if(map[nextRow][nextCol] == TILE_EXIT) {         
        if(player.treasure >= 1) {             
            map[player.row][player.col] = TILE_OPEN;             
            map[nextRow][nextCol] = TILE_PLAYER;              
            player.row = nextRow;             
            player.col = nextCol;             
            return 5;         
        }         
        nextRow = player.row;         
        nextCol = player.col;         
        return 0;     
    }  

    map[player.row][player.col] = TILE_OPEN;     
    map[nextRow][nextCol] = TILE_PLAYER;      
    player.row = nextRow;     
    player.col = nextCol;      
    return 1; 

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
    for (int i = player.row - 1; i>= 0; --i) {
        if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
        if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER;
        }
    }
    
    for (int j = player.row+1; j < maxRow; ++j) {
        if (map[j][player.col] == TILE_PILLAR) {
            break;
        }
        if (map[j][player.col] == TILE_MONSTER) {
            map[j][player.col] = TILE_OPEN;
            map[j - 1][player.col] = TILE_MONSTER;
        }
    }
    
    for (int q = player.col + 1; q < maxCol; ++q) {
        if (map[player.row][q] == TILE_PILLAR) {
            break;
        }
        if (map[player.row][q] == TILE_MONSTER) {
            map[player.row][q] = TILE_OPEN;
            map[player.row][q - 1] = TILE_MONSTER;
        }
    }
    for (int r = player.col - 1; r >= 0; --r) {
        if (map[player.row][r] == TILE_PILLAR) {
            break;
        }
        if (map[player.row][r] == TILE_MONSTER) {
            map[player.row][r] = TILE_OPEN;
            map[player.row][r + 1] = TILE_MONSTER;
        }
    }
    
    if (map[player.row][player.col] == TILE_MONSTER) {
        return true;
    }

    return false;
    // for (int i = player.row; i >= 0; i--) {
        //if (map[i][player.col] == TILE_PILLAR) {
            //break;
        //}
        //else if (map[i][player.col] == TILE_MONSTER) {
            //map[i][player.col] = TILE_OPEN;
            //map[i + 1][player.col] = TILE_MONSTER;
        //}
        // }
        // 
        // Looking down
        // for (int i = player.row; i < maxCol; i++) {
            //if (map[i][player.col] == TILE_PILLAR) {
                //break;
                //}
            //else if (map[i][player.col] == TILE_MONSTER) {
                //map[i][player.col] = TILE_OPEN;
                //map[i - 1][player.col] = TILE_MONSTER;
            //}
            // }
            // 
            // Looking left
            // for (int i = player.col; i >= 0; i--) {
                //if (map[player.row][i] == TILE_PILLAR) {
                    //break;
                //}
                //else if (map[player.row][i] == TILE_MONSTER) {
                        //map[player.row][i] = TILE_OPEN;
                        //map[player.row][i + 1] = TILE_MONSTER;
                //}
            // }
            // 
            // Looking right
            // for (int i = player.col; i < maxRow; i++) {
                //if (map[player.row][i] == TILE_PILLAR) {
                    //break;
                //}
                //else if (map[player.row][i] == TILE_MONSTER) {
                    //map[player.row][i] = TILE_OPEN;
                    //map[player.row][i - 1] = TILE_MONSTER;
                    //}
                    // }
                    // 
                    // Checking if monster on player
            // if (map[player.row][player.col] == TILE_MONSTER) {
                //return true;
                // }
                // else {return false;}
                //}
}

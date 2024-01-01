#include <raylib.h>

#include "game.hpp"


using namespace map;

Tile::Tile(const int& inX, const int& inY, const int& inId)
{
    x = inX;
    y = inY;
    id = inId;
}

int Tile::WorldX()
{
    return x * TILES_SIZE;
}

int Tile::WorldY()
{
    return y * TILES_SIZE;
}

bool Tile::IsRoad()
{
    if (groundType == GroundType::GD_ROAD || groundType == GroundType::GD_DIRT || groundType == GroundType::GD_EXIT || groundType == GroundType::GD_WAY_UP || groundType == GroundType::GD_WAY_DOWN || groundType == GroundType::GD_WAY_RIGHT || groundType == GroundType::GD_WAY_LEFT)
    {
        return true;
    }

    return false;
}

Map::Map()
{
    int mapWidth = SCREEN_WIDTH/TILES_SIZE;
    int mapHeight = (SCREEN_HEIGHT - 120)/TILES_SIZE;

    int count = 0;
    for (int j = 0; j < mapHeight; j++)
    {
        for (int i = 0; i < mapWidth; i++)
        {
            tilesArray.push_back({i, j, count});
            count++;
        }
    }
}

const char* Tile::GetLabel(GroundType type)
{
    switch (type)
    {
        default:
        case GroundType::GD_UNKNOWN: return "UNKNOWN";
        case GroundType::GD_DIRT: return "DIRT";
        case GroundType::GD_SAND: return "SAND";
        case GroundType::GD_ROAD: return "ROAD";
        case GroundType::GD_GRASS: return "GRASS";
        case GroundType::GD_EXIT: return "EXIT";
        case GroundType::GD_BUSH: return "BUSH";
        case GroundType::GD_GR_ROCK: return "GR_ROCK";
        case GroundType::GD_SD_ROCK: return "SD_ROCK";
        case GroundType::GD_WAY_UP: return "WAY_UP";
        case GroundType::GD_WAY_DOWN: return "WAY_DOWN";
        case GroundType::GD_WAY_RIGHT: return "WAY_RIGHT";
        case GroundType::GD_WAY_LEFT: return "WAY_LEFT";
    }
}

void Map::InitMap(const char* level, int entry, enemy::EnemyDir INfirstDir)
{
    mFirstDir = INfirstDir;
    mEntryId = entry;
    int mapWidth = SCREEN_WIDTH/TILES_SIZE;
    for (int j = 0; j < (SCREEN_HEIGHT - 120)/TILES_SIZE; j++)
    {
        for (int i = 0; i < mapWidth; i++)
        {
            int count = i + j * mapWidth;
            Tile tile = {i, j, count};

            if (level[count] == 'E')
            {
                tile.groundType = map::GroundType::GD_EXIT;
                if (mExitId == -1)
                    mExitId = count;
                else if (mSecondaryExitId == -1)
                    mSecondaryExitId = count;
                //else
                    // WHAT???
            }

            else if (level[count] == 'R')
            {
                tile.groundType = map::GroundType::GD_ROAD;
            }
            else if (level[count] == 'u')
            {
                tile.groundType = map::GroundType::GD_WAY_UP;
            }
            else if (level[count] == 'd')
            {
                tile.groundType = map::GroundType::GD_WAY_DOWN;
            }
            else if (level[count] == 'r')
            {
                tile.groundType = map::GroundType::GD_WAY_RIGHT;
            }
            else if (level[count] == 'l')
            {
                tile.groundType = map::GroundType::GD_WAY_LEFT;
            }

            else if (level[count] == 'D')
            {
                tile.groundType = map::GroundType::GD_DIRT;
            }
            else if (level[count] == '_')
            {
                tile.groundType = map::GroundType::GD_SAND;
            }
            else if (level[count] == '#')
            {
                tile.groundType = map::GroundType::GD_BUSH;
                tile.free = false;
            }
            else if (level[count] == 'o')
            {
                tile.groundType = map::GroundType::GD_GR_ROCK;
                tile.free = false;
            }
            else if (level[count] == 'O')
            {
                tile.groundType = map::GroundType::GD_SD_ROCK;
                tile.free = false;
            }
            else
            {
                tile.groundType = map::GroundType::GD_GRASS;
            }

            tilesArray.push_back(tile);
            count++;
        }
    }
}

Map::Map(const char* level, int entry, enemy::EnemyDir INfirstDir)
{
    InitMap(level, entry, INfirstDir);
}

Map::~Map()
{
    tilesArray.clear();
}

void Map::DrawTiles(Texture2D& tileSheet) const
{
    for (map::Tile tile : tilesArray)
    {
        Color color;
        const char* label;
        Rectangle src;
        switch (tile.groundType)
        {
            case map::GroundType::GD_UNKNOWN :
                color = WHITE;
                label = "UNKNOWN";
                break;

            case map::GroundType::GD_DIRT :
                color = BROWN;
                label = "DIRT";
                src = {1280, 384, 64, 64};
                break;
            
            case map::GroundType::GD_SAND :
                color = YELLOW;
                label = "SAND";
                src = {1408, 384, 64, 64};
                break;

            case map::GroundType::GD_SD_ROCK :
                color = YELLOW;
                label = "SAND";
                src = {1408, 384, 64, 64};
                break;

            case map::GroundType::GD_ROAD :
                color = GRAY;
                label = "ROAD";
                src = {1344, 384, 64, 64};
                break;
            
            case map::GroundType::GD_WAY_UP :
                color = GRAY;
                label = "ROAD";
                src = {1344, 384, 64, 64};
                break;

            case map::GroundType::GD_WAY_DOWN :
                color = GRAY;
                label = "ROAD";
                src = {1344, 384, 64, 64};
                break;

            case map::GroundType::GD_WAY_RIGHT :
                color = GRAY;
                label = "ROAD";
                src = {1344, 384, 64, 64};
                break;

            case map::GroundType::GD_WAY_LEFT :
                color = GRAY;
                label = "ROAD";
                src = {1344, 384, 64, 64};
                break;

            case map::GroundType::GD_GRASS :
                color = GREEN;
                label = "GRASS";
                src = {1216, 384, 64, 64};
                break;

            case map::GroundType::GD_BUSH :
                color = GREEN;
                label = "GRASS";
                src = {1216, 384, 64, 64};
                break;

            case map::GroundType::GD_GR_ROCK :
                color = GREEN;
                label = "GRASS";
                src = {1216, 384, 64, 64};
                break;

            case map::GroundType::GD_EXIT :
                color = GRAY;
                label = "EXIT";
                src = {1472, 0, 64, 64};

                break;

            default:
                color = WHITE;
                label = "UNKNOWN";
                break;
        }
        DrawRectangle(tile.WorldX(), tile.WorldY(), TILES_SIZE, TILES_SIZE, color);
        DrawTexturePro(tileSheet, src, {(float)tile.WorldX(), (float)tile.WorldY(), 80, 80}, {0,0}, 0, WHITE);
        if (tile.groundType == map::GroundType::GD_BUSH)
        {
            DrawTexturePro(tileSheet, {960, 320, 64, 64}, {(float)tile.WorldX() + 10, (float)tile.WorldY() + 10, 64, 64}, {0,0}, 0, WHITE);
        }
        else if (tile.groundType == map::GroundType::GD_GR_ROCK || tile.groundType == map::GroundType::GD_SD_ROCK)
        {
            DrawTexturePro(tileSheet, {1344, 320, 64, 64}, {(float)tile.WorldX() + 10, (float)tile.WorldY() + 10, 64, 64}, {0,0}, 0, WHITE);
        }

    }
}

void Map::DrawFrame()
{
    for (int i = 0; i < 20; i++)
    {
        DrawLine(tilesArray[i].WorldX(), tilesArray[i].WorldY(), tilesArray[i + 160].WorldX(), tilesArray[i + 160].WorldY() + 80, BLACK);
    }

    for (int i = 0; i < 10; i++)
    {
        DrawLine(tilesArray[i*20].WorldX(), tilesArray[i*20].WorldY(), tilesArray[i*20].WorldX() + SCREEN_WIDTH, tilesArray[i*20].WorldY(), BLACK);
    }
}

void Map::ChangeMap(const char* newOne, int entry, enemy::EnemyDir INfirstDir)
{
    tilesArray.clear();

    InitMap(newOne, entry, INfirstDir);
}

Tile& Map::GetTile(const int& x, const int& y)
{
    for(Tile& t : tilesArray)
        if(t.X() == x && t.Y() == y)
            return t;
    return tilesArray[0];
}
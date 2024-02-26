#include <graphics.h>
#include <conio.h>
#include <time.h>

#define GAME_WIDTH   800 // 游戏窗口宽度
#define GAME_HEIGHT  600 // 游戏窗口高度
#define MAP_SIZE     17  // 地图格子大小
#define MAX_SNAKE_LEN 100 // 蛇的最大长度

// 蛇的结构体
struct Snake {
    int x; // 蛇头x坐标
    int y; // 蛇头y坐标
    int len; // 蛇的长度
    int body[MAX_SNAKE_LEN][2]; // 蛇的身体
    int dir; // 蛇的方向
    int size;
};

// 食物的结构体
struct Food {
    int x; // 食物x坐标
    int y; // 食物y坐标
    int color; // 食物颜色
};

int map[GAME_WIDTH / MAP_SIZE][GAME_HEIGHT / MAP_SIZE] = { 0 }; // 地图
Snake snake; // 蛇
Food food; // 食物

// 初始化窗口
void InitWindow() {
    initgraph(GAME_WIDTH, GAME_HEIGHT);
    setbkcolor(RGB(255,192,203));
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
                map[i][j] = 0;
        }
    }
    cleardevice();

}

// 初始化蛇
void InitSnake() {
    snake.x = GAME_WIDTH / 2 / MAP_SIZE * MAP_SIZE;
    snake.y = GAME_HEIGHT / 2 / MAP_SIZE * MAP_SIZE;
    snake.len = 3;
    snake.body[0][0] = snake.x;
    snake.body[0][1] = snake.y;
    snake.body[1][0] = snake.x - MAP_SIZE;
    snake.body[1][1] = snake.y;
    snake.body[2][0] = snake.x - 2 * MAP_SIZE;
    snake.body[2][1] = snake.y;
    snake.dir = VK_RIGHT;
}

// 初始化食物
void InitFood() {
    srand(time(NULL));
    food.x = rand() % (GAME_WIDTH / MAP_SIZE) * MAP_SIZE;
    food.y = rand() % (GAME_HEIGHT / MAP_SIZE) * MAP_SIZE;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

// 绘制蛇
void DrawSnake() {
    for (int i = 0; i < snake.len; i++) {
        setfillcolor(RGB(0, 200, 200));
        fillrectangle(snake.body[i][0], snake.body[i][1], snake.body[i][0] + MAP_SIZE, snake.body[i][1] + MAP_SIZE);
    }
}

// 绘制食物
void DrawFood() {
    setfillcolor(food.color);
    fillcircle(food.x + MAP_SIZE / 2, food.y + MAP_SIZE / 2, MAP_SIZE / 2);
}

// 更新地图
void UpdateMap() {
    { 
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (map[i][j] == 2) {
                    map[i][j] = 0;
                }
            }
        }
        map[snake.x / MAP_SIZE][snake.y / MAP_SIZE] = 2;
    }
    map[food.x / MAP_SIZE][food.y / MAP_SIZE] = 3;
}

// 检测蛇是否吃到食物
void CheckEat() {
    if (snake.x == food.x && snake.y == food.y) {
        snake.len++;
        snake.body[snake.len - 1][0] = snake.body[snake.len - 2][0];
        snake.body[snake.len - 1][1] = snake.body[snake.len - 2][1];
        InitFood();
    }
}

// 检测蛇是否死亡
bool CheckDead() {
    if (snake.x < 0 || snake.x >= GAME_WIDTH || snake.y < 0 || snake.y >= GAME_HEIGHT) {
        return true;
    }
      if (map[snake.x/MAP_SIZE][snake.y/MAP_SIZE]==1) {
            return true;
        }
    return false;
}

// 更新蛇的位置
void UpdateSnake() {
    for (int i = snake.len - 1; i > 0; i--) {
        snake.body[i][0] = snake.body[i - 1][0];
        snake.body[i][1] = snake.body[i - 1][1];
    }
    switch (snake.dir) {
    case VK_UP:
        snake.y -= MAP_SIZE;
        break;
    case VK_DOWN:
        snake.y += MAP_SIZE;
        break;
    case VK_LEFT:
        snake.x -= MAP_SIZE;
        break;
    case VK_RIGHT:
        snake.x += MAP_SIZE;
        break;
    default:
        break;
    }
    snake.body[0][0] = snake.x;
    snake.body[0][1] = snake.y;
}

// 检测键盘输入
void CheckKey() {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
        case 'W':
        case 'w':
            if (snake.dir != VK_DOWN) {
                snake.dir = VK_UP;
            }
            break;
        case 'S':
        case 's':
            if (snake.dir != VK_UP) {
                snake.dir = VK_DOWN;
            }
            break;
        case 'A':
        case 'a':
            if (snake.dir != VK_RIGHT) {
                snake.dir = VK_LEFT;
            }
            break;
        case 'D':
        case 'd':
            if (snake.dir != VK_LEFT) {
                snake.dir = VK_RIGHT;
            }
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
        default:
            break;
        }
    }
}

// 游戏主循环
void GameLoop() {
    while (true) {
        cleardevice();
        DrawSnake();
        DrawFood();
        UpdateMap();
        CheckEat();
        UpdateSnake();
        if (CheckDead())
        {
            MessageBox(NULL, _T("游戏结束"), _T("提示"), MB_OK);
            break;
        }
        CheckKey();
        Sleep(130);
    }
}
int main() {
    InitWindow();
    InitSnake();
    InitFood();
    GameLoop();
    closegraph();
    return 0;
}
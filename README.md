# 公告
C++版的Canary版可能无法运行（编译错误），您可以游玩网页版。

# CHESTS IN THE MAPS Release Version 简介

这是一个**基于C++控制台开发的类Minecraft冒险游戏**，核心玩法是：随机生成地图→开箱子获取资源→击杀怪物→激活下界传送门→进入下界冒险→完成成就，支持存档读档、作弊指令、多游戏模式等完整功能。

## 一、核心功能总览

|模块|功能说明|
|---|---|
|地图生成|随机生成主世界/下界地图，包含墙壁、空地、箱子、怪物、传送门|
|玩家系统|生命值、饱食度、金钱、背包系统，支持移动、攻击、使用道具|
|怪物系统|主世界：僵尸、骷髅（射箭）；下界：熔岩僵尸、燃烧骷髅、烈焰人|
|道具系统|矿石、药水、末影珍珠、打火石、录音带（播放音乐）、末地钥匙|
|交互系统|开箱子、商店买卖、吃东西、使用道具、查看背包/成就|
|指令系统|支持/kill、/tp、/give、/gamemode等MC风格作弊指令|
|存档系统|自动保存地图、背包、坐标、怪物状态，支持读取存档|
|成就系统|8个游戏成就，解锁后提示|
## 二、核心数据结构

### 1. 全局变量

- 地图：`overworld[N][N]`（主世界）、`nether[N][N]`（下界）

- 玩家：坐标`x/y`、方向`fx`、生命值`hp`、饱食度`full`、金钱`money`

- 背包：`inventory[30]` 存储所有道具数量

- 怪物：用结构体`MobData`存储坐标、生命值、朝向，分僵尸/骷髅/烈焰人等数组

### 2. 枚举与映射

- 方块枚举：定义主世界/下界所有方块的数字ID（泥土、墙壁、箱子、怪物等）

- 映射表：`num_to_char_mp`（数字转显示字符）、`block_color`（方块控制台颜色）

## 三、核心函数解析

### 1. 地图生成

```C++

void make_world();       // 生成主世界
void make_world_nether();// 生成下界
void make_wall();        // 随机生成墙壁
void checkRoad();        // 检测地图是否有通路（保证可玩）
```

- 逻辑：随机填充墙壁→DFS检测玩家起点到终点是否连通→不连通则重新生成→放置箱子、怪物、传送门

### 2. 渲染显示

```C++

void mp();         // 渲染主世界（彩色控制台、显示状态）
void mp_Nether();   // 渲染下界
```

- 用`SetConsoleTextAttribute`实现**彩色方块显示**

- 顶部实时显示金钱、生命值、饱食度

- 调试模式可查看坐标、怪物状态、地图数据

### 3. 核心交互

```C++

void chest();       // 开箱子（随机获取资源）
void shop();        // 商店（买卖道具）
void useItem();     // 使用道具（末影珍珠、药水、打火石等）
void eatFood();     // 吃东西恢复饱食度
```

### 4. 怪物AI

- 追踪玩家：3格范围内自动向玩家移动

- 攻击逻辑：近战怪物贴身造成伤害；远程怪物（骷髅/烈焰人）发射箭矢/火焰弹

- 生命值：怪物受击后切换显示样式，死亡后掉落道具

### 5. 存档/读档

```C++

void read_dat();   // 读取存档文件
void write_dat();  // 写入存档文件
```

- 存档文件：`chest-game-data.dat`，存储地图、背包、坐标、怪物、成就等所有数据

- 皮肤文件：`skin.txt`，存储玩家自定义显示字符和颜色

### 6. 作弊指令

```C++

void do_order();
```

支持指令：

- `/kill <实体> <ID/all>`：杀死怪物/玩家

- `/tp <x> <y>`：传送玩家

- `/give <道具> <数量>`：给予道具

- `/gamemode`：切换生存/创造/冒险模式

## 四、游戏操作指南

|按键|功能|
|---|---|
|`W/A/S/D`|上下左右移动|
|`K`|攻击相邻怪物|
|`O`|打开前方箱子|
|`E`|查看背包|
|`Q`|吃东西|
|`U`|使用道具|
|`P`|查看成就|
|`/`|输入作弊指令（需开启作弊）|
|`1`|切换调试模式|
|`R`|返回主界面|
## 五、游戏流程

1. **启动游戏**：选择新建世界/读取存档

2. **主世界冒险**：移动→开箱子获取资源→击杀怪物赚道具

3. **解锁传送门**：用打火石激活终点门，解锁成就

4. **进入下界**：挑战更强怪物（熔岩僵尸、烈焰人）

5. **完成目标**：击杀烈焰人获取**末地钥匙**，解锁最终内容

6. **死亡机制**：生存模式死亡掉落物品，冒险模式死亡直接结束游戏

## 六、运行说明

1. 编译器：支持**Dev-C++、Code::Blocks、Visual Studio**

2. 系统：Windows（依赖`windows.h`、`conio.h`控制台库）

3. 运行后自动生成存档文件，关闭游戏自动保存

这是一个非常完整的**控制台版Minecraft小游戏**，代码结构清晰，功能丰富，非常适合C++初学者学习控制台图形化、数据存储、游戏逻辑开发！

# CHESTS IN THE MAPS Canary Version 简介

《Chests in the Maps》是一款可通过浏览器直接访问游玩的网页游戏，官网地址为[https://chests-game.pages.dev/](https://chests-game.pages.dev/) ，从页面展示信息来看，游戏围绕“宝箱”与“地图探索”打造核心玩法，且已推出全新的“下界（The Nether）”关卡，是游戏的进阶新内容。

### 核心基础功能

游戏页面提供了玩家游玩所需的核心操作入口，功能简洁且指向明确：

1. **🎮开始游戏**：直接进入游戏主玩法，开启地图探索与宝箱相关的冒险；

2. **🏆成就进度**：可查看游戏内各类成就的完成情况，为探索提供目标导向；

3. **📂读取存档**：支持存档功能，玩家可继续之前的游戏进度，无需重新开始；

4. **⚙️游戏设置**：可对游戏的基础游玩参数进行调整，适配个人操作习惯。

### 游戏核心线索

从游戏名称《Chests in the Maps》（地图中的宝箱）和“下界”新关卡的提示来看，**地图探索**与**宝箱收集/解锁**是游戏的核心玩法方向，大概率会包含不同难度的地图场景、隐藏的宝箱线索、关卡进阶挑战等内容，而下界作为“新等级”关卡，预计会有更具挑战性的探索机制和宝箱奖励设定。

目前该游戏从公开页面暂未展示更多玩法细节（如操作方式、宝箱奖励、地图类型等），可通过点击页面“开始游戏”入口体验完整内容，整体为轻量化网页游戏，无需下载安装，浏览器直接访问即可游玩。

# Chests in the Maps Canary Version: Console and Web Game Overview

# Announcement

The C++ Canary version may fail to run (compilation errors). You can play the web version instead.

# Introduction to CHESTS IN THE MAPS Release Version

This is a **Minecraft-like adventure game developed in C++ console**. The core gameplay loop is:

randomly generate a map → open chests for resources → kill monsters → activate the Nether portal → adventure in the Nether → complete achievements.

It includes full features such as save/load, cheat commands, and multiple game modes.

## I. Core Features Overview

|Module|Description|
|---|---|
|Map Generation|Randomly generates Overworld / Nether maps with walls, empty spaces, chests, monsters, and portals|
|Player System|Health, hunger, money, inventory; supports movement, attack, item usage|
|Monster System|Overworld: Zombie, Skeleton (ranged); Nether: Lava Zombie, Burning Skeleton, Blaze|
|Item System|Ores, potions, Ender Pearls, Flint and Steel, cassettes (music), End Key|
|Interaction|Open chests, shop, eat food, use items, view inventory / achievements|
|Command System|Minecraft-style cheats: /kill, /tp, /give, /gamemode, etc.|
|Save System|Auto-saves map, inventory, position, monster states; supports loading|
|Achievement System|8 in-game achievements with unlock notifications|
## II. Core Data Structures

### 1. Global Variables

- Maps: `overworld[N][N]` (Overworld), `nether[N][N]` (Nether)

- Player: coordinates `x/y`, direction `fx`, health `hp`, hunger `full`, money `money`

- Inventory: `inventory[30]` stores item counts

- Monsters: Struct `MobData` stores position, HP, direction; separate arrays for Zombie, Skeleton, Blaze, etc.

### 2. Enums & Mappings

- Block enum: Defines numeric IDs for all Overworld / Nether blocks (dirt, wall, chest, monster, etc.)

- Mapping tables: `num_to_char_mp` (number to display character), `block_color` (console color for blocks)

## III. Core Function Breakdown

### 1. Map Generation

```C++

void make_world();       // Generate Overworld
void make_world_nether();// Generate Nether
void make_wall();        // Randomly generate walls
void checkRoad();        // Ensure the map is traversable
```

- Logic: Randomly place walls → DFS check path from spawn to end → regenerate if disconnected → place chests, monsters, portals

### 2. Rendering

```C++

void mp();         // Render Overworld (color console, status display)
void mp_Nether();   // Render Nether
```

- Uses `SetConsoleTextAttribute` for **colored block display**

- Top bar shows real-time money, health, hunger

- Debug mode displays coordinates, monster states, map data

### 3. Core Interaction

```C++

void chest();       // Open chest (random resources)
void shop();        // Shop (buy/sell items)
void useItem();     // Use items (Ender Pearl, potion, Flint and Steel)
void eatFood();     // Restore hunger
```

### 4. Monster AI

- Chase: Automatically moves toward player within 3 blocks

- Attack: Melee monsters deal damage on contact; ranged (Skeleton / Blaze) fire arrows / fireballs

- HP: Visual changes when damaged; drops items on death

### 5. Save / Load

```C++

void read_dat();   // Load save file
void write_dat();  // Write save file
```

- Save file: `chest-game-data.dat` stores map, inventory, position, monsters, achievements

- Skin file: `skin.txt` for custom player character and color

### 6. Cheat Commands

```C++

void do_order();
```

Supported commands:

- `/kill <entity> <ID/all>`: Kill monster / player

- `/tp <x> <y>`: Teleport player

- `/give <item> <amount>`: Give items

- `/gamemode`: Switch Survival / Creative / Adventure

## IV. Controls

|Key|Function|
|---|---|
|`W/A/S/D`|Move up/left/down/right|
|`K`|Attack adjacent monster|
|`O`|Open chest in front|
|`E`|Open inventory|
|`Q`|Eat food|
|`U`|Use item|
|`P`|View achievements|
|`/`|Enter cheat command (cheats enabled)|
|`1`|Toggle debug mode|
|`R`|Return to main menu|
## V. Game Flow

1. **Launch**: New world / Load save

2. **Overworld**: Move → loot chests → fight monsters

3. **Unlock Portal**: Activate end portal with Flint and Steel

4. **Enter Nether**: Fight stronger mobs (Lava Zombie, Blaze)

5. **Complete Goal**: Kill Blaze to get **End Key** and unlock final content

6. **Death**: Survival drops items; Adventure ends game on death

## VI. Run Instructions

1. Compiler: Supports **Dev-C++, Code::Blocks, Visual Studio**

2. OS: Windows (depends on `windows.h`, `conio.h`)

3. Auto-saves on exit; creates save files automatically

This is a fully-featured **console Minecraft clone**. With clean structure and rich functions, it is excellent for C++ beginners to learn console graphics, data storage, and game logic development.

---

# Introduction to CHESTS IN THE MAPS Canary Version

*Chests in the Maps* is a browser-based game playable directly online. Official site: [https://chests-game.pages.dev/](https://chests-game.pages.dev/).

Based on the page info, the game centers on **chests and map exploration** and has introduced a new “The Nether” stage as advanced content.

### Core Basic Features

The page provides clear, essential gameplay options:

1. **🎮 Start Game** – Begin map exploration and chest-collecting adventure

2. **🏆 Achievements** – View progress and goals

3. **📂 Load Save** – Continue previous progress

4. **⚙️ Settings** – Adjust gameplay parameters

### Gameplay Core

From the title *Chests in the Maps* and the Nether stage, **exploration** and **chest collection/unlocking** are the core loops.

It likely includes multiple difficulty maps, hidden chest clues, and progressive challenges.

The Nether, as a new high-difficulty area, is expected to feature tougher mechanics and better rewards.

More details (controls, rewards, map types) are not fully shown on the public page.

You can experience the full game by clicking **Start Game**. It is a lightweight web game with no installation required.

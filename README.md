# CHESTS IN THE MAPS

## 项目概述

《Chests in the Maps》是一款类 Minecraft 的冒险游戏，分为**C\+\+ 控制台版（Release Version）** 和**网页版（Canary Version）** 两个版本。核心玩法围绕「随机地图探索→宝箱收集→怪物击杀→下界冒险→成就达成」展开，兼具完整的游戏系统与轻量化的游玩体验。

## CHESTS IN THE MAPS Release Version 简介

这是基于 C\+\+ 控制台开发的完整版本，依赖 Windows 控制台库实现，具备丰富的游戏系统与自定义功能，适合 C\+\+ 学习者研究控制台图形化、游戏逻辑开发。

### 1\. 核心功能总览

|模块|功能说明|
|---|---|
|地图生成|随机生成主世界 / 下界地图，包含墙壁、空地、宝箱、怪物、传送门，保证地图通路可玩|
|玩家系统|生命值、饱食度、金钱、背包系统，支持移动、攻击、道具使用等基础操作|
|怪物系统|主世界（僵尸、骷髅）、下界（熔岩僵尸、燃烧骷髅、烈焰人），区分近战 / 远程攻击|
|道具系统|矿石、药水、末影珍珠、打火石、录音带（播放音乐）、末地钥匙等多样道具|
|交互系统|开箱子、商店买卖、吃东西、查看背包 / 成就，交互逻辑完整|
|指令系统|支持 /kill、/tp、/give、/gamemode 等 MC 风格作弊指令|
|存档系统|自动保存地图、背包、坐标、怪物状态到本地文件，支持读取存档|
|成就系统|8 个游戏成就，解锁后实时提示，引导游戏流程|

### 2\. 核心数据结构

#### 全局变量

- 地图：`overworld\[N\]\[N\]`（主世界）、`nether\[N\]\[N\]`（下界）

- 玩家：坐标`x/y`、方向`fx`、生命值`hp`、饱食度`full`、金钱`money`

- 背包：`inventory\[30\]` 存储所有道具数量

- 怪物：结构体`MobData`存储坐标、生命值、朝向，按类型分数组管理

#### 枚举与映射

- 方块枚举：定义主世界 / 下界所有方块的数字 ID（泥土、墙壁、宝箱等）

- 映射表：`num\_to\_char\_mp`（数字转显示字符）、`block\_color`（控制台方块颜色）

### 3\. 核心函数解析

```cpp
// Entity
void update_mobs_overworld();
void update_mobs_nether();
void check_attack_overworld();
void check_attack_nether();

// Map
void print_map();
void print_map_Nether();
void generation_wall();
void generation_world();
void generation_world_nether();
void checkRoad();
int nether_block_check();

// UI & Gameplay
void title_screen();
void options();
void chest();
void chest_nether();
void shop();
void useItem();
void useItem_nether();
void eatFood();
void view_inventory();
void view_advencements();
void command();
void statistic();
int game_menu();

// Game Logic
void game_overworld();
void game_nether();

// Save & Load
void read_game_data();
void write_game_data();

// Easter egg
void eggs_mcplayer123();
```

### 4\. 怪物 AI

- 追踪：3 格范围内自动向玩家移动

- 攻击：近战怪物贴身造成伤害；远程怪物（骷髅 / 烈焰人）发射箭矢 / 火焰弹

- 状态：受击后切换显示样式，死亡掉落道具

### 5\. 操作指南

|按键|功能|
|---|---|
|`W/A/S/D`|上下左右移动|
|`K`|攻击相邻怪物|
|`O`|打开前方箱子|
|`E`|查看背包|
|`Q`|吃东西恢复饱食度|
|`U`|使用道具|
|`P`|查看成就|
|`/`|输入作弊指令（需开启作弊）|
|`1`|切换调试模式|
|`R`|返回主界面|
>提示：你可以在选项里按键绑定

### 6\. 游戏流程

1. 启动游戏：选择新建世界 / 读取存档

2. 主世界冒险：移动→开箱子→击杀怪物获取资源

3. 解锁传送门：用打火石激活终点传送门，解锁成就

4. 下界挑战：对抗熔岩僵尸、烈焰人等更强怪物

5. 完成目标：击杀烈焰人获取末地钥匙，解锁最终内容

6. 死亡机制：生存模式掉落物品，冒险模式直接结束游戏

### 7\. 运行说明

- 编译器：支持 Dev‑C\+\+、Code::Blocks、Visual Studio

- 系统：Windows（依赖`windows\.h`、`conio\.h`控制台库）

- 存档文件：自动生成`chest‑game‑data\.dat`（地图 / 背包 / 怪物数据）、`skin\.txt`（玩家自定义皮肤）

---

## CHESTS IN THE MAPS Canary Version 介绍

网页版无需下载安装，可通过浏览器直接访问游玩，轻量化设计适配多设备，核心玩法围绕「地图探索 \+ 宝箱收集」展开，新增下界关卡作为进阶内容。

### 1\. 访问地址

[https://chests\-game\.pages\.dev/](https://chests-game.pages.dev/)

### 2\. 核心功能

|功能入口|说明|
|---|---|
|🎮 开始游戏|进入核心玩法，开启地图探索|
|🏆 成就进度|查看成就完成情况，明确探索目标|
|📂 读取存档|加载过往游戏进度，无需重新开始|
|⚙️ 游戏设置|调整基础游玩参数，适配操作习惯|

### 3\. 核心玩法线索

- 核心：地图探索 \+ 宝箱收集 / 解锁，包含多难度地图场景、隐藏宝箱线索

- 下界关卡：作为进阶内容，提供更高挑战性的探索机制与宝箱奖励

- 轻量化：无安装依赖，浏览器直接运行，操作简洁易上手

> 注：更多玩法细节（如具体操作、宝箱奖励、地图类型）可通过页面「开始游戏」体验完整内容。

---

## 版本对比

|维度|C\+\+ 控制台版|网页版|
|---|---|---|
|运行环境|Windows（依赖控制台库）|任意浏览器（跨平台）|
|功能完整度|全系统（存档、作弊、AI 等）|轻量化核心玩法|
|上手难度|需编译运行，适合开发者|即开即玩，适合普通玩家|
|特色|可研究源码，自定义扩展|无需安装，跨设备游玩|

---

## 适合人群

- C\+\+ 控制台版：适合 C\+\+ 初学者学习控制台图形化、数据存储、游戏逻辑开发

- 网页版：适合所有玩家快速体验轻量化的地图探索与宝箱冒险玩法

# CHESTS IN THE MAPS

## Project Overview

*Chests in the Maps* is an adventure game in the style of Minecraft, available in two versions: the **C\+\+ Console Version \(Release Version\)** and the **Web Version \(Canary Version\)**\. The core gameplay revolves around \&\#34;random map exploration → chest collection → monster slaying → Nether adventure → achievement completion\&\#34;, featuring a complete game system combined with a lightweight gaming experience\.

> Note: The C\+\+ preview version may fail to compile and run; priority is recommended to experience the web version\.

---

## Introduction to CHESTS IN THE MAPS Release Version

This is a full\-featured version developed based on the C\+\+ console, implemented using Windows console libraries\. It has a rich game system and custom functions, making it suitable for C\+\+ learners to study console graphics and game logic development.

### 1\. Core Function Overview

|Module|Function Description|
|---|---|
|Map Generation|Randomly generates Overworld/Nether maps containing walls, open spaces, chests, monsters, and portals, ensuring playable map pathways|
|Player System|Health points, hunger level, money, inventory system, supporting basic operations such as movement, attack, and item usage|
|Monster System|Overworld \(Zombies, Skeletons\), Nether \(Lava Zombies, Blazing Skeletons, Blazes\), distinguishing melee/ranged attacks|
|Item System|Diverse items including ores, potions, Ender Pearls, Flint and Steel, tapes \(play music\), End Keys, etc\.|
|Interaction System|Opening chests, shop trading, eating food, checking inventory/achievements, with complete interaction logic|
|Command System|Supports MC\-style cheat commands like /kill, /tp, /give, /gamemode|
|Save System|Automatically saves maps, inventory, coordinates, and monster states to local files, supporting save file reading|
|Achievement System|8 in\-game achievements with real\-time prompts upon unlocking to guide the game process|

### 2\. Core Data Structures

#### Global Variables

- Maps: `overworld\[N\]\[N\]` \(Overworld\), `nether\[N\]\[N\]` \(Nether\)

- Player: Coordinates `x/y`, direction `fx`, health points `hp`, hunger level `full`, money `money`

- Inventory: `inventory\[30\]` stores the quantity of all items

- Monsters: The `MobData` structure stores coordinates, health points, and facing direction, managed in arrays by type

#### Enumerations and Mappings

- Block Enumeration: Defines numeric IDs for all Overworld/Nether blocks \(dirt, walls, chests, etc\.\)

- Mapping Tables: `num\_to\_char\_mp` \(numeric to display character\), `block\_color` \(console block color\)

### 3\. Core Function Analysis

```cpp
// Entity
void update_mobs_overworld();
void update_mobs_nether();
void check_attack_overworld();
void check_attack_nether();

// Map
void print_map();
void print_map_Nether();
void generation_wall();
void generation_world();
void generation_world_nether();
void checkRoad();
int nether_block_check();

// UI & Gameplay
void title_screen();
void options();
void chest();
void chest_nether();
void shop();
void useItem();
void useItem_nether();
void eatFood();
void view_inventory();
void view_advencements();
void command();
void statistic();
int game_menu();

// Game Logic
void game_overworld();
void game_nether();

// Save & Load
void read_game_data();
void write_game_data();

// Easter egg
void eggs_mcplayer123();
```

### 4\. Monster AI

- Tracking: Automatically move toward the player within a 3\-block range

- Attack: Melee monsters deal damage when in close contact; ranged monsters \(Skeletons/Blazes\) fire arrows/fireballs

- State: Switch display style after taking damage, drop items upon death

### 5\. Operation Guide

|Key|Function|
|---|---|
|`W/A/S/D`|Move up/left/down/right|
|`K`|Attack adjacent monsters|
|`O`|Open the chest ahead|
|`E`|Check inventory|
|`Q`|Eat food to restore hunger level|
|`U`|Use items|
|`P`|Check achievements|
|`/`|Enter cheat commands \(cheats must be enabled\)|
|`1`|Toggle debug mode|
|`R`|Return to main menu|
>Tip:You can bind keys in options.

### 6\. Game Process

1. Start the game: Choose to create a new world / load a save

2. Overworld adventure: Move → open chests → slay monsters to obtain resources

3. Unlock the portal: Activate the end portal with Flint and Steel to unlock achievements

4. Nether challenge: Confront stronger monsters such as Lava Zombies and Blazes

5. Complete objectives: Slay Blazes to obtain the End Key and unlock final content

6. Death mechanism: Drop items in Survival Mode; end the game directly in Adventure Mode

### 7\. Running Instructions

- Compilers: Supports Dev\-C\+\+, Code::Blocks, Visual Studio

- System: Windows \(relies on `windows\.h`, `conio\.h` console libraries\)

- Save files: Automatically generate `chest\-game\-data\.dat` \(map/inventory/monster data\), `skin\.txt` \(custom player skin\)

---

## Introduction to CHESTS IN THE MAPS Canary Version

The web version requires no download or installation and can be accessed and played directly through a browser\. Its lightweight design is compatible with multiple devices, with core gameplay centered around \&\#34;map exploration \+ chest collection\&\#34;, and newly added Nether levels as advanced content.

### 1\. Access Address

[https://chests\-game\.pages\.dev/](https://chests-game.pages.dev/)

### 2\. Core Functions

|Function Entry|Description|
|---|---|
|🎮 Start Game|Enter core gameplay and start map exploration|
|🏆 Achievement Progress|Check achievement completion status to clarify exploration goals|
|📂 Load Save|Load past game progress without restarting|
|⚙️ Game Settings|Adjust basic gameplay parameters to fit operational habits|

### 3\. Core Gameplay Clues

- Core: Map exploration \+ chest collection/unlocking, including multi\-difficulty map scenes and hidden chest clues

- Nether Levels: As advanced content, provide more challenging exploration mechanisms and chest rewards

- Lightweight: No installation dependencies, runs directly in the browser with simple and easy\-to\-use operations

> Note: For more gameplay details \(such as specific operations, chest rewards, map types\), experience the complete content through the \&\#34;Start Game\&\#34; button on the page\.

---

## Version Comparison

|Dimension|C\+\+ Console Version|Web Version|
|---|---|---|
|Running Environment|Windows \(relies on console libraries\)|Any browser \(cross\-platform\)|
|Function Completeness|Full system \(save, cheats, AI, etc\.\)|Lightweight core gameplay|
|Ease of Access|Requires compilation and running, suitable for developers|Instant play, suitable for ordinary players|
|Features|Source code research and custom expansion available|No installation required, cross\-device play|

---

## Target Audience

- C\+\+ Console Version: Suitable for C\+\+ beginners to learn console graphics, data storage, and game logic development

- Web Version: Suitable for all players to quickly experience lightweight map exploration and chest adventure gameplay

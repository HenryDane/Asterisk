# Game Data Format
This is the format of the game data file. This file is divided into multiple sections:
1. Level data
2. Item data
3. Quest data
4. NPC data
5. Map data
6. Cutscene data (Not yet supported so ignore)
7. Bitmap data (Not yet supported so ignore)

Each new section is started by placing the following on a new line like thus: `! LEVEL BEGIN` and ended with: `! LEVEL END`.

The file must start with a version section, like this:
``` 
! VERSION <version> START
# P <num instructions> <parser instructions>
# V <verbosity>
! VERSION END
```

Blank lines and extra whitespace are OK. *** Deviation from the format at all will likely cause the game to crash, load garbage and then crash, or exit. ***

## Level Data
This section is formatted in five subsections:
1. Quadrant 0 
2. Quadrant 1
3. Quadrant 2
4. Quadrant 3
5. Quadrant 4

Each of these sections is declared with `# QUADRANT 0 BEGIN` and ended with `# QUADRANT 0 END`.

Each of these sections contians the following sub-subsections:
1. Level map
2. Some number of `level_data` declarations
3. 10 Tile data declarations

Each of these three sections is repeated four times (once for each sector). A sector is started with `+ SECTOR <sector number>` and does not have to be ended.

The level map is declared by ten seperate lines, each containing ten positive integers. It is started with `$ LM START` and ended with `$ LM END` Immediately following this declaration is are the `level_data` declarations, which are declared in the following format:
```
$ LD <level data number (unique)> <number of entries> 
<x> <y> <name (string, underscores instead of spaces) > <persistence boolean> <type> <number of> <exists boolean> <id> <width> <height> 
. . . 
$ LD STOP <level data number (unique)>
```
The ten tile declarations work as follows:
```
$ TILES START
<x> <y> <name (string, underscores instead of spaces) > <number of entries in corresponding level_data area> <level_data id>
(repeated 10 times)
$ TILES END
```

## Item Data
This section lists all of the items in the game. 
At the start of the section, the first thing must be `$ NUM_ITEMS <number of items>`.
Each item is declared as follows:
```
# ITEM <id> BEGIN
$ ITEM_TYPE <item type>
$ ITEM_USEABLE <true/false>
$ ITEM_DATA <string, 10 chars max for flavor>
$ ITEM_DATA_LEN <length of ITEM_DATA
# ITEM <id> END
```

## Quest Data
This section is somewhat more complex than the Level Data section. In this area, the first line must be `# QUESTS <total number of quests>`. 
Each quest is declared as follows:
1. `# QUEST <quest number> BEGIN`.
2. Some number of `quest_dialogue_t` list declarations.
  ```
  $ DIALOGUE_NUM <number of lists>
  $ DIALOGUE_LIST <number dialogue declarations> <list id> BEGIN
  <string with _ instead of ' '> <length of string, 32 max> <image id for display with text, -1 for black, 0 for no change>
  . . . (repeat as declared)
  $ DIALOGUE_LIST END
  . . .     (more dialogue delcarations if needed)
  $ DIALOGUE END
  ```
3. Some number of assignment function ids.
  *** NOTE: currently the only supported function id is zero.
  ```
  $ ASSIGN <number of ids (must equal number of lists)> <id> <id> . . . <id>
  ```
4. Some number of validation function ids.
  *** NOTE: currently the only supported function id is zero.
  ```
  $ VALID <number of ids (must equal number of dialogue declarations)> <id> <id> . . . <id>
  ```
5. Some optionally different number of `dialogue_block` declarations.
  ```
  $ BLOCK_NUM <number of dialogue blocks>
  $ BLOCK <id> BEGIN
  <list id (from dialogue_list)> <length of list (number of dialogue declarations)>
  $ BLOCK <id> END
  . . .   (more blocks if needed)
  $ BLOCK_AREA END
  ```
6. The declaration of the actual quest
  ```
  # QUEST_TOP <quest number> BEGIN
  $ TITLE <length of title, 32 max> <string with _ instead of ' ' conaining the title>  
  $ ISSUER <length of issuer, 32 max> <string with _ instead of ' ' conaining the issuer name>
  $ LEN <length of list (number of dialogue declarations)>
  $ REWARD <reward exp (+ integer)> <reqard credits (+ integer)> <reward item id>
  # QUEST_TOP END
  ```
7. `# QUEST <quest number> END`. 

Repeat as necessary. 

## NPC Data
This section contains a list of all NPCs in the game. It must begin with `$ NUM_NPCS <total number of npcs>`.
Each NPC is declared as follows:
```
# NPC <id> BEGIN
$ NPC_HEALTH <npc's health (1000 max)>
$ NPC_TYPE <type>
$ NPC_INVENTORY <number of items> <item id> <item id> . . . <item id>
$ NPC_CFG <boolean is merchant> <boolean on fire> <boolean is alive>
$ NPC_QUEST <number of quests offered (currently must be 1 or 0)> <quest id> <quest id> . . . <quest id>
$ NPC_POS <x> <y>
$ NPC_MAP <number of maps NPC exists on> <map id> <map id>  . . . <map id>
# NPC <id> END
```

## Map Data
This is the data for the map for the rogue-like part. This section is very complex as all of the maps are different sizes and may connect to each other.
The map section must begin with `$ NUM_MAPS <number of maps>`. 
Each map is defined as follows:
1. `# MAP BEGIN <id>`
2. `$ MAP_SCALE <w> <h>`
3. Three grids of actual map info, <w> wide and <h> tall, e.g.
  ```
  (if w = 3 and h = 3)
  $ GRID_TYPE START
  0 0 2
  2 0 0
  1 0 5
  $ GRID_TYPE END
  $ GIRD_FIRE START
  false false false
  false false true
  false false false
  $ GRID_FIRE END
  $ GRID_WATER START
  true false false
  false false false
  false true false
  $ GRID_WATER END
  ```
4. The coordinates for starting: `$ COORD <x> <y>`
5. The NPC section. Here there is a list of NPCs and where they are located:
  ```
  $ NPC_PLACEMENT START <number of NPCs>
  <id> <x> <y>
  . . .
  $ NPC_PLACEMENT END
  ```
6. `# MAP END <id>`

These may be repeated as necessary. If a number in the `GRID_TYPE` area is negative then it when the player steps on it, they will be teleported to the map whose id (times negative one) it lists. This is useful for doors and the like.

## Cutscene and Bitmap Data
Neither of these are yet supported by the game or this format *** yet ***. They soon will be. 

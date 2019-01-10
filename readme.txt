==============
| ASTERISK   |
==============

This branch is the rework of Asterisk: Return to Deep Space. The original version is not on the `old` branch.

---- TODO ----
[C] make fake ROM/RAM check before title screen
[C] make title screen super pretty
[Sys] add game save/load
[Sys] add options
[Engine] create gamedata variable
[Engine] create cutscene mechanics
[Engine] add support for "inf" sized sectors by spawning at 0,0 and then having objects be kept in a list and using a special num_of and inf_regen flag instead of the current system
[Other] create gamedata generation utility

---- NOTES ----

---- STATES ----
0 -> intro window
1 -> main menu
2 -> save
3 -> load
4 -> credits
5 -> options
6 -> help
9 -> transition cutscene
10 -> character scale movement (CSM)
11 -> inventory use (sidebar appears)
12 -> NPC interaction
13 -> Quest accept/deny (sidebar)
14 -> Quest dialogue (sidebar)
15 -> Quest completion 
16 -> Generic dialogue
20 -> ship scale movement (SSM)
21 -> ship config 
22 -> warp interface
23 -> docking interface
24 -> view object
30 -> victory
31 -> game over

---- PLOT ----
Game follows character as he tries to find a cure for humanities travel crisis; humanity can not expand as much as they would like so they have resorted to building everywhere, including on random asteroids.

Character needs to find seven NPCs, some of which are hostile and some of which are hidden, etc. These NPCs are/know of/have the key to the final area.

The final area is a computer core on the Akkadian homeworld which contains the technology to unlock Spatial Drives, developed by the long-since collappsed Akkadian civilization.

Much of the gameplay involves exploring asteroids and looking for NPCs. 

Additionally there are side quests required for the player to get to certian areas and for them to get extra items/xp/cash.

Player begins as a United Terran Federation (UTF/Empire) Space Marine landing on Kerald (a rebel stronghold). Player is thrown into a morally dubious conflict with a rebel group which is comprised of random untrained individuals. Player is able to fight (gameplay) to a victory of debatable quality and acquires quest from dialogue with an elderly NPC.

Player then must choose to accept quest and go MIA from his squad (all dead but him) or kill the NPC and report back to base (NPC has button on big bad weapon (tm) -- "all clear" and then game goes to credits).
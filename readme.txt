==============
| ASTERISK   |
==============

This branch is the rework of Asterisk: Return to Deep Space. The original version is not on the `old` branch.

---- TODO ----
make fake ROM/RAM check before title screen
make title screen super pretty
add game save/load
add options
create gamedata variable
creat cutscene mechanics

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
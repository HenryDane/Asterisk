# Building
Building Asterisk is either easy or hard. You will need to do the following:
1. Extract `CSFML.zip` (usually found in the latest release (if not there, go back to the latest release containing it)) to a safe place.
2. Explain to your linker that it should use the following libraries, in the following order:
```
sfml-graphics
sfml-audio
sfml-network
sfml-window
sfml-system
```
3. Tell the compiler to look in the include directory.
4. Tell the linker to look in the lib directory.
5. You may or may not need to use `-std=c99` as an argument. 

If you have questions open an issue. 

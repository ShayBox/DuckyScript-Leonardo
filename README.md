# Leonardo-DuckyScript

This is a DuckyScript interpreter for Arduino Leonardo boards.

This was created for and tested on the [CJMCU Virtual Keyboard ATMEGA32U4](https://www.aliexpress.com/item/4001268341850.html),  
but it will work on any Arduino Leonardo with an SD card, you may have to modify pin variables.

This is forked from [Seytonic/Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD) which comes pre-loaded on these boards.  
I added missing instructions, added more pressable keys, made any pressable key a valid instruction, removed dip switch support, and added led indicator when script is finished.

| Instruction                | Arguments  | Description                                                                           |
|----------------------------|------------|---------------------------------------------------------------------------------------|
| REM                        |            | Skipped, used to comment                                                              |
| DEFAULT_DELAY DEFAULTDELAY | int        | Set default delay between instructions                                                |
| DELAY                      | int        | Delay the next instruction                                                            |
| STRING_DELAY STRINGDELAY   | int string | Like string, but with a delay between keys                                            |
| STRING                     | string     | Types the string                                                                      |
| REPEAT                     | int        | Repeat the previous instruction                                                       |
| Other                      |            | [Other instructions](https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript) |

You may have to use a few second delay at the start, windows takes time to initialize the keyboard.

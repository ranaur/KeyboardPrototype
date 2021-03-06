# Milestones

  * Make the membrane Keyboard work (with alt)
  * Detect USB rollover and fix them
  * Detect Phantom/Ghosting reading other column pins. If they get a zero, there is "leakage".
 
# Design Decisions

## Hardware
  * Solder keywire
  * Decide about tensy or pro micro (or STM32, VUSB and other board)
  * Make a board
    * Chip vs Miniboards
    * Put HUB Chip
    * Put audiocard

## Software
  * Decide about USB repost descriptor
    * 6KRO + Boot protocol
    * 12KRO / 18KRO multikeyboard
    * NKRO with bitmaps
    * 20KRO with extended attribute
    * 6KRO+Bitmap
  * Learn about whoe Numpad will work
  * LAlt + numpad
    * Put LAtl button
    * Make an USB Port to recognize a second keyboard
  * Study about Bluetooth
  * HUB

## Physical Design
  * Double keycaps
    * Two keys
    * Stabiizer
  * Cut on paperboard
  * Make holes board
    * Metal
    * Acrylic
  * Make case
    * Acrylic
    * Bended Metal
    * 3D printed
  * Keycaps

# Bill of Materials
  * Keys
  - Wire
  - Diodes
  - Stabilizers
  - Sockets
  - Case
  - Screws


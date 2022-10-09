# Lily58 keyboard keymap

## Getting started
- [Set up the QMK environment](https://docs.qmk.fm/#/newbs_getting_started)
    - [Install QMK Toolbox](https://github.com/qmk/qmk_toolbox)
    - [Install QMK MSYS](https://github.com/qmk/qmk_distro_msys/releases/latest)
- Update `keymap.c` in `keyboards/lily58/keymaps/oldfieldtc`.
- Set the following user configs
    - `qmk config user.keyboard=lily58/rev1`
    - `qmk config user.keymap=oldfieldtc`
- Run `qmk compile -kb lily58/rev1 -km oldfieldtc`
- Once compiled, open QMK Toolbox and open the `lily58_rev1_oldfieldtc.hex` file that is found at the root of the `qmk_firmware` directory.
- Disconnect one keyboard half and press the reset button on the half that is connected. A `Atmel DFU device connected (libusb0): Atmel Corp. ATmega32U4 (03EB:2FF4:0000)` notice should appear in the window.
- Press 'Flash' and the keyboard should be flashed.
- Disconnect that keyboard half and repeat the previous two steps with the other half.
- Connect both halves together and the keyboard should now be flashed with the new keymap.
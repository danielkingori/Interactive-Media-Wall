# Usage Guide

## Table of Contents

- [The Journey](#the-journey)
  - [Playing an audio file](#playing-an-audio-file)
  - [Prepairing audio files](#prepairing-audio-files)
  - [Playing audio files using toggle buttons](#playing-audio-files-using-toggle-buttons)
  - [Playing audio files using keypad](#playing-audio-files-using-keypad)
  - [Soldering](#soldering)
  - [Creating the map/final installation](#creating-the-mapfinal-installation)
- [How to Use the Player](#how-to-use-the-player)
- [Technical Documentation](#technical-documentation)

## The Journey

Our journey while working on this player was fun and riddled with challenges. We had to redesign the device several times because we could not find certain components or they failed to work as expected. We've tried to document as much as we can about our process and hope that this will make your attempt easier.

### Playing an audio file

Our first challenge was to play a single audio file using an arduino based device. Our plan was to accomplish this using four steps: pick a player, write and upload a program, connect an amplifier and speaker, and play the file.

  - Picking a player: Choosing a player was not straightforward as we thought as we had to merge the hardware and software. Initially, we wanted to play mp3 stereo files using an SD card, mp3 player module, and speaker. However, the only mp3 player module that we could get had a 3W amplifier which was too low for the speaker that we had. We tried to search for 2 3W speakers to match the amplifier but could not get some easily; we had the option of sourcing from [Amazon](https://www.amazon.com) but had a strict deadline and wanted to use easily available components anyway. Consequently, we decided to abandon our stereo plan and settled on using the [TMRpcm](https://www.arduino.cc/reference/en/libraries/tmrpcm/) library which can play WAV files, an amplifier and a speaker. We had a wide range of options for speakers because we could chose an amplifier or build one of our own. While this approach offers less sound quality since it does not support stereo files, it was the best alternative for us since we could easily source the components and customize it to our preferences.
  - Code: We adapted our program from examples provided in the [TMRpcm repository](https://github.com/TMRh20/TMRpcm/blob/master/examples/basic/basic.ino).
  - Connecting everything together: This step was also straightforward as we had help from instructables like [Connect SD Card Module with Arduino](https://www.instructables.com/SD-Card-Module-With-Arduino-How-to-ReadWrite-Data/).

We finally managed to play the audio file after making final tweaks to the program. We also tested the amplifier and settled on the resistance setting that we later used for the device.

### Prepairing audio files

Initially, we wanted to play mp3 stereo files using an SD card, mp3 player module, and speaker. However, due to the aforementioned circumstances, we were forced to settle on WAV files and convert our mp3 audio files to the following format:

  - Samples Per second (Hz): **16000**
  - Channel: **Mono**
  - Bits Per Sample: **8PCM**
  - format: PCM unsigned **8-bit**

Aside from the format, we also had to decide on a naming system that would satisfy two conditions:

  - Each name had to be easily matched to a 3 digit number to support keypad selection
  - The naming system had to support **previous** and **next** actions
  - The naming system had to support custom actions when there was no next or previous audio file after the respective button had been pushed. This was done to prevent users from selecting a song that did not exist.

Eventually, we settled on a naming system where files would be named using the format `001.wav, 002.wav --> 999.wav`. This way, the name of the file is a `3-digit number` which could be selected using a keypad. Also, the next and previous actions could be accomplished by simply adding or removing `1` from the current file that was being played. Finally, we could also run custom actions when the current file is `001.wav` or the last file such as `999.wav`.

### Playing audio files using toggle buttons

We quickly settled on using toggle buttons instead of pushbuttons because they would be a better match aesthetically for the map and provide a visual indicator so users know which file is being played. Unlike previously, we had no issues with the hardware since wiring was pretty straightforward.

Instead, we had to grapple with the program because the buttons operate asynchronously. It took several tries before we were able to get the buttons to work as intended. Eventually, we ended up separating the actions of each button due to the way the program handles state. In future, we would like to consolidate the button actions into a single function in line with DRY programming but hey,it works!

### Playing audio files using keypad

Playing audio files using a keypad brought back hardware problems. Initially, we wanted to use a [4x4 Keypad membrane](https://store.nerokas.co.ke/index.php?route=product/product&product_id=1213) but the keypad that we had didn't work properly. We tried others and found out that the internal circuitry of the membrane can be easily compromised and the component is, therefore, not reliable.

We then switched to an IR remote and receiver which can be easily sourced and have no reliability issues. Connecting them was straightforward but we encountered challenge while writing the program. Each key of the remote has a corresponding 10-digit number which can be decoded when the key is pressed. This 10-digit number can then be mapped to a specific action such as `next`, `previous`, or added as part of the name of a file. The problem we had is that different IR remotes have different values for the same key. So you have to decode each key for a different remote and rewrite the program to make it work. Other than that, however, the program worked like a charm and allowed us to add features such as `volume up` and `volume down`.

### Soldering

After verifying that everything worked, the next step was to solder the whole circuit to a circuit board. This process was also relatively straightforward save for the fact that we had to connect a lot of toggle switches and each had to be linked to an input pin on the arduino. Technically, you can connect upto 48 toggle switches but they are next to each other and presented a challenge in soldering. We ended up connecting only 14 toggle switches.

### Creating the map/final installation

## How to Use the Player

You can play an audio file using either a toggle switch or a keypad. The map contains information on each audio file and is fitted with several toggle switches that are positioned next to the description of the corresponding file that you can flick to play/pause the audio. Alternatively, you can scan the map for the audio file that you want to play and check out its 3-digit code. Press those numbers on the IR remote and the audio file will play immediately. 

The IR remote has keys that you can use for other actions:

  - :fast_forward: -> `Next`
  - :rewind: -> `Previous`
  - :arrow_forward: -> `Play/Pause`
  - :heavy_plus_sign: -> `Volume up`
  - :heavy_minus_sign: -> `Volume down`

## Technical Documentation

Here is a [link](/README.md) to the technical documentation.
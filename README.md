Run following command to run 
1. make clean
2. make
3. qemu-system-arm -M netduinoplus2 -kernel build/firmware.elf -nographic -serial mon:stdio | python3 tts_bridge.py
4. press "t" or "T" and wait for the audio output

In order to pasue the executio, run following command in another terminal:
1. killall qemu-system-arm

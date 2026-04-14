import sys
import subprocess

def main():
    print("TTS Bridge Started. Listening to QEMU...")
    sentence_to_speak = []

    # Read the output from QEMU line by line as it prints
    for line in sys.stdin:
        line = line.strip()
        
        # Print the raw line to the console so you can still see it
        print(line) 

        # If it's a token, extract the word/number and add it to our sentence
        if line.startswith("TOKEN "):
            word = line.split("TOKEN ")[1]
            sentence_to_speak.append(word)
            
        # If we hit END, we speak the sentence!
        elif line == "END":
            # Join the words together (e.g., "THE TIME IS 14 32 05")
            full_sentence = " ".join(sentence_to_speak)
            
            # Make the numbers sound natural (e.g., "14 hours 32 minutes")
            # We assume the last 3 elements are H, M, S
            if len(sentence_to_speak) >= 6:
                h = sentence_to_speak[-3]
                m = sentence_to_speak[-2]
                s = sentence_to_speak[-1]
                full_sentence = f"The time is {h} hours {m} minutes and {s} seconds"
            
            print(f"--> SPEAKING: {full_sentence}")
            
            # Call eSpeak to play the audio
            subprocess.run(["espeak", full_sentence])
            
            # Clear the list for the next keypress
            sentence_to_speak = []

if __name__ == "__main__":
    main()
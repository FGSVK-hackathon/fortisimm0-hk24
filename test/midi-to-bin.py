from sys import argv
from music21 import converter
import struct


def midi_to_frequency(midi_note):
    return 440 * (2 ** ((midi_note - 69) / 12))

def get_notes_from_midi(midi_file):
    # Load MIDI file
    midi_stream = converter.parse(midi_file)

    # Extract notes with duration and convert to frequencies
    notes_with_frequency = []
    for part in midi_stream.parts:
        for element in part.flat.notes:
            if element.isNote:
                try:
                    notes_with_frequency.append({
                        "frequency": midi_to_frequency(element.pitch.midi) + int(argv[3]),
                        "duration": element.duration.quarterLength
                    })
                except:
                    notes_with_frequency.append({
                        "frequency": midi_to_frequency(element.pitch.midi),
                        "duration": element.duration.quarterLength
                    })
    return notes_with_frequency


res = get_notes_from_midi(argv[1])

f = open(argv[2], "ab")
new_list = []


for i in range(len(res)):
    f.write(round(res[i]["frequency"]).to_bytes(2, "big"))
    f.write(round(res[i]["duration"] * 400).to_bytes(2, "big"))
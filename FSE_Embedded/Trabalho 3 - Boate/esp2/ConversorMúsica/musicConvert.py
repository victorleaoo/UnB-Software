import mido

def convert_midi_to_code(midi_file_path):
    code = ""
    mid = mido.MidiFile(midi_file_path)
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'note_on':
                note = msg.note
                velocity = msg.velocity
                duration = msg.time
                code += f"newNote({note}, {duration}),"
    return code

midi_file_path = "Sonic.mid"
code = convert_midi_to_code(midi_file_path)
print(code)

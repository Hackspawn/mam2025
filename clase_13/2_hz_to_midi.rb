#Método #2: Hertz a Midi

#se utiliza play tal cual y como se reproduce una nota MIDI "play 25"
#pero se cambia por hz_to_midi(frecuencia)
#se agregan otros elementos como attack, decay, sustain y release.

play hz_to_midi(90000), attack: 4, decay: 1, sustain: 2, release: 0.25
sleep 10
play hz_to_midi(4000), sustain: 2, release: 10
sleep 10
play hz_to_midi(200), sustain: 2, release: 10
sleep 10

from winsound import Beep

#winsound.Beep(440, 4000)

notes = {'C': 1635,
         'D': 1835,
         'E': 2060,
         'S': 1945,
         'F': 2183,
         'G': 2450,
         'A': 2750,
         'B': 3087,
         ' ': 37}
melodie = 'CDEFG G AAAAG AAAAG FFFFE E DDDDC'
for note in melodie:
    Beep(notes[note], 500)
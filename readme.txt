Modern OpenGL project:
The directory contains simple 2D animations for certains shapes.

Running the .sln file will display an empty black window , in which if the user presses "b",
a square will be rendered within the empty window, and pressing "n" will render a hexagon and
finally pressing the key "m" renders an octegaon.

Transformations:

Pressing "T" translates the rendered object from it's current position to the left side of the screen and back
Pressing "R" rotates the object continously (toggle) until the key is pressed again
Pressing "S" scales up the object until it fills the entire window, the scale down of the object didn't work for some reason
so instead we added the key "C" to scale down the object a certain ammount. Pressing "S" again stops the up scale.
Pressing "O" clears the screen.

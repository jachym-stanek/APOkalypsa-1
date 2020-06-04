## bool knobs_init()

Initializes the memory acces to read the knob values.

## short get_paddle_pos(char paddle)

Returns the knob position for the specified paddle.

Paddles can be `'a'` for the red knob, `'b'` for the blue knob or `'c'` for the green knob, otherewise returns -1;

## bool get_pause()

Returns true if the middle knob is pressed.

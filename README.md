# launch_controller
Model rocket launch controller

Montiors two buttons, an 'arm' button, and a 'fire' button.
After the 'arm' button is held down for a specified time,
and for as long as the button continues to be held, the controller
is considered 'armed'. If the 'fire' button is pressed while the
controller is 'armed', a relay is opened to allow current to flow
to an igniter. This circuit is held open for a specified time.
The 'fire' button does nothing unless the controller is 'armed'.

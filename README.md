# ArcheryGame
Archery Game, made in C++ and QT.

You are given 20 arrows to start with and your aim is to achieve the highest score possible. Every time you hit the Bullseye you get 10 points and an extra arrow and so theoretically there is no upper limit on the score if you are particularly skilled. Every time you nearly hit the bullseye you are rewarded with 5 points and an "Excellent" Message. Arrows are fired due to left button mouse presses which are captured in the Graphics View.

The Bow moves up and down at a random choice of speeds to make the Game Difficult and the Target moves to a random position every time it is hit. The collision detection in Qt works very well and as soon as the arrow impacts the target it becomes a child of it and so sticks to it as it moves until the next arrow is fired.

All assets on the screen are separate objects which are added to the Graphics Scene one by one. The scene is then set inside a Graphics View. A series of timers are then constructed and parented to provide the motion of the bow, target and arrows. Each arrow destroys itself when it goes out of range of whenever the next one is fired.

The Qt system of Signals/Slots make communication between classes particularly straight forward and so all objects are aware whenever an arrow is fired and when it collides with the target, hence the score can be updated and the sound resources can play in the correct order if an arrow strikes the target, hits the bullseye or goes right past it completely.

Finally Mouse Wheel events are captured for the Volume control which pops up whenever you click the Speaker Icon. This modulates the volume at which the Sound resources are played on the system without setting Global volumes.

You can download the Deploy Folder in order to try it out, it contains the Portable Executable.

https://user-images.githubusercontent.com/111576658/201221864-5b8b2f8e-563e-4d7d-8011-a449e335d464.mp4


https://github.com/StefKluskens/Programming4Engine

Main Engine:
	Game loop:
		Input
		Fixed Update
		Update
		Render
Managers:
	InputManager: Handles all input through commands. Recognises keyboard and controller input.
	Renderer: Renders all textures through SDL
	ResourceManager: Loads in all the files needed in the game (textures, fonts, sound)
	SceneManager: Handles the creating of the scenes, as well as swapping between them
GameObject:
	Has knowledge about the scene
	Owns its components and children
	Can be marked for delete, to be deleted at the end of the Update
Scene:
	Calls the game loop functions
	Gameobjects are attached to a root gameobject, owned by the scene
Component:
	Base class for all components
Component examples (engine):
	Collider
	Rigid body
	Animator
Component examples (game):
	Player behaviour
	Maita behaviour
	ZenChan behaviour
	Bubble behaviour
	Item pick up behaviour
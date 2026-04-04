extends TileMapLayer

var yellow = Vector2i(0,0)
var sky = Vector2i(1,0)
var blue = Vector2i(2,0)
var red = Vector2i(3,0)
var green = Vector2i(4,0)
var orange = Vector2i(5,0)
var purple = Vector2i(6,0)
var grey = Vector2i(7,0)

var shape_colors = [yellow, sky, blue, red, green, orange, purple]
var init_color


var O = [
	[0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0]
]

var I = [
	[0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0],
	[0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0]
]

var J = [
	[0,0,0, 1,1,1, 0,0,1],
	[0,1,0, 0,1,0, 1,1,0],
	[1,0,0, 1,1,1, 0,0,0],
	[0,1,1, 0,1,0, 0,1,0]
]

var L = [
	[0,0,0, 1,1,1, 1,0,0],
	[1,1,0, 0,1,0, 0,1,0],
	[0,0,1, 1,1,1, 0,0,0],
	[0,1,0, 0,1,0, 0,1,1]
]

var S = [
	[0,0,0, 0,1,1, 1,1,0],
	[0,1,0, 0,1,1, 0,0,1]
]

var Z = [
	[0,0,0, 1,1,0, 0,1,1],
	[0,0,1, 0,1,1, 0,1,0]
]

var T = [
	[0,0,0, 1,1,1, 0,1,0],
	[0,1,0, 1,1,0, 0,1,0],
	[0,1,0, 1,1,1, 0,0,0],
	[0,1,0, 0,1,1, 0,1,0],
]

var shapes = [O, I, S, Z, L, J, T]
var init_shape


var speed = 0
var steps = 0
var steps_req = 25

var line_pos = 1

var location = 1

func _ready() -> void:
	new_game()

func new_game():
	speed = 1.0
	init_shape = shapes[randi() % 4]
	init_color = shape_colors[randi() % 7]
	
func _process(delta: float) -> void:
	steps += speed
	var shape_rotation = randi() % init_shape.size()
	if steps >= steps_req:
		clear_piece()
		draw_shape_at(5, location, init_shape[shape_rotation], init_color)
		location += 1
		steps = 0

func draw_shape_at(x: int, y: int, shape: Array, color: Vector2i):
	var size = sqrt(shape.size())
	for i in range(size):
		for j in range(size):
			if shape[j + i * size]:
				var coords = Vector2i(x + j, y + i)
				set_cell(coords, 0, color, 0)

func clear_piece() -> void:
	for i in range(1,11):
		for j in range(1,20):
			erase_cell(Vector2i(i,j))
	

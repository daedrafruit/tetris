extends TileMapLayer

var yellow = Vector2i(0,0)
var sky = Vector2i(1,0)
var blue = Vector2i(2,0)
var red = Vector2i(3,0)
var green = Vector2i(4,0)
var orange = Vector2i(5,0)
var purple = Vector2i(6,0)
var grey = Vector2i(7,0)

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

var shape_colors = [yellow, sky, blue, red, green, orange, purple]
var curr_color

var shapes = [O, I, S, Z, L, J, T]
var curr_shape
var curr_shape_index

var curr_rotation = 0

var speed = 0
var steps = 0
var steps_req = 25

var line_pos = 1

var location = 1
var curr_location = Vector2i(4, 0)

func _ready() -> void:
	speed = 1.0
	curr_shape_index = randi() % 7
	curr_shape = shapes[curr_shape_index][rotation]
	curr_color = shape_colors[randi() % 7]

func _process(delta: float) -> void:
	steps += speed
	#var curr_rotation = randi() % init_shape.size()
	if steps >= steps_req:
		if not move_piece(0, 1):
			curr_location = Vector2i(4, 0)
			curr_shape_index = randi() % 4
			curr_shape = shapes[curr_shape_index][0]
			curr_color = shape_colors[randi() % 7]
		steps = 0

func _input(event):
	if event.is_action_pressed("left"):
		move_piece(-1,0)
	if event.is_action_pressed("right"):
		move_piece(1,0)
	if event.is_action_pressed("rotate clockwise"):
		rotate_piece_clockwise()

func rotate_piece_clockwise():
	if curr_rotation == shapes[curr_shape_index].size() - 1:
		curr_rotation = 0
	else:
		curr_rotation += 1
	clear_shape()
	curr_shape = shapes[curr_shape_index][curr_rotation]

func draw_shape():
	var size = sqrt(curr_shape.size())
	for j in range(size):
		for i in range(size):
			if not curr_shape[i + j * size]:
				continue

			var coords = Vector2i(curr_location.x + i, curr_location.y + j)
			set_cell(coords, 0, curr_color, 0)

func clear_shape():
	var size = sqrt(curr_shape.size())
	for j in range(size):
		for i in range(size):
			if not curr_shape[i + j * size]:
				continue

			var coords = Vector2i(curr_location.x + i, curr_location.y + j)
			erase_cell(coords)

func move_piece(x_offset: int, y_offset: int) -> bool:
	if can_move(x_offset, y_offset):
		clear_shape()
		curr_location.y += y_offset
		curr_location.x += x_offset
		draw_shape()
		return true
	else:
		return false
			
func can_move(x_offset: int, y_offset: int):
	var size = sqrt(curr_shape.size())
	for j in range(size):
		for i in range(size):
			if not curr_shape[i + j * size]:
				continue

			var x_rel = i + x_offset
			var y_rel = j + y_offset
			var within_shape = x_rel < size and y_rel < size

			if within_shape and curr_shape[x_rel + y_rel * size]:
				continue

			var coords = Vector2i(curr_location.x + x_rel, curr_location.y + y_rel)
			
			if get_cell_source_id(coords) != -1:
				return false
	return true

func clear_screen() -> void:
	for j in range(1,20):
		for i in range(1,11):
			erase_cell(Vector2i(i,j))
	

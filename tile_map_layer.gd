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

var piece_colors = [yellow, sky, blue, red, green, orange, purple]

var pieces = [O, I, S, Z, L, J, T]

var speed = 0
var steps = 0
var steps_req = 25


class piece:
	var id: int = randi() % 7
	var color_index: int = randi() % 7
	var rotation: int = 0
	var location: Vector2i = Vector2i(4, 0)

var curr_piece: piece

func _ready() -> void:
	speed = 1.0
	curr_piece = piece.new()

func _process(delta: float) -> void:
	steps += speed
	#var curr_rotation = randi() % init_piece.size()
	if steps >= steps_req:
		if not move_piece(curr_piece, 0, 1):
			curr_piece = piece.new()
		steps = 0

func _input(event):
	if event.is_action_pressed("left"):
		move_piece(curr_piece, -1,0)
	if event.is_action_pressed("right"):
		move_piece(curr_piece, 1,0)
	if event.is_action_pressed("rotate clockwise"):
		rotate_piece_clockwise(curr_piece)

func rotate_piece_clockwise(p: piece):
	clear_piece(p)
	if p.rotation == pieces[p.id].size() - 1:
		p.rotation = 0
	else:
		p.rotation += 1
	draw_piece(p)

func get_piece_array(p: piece) -> Array:
	return pieces[p.id][p.rotation]

func draw_piece(p: piece):
	var curr_piece_array = get_piece_array(p)

	var size = sqrt(curr_piece_array.size())
	for j in range(size):
		for i in range(size):
			if not curr_piece_array[i + j * size]:
				continue

			var coords = Vector2i(p.location.x + i, p.location.y + j)
			set_cell(coords, 0, piece_colors[p.color_index], 0)

func clear_piece(p: piece):
	var curr_piece_array = get_piece_array(p)
	var size = sqrt(curr_piece_array.size())
	for j in range(size):
		for i in range(size):
			if not curr_piece_array[i + j * size]:
				continue

			var coords = Vector2i(p.location.x + i, p.location.y + j)
			erase_cell(coords)

func move_piece(p: piece, x_offset: int, y_offset: int) -> bool:
	if can_move(p, x_offset, y_offset):
		clear_piece(p)
		p.location.y += y_offset
		p.location.x += x_offset
		draw_piece(p)
		return true
	else:
		return false
			
func can_move(p: piece, x_offset: int, y_offset: int):
	var curr_piece_array = get_piece_array(p)
	var size = sqrt(curr_piece_array.size())
	for j in range(size):
		for i in range(size):
			if not curr_piece_array[i + j * size]:
				continue

			var x_rel = i + x_offset
			var y_rel = j + y_offset
			var within_piece = x_rel < size and y_rel < size

			if within_piece and curr_piece_array[x_rel + y_rel * size]:
				continue

			var coords = Vector2i(p.location.x + x_rel, p.location.y + y_rel)
			
			if get_cell_source_id(coords) != -1:
				return false
	return true

func clear_screen() -> void:
	for j in range(1,20):
		for i in range(1,11):
			erase_cell(Vector2i(i,j))
	

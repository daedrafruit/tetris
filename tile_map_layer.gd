extends TileMapLayer

var yellow = Vector2i(0,0)
var sky = Vector2i(1,0)
var blue = Vector2i(2,0)
var red = Vector2i(3,0)
var green = Vector2i(4,0)
var orange = Vector2i(5,0)
var purple = Vector2i(6,0)
var grey = Vector2i(7,0)

var line_pos = 1

func _ready() -> void:
	pass

func _process(delta: float) -> void:

	var time_step = 0.5
	var max_time_step = 0.25
	var accumulator = 0.0

	accumulator += max(delta, max_time_step)

	if accumulator >= time_step:
		clear_screen()

		draw_line_at(2,line_pos)
		line_pos += 1
		accumulator -= time_step


	pass

func draw_line_at(x: int, y: int):
	for i in range(4):
		var coords = Vector2i(x,y + i)
		set_cell(coords, 0, yellow, 0)

func clear_screen() -> void:
	for i in range(1,11):
		for j in range(1,20):
			erase_cell(Vector2i(i,j))
	

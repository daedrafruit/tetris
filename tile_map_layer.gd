extends TileMapLayer
@onready var timer: Timer = $Timer

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
	timer.timout.connect(_on_timeout)
	pass

func _process(delta: float) -> void:

	clear_screen()

	draw_line_at(2,line_pos)

	pass

func _on_timeout() -> void:
	line_pos += 1
	

func draw_line_at(x: int, y: int):
	for i in range(4):
		var coords = Vector2i(x,y + i)
		set_cell(coords, 0, yellow, 0)

func clear_screen() -> void:
	for i in range(1,11):
		for j in range(1,20):
			erase_cell(Vector2i(i,j))
	

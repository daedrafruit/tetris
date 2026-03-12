extends TileMapLayer

var yellow = Vector2i(0,0)
var sky = Vector2i(1,0)
var blue = Vector2i(2,0)
var red = Vector2i(3,0)
var green = Vector2i(4,0)
var orange = Vector2i(5,0)
var purple = Vector2i(6,0)
var grey = Vector2i(7,0)


func _ready():
	draw_line_at(2,2)
	pass

func draw_line_at(x, y):
	for i in range(4):
		var coords = Vector2i(x,y + i)
		set_cell(coords, 0, yellow, 0)
	

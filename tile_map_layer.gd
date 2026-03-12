extends TileMapLayer


func _ready():
	var coords = Vector2i(1,1)
	var atlas_coords = Vector2i(1,0)
	set_cell(coords, 0, atlas_coords, 0)
	pass


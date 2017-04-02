-- Variables of this script will be contained within this table.
test_class = {
	name = "This is a word"
}

function test_class:on_create()
	print(Camera.get_main().field_of_view)
end

function test_class:update(dt)
	print("Update method.")
end
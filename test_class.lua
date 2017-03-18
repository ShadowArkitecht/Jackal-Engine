-- Variables of this script will be contained within this table.
test_class = {
	name = "This is a word"
}

function test_class:create()
	local c = Colour.white()
	print(c)
end

function test_class:update(dt)
	print("Update method.")
end
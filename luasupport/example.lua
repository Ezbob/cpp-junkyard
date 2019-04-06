Player = {
    Name = "Xexus",
    Title = "Duke of Cubines",
    Level = 40,
    Stuff = "Hello",
    Fun = function()
        print("Hello")
    end
}

print(super.answer)
print(super.f(1, 2))

function AddStuff(a, b)
    print("ADDSTUFF")
    return a * b + 2
end

function DoAThing(a, b)
    print("Do a thing")
    return HostFunction(a + 10, b + 15)
end

Player = {
    Name = "Xexus",
    Title = "Duke of Cubines",
    Level = 40
}

function AddStuff(a, b)
    print("ADDSTUFF")
    return a * b + 2
end

function DoAThing(a, b)
    print("Do a thing")
    c = HostFunction(a + 10, b + 15)
    return c
end

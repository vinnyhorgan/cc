value = 0
value2 = 0
checked = true
name = "Andrew"

berlu = nil

function load()
    gui.enableDocking();

    berlu = graphics.loadTexture("assets/b.png");
end

function update()

end

function draw()
    -- gui.dockSpace();

    if gui.beginMainMenuBar() then
        if gui.beginMenu("File") then
            if gui.menuItem("Open") then
                print("Open")
                checked = true
            end

            gui.endMenu()
        end

        gui.endMainMenuBar();
    end

    if checked then
        checked = gui.begin("Hello", checked, { noMove = true });

        value = gui.sliderInt("Value", value, 0, 100);
        value2 = gui.sliderFloat("Value2", value2, 0, 100);
        gui.separator();
        checked = gui.checkbox("Checked", checked);
        gui.separator();
        name = gui.inputText("Name", name);
        gui.separator();
        gui.text("Helloooooo");
        gui.sameLine();

        if (gui.button("Click me")) then
            print("Clicked!")
        end

        gui.endd();
    end

    gui.begin("Tool", true, { menuBar = true })

    if gui.beginMenuBar() then
        if gui.beginMenu("File") then
            if gui.menuItem("Open") then
                print("Open")
                checked = true
            end

            gui.endMenu()
        end

        gui.endMenuBar();
    end

    gui.textColored("fancy title", 255, 0, 0, 255)

    gui.beginChild("Child");

    gui.text("Helloooooo");
    gui.text("Helloooooo");
    gui.text("Helloooooo");
    gui.text("Helloooooo");

    gui.endChild();

    gui.endd();

    graphics.drawTexture(berlu, 100, 100);
end

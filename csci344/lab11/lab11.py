#sample program to render an image using tkinter
#use a grid of squares to simulate memory block decay over time
#each "day" every square has a chance to alter its state
from tkinter import *
import random
from math import floor

#21*30 - an arbitrary value chosen because it fits on my screen
canvas_width = 630
canvas_height = 630

#god class that does everything - I would refactor if the scope of this assignment was any larger
class DataSim:
    def __init__(self, master):
        random.seed() #set seed here if you want to test specific runs

        #title of window
        self.master = master
        master.title = "Data Simulator"

        self.num_days = 0 #total number of days simulated
        self.days_to_advance = 1 #default value, reads from input field

        #display total days passed
        self.total_days_text = IntVar()
        self.total_days_text.set(self.num_days)
        self.total_label = Label(master, textvariable=self.total_days_text)

        self.label = Label(master, text="Days passed: ")

        self.label.pack()
        self.total_label.pack()

        #input field
        vcmd = master.register(self.validate) # we have to wrap the command
        self.entry = Entry(master, validate="key", validatecommand=(vcmd, '%P'))
        self.entry.pack()

        #advances the simulation by 1 day or by number of days given in textbox
        self.advance_button = Button(master, text="Advance", command=self.next_day)
        self.advance_button.pack()

        self.canvas = Canvas(root, width=canvas_width, height=canvas_height)
        self.canvas.pack()

        #21x21 grid - tracks state of each memory block
        self.grid = []
        for i in range(21):
            self.grid.append([])
            for j in range(21):
                self.grid[i].append(1)

    #validator for input field
    def validate(self, new_text):
        if not new_text: #field is being cleared
            self.days_to_advance = 1
            return True
        try:
            self.days_to_advance = int(new_text)
            return True
        except ValueError:
            return False

    #translates digit representation in grid[][] to a color
    def get_color(self, i, j):
        #avoid out-of-bounds referencea black square is considered an error
        if (i > 20 or j > 20):
            return "black" #a black square is considered an error
        x = self.grid[i][j]
        if x == 0:   #defective
            return "red"
        elif x == 1: #new
            return "dark green"
        elif x == 2: #normal
            return "green"
        elif x == 3: #aged
            return "light green"
        return "black" #should never execute

    #renders the grid squares with the appropriate colors
    def color_grid(self):
        dict = { }
        for i in range(21):
            for j in range(21):
                if self.grid[i][j] in dict:
                    dict[self.grid[i][j]] += 1
                else:
                    dict[self.grid[i][j]] = 1
                self.canvas.create_rectangle((i*30)+1, (j*30)-1, ((i+1)*30)+1, ((j+1)*30)-1, fill=self.get_color(i, j))
        print("DAY " + str(self.num_days))
        #for key in dict:
            #print(str(key) + ": " + str(dict[key]))
        if 0 in dict: print(str(dict[0]) + " defective: " + str(round(dict[0]/441*100, 2)) + "%")
        if 1 in dict: print(str(dict[1]) + " new: " + str(round(dict[1]/441*100, 2)) + "%")
        if 2 in dict: print(str(dict[2]) + " normal: " + str(round(dict[2]/441*100, 2)) + "%")
        if 3 in dict: print(str(dict[3]) + " aged: " + str(round(dict[3]/441*100, 2)) + "%")
        print()

    """
    Given a grid item, update its state based on the specified probability values
    This function is not actually used. I use the function below this one,
    but I kept this version in because I think it's interesting to compare the two

    How I handle the probability in this (deprecated) function:
        Because the repair chance is variable, all other probabilities will of necessity be variable as well.
        The sum of all chances besides repair is 95%,
        so I translate the percentage of defective blocks to a number 0:100 and add it to 95.
        Thus, our effective probability range is between 95 and 195.
        This means that the more defective blocks there are, the more likely a repair is to occur,
        and the less likely anything else is to occur.
        From there, random selection is a simple matter of generating a random number in our range

    On a given "day", every block has the same probability range.
    Each square generates its own random number for the day and takes action according to its result.
    If the action it receives does not correspond to its current state, the action is discarded.
    For example, if a "new" square receives the "decay" action (an action specific to "old" squares),
    it takes no action that day
    """
    def alternative_update_block(self, i, j, percentage):
        action = floor(random.random() * (95 + percentage))
        if action < 40: #install
            if self.grid[i][j] == 1: #square must be new
                self.grid[i][j] = 2
        elif action < 45: #wear & tear
            if self.grid[i][j] == 2: #square must be normal
                self.grid[i][j] = 3
        elif action < 55: #decay
            if (self.grid[i][j] == 3): #square must be old
                self.grid[i][j] = 0

        #this is the point where the probability values start to vary
        elif action < (percentage + 55): #repair
            if self.grid[i][j] == 0: #square must be defective
                self.grid[i][j] = 1
        elif action < (percentage + 70): #prevention
            if self.grid[i][j] == 2: #square must be normal
                self.grid[i][j] = 1
        elif action < (percentage + 75): #lemon
            if self.grid[i][j] == 1: #square must be new
                self.grid[i][j] = 0
        elif self.grid[i][j] == 2: #neighbor is the default - square must be normal
            #"neighbor" is unique because it requires checking adjacent tiles for defective squares
            hasDefectiveNeighbor = False
            for idx in range(-1, 2):
                for jdx in range(-1, 2):
                    adji = i + idx
                    adjj = j + jdx
                    #prevent out-of-bounds indexing
                    if (adji >= 0) and (adji < 21) and (adjj >= 0) and (adjj < 21):
                        #value will only remain false so long as it never enounters a defective square
                        hasDefectiveNeighbor = hasDefectiveNeighbor or self.grid[adji][adjj] == 0
            if hasDefectiveNeighbor:
                self.grid[i][j] = 0

    """
    This is the version I actually use in the code. I generate a random value between 0 and 100.
    Based on the state of the current block, I determine whether that block takes an action
    using the specified probability values

    The major difference is that the previous version determines an action to take,
    then determines whether the current square can take that action.
    This version fragments the probabilities so actions are only seen if the current block can take them.
    The mathematical difference between the two is interesting to me:
    In the first version, changes seemed to occur more rapidly and chaotically than in this version
    """
    def update_block(self, i, j, percentage):
        action = floor(random.random() * 100)
        if self.grid[i][j] == 0:
            if action < percentage: #repair
                self.grid[i][j] = 1

        elif self.grid[i][j] == 1:
            if action < 40: #install
                self.grid[i][j] = 2
            elif action < 45: #lemon
                self.grid[i][j] = 0

        elif self.grid[i][j] == 2:
            if action < 5: #wear & tear
                self.grid[i][j] = 3
            elif action < 20: #prevention
                self.grid[i][j] = 1
            elif action < 40: #neighbor
                #"neighbor" is unique because it requires checking adjacent tiles for defective squares
                hasDefectiveNeighbor = False
                for idx in range(-1, 2):
                    for jdx in range(-1, 2):
                        adji = i + idx
                        adjj = j + jdx
                        #prevent out-of-bounds indexing
                        if (adji >= 0) and (adji < 21) and (adjj >= 0) and (adjj < 21):
                            #value will only remain false so long as it never enounters a defective square
                            hasDefectiveNeighbor = hasDefectiveNeighbor or self.grid[adji][adjj] == 0
                if hasDefectiveNeighbor:
                    self.grid[i][j] = 0

        else:
            if action < 10: #decay
                self.grid[i][j] = 0


    """
    update each tile once per day for specified number of days
    once all days have run, update num_days counter, clear input field, and refresh the grid
    """
    def next_day(self):
        for days in range(self.days_to_advance):
            ctr = 0
            total = 441
            for i in range(21):
                for j in range(21):
                    if self.grid[i][j] == 0: ctr += 1
            percentage = floor((ctr / total) * 100)

            for i in range(21):
                for j in range(21):
                    self.update_block(i, j, percentage)

        self.num_days += self.days_to_advance
        self.total_days_text.set(self.num_days)
        self.entry.delete(0, END)
        self.color_grid()
#end class DataSim

"""
MAIN - generate the view
"""
root = Tk()
myDataSim = DataSim(root)

#initial coloring of grid squares - should all be dark green
myDataSim.color_grid()

root.mainloop()

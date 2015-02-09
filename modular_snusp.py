import datetime
import sys

def getch():
    try:
        import termios
    except ImportError:
        # Non-POSIX. Return msvcrt's (Windows') getch.
        import msvcrt
        return msvcrt.getch
    # POSIX system. Create and return a getch that manipulates the tty.
    import sys, tty
    def _getch():
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

    return _getch

Direction = {
    'right' : -2,
    'left' : +2,
    'up' : -1,
    'down' : +1,
}

class Snusp(object):
    def __init__(self,file_path):
        file_obj = open(file_path)
        self.program_exit = 0 
        self.data = [0]*30000
        self.instruction = file_obj.readlines()
        self.data_ptr = 0
        self.inst_ptr_x = 0
        self.inst_ptr_y = 0
        for i in xrange(0,len(self.instruction)):
            for j in xrange(0,len(self.instruction[i])):
                if self.instruction[i][j] == '$':
                    self.inst_ptr_x = j
                    self.inst_ptr_y = i
                    break
        self.prev_time = datetime.datetime.now()
        self.direction = Direction['right']
        self.function_stack = []

    def lurd(self):
        if self.direction == Direction['left']:
            self.direction = Direction['up']
        elif self.direction == Direction['right']:
            self.direction = Direction['down']
        elif self.direction == Direction['up']:
            self.direction = Direction['left']
        else:
            self.direction = Direction['right']
    
    def ruld(self):
        if(self.direction == Direction['right']):
            self.direction = Direction['up']
        elif(self.direction == Direction['left']):
            self.direction = Direction['down']
        elif(self.direction == Direction['down']):
            self.direction = Direction['left']
        else:
            self.direction = Direction['right']
    
    def move_ahead(self):
        if self.direction == Direction['right']:
            self.inst_ptr_x += 1
        elif self.direction == Direction['down']:
            self.inst_ptr_y += 1
        elif self.direction == Direction['left']:
            self.inst_ptr_x -= 1
        elif self.direction == Direction['up']:
            self.inst_ptr_y -= 1
        if self.inst_ptr_y < 0 or self.inst_ptr_x < 0:
            self.program_exit += 1

    def current_instruction(self):
        try:
            return self.instruction[self.inst_ptr_y][self.inst_ptr_x]
        except:
            self.program_exit += 1

    def enter_function(self):
        self.function_stack.append([self.inst_ptr_x,self.inst_ptr_y,self.direction])
        
    def exit_function(self):
        try:
            self.inst_ptr_x,self.inst_ptr_y,self.direction = self.function_stack.pop()
            self.move_ahead()
        except:
            self.program_exit += 1

    def execute(self):
        while self.current_instruction() != '\n' and self.program_exit <= 0:
            inst = self.current_instruction()
            if inst == '<':
                if self.data_ptr > 0:
                    self.data_ptr -= 1
                else:
                    self.program_exit += 1
            elif inst == '>':
                if self.data_ptr < 30000:
                    self.data_ptr += 1
                else:
                    self.program_exit += 1
            elif inst == '+':
                self.data[self.data_ptr] += 1
            elif inst == '-':
                if self.data[self.data_ptr] > 0: 
                    self.data[self.data_ptr] -= 1
            elif inst == ',':
                self.data[self.data_ptr] = getch()
            elif inst == '.':
                sys.stdout.write(chr(self.data[self.data_ptr]))
            elif inst == '\\':
                self.lurd()
            elif inst == '/':
                self.ruld()
            elif inst == '!':
                self.move_ahead()
            elif inst == '?':
                if self.data[self.data_ptr] == 0:
                    self.move_ahead()
            elif inst == '@':
                self.enter_function()
            elif inst == '#':
                self.exit_function()
            self.move_ahead()

def run():
    try:
        snusp = Snusp(sys.argv[1])
        snusp.execute()
    except:
        return -1
    return 0

run()
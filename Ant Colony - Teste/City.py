class City:
    def __init__(self, id:int, x:float, y:float):
        self.id = id
        self.x = x
        self.y = y
    
    def get_id(self):
        return self.id
    
    def get_x(self):
        return self.x

    def get_y(self):
        return self.y
    
    def __str__(self):
        return "city:{}, x:{}, y:{}".format(self.id, self.x, self.y)
class City:
    def __init__(self, id, x, y):
        self.id = int(id)
        self.x = float(x)
        self.y = float(y)
    
    def get_id(self):
        return self.id
    
    def get_x(self):
        return self.x

    def get_y(self):
        return self.y
    
    def __str__(self):
        return "city:{}, x:{}, y:{}".format(self.id, self.x, self.y)
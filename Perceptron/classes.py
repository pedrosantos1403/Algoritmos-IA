class Matrix:
    def __init__(self, data=0) -> None:
        self.rows = 0
        self.columns = 0
        self.items = []
        if not data == 0:
            for row in data:
                self.columns = 0
                self.items.append([])
                for item in row:
                    self.items[self.rows].append(item)
                    self.columns += 1
                self.rows += 1
    
    def __str__(self) -> str:
        # output = str(self.rows)+' x '+str(self.columns)+'\n'
        output = ''
        for i in range(self.rows):
            output += '[\t'
            for j in range(self.columns):
                output += str(self.items[i][j])+'\t'
            output += ']\n'
        return output

    def insert_row(self, row:list) -> None:
        self.items.append([])
        self.columns = 0
        for item in row:
            self.items[self.rows].append(item)
            self.columns += 1
        self.rows += 1
    
    def get_item(self, r:int, c:int) -> float:
        return self.items[r][c]
    
    def get_size_rows(self) -> int:
        return self.rows

    def get_size_columns(self) -> int:
        return self.columns
    
    def get_row(self, r:int) -> list:
        row = []
        for c in range(self.columns):
            row.append(self.items[r][c])
        return row

    def set_row(self, r:int, L:list) -> None:
        for c in range(self.columns):
            self.items[r][c] = L[c]
    
    def get_column(self, c:int) -> list:
        column = []
        for r in range(self.rows):
            column.append(self.items[r][c])
        return column

    def set_column(self, c:int, K:list) -> None:
        for r in range(self.rows):
            self.items[r][c] = K[r]

    def set_item(self, r:int, c:int, value:float) -> None:
        self.items[r][c] = value

class Vector:
    def __init__(self, data=0) -> None:
        self.rows = 0
        self.items = []
        if not data == 0:
            for item in data:
                self.items.append(item)
                self.rows += 1
        
    def __str__(self) -> str:
        # output = str(self.rows)+'\n'
        output = ''
        for i in self.items:
            output += '[ '+str(i)+' ]\n'
        return output

    def insert_item(self, item:float):
        self.items.append(item)
        self.rows += 1
    
    def get_item(self, r:int) -> float:
        return self.items[r]

    def set_item(self, r:int, item:float) -> None:
        self.items[r] = item

    def get_size(self) -> int:
        return self.rows
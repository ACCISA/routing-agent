class Protocol:

    def __init__(self, bytes):
        self.bytes = bytes

    def is_destination(self):
        return int.from_bytes(self.bytes[0:1])

    def is_forward(self):
        return int.from_bytes(self.bytes[1:2])

    def has_response(self):
        return int.from_bytes(self.bytes[2:3])

    def instruction(self):
        return int.from_bytes(self.bytes[3:4])

    def num_sections(self):
        return int.from_bytes(self.bytes[4:8])

    def cur_section(self):
        return int.from_bytes(self.bytes[8:12])
    
    def response_len(self):
        return int.from_bytes(self.bytes[12:16])

    def msg_id(self):
        return int.from_bytes(self.bytes[16:20])

    def sections_len(self):
        sections_len = []
        idx = 0
        for i in range(0, self.num_sections()):
            sections_len.append(self.bytes[20+idx:20+idx+4])
        return sections_len




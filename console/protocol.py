class Protocol:

    def __init__(self, bytes):
        self.bytes = bytes

    def is_destination(self):
        return int.from_bytes(self.bytes[0:1], byteorder='little')

    def is_forward(self):
        return int.from_bytes(self.bytes[1:2], byteorder='little')

    def has_response(self):
        return int.from_bytes(self.bytes[2:3], byteorder='little')

    def instruction(self):
        return int.from_bytes(self.bytes[3:4], byteorder='little')

    def num_sections(self):
        return int.from_bytes(self.bytes[4:8], byteorder='little')

    def cur_section(self):
        return int.from_bytes(self.bytes[8:12], byteorder='little')
    
    def response_len(self):
        return int.from_bytes(self.bytes[12:16], byteorder='little')

    def msg_id(self):
        return int.from_bytes(self.bytes[16:20], byteorder='little')

    def sections_len(self):
        sections_len = []
        idx = 0
        for i in range(0, self.num_sections()):
            sections_len.append(self.bytes[20+idx:20+idx+4])
        return sections_len



forward_hostname = bytes([
    0x01, # is_destination
    0x01, # is_forward
    0x00, # has_response
    0x00, # instruction
    0x02, 0x00, 0x00, 0x00, # num_sections
    0x01, 0x00, 0x00, 0x00, # cur_section
    0x00, 0x00, 0x00, 0x00, # response_len
    0x00, 0x00, 0x00, 0x00, # msg_id
    0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, # sections_len
    0x3b, 
    0x41, 0x31, 0x2c, 0x41, 0x32, 0x2c, 0x41, 0x31, # A1,A2,A1
    #0x42, 0x34, 0x2c, 0x41, 0x33, 0x2c, 0x41, 0x33, # A2,A3,A3
])

proto = Protocol(forward_hostname)
print(proto.bytes)
print(proto.bytes[4:8])

print(proto.is_destination())
print(proto.num_sections())
print(proto.sections_len())
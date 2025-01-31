class VWLZSSA5:
    """Implements a custom LZSS variant with a 6-bit length and 10-bit displacement."""

    def __init__(self):
        self.window_size = 1023  # Max lookback size
        self.min_match_length = 3
        self.max_match_length = 63

    def compress(self, input_data: bytes) -> bytearray:
        input_length = len(input_data)
        output = bytearray()
        read_pos = 0
        bit_flag_pos = len(output)
        bit_flags = 0
        bit_count = 0
        output.append(0)  # Placeholder for bit flags

        while read_pos < input_length:
            match_length, match_offset = self.find_longest_match(input_data, read_pos)
            if match_length >= self.min_match_length:
                output.append((match_length << 2) | (match_offset >> 8))
                output.append(match_offset & 0xFF)
                read_pos += match_length
                bit_flags |= 1 << (7 - bit_count)
            else:
                output.append(input_data[read_pos])
                read_pos += 1
            bit_count += 1

            if bit_count == 8:
                output[bit_flag_pos] = bit_flags
                bit_flag_pos = len(output)
                output.append(0)
                bit_flags = 0
                bit_count = 0

        if bit_count > 0:
            output[bit_flag_pos] = bit_flags

        return output

    def decompress(self, input_data: bytes) -> bytearray:
        output = bytearray()
        it = iter(input_data)

        def readbyte():
            return next(it)

        def readshort():
            return (readbyte() << 8) | readbyte()

        try:
            while True:
                flags = readbyte()
                for i in range(8):
                    if flags & (1 << (7 - i)):
                        sh = readshort()
                        count = sh >> 10
                        disp = sh & 1023
                        for _ in range(count):
                            output.append(output[-disp])
                    else:
                        output.append(readbyte())
        except StopIteration:
            pass

        return output

    def find_longest_match(self, data: bytes, current_pos: int):
        max_offset = min(current_pos, self.window_size)
        best_length = 0
        best_offset = 0

        for offset in range(3, max_offset + 1):
            match_length = self.calculate_match_length(data, current_pos, current_pos - offset)
            if match_length > best_length:
                best_length = match_length
                best_offset = offset
                if best_length >= self.max_match_length:
                    break

        return best_length, best_offset

    def calculate_match_length(self, data, pos1, pos2):
        max_len = min(len(data) - pos1, self.max_match_length)
        length = 0
        while length < max_len and data[pos1 + length] == data[pos2 + length]:
            length += 1
        return length
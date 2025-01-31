#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 1023
#define MIN_MATCH_LENGTH 3
#define MAX_MATCH_LENGTH 63

// Function to get the bits of a byte
void bits(unsigned char byte, int *bitArray) {
    for (int i = 0; i < 8; i++) {
        bitArray[i] = (byte >> (7 - i)) & 1;
    }
}

// Function to find the longest match in the window
int find_longest_match(const unsigned char *data, int current_pos, int length, int *best_offset) {
    int max_offset = (current_pos < WINDOW_SIZE) ? current_pos : WINDOW_SIZE;
    int best_length = 0;
    *best_offset = 0;

    for (int offset = 3; offset <= max_offset; offset++) {
        int match_length = 0;
        while (match_length < MAX_MATCH_LENGTH && (current_pos + match_length) < length &&
               data[current_pos + match_length] == data[current_pos - offset + match_length]) {
            match_length++;
        }
        if (match_length > best_length) {
            best_length = match_length;
            *best_offset = offset;
            if (best_length >= MAX_MATCH_LENGTH) {
                break;
            }
        }
    }
    return best_length;
}

// LZSS Compression
unsigned char *lzss_compress(const unsigned char *input_data, int input_length, int *output_length) {
    unsigned char *output = (unsigned char *)malloc(input_length * 2);
    int read_pos = 0, write_pos = 0;
    unsigned char bit_flags = 0;
    int bit_count = 0, flag_pos = 0;
    output[write_pos++] = 0;
    flag_pos = 0;

    while (read_pos < input_length) {
        int match_offset, match_length = find_longest_match(input_data, read_pos, input_length, &match_offset);
        if (match_length >= MIN_MATCH_LENGTH) {
            output[write_pos++] = (match_length << 2) | (match_offset >> 8);
            output[write_pos++] = match_offset & 0xFF;
            read_pos += match_length;
            bit_flags |= (1 << (7 - bit_count));
        } else {
            output[write_pos++] = input_data[read_pos++];
        }
        bit_count++;
        if (bit_count == 8) {
            output[flag_pos] = bit_flags;
            flag_pos = write_pos++;
            bit_flags = 0;
            bit_count = 0;
        }
    }
    if (bit_count > 0) {
        output[flag_pos] = bit_flags;
    }
    *output_length = write_pos;
    return output;
}

// LZSS Decompression
unsigned char *lzss_decompress(const unsigned char *input_data, int input_length, int *output_length) {
    unsigned char *output = (unsigned char *)malloc(input_length * 2);
    int read_pos = 0, write_pos = 0;
    while (read_pos < input_length) {
        unsigned char flags = input_data[read_pos++];
        int bits_arr[8];
        bits(flags, bits_arr);
        for (int i = 0; i < 8 && read_pos < input_length; i++) {
            if (bits_arr[i] == 0) {
                output[write_pos++] = input_data[read_pos++];
            } else {
                int sh = input_data[read_pos++] << 8;
                sh |= input_data[read_pos++];
                int count = sh >> 10;
                int disp = sh & 1023;
                for (int j = 0; j < count; j++) {
                    output[write_pos] = output[write_pos - disp];
                    write_pos++;
                }
            }
        }
    }
    *output_length = write_pos;
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <compress|decompress> <input file> <output file>\n", argv[0]);
        return 1;
    }
    
    FILE *input_file = fopen(argv[2], "rb");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }
    
    fseek(input_file, 0, SEEK_END);
    int input_length = ftell(input_file);
    rewind(input_file);
    
    unsigned char *input_data = (unsigned char *)malloc(input_length);
    fread(input_data, 1, input_length, input_file);
    fclose(input_file);
    
    int output_length;
    unsigned char *output_data;
    
    if (strcmp(argv[1], "compress") == 0) {
        output_data = lzss_compress(input_data, input_length, &output_length);
    } else if (strcmp(argv[1], "decompress") == 0) {
        output_data = lzss_decompress(input_data, input_length, &output_length);
    } else {
        printf("Invalid option. Use 'compress' or 'decompress'.\n");
        return 1;
    }
    
    FILE *output_file = fopen(argv[3], "wb");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }
    fwrite(output_data, 1, output_length, output_file);
    fclose(output_file);
    
    free(input_data);
    free(output_data);
    
    printf("Operation completed successfully.\n");
    return 0;
}
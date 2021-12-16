# hashing-algorithms

The purpose of this project is to recreate md5 and sha256 hash algorithms


Usage: algorithm [-p -q -r] [-s string] [file...]
    algorithm       Algorithm to hash input (md5/sha256)
    file            files to digest
    -p              Process STDIN input
    -q              Quiet mode (output hash only)
    -r              Reverse mode (output source after the hash)
    -s              Process string

examples:
    ./ft_ssl md5 file.txt
    ./ft_ssl -s sha256 "hello world"
    echo "hello world" | ./ft_ssl md5
    echo "hello world" | ./ft_ssl sha256 -p file.txt
    echo "hello world" | ./ft_ssl md5 -p -s "hello world" file.txt

The program scans throught the forensic image in a .RAW file for jpeg signatures (assuming no slack space in the file), upon finding a jpeg signature, it creates a new file to restore the image.
The sample card.raw file has 50 lost images.

Usage: ./recover [input path]
eg: ./recover card.raw

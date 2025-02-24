#!/usr/bin/env python

import os
import re

def list_files(dir_path):
    file_list = [];

    for root, dirs, files in os.walk(dir_path):
        for f in files:
            path = os.path.join(root, f)
            path = os.path.normcase(path)
            if (f == "lx.mk" or f == "lxconfig"):
                file_list.append(path)
    return file_list

def insert_copyright(f, regex, copyright):
    fo = open(f, 'r+')
    string = fo.read()
    if not re.search(regex, string, re.M):
        fo.seek(0, 0)
        fo.write(copyright)
        fo.write(string)

    fo.close()

def main():
    regex = r'Copyright'

    fo = open("./copyright.mk", 'r')
    copyright = fo.read()
    fo.close()

    file_list = list_files("./")
    for f in file_list:
        print f
        insert_copyright(f, regex, copyright)

if __name__ == '__main__':
    main()


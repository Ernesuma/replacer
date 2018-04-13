#!/usr/bin/env python3

import csv
from pathlib import Path
import re


# parameters
# ----------
test_text_path = Path("./test_text.txt")
filler_csv_path = Path("./test_filler.csv")

text_set = set()
filler_dict = {"mail": "test@mail.de",
               "date": "04.04.2018"}
text_set.add('test')

re_replacee = re.compile(r"({\w+})")
# re_replacee = re.compile(r"[^{]({\w+})[^{]")


class Replacer():

    def __init__(self, text_path, filler_csv_path):
        self._text_file_path = text_path
        self._filler_dict = self._import_filler_dict(filler_csv_path)

    def get_filler_dict(self):
        return self._filler_dict

    def _import_filler_dict(self, csv_path):
        filler_dict = {}
        with csv_path.open(newline='', encoding='utf-8') as csv_file:

            # set up csv DictReader --> reads every row into a dict, csv headers are keys
            csv_2_dict_reader = csv.DictReader(csv_file, delimiter=',')

            # iterate over csv rows
            for row in csv_2_dict_reader:
                # check for double id definitions
                if row('id') not in filler_dict:
                    filler_dict[row('id')] = row('value')
                else:
                    print(f"WARNING: Double definition of id '{row['id']}' in '{csv_path}'")

        # debug print
        print(filler_dict)

        return filler_dict

    def filled_text_gen(self):
        with self._text_file_path.open() as text_file:
            for line in text_file:
                replacee = line
                match_objects = re_replacee.finditer(line)
                if match_objects:
                    for match in match_objects:
                        print(match)

                yield line

#   def fill(self):
#       self._filled_text = str(self._text)
#       fd = self.get_filler_dict()
#       # for filler_key in iter(self._filler):
#       for filler_key in self._filler.keys():
#           print("DEBUG: filler key: '{}'".format(filler_key))
#
#           self._filled_text = self._filled_text.replace('{{{}}}'.format(filler_key), fd[filler_key])
#           print("DEBUG: filled text: '{}'".format(self._filled_text))
#       return self._filled_text


if '__main__' == __name__:
    my_replacer = Replacer(test_text_path, filler_csv_path)
    print(my_replacer)

    counter = 0
    for line in my_replacer.filled_text_gen():
        print(counter)
        counter += 1
        print(line)
